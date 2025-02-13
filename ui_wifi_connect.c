// ui_wifi_connect.c
#include "ui_wifi_connect.h"
#include "app_state.h"
#include <lvgl/lvgl.h>



static lv_obj_t *g_connect_screen = NULL;
static lv_obj_t *g_kb = NULL;
static void lv_obj_set_hidden(lv_obj_t*obj,bool enable){
    if(enable){
        lv_obj_add_flag(obj,LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_remove_flag(obj,LV_OBJ_FLAG_HIDDEN);
    }
}
// 输入框焦点事件（动态创建/销毁键盘）
static void on_ta_focus(lv_event_t *e) {
    lv_event_code_t code= lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (code == LV_EVENT_FOCUSED) {
        g_kb = lv_keyboard_create(lv_layer_top());  // 顶层显示键盘
        lv_keyboard_set_textarea(g_kb, ta);
    } else if (code == LV_EVENT_DEFOCUSED) {
        lv_obj_del(g_kb);
        g_kb = NULL;
    }
}
// 连接按钮事件（模拟连接过程）
static void func(lv_timer_t *t) {
    lv_obj_t*obj =  lv_timer_get_user_data(t);
    lv_obj_del(obj);
    lv_timer_del(t);
}
static void on_connect(lv_event_t *e) {
    lv_obj_t *btn = lv_event_get_target(e);
    lv_label_set_text(lv_obj_get_child(btn, 0), "Connecting...");
    ui_pop();  // 返回上一级
    lv_obj_t *toast = lv_label_create(lv_scr_act());
    lv_label_set_text(toast, "Connected!");
    lv_obj_align(toast, LV_ALIGN_CENTER, 0, 0);
    lv_timer_create(func, 2000, toast);
}

void ui_wifi_connect_create(void) {
    if (g_connect_screen) return;

    g_connect_screen = lv_obj_create(NULL);
    lv_obj_set_size(g_connect_screen,LV_PCT(100),LV_PCT(100)); 
    lv_obj_set_style_pad_all(g_connect_screen,0,0);
    lv_obj_set_hidden(g_connect_screen,true);
    // 标题显示SSID
    lv_obj_t *title = lv_label_create(g_connect_screen);
    lv_label_set_text_fmt(title, "Connect to: %s", g_state.selected_ssid);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    // 密码输入框
    lv_obj_t *ta = lv_textarea_create(g_connect_screen);
    lv_textarea_set_password_mode(ta, true);
    lv_textarea_set_one_line(ta, true);
    lv_obj_set_width(ta, LV_PCT(80));
    lv_obj_align(ta, LV_ALIGN_CENTER, 0, -30);
    lv_obj_add_event_cb(ta, on_ta_focus, LV_EVENT_ALL, NULL);

    // 按钮行
    lv_obj_t *btn_row = lv_obj_create(g_connect_screen);
    lv_obj_set_size(btn_row, LV_PCT(80), 40);
    lv_obj_align(btn_row, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_set_flex_flow(btn_row, LV_FLEX_FLOW_ROW);

    lv_obj_t *cancel_btn = lv_btn_create(btn_row);
    lv_obj_add_event_cb(cancel_btn, ui_pop, LV_EVENT_CLICKED, NULL);
    lv_obj_t* cancel = lv_label_create(cancel_btn);
    lv_label_set_text(cancel,"Cancel");

    lv_obj_t *connect_btn = lv_btn_create(btn_row);
    lv_obj_add_event_cb(connect_btn, on_connect, LV_EVENT_CLICKED, NULL);
    lv_obj_t* connect_label = lv_label_create(connect_btn);
    lv_label_set_text(connect_label,"Connect");
}

void ui_wifi_connect_show(void) {
    lv_obj_remove_flag(g_connect_screen,LV_OBJ_FLAG_HIDDEN);
    lv_scr_load_anim(g_connect_screen, LV_SCR_LOAD_ANIM_OVER_TOP, 300, 0, false);
}

void ui_wifi_connect_hide(void) {
    if (g_kb) lv_obj_del(g_kb);  // 确保键盘被销毁
    lv_obj_add_flag(g_connect_screen,LV_OBJ_FLAG_HIDDEN);
}
const UiScreenOps g_wifi_connect_ops = {
    .create = ui_wifi_connect_create,
    .show = ui_wifi_connect_show,
    .hide = ui_wifi_connect_hide
};
