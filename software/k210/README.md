# K210 视觉识别模块 / K210 Vision Recognition Module

本目录包含 MaixPy / K210 端运行文件。
This directory contains runtime files for the MaixPy / K210 vision module.

## 文件 / Files

- `boot.py`：目标检测主程序，加载 `m.kmodel` 并发送目标坐标。
  `boot.py`: main object-detection program. It loads `m.kmodel` and sends target coordinates.
- `main.py`：MaixPy 默认启动/测试脚本。
  `main.py`: default MaixPy startup or test script.
- `m.kmodel`：MaixHub 训练得到的模型文件。
  `m.kmodel`: model file trained with MaixHub.
- `labels.txt`：训练标签文件。
  `labels.txt`: training label file.
- `MAIXHUB_README.txt`：MaixHub 导出的原始使用说明，已整理为中英双语。
  `MAIXHUB_README.txt`: original MaixHub usage guide, reorganized as a bilingual Chinese-English note.

## 串口 / UART

`boot.py` 使用 UART1：
`boot.py` uses UART1:

```python
fm.register(9, fm.fpioa.UART1_TX, force=True)
fm.register(10, fm.fpioa.UART1_RX, force=True)
uart = UART(UART.UART1, 9600, read_buf_len=4096)
```

检测到目标后发送：
After detecting a target, it sends:

```text
HEAD,x,y,z,type,TAIL
```

## 注意 / Notes

当前 `boot.py` 内部固定使用 `labels = ['strawberry']`，而 `labels.txt` 是 MaixHub 导出的多分类标签。
The current `boot.py` uses a fixed internal label list, `labels = ['strawberry']`, while `labels.txt` is the multi-class label file exported from MaixHub.

若重新训练模型，需要同步检查脚本标签和模型输出类别是否一致。
If the model is retrained, check that the script labels match the model output classes.
