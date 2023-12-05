# LiDAR Setting {#LiDARSetting}

Welcome to the LiDAR Setting Manual for FlexXlam.
This guide will walk you through the necessary steps to successfully connect LiDAR with FlexXlam.

[TOC]

# 1. Livox MID-360 {#LiDARSetting-MID360}

Livox MID 360 is ...

# 2. Livox AVIA {#LiDARSetting-AVIA}

## 2.1. Preparing for LiDAR setup

Before starting the setup process, make sure you have following:

* LiDAR configuration software

* Computer with Ethernet ports (Ubuntu or Windows)

## 2.2. AVIA Configuration Steps

### 2.2.1. Download Livox Viewer for AVIA

Please visit AVIA [downloader center](https://www.livoxtech.com/avia/downloads) and download Livox Viewer compatible with your operating system.

### 2.2.2. Conecting AVIA to the Computer

Connect the AVIA LiDAR to your computer using the Ethernet cable.

### 2.2.3. Setting Computer IP Address

Set the computer's IP address according to the AVIA default setting. The default setting of AVIA is to set your IP Address to `192.168.1.x`.
In this tutorial, we will set IP address to `192.168.1.50`


![IP Address Setting](getting_started/lidar_setting/ip_setting_192_168_1_50.png){width=800px}


### 2.2.4. Launching LiDAR Viewer Software

Extract Livox Viewer and launch Livox Viewer via `livox_viewer.sh` script.

![Livox Viewer](getting_started/lidar_setting/Livox_Viewer_0_10_init.png)

Make sure the LiDAR is detected on Device Manager. Check if LiDAR is working as below screenshot.

![Livox Viewer Visualization](getting_started/lidar_setting/Livox_Viewer_0_10_working.png)

### 2.2.5. Setting LiDAR IP Address

Once the connection is established, click on Device Settings icon.
Modify IP Settings to `Static IP` and IP Address: `192.168.1.100`, Subnet Mask: `255.255.255.0`, and Gateway: `192.168.1.1`

![Modify IP Settings](getting_started/lidar_setting/Livox_Viewer_0_10_setting.png)


Click on Confirm and REBOOT. Make sure the LiDAR connects after reboot procedure.
Now AVIA is ready to connect with FlexXlam device. Connect AVIA to FlexXlam device via ethernet cable.

# 3. Ouster OS0 Famly (OS0-32, OS0-64, and OS0-128) {#LIDARSetting-OusterOS0}

