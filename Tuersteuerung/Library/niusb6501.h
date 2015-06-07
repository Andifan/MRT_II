#ifndef _NIUSB6501_H_
#define _NIUSB6501_H_

#include <usb.h>

#ifdef __cplusplus
extern "C" {
#endif
extern size_t niusb6501_list_devices(struct usb_device *devices[], size_t size);
extern struct usb_dev_handle *niusb6501_open_device(struct usb_device *device);
extern int niusb6501_close_device(struct usb_dev_handle *handle);

extern int niusb6501_read_port(struct usb_dev_handle *handle, unsigned char port, unsigned char *value);
extern int niusb6501_write_port(struct usb_dev_handle *handle, unsigned char port, unsigned char value);

extern int niusb6501_set_io_mode(struct usb_dev_handle *handle, unsigned char port0, unsigned char port1, unsigned char port2);

#ifdef __cplusplus
}
#endif

#endif

