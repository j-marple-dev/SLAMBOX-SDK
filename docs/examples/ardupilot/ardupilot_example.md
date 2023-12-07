# Ardupilot Example {#ArdupilotExample}

[TOC]

# 1. Setup Ardupilot

- **NOTE**: For Ardupilot, recommend to use *Mission planner* with **Windows**

- The *QGroundControl* also can be used but not recommended

## 1.1. Install Mission Planner

- Install Ardupilot *Mission Planner* from the [link](https://ardupilot.org/planner/docs/mission-planner-installation.html)

## 1.2. Install the Ardupilot Firmware

- Install *Ardupilot OS* with matching version of your flight controller

- Open *QGroundControl*, click the **Q** Logo, **Vehicle Settings**

<!-- ![](images/vehicle_settings.png) -->

- Click **Firmware** and upload the downloaded firmware

- Setup the flight controller parameters

  `AHRS_EKF_TYPE` parameter to `2` or `Enable EKF2`

  `EK2_ENABLE` parameter to `1` or `Enable`

  `EK3_ENABLE` parameter to `0` or `Disable`

  `GPS_TYPE` parameter to `0` or `None`

  `EK2_GPS_TYPE` parameter to `3` or `No gps`

  `EK2_POSNE_M_NSE` parameter to 0.1

  `EK2_VELD_M_NSE` parameter to 0.1

  `EK2_VelNE_M_NSE` parameter to 0.1

  `COMPASS_ENABLE`, `COMPASS_USE`, `COMPASS_USE2`, `COMPASS_USE3` parameters to 0

  `VISO_TYPE` parameter to 2

<!-- ![ekf2 aid mask](EKF2_AID_MASK.png){width=50%} -->
<!-- ![ekf2 height mode](EKF3_HGT_MODE.png){width=50%} -->

## 1.3. Connect RC and calibrate the Remote Controller

- Connect RC controller receiver to FC

![RC receiver with Pixhawk](ardupilot/rc_connection.jpeg){width=50%}

- Calibrate RC with Ardupilot *Mission Planner*

![RC Calibration with Mission Planner](ardupilot/mp_radio_calibration.png){width=100%}



# 2. Connect Ardupilot with UART
- To connect Ardupilot and companion board with uart, use usb-to-tts and connect it to `TEL1` on px4 board

![Companion Board and Pixhawk Connection](companion_px4_connection.jpg){width=50%}

- Then set the port with *QGroundContol*

- Setting baud rate as same as the SLAMBOX configuration

- See how to configure SLAMBOX ([link](SLAMBOXSetting.html))

- **NOTE**: the *SLAMBOX's baud rate* and *Ardupilot's baud rate* should be **SAME**

<!-- ![Set Serial Baud Rate and Serial Protocol](ardupilot/set_serial1.png){width=50%} -->

- To get data from *Ardupilot* FC, need to set the parameters of *Ardupilot* to send data

- Note that the SR1 means the telem1 port of FC

![Set Parameters to get data from Ardupilot](ardupilot/SR_set_hz.png){width=100%}

# 3. Update SLAM BOX Setting

- Update SLAMBOX Mavlink setting with command below

- Check the details [here](SLAMBOXSetting.html#SLAMBOXSettingsWithSerial-ConfigureSLAMBOX-SLAMBOXMavlinkConfiguration)

```
# Enable Mavlink
$MAVLINK_ENABLE 1#

# Change baudrate
$MAVLINK_BAUD 921600#

# Set Mavlink type to px4
$MAVLINK_TYPE 1#
```
