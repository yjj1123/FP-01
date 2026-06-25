# STM32 主控固件 / STM32 Controller Firmware

本目录是主控板 Keil 工程源码。
This directory contains the Keil project source code for the controller board.

## 工程信息 / Project Information

- 工程文件：`USER/MiniBalance.uvprojx`
  Project file: `USER/MiniBalance.uvprojx`
- 目标芯片：STM32F103C8
  Target chip: STM32F103C8
- 主要入口：`USER/MiniBalance.c`
  Main entry: `USER/MiniBalance.c`
- 核心控制：`MiniBalance/CONTROL/control.c`
  Core control logic: `MiniBalance/CONTROL/control.c`

## 主要模块 / Main Modules

- `MiniBalance/CONTROL/`：机械臂逆运动学、状态机、总线舵机指令。
  Robotic-arm inverse kinematics, state machine, and bus-servo commands.
- `MiniBalance_HARDWARE/Trailing/`：头尾巡线和底盘运动控制。
  Front and rear line tracking, plus chassis motion control.
- `MiniBalance_HARDWARE/MOTOR/`：TIM2 PWM 输出。
  TIM2 PWM output.
- `MiniBalance_HARDWARE/USART3/`：USART3 收发。
  USART3 transmit and receive.
- `SYSTEM/usart/`：主串口接收缓存和空闲中断。
  Main UART receive buffer and idle interrupt handling.
- `STM32F10x_FWLib/`：STM32F10x 标准外设库。
  STM32F10x Standard Peripheral Library.

## 编译 / Build

使用 Keil MDK-ARM 打开：
Open with Keil MDK-ARM:

```text
firmware/stm32/USER/MiniBalance.uvprojx
```

编译产物不会提交到 GitHub，已通过 `.gitignore` 排除。
Build outputs are excluded from GitHub by `.gitignore`.
