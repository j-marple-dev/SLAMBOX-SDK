# FlexXlam SDK
FlexXlam SDK is a C++ library specifically designed for seamless communication with the FlexXlam device.
The FlexXlam device empowers LiDAR devices with simultaneous localization and mapping (SLAM) algorithms.
FlexXlam SDK allows developers to effortlessly integrate and control FlexXlam functionality in their C++ applications, offering advanced spatial awareness and navigation capabilities.


# 1. Getting started

## 1.1. Prerequisites

- Linux system (tested on Ubuntu 22.04)
- CMake (>= 3.0.2)
  - Please check on [CONTRIBUTING.md](CONTRIBUTING.md#Install-CMake->-3.16.3) for manual installiation.
- glog (>=v0.6.0)
    - How to install:
    ```bash
    git clone https://github.com/google/glog.git -b v0.6.0
    cmake -S . -B build -G "Unix Makefiles"
    cmake --build build
    sudo cmake --build build --target install
    ```
- libserial (>= 1.0.0)
    - How to install(Ubuntu >=20.04):
    ```bash
    sudo apt-get install libserial-dev
    ```

    - How to install manually:
    ```bash
    git clone https://github.com/crayzeewulf/libserial.git
    cd libserial
    git checkout f1504de092d94148e2ec690bbb1e7ee21889ede7
    mkdir build
    cd build
    cmake ..
    make -j
    sudo make install
    ```


## 1.2. Installiation

1. Clone the FlexXlam SDK repository:
```bash
git clone https://github.com/j-marple-dev/FlexXlam-SDK.git
```

2. Build and install FlexXlam SDK:
```bash
mkdir -p FlexXlam-SDK/build
cd FlexXlam-SDK/build
cmake ..
make -j
sudo make install
```

# 2. Examples
Check the [examples](examples) directory for sample code.
Each subdirectory within examples contains an example demonstrating the usage of FlexXlam SDK in different scenarios.


# 3. Contributing
- We welcome contributions from the community. If you find a bug or have an enhancement in mind, please open an issue or submit a pull request. Check our [contribution guidelines](CONTRIBUTING.md) for more information.


# 4. External resources
- [glog](https://github.com/google/glog) - Google Logging Library
- [libserial](https://github.com/crayzeewulf/libserial) - Serial Communication Library
- [ducker](https://github.com/JeiKeiLim/ducker) - Docker Helper CLI application

# 5. Contact
For any inquiries or support, please contact us at limjk@jmarple.ai

