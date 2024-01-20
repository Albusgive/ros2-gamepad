#include "gamepad.h"
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("gamepad_test_node");
    auto pub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", rclcpp::QoS(1));
    auto pub1 = node->create_publisher<geometry_msgs::msg::Twist>("/turtlesim1/turtle1/cmd_vel", rclcpp::QoS(1));
    auto pub2 = node->create_publisher<geometry_msgs::msg::Twist>("/turtlesim2/turtle1/cmd_vel", rclcpp::QoS(1));
    geometry_msgs::msg::Twist msg;
    GamePad pad;
    pad.showGamePads();
    if (pad.GamePadpads.empty())
    {
        RCLCPP_INFO(node->get_logger(), "No gamepads connected");
        return 0;
    }
    pad.bindGamePadValues([&](GamePadValues map)
                          { 
         msg.linear.x=(double)-map.ly/32767*5;         
         msg.linear.y=(double)-map.lx/32767*5;
         msg.linear.z=0;
         msg.angular.x=(double)map.rx/32767*5;         
         msg.angular.y=(double)map.ry/32767*5;
         msg.angular.z=(double)-map.rx/32767*5;
         });
    int is;
    std::string opid = pad.GamePadpads.begin()->first;
    if (pad.GamePadpads.size() > 1)
    {
        std::cout << "more than one gamepad" << std::endl;
        while (rclcpp::ok())
        {
            std::cout << "please input the gamepad id" << std::endl;
            std::cin >> opid;
            is = pad.openGamePad(opid);
            if (is >= 0)
            {
                break;
            }
        }
    }
    else
    {
        is = pad.openGamePad(opid);
        if (is < 0)
        {
            std::cout << "open gamepad fail" << std::endl;
            return 0;
        }
    }
    pad.readGamePad();
    rclcpp::Rate loop_rate(10); // 10Hz
    while (rclcpp::ok())
    {
        pub->publish(msg);
        pub1->publish(msg);
        pub2->publish(msg);
        loop_rate.sleep();
    }
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
