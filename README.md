## 安装编译环境.
`cd ros2_gamepad`  
`sduo sh makepre.sh`  
## 回到工作空间.
`colcon build --packages-select ros2_gamepad`   
`source install/setup.bash` 
## 运行 测试代码
`ros2 run gamepad gamepad_test_node`     
打印如  
备名称：Sony Computer Entertainment Wireless Controller   
  ∟﹣﹣﹣设备路径：/dev/input/js0  
  ∟﹣﹣﹣详细信息：USB DEVICE: Sony Computer Entertainment| Wireless Controller   

first gamepad id is /dev/input/js0  
decode type: Sony  
Time:13042232 A:0 B:0 X:0 Y:0 LB:0 RB:0 start:0 menu:0 home:0 screenhot:0 LO:0 RO:0 XX:0      YY:0      LX:0      LY:0      RX:0      RY:0      LT:-32767 RT:-32767   
## 运行海龟控制
`ros2 run gamepad gamepad_test_node`        
`ros2 run turtlesim turtlesim_node` 或 `ros2 launch turtlesim multisim.launch.py`   
