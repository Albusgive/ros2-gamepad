#include "gamepad.h"
#include "rclcpp/rclcpp.hpp"
int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("gamepad_test_node");
    GamePad pad;
    pad.xboxpads();
    if (pad.GamePadpads.empty())
    {
        RCLCPP_INFO(node->get_logger(), "No gamepads connected");
        return 0;
    }
    pad.bindGamePadValues([=](GamePadValues map)
                          { printf("\rTime:%8d A:%d B:%d X:%d Y:%d LB:%d RB:%d start:%d menu:%d home:%d screenhot:%d LO:%d RO:%d XX:%-6d YY:%-6d LX:%-6d LY:%-6d RX:%-6d RY:%-6d LT:%-6d RT:%-6d \n",
                                   map.time, map.a, map.b, map.x, map.y, map.lb, map.rb, map.start, map.menu, map.home, map.screenhot, map.lo, map.ro,
                                   map.xx, map.yy, map.lx, map.ly, map.rx, map.ry, map.lt, map.rt); });
    int is;
    std::string opid = pad.GamePadpads.begin()->first;
    std::cout << "first gamepad id is " << opid << std::endl;
    if (pad.GamePadpads.size() > 1)
    {
        std::cout << "more than one gamepad" << std::endl;
        while (rclcpp::ok())
        {
            std::cout << "please input the gamepad id" << std::endl;
            std::cin >> opid;
            is = pad.openGamePad(opid);
            if (is>=0)
            {
                break;
            }
        }
    }
    else
    {
        is = pad.openGamePad(opid);
        if (is<0)
        {
            std::cout << "open gamepad fail" << std::endl;
            return 0;
        }
    }
    pad.readGamePad();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
