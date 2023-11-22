# Ardupilot Example {#ArdupilotExample}

[TOC]


# 1. Setup environment

## 1.1. Setup Ardupilot

- **NOTE**: For Ardupilot, recommend to use *Mission planner* with **Windows**

- The *QGroundControl* also can be used but not recommended

### 1.1.1. Install Mission Planner

- Install Ardupilot *Mission Planner* from the [link](https://ardupilot.org/planner/docs/mission-planner-installation.html)

### 1.1.2. Install the Ardupilot Firmware

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

### 1.1.3. Connect RC and calibrate the Remote Controller

- Connect RC controller receiver to FC

![RC receiver with Pixhawk](ardupilot/rc_connection.jpeg){width=30%}

- Calibrate RC with Ardupilot *Mission Planner*

![RC Calibration with Mission Planner](ardupilot/mp_radio_calibration.png){width=50%}



## 1.2. Connect Ardupilot with UART
- To connect Ardupilot and companion board with uart, use usb-to-tts and connect it to `TEL1` on px4 board

![Companion Board and Pixhawk Connection](companion_px4_connection.jpg){width=30%}

- Then set the port with *QGroundContol*

- Setting baud rate as same as the FlexXlam configuration
- See how to configure FlexXlam ([link](https://github.com/j-marple-dev/FlexXlam_driver#122-server-configuration))
- **NOTE**: the *FlexXlam's baud rate* and *Ardupilot's baud rate* should be **SAME**

<!-- ![Set Serial Baud Rate and Serial Protocol](ardupilot/set_serial1.png){width=50%} -->

- To get data from *Ardupilot* FC, need to set the parameters of *Ardupilot* to send data

- Note that the SR1 means the telem1 port of FC

![Set Parameters to get data from Ardupilot](ardupilot/SR_set_hz.png){width=50%}

# 2. Using MavROS
- If you are using our docker, You do not need to follow this part

## 2.1. Install MavROS binary

```bash
# Install mavros ros packages
sudo apt-get install ros-${ROS_DISTRO}-mavros ros-${ROS_DISTRO}-mavros-extras ros-${ROS_DISTRO}-mavros-msgs

# Install GeographicLib
wget https://raw.githubusercontent.com/mavlink/mavros/master/mavros/scripts/install_geographiclib_datasets.sh
sudo bash ./install_geographiclib_datasets.sh   
```
