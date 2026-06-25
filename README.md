# 农智中枢 / FP Strawberry 01

面向草莓种植场景的视觉识别采摘机器人项目。
An intelligent strawberry harvesting robot project for strawberry planting scenarios, based on visual recognition.

仓库仅保留与系统实现、嵌入式控制、视觉识别、通信协议和舵机动作相关的技术资料。
This repository keeps only technical materials related to system implementation, embedded control, visual recognition, communication protocol, and servo actions.

## 技术组成 / Technical Components

- 视觉识别：K210 / MaixPy 运行目标检测模型，识别草莓并输出目标坐标。
  Vision recognition: K210 / MaixPy runs an object detection model to detect strawberries and output target coordinates.
- 坐标通信：视觉端通过串口发送 `HEAD,x,y,z,type,TAIL` 数据给 STM32 主控。
  Coordinate communication: the vision module sends `HEAD,x,y,z,type,TAIL` data to the STM32 controller through UART.
- 主控固件：STM32F103C8 / Keil MDK 工程负责串口解析、状态机、巡线底盘、舵机和机械臂动作控制。
  Controller firmware: the STM32F103C8 / Keil MDK project handles UART parsing, state control, line-following chassis control, servo control, and robotic arm actions.
- 机械臂控制：根据目标坐标执行逆运动学求解，并向幻尔总线舵机发送单舵机或动作组指令。
  Robotic arm control: inverse kinematics is calculated from target coordinates, then single-servo or action-group commands are sent to the Hiwonder bus servos.
- 底盘运动：头尾三路巡线传感器配合 TIM2 PWM 驱动完成前进、后退和转向。
  Chassis motion: front and rear three-channel line-tracking sensors work with TIM2 PWM motor control for forward, backward, and turning movements.
- 路径规划：技术文档记录 DFS + Dijkstra 的混合搜索思路，用于节点遍历和局部最短路径优化。
  Path planning: the technical notes describe a hybrid DFS + Dijkstra search strategy for node traversal and local shortest-path optimization.

## 仓库结构 / Repository Structure

```text
.
├── actions/
│   └── bus-servo/              # 幻尔总线舵机动作组 / Hiwonder bus-servo action groups
├── docs/
│   ├── architecture.md         # 系统架构说明 / System architecture
│   └── uart-protocol.md        # 视觉端与主控串口协议 / UART protocol between vision module and controller
├── firmware/
│   └── stm32/                  # STM32F103C8 Keil 工程源码 / STM32F103C8 Keil project source code
└── software/
    ├── k210/                   # K210 / MaixPy 目标检测脚本与模型 / K210 / MaixPy detection scripts and model
    └── openmv-color-demo/      # OpenMV 色块识别调试脚本 / OpenMV color-blob recognition demo
```

## 快速开始 / Quick Start

### K210 视觉识别 / K210 Vision Recognition

1. 将 `software/k210/boot.py`、`software/k210/m.kmodel`、`software/k210/labels.txt` 放入 MaixPy 设备 SD 卡根目录。
   Copy `software/k210/boot.py`, `software/k210/m.kmodel`, and `software/k210/labels.txt` to the root directory of the MaixPy device SD card.
2. 设备上电后运行 `boot.py`。
   Run `boot.py` after powering on the device.
3. 识别到目标后，脚本会通过 UART1 以 9600 波特率发送目标坐标。
   After detecting a target, the script sends target coordinates through UART1 at 9600 baud.

### STM32 主控 / STM32 Controller

1. 用 Keil MDK-ARM 打开 `firmware/stm32/USER/MiniBalance.uvprojx`。
   Open `firmware/stm32/USER/MiniBalance.uvprojx` with Keil MDK-ARM.
2. 目标芯片为 `STM32F103C8`。
   The target chip is `STM32F103C8`.
3. 编译后烧录到主控板。
   Build the project and flash it to the controller board.
4. 主控通过串口接收视觉端数据，并驱动底盘、舵机和机械臂动作。
   The controller receives vision data through UART and drives the chassis, servos, and robotic arm.

## 技术文档 / Technical Documentation

- [系统架构 / System Architecture](docs/architecture.md)
- [串口通信协议 / UART Communication Protocol](docs/uart-protocol.md)
- [K210 视觉识别说明 / K210 Vision Module Guide](software/k210/README.md)
- [STM32 主控固件说明 / STM32 Controller Firmware Guide](firmware/stm32/README.md)
- [总线舵机动作组说明 / Bus-Servo Action Group Guide](actions/bus-servo/README.md)
