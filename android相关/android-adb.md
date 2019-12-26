# android的fastboot解析


### 查看usb id

    ~/.android$ lsusb
    Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
    Bus 001 Device 003: ID 2c7c:0435  
    Bus 001 Device 002: ID 80ee:0021 VirtualBox USB Tablet
    Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
	
### 配置adb_usb.ini---解决 error: device not found

~/.android$ echo 0x2c7c > adb_usb.ini
~/.android$ sudo adb-killserver

~/.android$ adb shell
* daemon not running. starting it now on port 5037 *
* daemon started successfully *
error: insufficient permissions for device

### 配置/etc/udev/rules.d/  解决 error: insufficient permissions for device

/etc/udev/rules.d$ cat 51-android.rules 
UBSYSTEM=="usb", ATTRS{idVendor}=="0c7c", ATTRS{idProduct}=="0435",MODE="0666" GROUP="xxx"
SUBSYSTEM=="usb", ENV{DEVTYPE}=="usb_device", MODE="0666"
/etc/udev/rules.d$ 
/etc/udev/rules.d$ sudo  /etc/init.d/udev restart