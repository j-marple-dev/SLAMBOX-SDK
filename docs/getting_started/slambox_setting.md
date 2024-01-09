# SLAMBOX Setting {#SLAMBOXSetting}

The `SLAMBOX` configuration can be configured via *serial communication with ascii texts*

[TOC]

## Install Serial Communication Tools {#SLAMBOXSetting-InstallSerialCommunicationTools}

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

    Set Hardware Flow Control to `No`. It can be done by pressing `<Ctrl>+a` -> `o` -> Serial port setup -> Press `f`.

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
    
Once you set `Hardware Flow Control` to NO, presse `<Enter>` -> `<ESC>` to escape setting menu.

For your convinience, turn Local echo on by pressing `<Ctrl>+a` -> `z` -> `e`. Minicom does not show you what you type if Local echo is off.

Then, start configuration as your needs by following [below section](#SLAMBOXSetting-ConfigureSLAMBOX).

**NOTE** Once you have finished setup process, minicom must be exited in order to continue on next step.

Minicom can be exited by pressing `<Ctrl>+a` -> `x` -> `<Enter>`

</details>

<details open>
<summary> Windows OS </summary>

1. Install ComPortMaster

    Working with Windows OS, use *ComPortMaster* to configure the **SLAMBOX**

    Install the *ComPortMaster* from the [link](http://withrobot.com/data/?mod=document&uid=12)

2. Connect to SLAMBOX serial

    Please follow settings as below screenshot. `Device` name might be different depending on your OS condition.

![How to use ComPortMaster](getting_started/slambox_setting/comportmaster.png)

If you successfully open port, start configuration as your needs by following [below section](#SLAMBOXSetting-ConfigureSLAMBOX).


**NOTE** Once you have finished setup process, you must disconnect connection on ComPortMaster to continue on next step.
</details>

## Configure SLAMBOX {#SLAMBOXSetting-ConfigureSLAMBOX}

Use ascii command to change configuration of **SLAMBOX**

- The commands must be start with `$` and ends with `#` which is header and ender of the command
    - example) If you want to check current configuration status, send `$CONFIG#`

- The commands are case insensitive. You can use either *upper case* or *lower case*.

- The following commands below, type the commands in *minicom* or *ComPortMaster*

**NOTE** The **Baudrate** of serial connection for setting is fixed to **115200**

### Check current configuration status on SLAMBOX

You can see current cofiguration status on SLAMBOX by following command.

```
$CONFIG#
```

- Example:
    ```
$CONFIG#
[MAVLINK]
 [enabled] false
 [baudrate] 921600
 [type] px4
[Serial]
 [enabled] true
 [baudrate] 921600
[Ethernet]
 [enabled] false
 [port] 21580
 [IP] 192.168.101.101
[Sensor]
 [type] avia
    ```



### SLAMBOX Serial Configuration {#SLAMBOXSetting-ConfigureSLAMBOX-SLAMBOXSerialConfiguration}

- `SERIAL_ENABLE` with option `0` or `1`. `0` means to disable and `1` means enable this option

- `SERIAL_BAUD` with option *baudrate*.

- Please check the available baud rate table below

**NOTE**: The *maximum* and *minimum* baud rate could be different depands on your USB2TTL device.
**NOTE** Regardless of whether you disable serial communication, this configuration mode will always work with baudrate 115200.

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

**Example)** Enable serial communication
```
$SERIAL_ENABLE 1#
```

**Example)** Set baudrate of serial communication to 921600
```
$SERIAL_BAUD 921600#
```

**NOTE** If you set both `Serial` and `UDP` communication enabled, pointcloud will only be sent via `UDP` communication.


### SLAMBOX Ethernet Configuration {#SLAMBOXSetting-ConfigureSLAMBOX-SLAMBOXEthernetConfiguration}

- `ETH_ENABLE` with option `0` or `1`. `0` means to disable and `1` means enable this option

- `ETH_PORT` with option *port* to connect. ex) 8888

- `ETH_IP` with option *IP* of host. ex) 192.168.1.50

**Example)** Enable ethernet communication
```
$ETH_ENABLE 1#
```

**Example)** Set ethernet communication port to 21580
```
$ETH_PORT 21580#
```

**NOTE** If you set both `Serial` and `UDP` communication enabled, pointcloud will only be sent via `UDP` communication.

### SLAMBOX Mavlink Configuration {#SLAMBOXSetting-ConfigureSLAMBOX-SLAMBOXMavlinkConfiguration}

- `MAVLINK_ENABLE` with option `0` or `1`. `0` means to disable and `1` means enable this option

- `MAVLINK_BAUD` with option *baudrate*.

- `MAVLINK_TYPE` with options `0` to `1`

| option   | type |
|:---------------: | :---------------: |
| 0  | px4   |
| 1  | ardupilot (apm)   |


**NOTE** Please check the *Avaiable baud rate* table

**Example)** Enable Mavlink communication
```
$MAVLINK_ENABLE 1#
```

**Example)** Set baudrate of Mavlink communication
```
$MAVLINK_BAUD 921600#
```

**Example)** Set Mavlink type for PX4
```
$MAVLINK_TYPE 0#
```

### SLAMBOX Sensor Configuration {#SLAMBOXSetting-ConfigureSLAMBOX-SLAMBOXSensorConfiguration}
- `LIDAR_TYPE` with option `0` to `5`

|  option  | sensor |
|:--------:|:-------:| 
|  1  |  mid360  |
|  2  |  ouster32  |
|  3  |  ouster64  |
|  4  |  ouster128  |
|  5  |  avia  |
|  7  |  velodyne_puck  |

**Example)** Set LiDAR type to `mid360`
```
$LIDAR_TYPE 1#
```

**NOTE** Once you have changed `LIDAR_TYPE`, restarting SLAMBOX device is required to take an effect.

**NOTE** If you are done with setting SLAMBOX, you must exit serial communication application.
