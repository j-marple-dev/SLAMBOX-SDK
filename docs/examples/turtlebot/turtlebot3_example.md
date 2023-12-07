# Turtle-Bot Example {#TurtleBotExample}

[TOC]


# 1. Setup the environment
- Setup environment for communication with SLAMBOX and turtlebot

## 1.1. Hardware setup

### 1.1.1. Setup raspberry pi for TurtleBot

- Build Driver with local ROS, please use ROS version noetic ([Installation](https://wiki.ros.org/noetic/Installation/Ubuntu))

- **NOTE**: We prefer you to use docker because the Debian OS version which supports ROS noetic is out of date

<details>
<summary>How to install docker in RPi Debian OS</summary>

- [Official Docker installation website](https://docs.docker.com/engine/install/debian/)

1. Uninstall the installed old version docker
```bash
# Uninstall the installed old version Docker
for pkg in docker.io docker-doc docker-compose podman-docker containerd runc; do sudo apt-get remove $pkg; done
```


2. Set up docker's apt repository
```bash
# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl gnupg
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/debian/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg

# Add the repository to Apt sources:
echo \
  "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/debian \
  "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
```


3. Install the Docker packages
```bash
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```


4. Verity that the installation is successful by running the `hello-world` image
```bash
sudo docker run hello-world
```


5. Give permission to user to use docker w/o sudo
```bash
# Create the docker group
sudo groupadd docker

# Add your user to the docker group
sudo usermod -aG docker $USER

# Log out and log back in so that your group membership is re-evaluated.
newgrp docker

# Check the authority
docker run hello-world
```


6. (Optional) Install ducker to use docker easier
```bash
curl https://raw.githubusercontent.com/JeiKeiLim/ducker/main/install.sh | bash -s install linux arm64
```
</details>

## 1.2. Driver setup
### 1.2.1. Build the Driver on TurtleBot Raspberry Pi

- Should build the driver on TurtleBot raspberry pi for get data from SLAMBOX with ROS message

- Please check the [README](https://github.com/j-marple-dev/SLAMBOX_driver/blob/main/README.md) for building SLAMBOX driver

-----
# 2. Run client

- The SLAMBOX driver for server will be launched automatically.

- To check the result of SLAMBOX, use **Remote server** of turtlebot to run rviz

- **NOTE**: The RPi of turtlebot and the remote server must be connected with same network

- **NOTE**: The command below should be type inside the docker container

```bash
# 1. Set the ROS master ip of Remote server
$ export ROS_MASTER_URI=http://{remote_server_ip}:11311
$ export ROS_HOSTNAME={remote_server_ip}

# 2. Turn on the roscore
$ roscore

# 3. launch ros core and rviz
$ rviz -d {SLAMBOX_driver_dir}/docs/examples/turtlebot/config/rviz.rviz
```

- Set the remote server ip to turtlebot Raspberry Pi

- If the remote server ip is `192.168.0.3` the `ROS_MASTER_URI` will be `http://192.168.0.3:11311`

```bash
# if using docker, the command below run inside the docker
# 1. Setup the master ip of ROS and the host name
$ export ROS_MASTER_URI=http://{remote_server_ip}:11311
$ export ROS_HOSTNAME={turtlebot_rpi_ip}

$ source devel/setup.bash
$ roslaunch slambox_driver slambox_driver_client.launch
```

# 3. Configure SLAMBOX Configurations
- Check the [SLAM BOX setting](SLAMBOXSetting.html)

---

# 4. Hardware connection
## 4.1. Serial Connection

- To make the serial communication module, connect the pins of module like below

![Image from https://www.vectornav.com](uart_rxtx_twist.jpg){ width=30% }

- Connect SLAMBOX with *TurtleBot RPi*, use serial module and connect like below

![Serial with flexlam and turtlebot3 rpi](turtlebot3-rpi-connection.jpg){ width=50% }

---

# 5. Custom usage for SLAMBOX data

## 5.1. Subscriber example for SLAMBOX data

```cpp
#include <ros.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/PointCloud2.h>

// There are two major data from SLAMBOX sensor
void odometry_callback(const nav_msgs::Odometry::ConstPtr &msg) {
  // Do something with odometry msg

  std::cout << "pos x: " << msg.pose.pose.position.x <<
               " pos y: " << msg.pose.pose.position.y <<
               " pos z: " << msg.pose.pose.position.z << std::endl;
}

void pointcloud_callback(const sensor_msgs::PointCloud2::ConstPtr &msg) {
  // Do somting with pointcloud msg here
  return;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "exampleSubscriber");

  ros::NodeHandle nh;
  odom_sub = nh.subscribe<nav_msgs::Odometry>("/SLAMBOX/odom", 200000, odometry_callback);
  pointcloud_sub = nh.subscribe<sensor_msgs::PointCloud2>("/SLAMBOX/pointcloud", 200000, pointcloud_callback);

  ros::spin();
  return 0;
}
```

## 5.2. Save PCD data

```bash
# CMD,SAVE_PCD,save_pcd_flag,reset_flag
$ rostopic pub /SLAMBOX/request std_msgs/String CMD,SAVE_PCD,1,0
```
- You can send the msg to SLAMBOX with code if you need

---
