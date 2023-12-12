# PX4 Example {#PX4Example}

[TOC]

# 1. Setup PX4

## 1.1. Install QGroundControl

  - Install QGroundControl from the [link](https://docs.qgroundcontrol.com/master/en/getting_started/download_and_install.html)

## 1.2. Install the PX4 Firmware

- **NOTE**: Should use specific version of PX4([1.12.3](https://github.com/PX4/PX4-Autopilot/releases/tag/v1.12.3))

- Install the firmware file from the link above which matches with your flight controller

- Open *QGroundControl*, click the **Q** Logo, **Vehicle Settings**

- Click **Firmware** and upload the downloaded firmware


![Select Firmware](px4/firmware_selection.png){width=100%}


- Setup the flight controller parameters

  `EKF2_AID_MASK` parameter to 24

  `EKF2_HGT_MODE` parameter to `Vision`

  `CP_DIST` parameter to `-1`

  `COM_OBS_AVOID` paramter to `0`

![Set AID MASK Parameter](px4/EKF2_AID_MASK.png){width=100%}

![Set Height Mode Parameter](px4/EKF2_HGT_MODE.png){width=100%}

# 2. Connect PX4 with UART

- To connect PX4 and companion board with uart, use usb-to-tts and connect it to `TEL1` on px4 board

![Connect Companion Board with PixHawk](companion_px4_connection.jpg){width=50%}

- Then set the port with *QGroundContol*

![Set Communication Port](px4/set_port.png){width=100%}

- Setting baud rate as same as the SLAMBOX configuration

- Check the [SLAMBOX setting](SLAMBOXSetting.html)

- **NOTE**: the *SLAMBOX's baud rate* and *PX4's baud rate* should be **SAME**

![Set Baud Rate](px4/set_baud_rate.png){width=100%}

# 3. Update SLAMBOX Setting

- Update SLAMBOX Mavlink setting with command below

- Check the details [here](SLAMBOXSetting.html#SLAMBOXSetting-ConfigureSLAMBOX-SLAMBOXMavlinkConfiguration)

```
# Enable Mavlink
$MAVLINK_ENABLE 1#

# Change baudrate
$MAVLINK_BAUD 921600#

# Set Mavlink type to px4
$MAVLINK_TYPE 0#
```
