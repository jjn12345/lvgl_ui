// ui_manager.h
#pragma once
#include "lvgl/lvgl.h"
#include "app_state.h"

// 界面ID（严格顺序匹配初始化）
typedef enum {
    UI_SCREEN_HOME,
    UI_SCREEN_WIFI,
    UI_SCREEN_WIFI_CONNECT,
    UI_SCREEN_MAX  // 必须为最后一个元素
} UiScreenID;

// 界面操作函数原型
typedef struct {
    bool is_created;
    bool is_persistent;
    void (*create)(void);    // 创建界面（仅调用一次）
    void (*show)(void);      // 显示界面（带入场动画）
    void (*hide)(void);      // 隐藏界面（带离场动画）
} UiScreenOps;

// 界面管理器API
void ui_init(void);                       // 初始化所有界面
void ui_push(UiScreenID screen_id);       // 压入界面栈（支持返回）
void ui_pop(void);                        // 弹出界面栈（返回上一级）
void ui_register_screen(UiScreenID id, 
                       void (*create)(void),
                       void (*show)(void),
                       void (*hide)(void));
// 全局界面栈（深度为3，节省内存）
#define UI_STACK_DEPTH 3