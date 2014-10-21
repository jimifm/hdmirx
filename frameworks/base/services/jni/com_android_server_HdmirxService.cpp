#define LOG_TAG "HdmirxService"
#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"
#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/hdmirx.h>
#include <stdio.h>

namespace android
{
        /*在硬件抽象层中定义的硬件访问结构体，参考<hardware/hdmirx.h>*/
        struct hdmirx_device_t* hdmirx_device = NULL;
                /*通过硬件抽象层定义的硬件访问接口设置硬件寄存器val的值*/
        static void hdmirx_device_init(JNIEnv* env, jobject clazz, jint value) {

            hdmirx_device->init_hdmirx(hdmirx_device);
        }
                           
        /*通过硬件抽象层定义的硬件访问接口读取硬件寄存器val的值*/ 
        static jint hdmirx_device_run(JNIEnv* env, jobject clazz) {                        
            
            hdmirx_device->run_hdmirx(hdmirx_device);
            ALOGI("Hdmirx JNI:running.");
                                                      
            return 0;
                                                      
        }
                             
        static void hdmirx_device_stop(JNIEnv* env, jobject clazz, jint value) {

            hdmirx_device->stop_hdmirx(hdmirx_device);
        }
        /*通过硬件抽象层定义的硬件模块打开接口打开硬件设备*/
        static inline int hdmirx_device_open(const hw_module_t* module, struct hdmirx_device_t** device) {
                                        
            return module->methods->open(module, HDMIRX_HARDWARE_MODULE_ID, (struct hw_device_t**)device);
        }
        
        /*通过硬件模块ID来加载指定的硬件抽象层模块并打开硬件*/
         
        static jboolean hdmirx_init(JNIEnv* env, jclass clazz) {
          
            hdmirx_module_t* module;
                                                    
            ALOGI("Hdmirx JNI: initializing......");
            
            if(hw_get_module(HDMIRX_HARDWARE_MODULE_ID, (const struct hw_module_t**)&module) == 0) {
            
                ALOGI("Hdmirx JNI: hdmirx Stub found.");
                                                                                       
                if(hdmirx_device_open(&(module->common), &hdmirx_device) == 0) {
                
                    ALOGI("Hdmirx JNI: hdmirx device is open.");
                    return 0;
                }
                    
                ALOGE("Hdmirx JNI: failed to open hdmirx device.");
                
                return -1;
            }
            ALOGE("Hdmirx JNI: failed to get hdmirx stub module.");
            return -1;      
        }
            
        /*JNI方法表*/
        
        static const JNINativeMethod method_table[] = {
        
            {"init_native", "()Z", (void*)hdmirx_init},
            {"hdmirx_init_native", "()Z", (void*)hdmirx_device_init},
            {"hdmirx_run_native", "()V", (void*)hdmirx_device_run},
            {"hdmirx_stop_native", "()I", (void*)hdmirx_device_stop},
        };
                                            /*注册JNI方法*/
        int register_android_server_HdmirxService(JNIEnv *env) {
        
            return jniRegisterNativeMethods(env, "com/android/server/HdmirxService", method_table, NELEM(method_table));
        }
};
