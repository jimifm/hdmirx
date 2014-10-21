#ifndef ANDROID_HDMIRX_INTERFACE_H
#define ANDROID_HDMIRX_INTERFACE_H
#include <hardware/hardware.h>

__BEGIN_DECLS

/*定义模块ID*/
#define HDMIRX_HARDWARE_MODULE_ID "hdmirx"

/*硬件模块结构体*/
struct hdmirx_module_t {
        struct hw_module_t common;
};

/*硬件接口结构体*/
struct hdmirx_device_t {
        struct hw_device_t common;
        int fd;
        //int (*set_val)(struct hdmirx_device_t* dev, int val);
        //int (*get_val)(struct hdmirx_device_t* dev, int* val);
        int (*init_hdmirx)(struct hdmirx_device_t *dev);
        int (*run_hdmirx)(struct hdmirx_device_t *dev);
        int (*stop_hdmirx)(struct hdmirx_device_t *dev);
};

__END_DECLS

#endif
