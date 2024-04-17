# Firmware Update {#FirmwareUpdate}
This document describes the firmware update procedure for the SLAMBOX.
The firmware update process is described below.

[TOC]

## Step 1: Download Firmware
- Download the firmware file from the [firmware download page](https://drive.google.com/drive/folders/1xsq_qMkPi7elDNQZtLHVoChtT2tdOtcf?usp=sharing).

## Step 2: Connect OTG cable
- Connect power cable to the SLAMBOX and connect the SLAMBOX to the host PC using an OTG (On-The-Go) cable. Ensure you use a compatible OTG cable for the connection.


## Step 3: Upload firmware file to the SLAMBOX
- Visit http://192.168.101.101:8080 for file managing system.
- The default user ID and password are `user` / `user`
- Upload the firmware file, named according to the version (e.g., `slambox_firmware_v0.x.x.tar`), to the root directory.


## Step 4: Apply firmware update
- Once the upload procedure is complete, reboot your SLAMBOX device.
- Wait a few minutes until the LED is blinking rapidly, indicating the firmware update is in progress.
- When the LED stops blinking, the firmware update is finished.


## Step 5: Verify the Firmware Update
- Connect the SLAMBOX device with a serial cable.
- Send the `$VERSION#` message through the serial communication to verify the firmware version.

## Wrap-up
Congratulations! You have successfully updated the firmware of your SLAMBOX device. For further assistance or inquiries, please refer to the user manual or contact our support team.

## Version history

### v0.2.3 (latest)
- Change savine PCD method. The PCD files will be saved in 10-second intervals.
- Add ML-X LiDAR support.

### Previous versions
<details close>
<summary>Click to show</summary>

<H2>v0.2.2</H2>
- Change saving PCD mapping file regardless of the connection status of the host.
- Fix an issue where config changes do not apply.

<H2>v0.2.0</H2>
- Add firmware update function.
- Add a file managing system.
- Add Unitree L1 LiDAR support.

<H2>v0.1.0a</H2>
- Add Velodyne Puck LiDAR support.

<H2>v0.1.0</H2>
- Initial release
</details>
