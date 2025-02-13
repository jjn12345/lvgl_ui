// ui_manager.c
#include "ui_manager.h"
#include "app_state.h"

volatile AppState g_state = {0};  // 全局状态初始化


static UiScreenOps s_screen_ops[UI_SCREEN_MAX];
static UiScreenID s_screen_stack[UI_STACK_DEPTH];
static int s_stack_top = -1;

void ui_register_screen(UiScreenID id, 
                       void (*create)(void),
                       void (*show)(void),
                       void (*hide)(void)) {
    s_screen_ops[id] = (UiScreenOps){
        .create = create,
        .show = show,
        .hide = hide,
        .is_created = false,
        .is_persistent = (id == UI_SCREEN_HOME)  // 主界面常驻
    };
}

// 界面切换逻辑（按需创建）
void ui_push(UiScreenID screen_id) {
    if (s_stack_top >= UI_STACK_DEPTH-1) return;

    UiScreenOps *new_ops = &s_screen_ops[screen_id];
    if (!new_ops->is_created) {
        new_ops->create();
        new_ops->is_created = true;
    }

    if (s_stack_top >= 0) {
        UiScreenOps *old_ops = &s_screen_ops[s_screen_stack[s_stack_top]];
        if (old_ops->hide) old_ops->hide();
    }

    new_ops->show();
    s_screen_stack[++s_stack_top] = screen_id;
}
// 弹出界面栈（返回上一级）
void ui_pop(void) {
    if (s_stack_top < 0) return;
    
    const UiScreenOps *old_ops = &s_screen_ops[s_screen_stack[s_stack_top]];
    if (old_ops->hide) old_ops->hide();
    s_stack_top--;
    
    if (s_stack_top >= 0) {
        const UiScreenOps *new_ops = &s_screen_ops[s_screen_stack[s_stack_top]];
        if (new_ops->show) new_ops->show();
    }
}

// 初始化所有界面（仅创建一次）
void ui_init(void) {
    ui_push(UI_SCREEN_HOME);
}
