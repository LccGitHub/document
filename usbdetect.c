#include "stdlib.h"
#include <stdio.h>
#include "iostream"
#include <libusb-1.0/libusb.h>
using namespace std;

//??????????
//????????????????????????libusb?????????
static int hotplug_callback(
    struct libusb_context *ctx,
    struct libusb_device *device,
    libusb_hotplug_event event,
    void *user_data) {
    //??????????
    uint8_t deviceAddress = libusb_get_device_address(device);
    //enum libusb_hotplug_event {
    //     LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED = 0x01,
    //     LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT = 0x02 }
    if(event == LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED) {
        printf("???? \n");
    } else if (event == LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT) {
        printf("???? \n");
    }
    return 0;
}

int main () {
  printf("testUSB\n");
  //libusb?????????????????
  libusb_context *context;
  //???libusb,?????
  int ret = libusb_init(&context);
  if (ret != LIBUSB_SUCCESS) {
      printf("initialize libusb failed");
      return -1;
  }
  //???????????????
  if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG)) {
      printf("this version's libusb doesn't support hotplug");
      return -1;
  }
  //??hotplug
  //?????VID????LIBUSB_HOTPLUG_MATCH_ANY?????VID
  int vendor_id = LIBUSB_HOTPLUG_MATCH_ANY;
  //?????PID ???LIBUSB_HOTPLUG_MATCH_ANY?????PID
  int product_id = LIBUSB_HOTPLUG_MATCH_ANY;
  //????????class,???LIBUSB_HOTPLUG_MATCH_ANY???????libusb_device_descriptor?class??
  //????????
  int device_class = LIBUSB_HOTPLUG_MATCH_ANY;
  //???????????????
  libusb_hotplug_event event = static_cast<libusb_hotplug_event> (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED | LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT);

  //typedef enum {
  //    LIBUSB_HOTPLUG_NO_FLAGS = 0,//?????????????????????
  //    LIBUSB_HOTPLUG_ENUMERATE = 1<<0,//???????????????????????
  //} libusb_hotplug_flag;
  libusb_hotplug_flag flag = static_cast<libusb_hotplug_flag>(1);

  //????????????
  libusb_hotplug_callback_handle handle;

  //?????????
  void *user_data;

  // int LIBUSB_CALL libusb_hotplug_register_callback(libusb_context *ctx,
  //                        libusb_hotplug_event events,
  //                        libusb_hotplug_flag flags,
  //                        int vendor_id, int product_id,
  //                        int dev_class,
  //                        libusb_hotplug_callback_fn cb_fn,
  //                        void *user_data,
  //                        libusb_hotplug_callback_handle *callback_handle);
  printf("libusb_hotplug_register_callback\n");
  int result_Register = libusb_hotplug_register_callback(context, event, flag, vendor_id, product_id, device_class, hotplug_callback, &user_data, &handle);
  if (result_Register != LIBUSB_SUCCESS) {
      printf("resigter hotplug_callback failed");
      return -1;
  } else {
      printf("resigter hotplug_callback successfully");
  }

  //??????????????????libusb_handle_events
  //????????????????
  while(1) {
        //?????????????
        printf("libusb_handle_events\n");
        libusb_handle_events(context);
  }

  //??????
  libusb_hotplug_deregister_callback(context, handle);
  libusb_exit(context);
  return 0;
}
