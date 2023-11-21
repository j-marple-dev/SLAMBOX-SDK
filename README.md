# FlexXlam Driver
FlexXlam driver is a ROS package to communicate with FlexXlam device.

Table of Contents
=================

TBD: Fix this document

* [FlexXlam Driver](#flexxlam-driver)
* [Table of Contents](#table-of-contents)
* [1. Getting started](#1-getting-started)
   * [1.1. Installation](#11-installation)
      * [1.1.1. Requirements](#111-requirements)
      * [1.1.2. (Optional) Building the docker image](#112-optional-building-the-docker-image)
      * [1.1.3. Local ROS system](#113-local-ros-system)
   * [1.2. Configuration](#12-configuration)
      * [1.2.1. Client configuration](#121-client-configuration)
      * [1.2.2. Server configuration](#122-server-configuration)
   * [1.3. Usage](#13-usage)
* [2. Features](#2-features)
   * [2.1. Client features](#21-client-features)
   * [2.2. Supported Communication Interfaces](#22-supported-communication-interfaces)
      * [2.2.1. UART](#221-uart)
      * [2.2.2. Ethernet](#222-ethernet)
* [3. Contributing](#3-contributing)
* [4. External resources](#4-external-resources)

# 1. Getting started
## 1.1. Installation
### 1.1.1. Requirements
- ROS noetic (Recommended)
- glog (>=v0.6.0)
- CMake (>= 3.16.3)
- docker (Optional but highly recommended)
- `dialout` group permission. Use below command to include `dialout` group to your linux account for UART communication.
    ```shell
    sudo usermod -aG dialout $USER
    ```

### 1.1.2. (Optional) Building the docker image
* Our docker image includes development environment. We highly recommend docker system.
    ```shell
    # Clone this repository
    git clone https://github.com/j-marple-dev/FlexXlam_driver.git --recursive

    # Build docker image
    docker build . -t jmarpledev/flexxlam_driver -f docker/Dockerfile  --build-arg UID=$(id -u) --build-arg GID=$(id -u)

    # Run docker container with shell (For development environment)
    docker run -tid --privileged -e DISPLAY=:0 -e TERM=xterm-256color -v /tmp/.X11-unix:/tmp/.X11-unix:ro -v /dev:/dev -v $PWD:/home/user/catkin_ws/src/flexxlam_driver --network host jmarpledev/flexxlam_driver /usr/bin/zsh

    # Run docker container for running FlexXlam driver client
    docker run -ti --privileged -e TERM=xterm-256color -v /dev:/dev -v $PWD:/home/user/catkin_ws/src/flexxlam_driver --network host jmarpledev/flexxlam_driver /usr/bin/bash -lic "roslaunch flexxlam_driver flexxlam_driver_server.launch"
    ```

### 1.1.3. Local ROS system
```shell
# Assuming that your ROS workspace is ~/catkin_ws
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
git clone https://github.com/j-marple-dev/FlexXlam_driver.git --recursive
cd ../
catkin build flexxlam_driver
# Choose the shell which you are using
source devel/setup.{bash|zsh}
```

## 1.2. Configuration
### 1.2.1. Client configuration
- Please refer to [config/client.yaml](config/client.yaml) for configuration on client side.
```yaml
serial_communication:
  enabled: true
  port_name: "/dev/ttyUSB0"
  baudrate: 1500000

ethernet_communication:
  enabled: true
  server_addr: "192.168.1.50"
  port: 21580

publish:
  odom_topic: "/FlexXlam/odom"
  pointcloud_topic: "/FlexXlam/pointcloud"

subscribe:
  request_topic: "/FlexXlam/request"
```

### 1.2.2. Server configuration
- **Note** that [config/server.yaml](config/server.yaml) is used in FlexXlam device. Thus modifying this will affect nothing.
- Please connect UART port to your system and run `flexxlam_driver-config_cli ${UART_DEV} ${BAUDRATE}`
    ```shell
    # In ROS environment
    rosrun flexxlam_driver flexxlam_driver-config_cli /dev/ttyUSB0 1152000
    ```

## 1.3. Usage

# 2. Features
## 2.1. Client features
- (TBD)

## 2.2. Supported Communication Interfaces
### 2.2.1. UART
### 2.2.2. Ethernet

# Examples
- [Turtle Bot3 / ROS](examples/turtlebot/README.md)

# 3. Contributing
- For those who wish to contribute to this proejct please refer to the [CONTRIBUING.md](CONTRIBUTING.md).

# 4. External resources
- [glog](https://github.com/google/glog) - Google Logging Library
- [libserial](https://github.com/crayzeewulf/libserial) - Serial Communication Library
- [cli](https://github.com/daniele77/cli) - C++ CLI Library
- [ducker](https://github.com/JeiKeiLim/ducker) - Docker Helper CLI application
