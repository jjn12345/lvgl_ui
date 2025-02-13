#pragma once
#include "model.h"
#include "lvgl/lvgl.h"
typedef enum{
    view_wifi_start = 0x100,
    view_wifi_close = 0x200,
    view_wifi_connect = 0x300,
}ViewEventType_t;

typedef struct{
    char ssid[33];
    char pwd[64];
}wifi_counter;

typedef struct{
    module_t base;
    /* wifi_Page */
    lv_obj_t* wifi_info;
    wifi_counter ConnectCounter;
}view_module_t;

extern view_module_t g_view_module;


/* 专门给模拟器留的接口 */
void lvgl_init(void);
