# Tutorial {#Tutorial}

[TOC]

# 1. Communication Setting {#Tutorial-CommunicationSetting}

- To communicate with *SLAMBOX*, you need to setup the serial and ethernet of your **host PC**

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

## 1.2. Ethernet (OTG) {#Tutorial-CommunicationSetting-Ethernet}

To get data from *SLAMBOX* through etherent, then set your host PC's host IP like below.

### 1.2.1. Set Static IP with Terminal {#Tutorial-CommunicationSetting-Ethernet-SetStaticIPwithTerminal}

To set static ip to your host PC, please follow the commands below

**NOTE**: The default IP address of OTG port of *SLAMBOX* is `192.168.101.101`

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

The device name `enx5ad1753eff84` is the OTG ethernet connection of SLAMBOX

Then set the device's IP 

In this example, set the static IP to `192.168.101.5`

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

![Check the SLAMBOX connection](imgs/getting_started/communication_setup/ubuntu_ip_setup_gui.jpg)

Click the **Setting** buttion(gear logo) then goto ipv4 tab

Then, set the device IP like the screen shot below

![Set static ip of the host device](imgs/getting_started/communication_setup/setup_static_ip_gui.jpg){width=70%}

# 2. LiDAR Setting {#Tutorial-LiDARSetting}

- Check how to setup LiDAR to *SLAMBOX*, please see here([LiDAR Setting](#LiDARSetting))

# 3. SLAMBOX Setting {#Tutorial-SLAMBOXSetting}

- Check how to setup *SLAMBOX* or how to configure *SLAMBOX*, please see here([SLAMBOX Setting](#SLAMBOXSetting))

# 4. Advanced {#Tutorial-Advanced}

We prefer you to check examples below

- [TurtleBot3 example](#TurtleBotExample)

- [PX4 example](#PX4Example)

- [Ardupilot example](#ArdupilotExample)

- [ROS example](https://github.com/j-marple-dev/slambox-ros)
