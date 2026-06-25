# 系统架构 / System Architecture

本项目采用“视觉识别端 + STM32 主控端 + 总线舵机机械臂 + 巡线底盘”的分层结构。
The project uses a layered architecture: vision module + STM32 controller + bus-servo robotic arm + line-following chassis.

## 1. 视觉识别端 / Vision Module

位置：`software/k210/`
Location: `software/k210/`

- 硬件：K210 / MaixPy 设备。
  Hardware: K210 / MaixPy device.
- 模型：`m.kmodel`。
  Model: `m.kmodel`.
- 主脚本：`boot.py`。
  Main script: `boot.py`.
- 功能：摄像头采集图像，YOLO2/KPU 推理，选取距离画面中心最近的目标框。
  Function: captures camera images, runs YOLO2/KPU inference, and selects the target box closest to the image center.
- 输出：将像素坐标转换为机械臂坐标，并通过 UART1 发送到主控。
  Output: converts pixel coordinates to robotic-arm coordinates and sends them to the controller through UART1.

另有 `software/openmv-color-demo/main.py`，这是基于颜色阈值的 OpenMV 调试脚本，可作为早期色块识别或硬件联调参考。
`software/openmv-color-demo/main.py` is an OpenMV color-threshold debugging script for early color-blob recognition or hardware bring-up.

## 2. STM32 主控端 / STM32 Controller

位置：`firmware/stm32/`
Location: `firmware/stm32/`

- 工程：`USER/MiniBalance.uvprojx`。
  Project file: `USER/MiniBalance.uvprojx`.
- 芯片：STM32F103C8。
  Chip: STM32F103C8.
- 编译环境：Keil MDK-ARM。
  Build environment: Keil MDK-ARM.
- 主要入口：`USER/MiniBalance.c`。
  Main entry: `USER/MiniBalance.c`.
- 核心控制：`MiniBalance/CONTROL/control.c`。
  Core control logic: `MiniBalance/CONTROL/control.c`.

主控初始化串口、PWM、巡线传感器和定时器。主要控制逻辑位于 TIM2 定时中断中，周期性处理串口数据、状态机、机械臂逆运动学和动作发送。
The controller initializes UART, PWM, line-tracking sensors, and timers. The main control logic runs in the TIM2 timer interrupt, where it periodically handles UART data, the state machine, robotic-arm inverse kinematics, and action commands.

## 3. 数据流 / Data Flow

```text
摄像头图像 / Camera image
  ↓
K210 / OpenMV 目标识别 / K210 / OpenMV target recognition
  ↓
像素坐标转换为机械臂坐标 / Pixel coordinates converted to robotic-arm coordinates
  ↓
UART: HEAD,x,y,z,type,TAIL
  ↓
STM32 解析坐标 / STM32 coordinate parsing
  ↓
逆运动学求解舵机位置 / Inverse kinematics calculates servo positions
  ↓
幻尔总线舵机执行抓取动作 / Hiwonder bus servos execute the picking action
```

## 4. 底盘与传感器 / Chassis and Sensors

位置：`firmware/stm32/MiniBalance_HARDWARE/Trailing/car.c`
Location: `firmware/stm32/MiniBalance_HARDWARE/Trailing/car.c`

- 头部巡线：PC13、PC14、PC15。
  Front line-tracking sensors: PC13, PC14, PC15.
- 尾部巡线：PA11、PB0、PA6。
  Rear line-tracking sensors: PA11, PB0, PA6.
- 电机 PWM：TIM2 CH1-CH4。
  Motor PWM: TIM2 CH1-CH4.
- 运动函数：`move()`、`turn()`、`car_stop()`。
  Motion functions: `move()`, `turn()`, `car_stop()`.

## 5. 机械臂 / Robotic Arm

位置：`firmware/stm32/MiniBalance/CONTROL/control.c`
Location: `firmware/stm32/MiniBalance/CONTROL/control.c`

- 逆运动学函数：`inserve_kinematics()`。
  Inverse kinematics function: `inserve_kinematics()`.
- 舵机动作发送：`Action_Singnal()`、`Action_Six_BUS()`、`Action_Group()`。
  Servo command functions: `Action_Singnal()`, `Action_Six_BUS()`, `Action_Group()`.
- 抓取状态机：TIM2 中断内的 `step` 分支。
  Picking state machine: the `step` branches inside the TIM2 interrupt.
- 夹爪控制：`Grasp` / `Unstuck` 宏定义在 `control.h`。
  Gripper control: `Grasp` / `Unstuck` macros are defined in `control.h`.
