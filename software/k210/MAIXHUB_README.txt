------------------------------------------

MaixHub 目标检测训练结果使用说明 / MaixHub Object Detection Training Result Guide

------------------------------------------

文件说明 / File Description:

* boot.py: 在 MaixPy 上运行的代码 / Code that runs on MaixPy.
* *.kmodel 或 *.smodel: 训练好的模型文件，smodel 是加密模型 / Trained model file. `smodel` is an encrypted model.
* labels.txt: 分类标签 / Class labels.
* startup.jpg: 启动图标 / Startup icon.
* report.jpg: 训练报告，包括损失和准确度报告等 / Training report, including loss and accuracy reports.
* warning.txt: 训练警告信息，如果存在该文件请务必阅读 / Training warning information. Read this file carefully if it exists.

使用方法 / Usage:

0. 按照文档 `maixpy.sipeed.com` 更新到最新固件。
   Follow the documentation at `maixpy.sipeed.com` to update to the latest firmware.
   如果新固件存在问题，可使用以下固件测试，选择 `minimum_with_ide_support.bin`。
   If the latest firmware has issues, test with the following firmware and choose `minimum_with_ide_support.bin`.
   https://api.dl.sipeed.com/shareURL/MAIX/MaixPy/release/master/maixpy_v0.6.0_2_g9720594
1. 准备一张 SD 卡，将本目录下的文件复制到 SD 卡根目录。
   Prepare an SD card and copy the files in this directory to the root of the SD card.
2. 将 SD 卡插入开发板。
   Insert the SD card into the development board.
3. 给开发板上电启动。
   Power on the development board.
4. 将摄像头对准训练目标。
   Aim the camera at the trained target object.
   屏幕左上角会显示物体标签和概率。
   The top-left corner of the screen shows the object label and probability.
   屏幕左下角会显示模型运行耗时，单位为毫秒。
   The bottom-left corner shows the model runtime in milliseconds.

如果没有 SD 卡 / If No SD Card Is Available:

* 按照 `maixpy.sipeed.com` 文档，将模型烧录到 flash。
  Burn the model to flash according to the `maixpy.sipeed.com` documentation.
* 修改 `boot.py` 中 `main` 函数调用参数，将 `model` 设置为模型在 flash 中的地址。
  Modify the `main` call in `boot.py` and set `model` to the model address in flash.
* 其他资源文件，例如 `startup.jpg`，可以通过工具发送到开发板文件系统；如果省略，程序会自动跳过显示。
  Other resource files, such as `startup.jpg`, can be sent to the development-board file system. If omitted, the program automatically skips their display.
* 运行 `boot.py`。
  Run `boot.py`.
* 如果不理解以上步骤，建议先完整阅读并实践 `maixpy.sipeed.com` 文档。
  If the steps above are unclear, read and follow the `maixpy.sipeed.com` documentation first.

问题反馈 / Feedback:

* MaixPy 问题请到 GitHub Issues 提问，提问前请先搜索是否已有相同问题。
  For MaixPy questions, open an issue on GitHub. Search existing issues before asking.
  https://github.com/sipeed/MaixPy/issues
* MaixHub 相关问题请邮件联系 `support@sipeed.com`。
  For MaixHub-related questions, contact `support@sipeed.com`.
* 邮件标题建议格式：`[maixhub][故障/建议] 简洁的问题标题`。
  Recommended email subject format: `[maixhub][Troubleshooting/Suggestion] concise issue title`.
* 邮件内容应包含错误现象和详细复现过程。
  The email body should include the observed error and detailed reproduction steps.
* 也可以到 `bbs.sipeed.com` 进行讨论。
  Discussion is also available at `bbs.sipeed.com`.
