# FlexXlam Setting {#FlexXlamSetting}

The `FlexXlam` configuration can be configured by *serial commands*

[TOC]

## Install Serial Communication Tools {#FlexXlamSettingsWithSerial-InstallSerialCommunicationTools}

<details open>
<summary> Unix OS </summary>

Working with Unix OS, use `minicom` to configure the **FlexXlam**

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

    Set the serial port and baudrate of your PC

    First, plug in the USB2TTL module

    ![USB2TTL to PC](flexxlam_setting/usb2ttl.JPG){width=50%}

    Then, using command below connect with **FlexXlam**

</details>

<details open>
<summary> Windows OS </summary>

1. Install ComPortMaster

    Working with Windows OS, use *ComPortMaster* to configure the **FlexXlam**

    Install the *ComPortMaster* from the [link](http://withrobot.com/data/?mod=document&uid=12)

    ![How to use ComPortMaster](flexxlam_setting/comportmaster.png)

</details>

## Configure FlexXlam {#FlexXlamSettingsWithSerial-ConfigureFlexXlam}

Using ascii command to change configuration of **FlexXlam**

- The commands must be start with `$` and ends with `#` which is header and ender of the command

- No matter using *upper case* or *lower case* it works

- Regardless of changing configuration of **FlexXlam**, the serial communication for settings operates

- The following commands below, type the commands in *minicom* or *ComPortMaster*

**NOTE** The **Baud rate** of serial connection for setting is fixed to **115200**

### FlexXlam Serial Configuration {#FlexXlamSettingsWithSerial-ConfigureFlexXlam-FlexXlamSerialConfiguration}

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

### FlexXlam Ethernet Configuration {#FlexXlamSettingsWithSerial-ConfigureFlexXlam-FlexXlamEthernetConfiguration}

- `ETH_ENABLE` with option `0` or `1`. `0` means to disable and `1` means enable this option

- `ETH_PORT` with option *port* to connect. ex) 8888

- `ETH_IP` with option *IP* of host. ex) 192.168.1.50

```
# Enable ethernet communication
$ETH_ENABLE 1#

# Change ethernet port number
$ETH_PORT 25180#

# Change ethernet IP address of FlexXlam
$ETH_IP 192.168.1.50#
```

### FlexXlam Mavlink Configuration {#FlexXlamSettingsWithSerial-ConfigureFlexXlam-FlexXlamMavlinkConfiguration}

- `MAVLINK_ENABLE` with option `0` or `1`. `0` means to disable and `1` means enable this option

- `MAVLINK_BAUD` with option *baudrate*.

**NOTE** Please check the *Avaiable baud rate* table

```
# Enable Mavlink
$MAVLINK_ENABLE 1#

# Set baudrate
$MAVLINK_BAUD 921600#
```

### FlexXlam Sensor Configuration {#FlexXlamSettingsWithSerial-ConfigureFlexXlam-FlexXlamSensorConfiguration}
- `LIDAR_TYPE` with option `0` to `5`

| option   | sensor |
|:---------------: | :---------------: |
|  0  |  Flexx2  |
|  1  |  mid360  |
|  2  |  ouster32  |
|  3  |  ouster64  |
|  4  |  ouster128  |
|  5  |  avia  |

### Save Configurations {#FlexXlamSettingsWithSerial-ConfigureFlexXlam-SaveConfigurations}

- Configurtaion can be saved by command `SAVE` or `START`

- The command `SAVE` just save the configuration

- The command `START` finish the configuration and start the *FlexXlam*

```
# save configuration
$SAVE#

# save and start FlexXlam
$START#
```
