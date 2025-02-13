// ui_wifi.c
#include "ui_wifi.h"
#include "app_state.h"
#include <lvgl/lvgl.h>


static lv_obj_t *g_wifi_screen = NULL;
static lv_obj_t *g_switch = NULL;
static lv_obj_t *g_ap_list = NULL;

// WIFI开关事件
static void lv_obj_set_hidden(lv_obj_t*obj,bool enable){
    if(enable){
        lv_obj_add_flag(obj,LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_remove_flag(obj,LV_OBJ_FLAG_HIDDEN);
    }
}

static void on_wifi_switch(lv_event_t *e) {
    lv_obj_t *sw = lv_event_get_target(e);
    g_state.wifi_enabled = lv_obj_has_state(sw, LV_STATE_CHECKED);
    lv_obj_set_hidden(g_ap_list, !g_state.wifi_enabled);  // 显示/隐藏AP列表
}

// AP点击事件
static void on_ap_click(lv_event_t *e) {
    lv_obj_t *btn = lv_event_get_target(e);
    const char *ssid = lv_list_get_btn_text(g_ap_list, btn);
    strncpy(g_state.selected_ssid, ssid, sizeof(g_state.selected_ssid));
    ui_push(UI_SCREEN_WIFI_CONNECT);  // 进入连接界面
}

void ui_wifi_create(void) {
    if (g_wifi_screen) return;
    
    g_wifi_screen = lv_obj_create(NULL);
    lv_obj_set_size(g_wifi_screen,LV_PCT(100),LV_PCT(100)); 
    lv_obj_set_style_pad_all(g_wifi_screen,0,0);
    lv_obj_set_hidden(g_wifi_screen,true);
    // 返回按钮（固定在顶部）
    lv_obj_t *back_btn = lv_btn_create(g_wifi_screen);
    lv_obj_align(back_btn, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(back_btn, ui_pop, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label = lv_label_create(back_btn);
    lv_label_set_text(label, LV_SYMBOL_LEFT " Back");
    // WIFI开关行
    lv_obj_t *sw_row = lv_obj_create(g_wifi_screen);
    lv_obj_set_size(sw_row, LV_PCT(100), 40);
    lv_obj_align(sw_row, LV_ALIGN_TOP_MID, 0, 50);

    lv_obj_t *sw_label = lv_label_create(sw_row);
    lv_label_set_text(sw_label, "WIFI:");
    lv_obj_align(sw_label, LV_ALIGN_LEFT_MID, 10, 0);

    g_switch = lv_switch_create(sw_row);
    lv_obj_align(g_switch, LV_ALIGN_RIGHT_MID, -10, 0);
    lv_obj_add_event_cb(g_switch, on_wifi_switch, LV_EVENT_VALUE_CHANGED, NULL);

    // AP列表（初始隐藏）
    g_ap_list = lv_list_create(g_wifi_screen);
    lv_obj_set_size(g_ap_list, LV_PCT(90), LV_PCT(60));
    lv_obj_align(g_ap_list, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_set_hidden(g_ap_list, true);

    // 模拟AP数据（实际应从WIFI驱动读取）
    const char* aps[] = {"Home_AP", "Office_AP", "Guest_AP"};
    for (int i = 0; i < 3; i++) {
        lv_obj_t *btn = lv_list_add_btn(g_ap_list, LV_SYMBOL_WIFI, aps[i]);
        lv_obj_add_event_cb(btn, on_ap_click, LV_EVENT_CLICKED, NULL);
    }
}


void ui_wifi_show(void) {
    
    lv_obj_set_state(g_switch, LV_STATE_CHECKED,g_state.wifi_enabled);
    lv_obj_set_hidden(g_ap_list, !g_state.wifi_enabled);
    lv_obj_set_hidden(g_wifi_screen,false);
    lv_scr_load_anim(g_wifi_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
}

void ui_wifi_hide(void) {
    // 保持界面对象，仅隐藏
    lv_obj_add_flag(g_wifi_screen,LV_OBJ_FLAG_HIDDEN);
}
const UiScreenOps g_wifi_ops = {
    .create = ui_wifi_create,
    .show = ui_wifi_show,
    .hide = ui_wifi_hide,
};
