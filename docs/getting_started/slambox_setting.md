# SLAMBOX Setting {#SLAMBOXSetting}

The `SLAMBOX` configuration can be configured via *serial communication with ascii texts*

[TOC]

## Install Serial Communication Tools {#SLAMBOXSettingsWithSerial-InstallSerialCommunicationTools}


<details open>
<summary> Unix OS </summary>

Working with Unix OS, use `minicom` to configure the **SLAMBOX**

1. Install minicom

    ```bash
    # For Ubuntu
    sudo apt install minicom

    # For Mac OS (Homebrew)
    brew install minicom
    ```

2. Add group to user

    Need to add user to group `dialout` for using the USB or serial port without `sudo` permission.

    Then reboot your pc to update the user group

    ```bash
    sudo usermod -a -G dialout ${USER}
    sudo reboot now
    ```

3. Set port and baudrate

    First, plug in the USB2TTL module

    ![USB2TTL to PC](getting_started/slambox_setting/usb2ttl.JPG){width=50%}

    Check device path.
    ```shell
    $ ls -lh /dev/ttyUSB*

    crw-rw---- 1 root dialout 188, 0 Dec 11 14:43 /dev/ttyUSB0
    ```

    Set the serial port and baudrate of your PC. In this tutorial, `${SERIAL_PORT}` is `/dev/ttyUSB0`

    ```bash
    minicom -D ${SERIAL_PORT} -b 115200
    ```

    Set Hardware Flow Control to `No`. It can be done by pressing `<Ctrl>+A o` -> Serial port setup -> Press `f`.

```
+------------------------------------------------+
| A -    Serial Device      : /dev/ttyUSB0       |
| B - Lockfile Location     : /var/lock          |
| C -   Callin Program      :                    |
| D -  Callout Program      :                    |
| E -    Bps/Par/Bits       : 115200 8N1         |
| F - Hardware Flow Control : No                 |
| G - Software Flow Control : No                 |
|                                                |
|    Change which setting?                       |
+------------------------------------------------+
```

For your convinience, turn Local echo on by pressing `<Ctrl>+A z e`

Then, start configuration as your needs by following [below section](#SLAMBOXSettingsWithSerial-ConfigureSLAMBOX).

</details>

<details open>
<summary> Windows OS </summary>

1. Install ComPortMaster

    Working with Windows OS, use *ComPortMaster* to configure the **SLAMBOX**

    Install the *ComPortMaster* from the [link](http://withrobot.com/data/?mod=document&uid=12)

    ![How to use ComPortMaster](getting_started/slambox_setting/comportmaster.png)

</details>

## Configure SLAMBOX {#SLAMBOXSettingsWithSerial-ConfigureSLAMBOX}

Using ascii command to change configuration of **SLAMBOX**

- The commands must be start with `$` and ends with `#` which is header and ender of the command

- No matter using *upper case* or *lower case* it works

- Regardless of changing configuration of **SLAMBOX**, the serial communication for settings operates

- The following commands below, type the commands in *minicom* or *ComPortMaster*

**NOTE** The **Baud rate** of serial connection for setting is fixed to **115200**

### SLAMBOX Serial Configuration {#SLAMBOXSettingsWithSerial-ConfigureSLAMBOX-SLAMBOXSerialConfiguration}

- `SERIAL_ENABLE` with option `0` or `1`. `0` means to disable and `1` means enable this option

- `SERIAL_BAUD` with option *baudrate*.

- Please check the available baud rate table below

**NOTE**: The *maximum* and *minimum* baud rate could be different depands on your USB2TTL device.

|Available baud rate|
|:---:|
|9600|
|19200|
|57600|
|115200|
|230400|
|921600|
|1000000|
|1152000|
|1500000|
|2000000|
|2500000|
|3000000|
|3500000|
|4000000|

```bash
# Enable serial
# Want to disable serial, then change 1 to 0
$SERIAL_ENABLE 1#

# Set baudrate of serial
$SERIAL_BAUD 921600#
```

### SLAMBOX Ethernet Configuration {#SLAMBOXSettingsWithSerial-ConfigureSLAMBOX-SLAMBOXEthernetConfiguration}

- `ETH_ENABLE` with option `0` or `1`. `0` means to disable and `1` means enable this option

- `ETH_PORT` with option *port* to connect. ex) 8888

- `ETH_IP` with option *IP* of host. ex) 192.168.1.50

```
# Enable ethernet communication
$ETH_ENABLE 1#

# Change ethernet port number
$ETH_PORT 25180#

# Change ethernet IP address of SLAMBOX
$ETH_IP 192.168.1.50#
```

### SLAMBOX Mavlink Configuration {#SLAMBOXSettingsWithSerial-ConfigureSLAMBOX-SLAMBOXMavlinkConfiguration}

- `MAVLINK_ENABLE` with option `0` or `1`. `0` means to disable and `1` means enable this option

- `MAVLINK_BAUD` with option *baudrate*.

- `MAVLINK_TYPE` with options `0` to `1`

| option   | type |
|:---------------: | :---------------: |
| 0  | px4   |
| 1  | ardupilot (apm)   |


**NOTE** Please check the *Avaiable baud rate* table

```
# Enable Mavlink
$MAVLINK_ENABLE 1#

# Set baudrate
$MAVLINK_BAUD 921600#

# Set Mavlink mode for PX4
$MAVLINK_TYPE 0#
```

### SLAMBOX Sensor Configuration {#SLAMBOXSettingsWithSerial-ConfigureSLAMBOX-SLAMBOXSensorConfiguration}
- `LIDAR_TYPE` with option `0` to `5`

|  option  | sensor |
|:--------:|:-------:| 
|  1  |  mid360  |
|  2  |  ouster32  |
|  3  |  ouster64  |
|  4  |  ouster128  |
|  5  |  avia  |

```
# Set MID-360 LiDAR
$LIDAR_TYPE 1#
```

### Save Configurations {#SLAMBOXSettingsWithSerial-ConfigureSLAMBOX-SaveConfigurations}

- Configurtaion can be saved by command `SAVE` or `START`

- The command `SAVE` just save the configuration

- The command `START` finish the configuration and start the *SLAMBOX*

```
# save configuration
$SAVE#

# save and start SLAMBOX
$START#
```
