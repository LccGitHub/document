## huaweiE8372  4G donge 调试

当donge插入usb时，dmesg会显示如下信息

    [123155.184472] usb 1-12: new high-speed USB device number 11 using xhci_hcd
    [123155.334140] usb 1-12: New USB device found, idVendor=12d1, idProduct=1f01, bcdDevice= 1.02
    [123155.334146] usb 1-12: New USB device strings: Mfr=1, Product=2, SerialNumber=3
    [123155.334150] usb 1-12: Product: HUAWEI_MOBILE
    [123155.334153] usb 1-12: Manufacturer: HUAWEI_MOBILE
    [123155.334156] usb 1-12: SerialNumber: 0123456789ABCDEF
    [123155.336123] usb-storage 1-12:1.0: USB Mass Storage device detected
    [123155.336528] scsi host5: usb-storage 1-12:1.0
    [123156.344909] usb 1-12: USB disconnect, device number 11
    [123156.772489] usb 1-12: new high-speed USB device number 12 using xhci_hcd
    [123156.922764] usb 1-12: New USB device found, idVendor=12d1, idProduct=14db, bcdDevice= 1.02
    [123156.922770] usb 1-12: New USB device strings: Mfr=1, Product=2, SerialNumber=0
    [123156.922774] usb 1-12: Product: HUAWEI_MOBILE
    [123156.922777] usb 1-12: Manufacturer: HUAWEI_MOBILE
    [123157.094522] cdc_ether 1-12:1.0 eth0: register 'cdc_ether' at usb-0000:00:14.0-12, CDC Ethernet Device, 00:1e:10:1f:00:00 // 如果没有这句log，则需要在option.c的option_ids添加相应信息即可
    [123157.096551] usbcore: registered new interface driver cdc_ether
    [123157.133016] cdc_ether 1-12:1.0 enx001e101f0000: renamed from eth0  // 有时候会是eth1
    
此时 ifconfig     enx001e101f0000 会被分配ip，如果没有自动分配ip，可以通过如下命令设置ip和路由

    ifconfig enx001e101f0000 192.168.8.100  // 因为华为donge默认的网页为192.168.8.1 
    ip route del default // 删除之前的默认路由
    ip route add default via 192.168.8.1 dev enx001e101f0000 // 设置华为 donge为默认路由
