# Tutorial {#Tutorial}

This tutorial guides you on how to setup SLAMBOX and your environment. [Chapter 1. Communication Setting](#Tutorial-CommunicationSetting) shows how to make communication available between SLAMBOX and your robot or PC.

[TOC]

# 1. Communication Setting {#Tutorial-CommunicationSetting}

- To communicate with *SLAMBOX*, you need to setup the serial communication or ethernet communication of your **host PC**

## 1.1. Serial {#Tutorial-CommunicationSetting-Serial}

- To get data from SLAMBOX through serial, check your **host PC's** serial communication port

```bash
# check which serial port is online
ls -al /dev/ttyUSB*
```

If you connect the TTL2USB module properly, then the result shows like this

```
crw-rw---- 1 root dialout 188, 0 Dec 11 10:46 /dev/ttyUSB0
```

The result means the serial communication port is `/dev/ttyUSB0`

If your host PC account do not have a permission to `dialout` group, add the account to the group `dialout`

```bash
# add $USER to group dialout
sudo usermod -a -G dialout $USER

# activate the changes of group
newgrp dialout
```

## 1.2. OTG {#Tutorial-CommunicationSetting-OTG}

Once you plug in OTG cable into your host computer, the IP address is automatically assigned via DHCP server built in SLAMBOX. Please check if the IP address has been acquired. If IP address is assigned, the host computer is ready to communicate via OTG cable.

## 1.3. Ethernet {#Tutorial-CommunicationSetting-Ethernet}

Some LiDARs, such as Unitree L1, requires to connect with USB. The OTG cable of the SLAMBOX will be disabled if you use such LiDARs. In that case, you can connect SLAMBOX via serial or ethernet communication.

To get data from *SLAMBOX* through etherent, set your host computer IP as below. You set this up either via [CLI](#Tutorial-CommunicationSetting-Ethernet-SetStaticIPwithTerminal) or [GUI](#Tutorial-CommunicationSetting-Ethernet-SetStaticIPwithUbuntuGUI).

### 1.2.1. Set Static IP with CLI {#Tutorial-CommunicationSetting-Ethernet-SetStaticIPwithTerminal}

To set static ip to your host PC, please follow the commands below

**NOTE**: The default IP address of *SLAMBOX* is `192.168.101.101`. You need to avoid using this IP address.

```bash
# check the ethernet device
ifconfig

# result will show the ethernet port which connected with SLAMBOX
enx5ad1753eff84: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet6 fe80::b045:854e:fa2e:21b3  prefixlen 64  scopeid 0x20<link>
        ether xx:xx:xx:xx:xx:xx txqueuelen 1000  (Ethernet)
        RX packets 24  bytes 3121 (3.1 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 42  bytes 7403 (7.4 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

Then set the device's IP.

In this example, we set the static IP to `192.168.101.5`

```bash
# set device's IP
sudo ifconfig enx5ad1753eff84 down
sudo ip addr add 192.168.101.5/24 dev enx5ad1753eff84
sudo ifconfig enx5ad1753eff84 up

# check the IP is set properly
ifconfig

enx5ad1753eff84: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.101.5 netmask 255.255.255.0 broadcast 0.0.0.0
        inet6 fe80::b045:854e:fa2e:21b3  prefixlen 64  scopeid 0x20<link>
        ether xx:xx:xx:xx:xx:xx txqueuelen 1000  (Ethernet)
        RX packets 24  bytes 3121 (3.1 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 42  bytes 7403 (7.4 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

### 1.2.2. Set Static IP with Ubuntu GUI {#Tutorial-CommunicationSetting-Ethernet-SetStaticIPwithUbuntuGUI}

This part demonstrates how to set static ip to your host PC with ubuntu GUI.

![Check the SLAMBOX connection](imgs/getting_started/communication_setup/ubuntu_ip_setup_gui.png)

Click the **Setting** buttion(gear logo) then goto ipv4 tab

Then, set the device IP like the screen shot below

![Set static ip of the host device](imgs/getting_started/communication_setup/setup_static_ip_gui.png){width=70%}

# 2. SLAMBOX Setting {#Tutorial-SLAMBOXSetting}

- Check how to setup *SLAMBOX* or how to configure *SLAMBOX*, please see here([SLAMBOX Setting](#SLAMBOXSetting))

# 3. LiDAR Setting {#Tutorial-LiDARSetting}

- Check how to setup LiDAR to *SLAMBOX*, please see here([LiDAR Setting](#LiDARSetting))

# 4. Download Mapping File {#Tutorial-DownloadMappingFile}

- Mapping results are saved periodically in the SLAMBOX device. The saved mapping file(.PCD) can be downloaded by visiting web URL (http://192.168.101.101:8080).

- The default user ID and password are `user` / `user`

    **NOTE** USB-C (OTG) or ethernet cable must be plugged into your computer in order to access the URL.

# 5. Advanced {#Tutorial-Advanced}

Please check following pages for the next step.

- [ROS example](https://github.com/j-marple-dev/slambox-ros)

- [TurtleBot3 example](#TurtleBotExample)

- [PX4 example](#PX4Example)

- [Ardupilot example](#ArdupilotExample)

