# 串口通信协议 / UART Communication Protocol

视觉识别端识别到目标后，通过串口向 STM32 主控发送 ASCII 文本协议。
After the vision module detects a target, it sends an ASCII text protocol frame to the STM32 controller through UART.

## 参数 / Parameters

- 波特率：9600
  Baud rate: 9600
- 数据位：8
  Data bits: 8
- 停止位：1
  Stop bits: 1
- 校验：无
  Parity: none

## 帧格式 / Frame Format

```text
HEAD,<x>,<y>,<z>,<type>,TAIL
```

示例：
Example:

```text
HEAD,0.123000,0.045000,-0.160000,4,TAIL
```

## 字段含义 / Field Definitions

- `x`：目标在机械臂坐标系中的 X 坐标，单位为米。
  `x`: X coordinate of the target in the robotic-arm coordinate system, in meters.
- `y`：目标在机械臂坐标系中的 Y 坐标，单位为米。
  `y`: Y coordinate of the target in the robotic-arm coordinate system, in meters.
- `z`：目标在机械臂坐标系中的 Z 坐标，单位为米。
  `z`: Z coordinate of the target in the robotic-arm coordinate system, in meters.
- `type`：目标类型编号。草莓抓取脚本中通常固定发送 `4`。
  `type`: target type ID. The strawberry picking script usually sends a fixed value of `4`.

## 主控解析位置 / Controller Parsing Location

STM32 端在 `firmware/stm32/MiniBalance/CONTROL/control.c` 中检查串口缓存：
The STM32 side checks the UART receive buffer in `firmware/stm32/MiniBalance/CONTROL/control.c`:

- `CRStrLib_isValidData(RXBuff, "HEAD", "TAIL")`
- `CRStrLib_findNextFloat(...)`
- `CRStrLib_findNextInt(...)`

解析成功后设置 `start_flag=1`，进入抓取状态机。
After parsing succeeds, `start_flag=1` is set and the picking state machine starts.
