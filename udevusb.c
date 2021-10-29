/*******************************************
 libudev example.

 This example prints out properties of
 each of the hidraw devices. It then
 creates a monitor which will report when
 hidraw devices are connected or removed
 from the system.

 This code is meant to be a teaching
 resource. It can be used for anyone for
 any reason, including embedding into
 a commercial product.

 The document describing this file, and
 updated versions can be found at:
    http://www.signal11.us/oss/udev/

 Alan Ott
 Signal 11 Software
 2010-05-22 - Initial Revision
 2010-05-27 - Monitoring initializaion
              moved to before enumeration.
*******************************************/

#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <signal.h>

static unsigned int run = 1;

static void unset_run(int signo)
{
	(void) signo;
	run = 0;
}

static int set_signal_handler(void (*signal_handler)(int))
{
	struct sigaction new_action;
	struct sigaction old_action;
	int ret;

	new_action.sa_handler = signal_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;

	ret = sigaction(SIGINT, NULL, &old_action);
	if (ret < 0) {
		perror("sigaction on old_action");
		goto out;
	}

	if (old_action.sa_handler != SIG_IGN) {
		ret = sigaction(SIGINT, &new_action, NULL);
		if (ret < 0) {
			perror("sigaction on new_action");
			goto out;
		}
	}

out:
	return ret;
}

/* Require libudev >= 172 for udev_enumerate_add_match_parent() */
static int get_leds_devices(struct udev_device *udevice)
{
	struct udev_list_entry *devices, *dev_list_entry;
	struct udev_enumerate *enumerate;
	struct udev_device *hid_parent;
	int ret;

	hid_parent = udev_device_get_parent_with_subsystem_devtype(udevice,
								"hid", NULL);

	enumerate = udev_enumerate_new(udev_device_get_udev(udevice));
	//udev_enumerate_add_match_parent(enumerate, hid_parent);
	udev_enumerate_add_match_subsystem(enumerate, "leds");
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);

	if (devices == NULL) {
		ret = -1;
		goto out;
	}

	udev_list_entry_foreach(dev_list_entry, devices) {
		const char *syspath = udev_list_entry_get_name(dev_list_entry);
		fprintf(stderr, "syspath: %s\n", syspath);
	}

	ret = 0;
out:
	udev_enumerate_unref(enumerate);
	return ret;
}

int main (void)
{
	struct udev *udev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices, *dev_list_entry;
	struct udev_device *dev;

	struct udev_monitor *mon;
	int fd;

	if (set_signal_handler(unset_run) < 0)
		exit(1);

	/* Create the udev object */
	udev = udev_new();
	if (!udev) {
		printf("Can't create udev\n");
		exit(1);
	}

	/* This section sets up a monitor which will report events when
	   devices attached to the system change.  Events include "add",
	   "remove", "change", "online", and "offline".

	   This section sets up and starts the monitoring. Events are
	   polled for (and delivered) later in the file.

	   It is important that the monitor be set up before the call to
	   udev_enumerate_scan_devices() so that events (and devices) are
	   not missed.  For example, if enumeration happened first, there
	   would be no event generated for a device which was attached after
	   enumeration but before monitoring began.

	   Note that a filter is added so that we only get events for
	   "hidraw" devices. */

	/* Set up a monitor to monitor hidraw devices */
	mon = udev_monitor_new_from_netlink(udev, "udev");
	//udev_monitor_filter_add_match_subsystem_devtype(mon, "hidraw", NULL);
    udev_monitor_filter_add_match_subsystem_devtype(mon, "tty", NULL);
	udev_monitor_enable_receiving(mon);
	/* Get the file descriptor (fd) for the monitor.
	   This fd will get passed to select() */
	fd = udev_monitor_get_fd(mon);


	/* Create a list of the devices in the 'hidraw' subsystem. */
	enumerate = udev_enumerate_new(udev);
	//udev_enumerate_add_match_subsystem(enumerate, "hidraw");
	udev_enumerate_add_match_subsystem(enumerate, "tty");
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);
	/* For each item enumerated, print out its information.
	   udev_list_entry_foreach is a macro which expands to
	   a loop. The loop will be executed for each member in
	   devices, setting dev_list_entry to a list entry
	   which contains the device's path in /sys. */
	udev_list_entry_foreach(dev_list_entry, devices) {
		const char *path;
		struct udev_device *usb_dev;

		/* Get the filename of the /sys entry for the device
		   and create a udev_device object (dev) representing it */
		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);

		/* usb_device_get_devnode() returns the path to the device node
		   itself in /dev. */
		//printf("Device Node Path: %s\n", udev_device_get_devnode(dev));

		/* The device pointed to by dev contains information about
		   the hidraw device. In order to get information about the
		   USB device, get the parent device with the
		   subsystem/devtype pair of "usb"/"usb_device". This will
		   be several levels up the tree, but the function will find
		   it.*/
		usb_dev = udev_device_get_parent_with_subsystem_devtype(
		       dev,
		       "usb",
		       "usb_device");
		if (!usb_dev) {
			//exit(1);
		}

        if (usb_dev) {
           printf("Device Node Path: %s\n", udev_device_get_devnode(dev));
		    /* From here, we can call get_sysattr_value() for each file
		       in the device's /sys entry. The strings passed into these
		       functions (idProduct, idVendor, serial, etc.) correspond
		       directly to the files in the /sys directory which
		       represents the USB device. Note that USB strings are
		       Unicode, UCS2 encoded, but the strings returned from
		       udev_device_get_sysattr_value() are UTF-8 encoded. */
		    printf("  VID/PID: %s %s\n",
		            udev_device_get_sysattr_value(usb_dev,"idVendor"),
		            udev_device_get_sysattr_value(usb_dev, "idProduct"));
		    printf("  %s\n  %s\n",
		            udev_device_get_sysattr_value(usb_dev,"manufacturer"),
		            udev_device_get_sysattr_value(usb_dev,"product"));
		    printf("  serial: %s\n",
		             udev_device_get_sysattr_value(usb_dev, "serial"));

		    /* unref only the original dev, not the parent device;
		       the latter will be unreferenced automatically if set. */
		    udev_device_unref(dev);
        }
	}
	/* Free the enumerator object */
	udev_enumerate_unref(enumerate);

	/* Begin polling for udev events. Events occur when devices
	   attached to the system are added, removed, or change state.
	   udev_monitor_receive_device() will return a device
	   object representing the device which changed and what type of
	   change occured.

	   The select() system call is used to ensure that the call to
	   udev_monitor_receive_device() will not block.

	   The monitor was set up earler in this file, and monitoring is
	   already underway.

	   This section will run continuously, calling usleep() at the end
	   of each pass. This is to demonstrate how to use a udev_monitor
	   in a non-blocking way. */
	while (run) {
		/* Set up the call to select(). In this case, select() will
		   only operate on a single file descriptor, the one
		   associated with our udev_monitor. Note that the timeval
		   object is set to 0, which will cause select() to not
		   block. */
		fd_set fds;
		struct timeval tv;
		int ret;

		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		ret = select(fd+1, &fds, NULL, NULL, &tv);

		/* Check if our file descriptor has received data. */
		if (ret > 0 && FD_ISSET(fd, &fds)) {
			printf("\nselect() says there should be data\n");

			/* Make the call to receive the device.
			   select() ensured that this will not block. */
			dev = udev_monitor_receive_device(mon);
			if (dev) {
				printf("Got Device\n");
				printf("   Node: %s\n", udev_device_get_devnode(dev));
				printf("   Subsystem: %s\n", udev_device_get_subsystem(dev));
				printf("   Devtype: %s\n", udev_device_get_devtype(dev));

				printf("   Action: %s\n", udev_device_get_action(dev));
				get_leds_devices(dev);
				udev_device_unref(dev);
			}
			else {
				printf("No Device from receive_device(). An error occured.\n");
			}
		}
		usleep(250*1000);
		printf(".");
		fflush(stdout);
	}

	udev_monitor_unref(mon);
	udev_unref(udev);

	return 0;
}
