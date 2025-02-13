// ui_home.c
#include "ui_home.h"
#include "app_state.h"
#include <lvgl/lvgl.h>

static lv_obj_t *g_home_screen = NULL;  // 静态对象，避免重复创建

static void lv_obj_set_hidden(lv_obj_t*obj,bool enable){
    if(enable){
        lv_obj_add_flag(obj,LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_remove_flag(obj,LV_OBJ_FLAG_HIDDEN);
    }
}
// 主界面按钮点击事件
static void on_home_btn_click(lv_event_t *e) {
    UiScreenID target = (UiScreenID)(intptr_t)lv_event_get_user_data(e);
    if(target != UI_SCREEN_HOME){
        ui_push(target);  // 使用栈式切换
    }
    
}

// 创建主界面（仅在首次调用时创建）
void ui_home_create(void) {
    if (g_home_screen) return;  // 防止重复初始化
    g_home_screen = lv_obj_create(NULL);
    lv_obj_set_size(g_home_screen,LV_PCT(100),LV_PCT(100)); 
    lv_obj_set_style_pad_all(g_home_screen,0,0);
    lv_obj_set_hidden(g_home_screen,true);
    lv_obj_set_style_bg_color(g_home_screen, lv_color_hex(0xF0F0F0), 0);

    // 居中列表容器
    lv_obj_t *list = lv_list_create(g_home_screen);
    lv_obj_set_size(list, LV_PCT(80), LV_PCT(80));
    lv_obj_align(list, LV_ALIGN_CENTER, 0, 0);

    // 添加列表项（WIFI/BLE/SETTINGS）
    const char* items[] = {"WIFI", "BLE", "SETTINGS"};
    const UiScreenID targets[] = {UI_SCREEN_WIFI, UI_SCREEN_HOME, UI_SCREEN_HOME};
    for (int i = 0; i < 3; i++) {
        lv_obj_t *btn = lv_list_add_btn(list, LV_SYMBOL_WIFI, items[i]);
        lv_obj_add_event_cb(btn, on_home_btn_click, LV_EVENT_CLICKED, (void*)(intptr_t)targets[i]);
    }
}

void ui_home_show(void) {
    lv_obj_remove_flag(g_home_screen,LV_OBJ_FLAG_HIDDEN);
    lv_scr_load_anim(g_home_screen, LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, false);
}

void ui_home_hide(void) {
    // 无需销毁，保持常驻
    lv_obj_add_flag(g_home_screen,LV_OBJ_FLAG_HIDDEN);
}
const UiScreenOps g_home_ops = {
    .create = ui_home_create,
    .show = ui_home_show,
    .hide = ui_home_hide
};
