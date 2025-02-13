// app_state.h
#pragma once
#include <stdbool.h>

// 全局状态（保证原子性访问）
typedef struct {
    bool wifi_enabled;       // WIFI开关状态
    char selected_ssid[32];  // 当前选中的AP名称
    char password[64];       // 输入的密码
} AppState;

extern volatile AppState g_state;  // 声明全局状态（volatile防止编译器优化）