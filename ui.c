#include "ui.h"
#include "ui_manager.h"
#include "ui_home.h"
#include "ui_wifi.h"
#include "ui_wifi_connect.h"

LV_FONT_DECLARE(lv_font_chinese)    /* 声明中文字库 */
#define USE_DEMO        1
#define USE_DEMO1       0
#define USE_DEMO2       1
/* 互斥锁 */
#define lvgl_port_lock(x)       LV_UNUSED(x)
#define lvgl_port_unlock()      LV_UNUSED(0)
#define assert(x)               x

#if !USE_DEMO    
static lv_obj_t* root_screen = NULL;     /*根屏幕,后续所有屏幕基于此屏幕创建 */


static void ui_init(void){
    root_screen = lv_screen_active();
}
/* 大小 */
void ui_size(void){
    lv_obj_t * sub_obj;
    int32_t obj_h = 0;
    int32_t obj_w = 0;
    int32_t content_w;
    int32_t content_h;
    sub_obj = lv_obj_create(root_screen);
    // lv_obj_set_size(sub_obj,120,100);
    lv_obj_set_width(sub_obj,LV_PCT(70));
    lv_obj_set_height(sub_obj,LV_PCT(70));
    lv_obj_update_layout(sub_obj);
    obj_w = lv_obj_get_width(sub_obj);
    obj_h = lv_obj_get_height(sub_obj);
    content_w = lv_obj_get_content_width(sub_obj);
    content_h = lv_obj_get_content_height(sub_obj);
    LV_LOG_USER("obj_w:obj_h --- %d:%d",obj_w,obj_h);
    LV_LOG_USER("content_w:content_h --- %d:%d",content_w,content_h);

}
/* 位置 */
void ui_pos(void){
    lv_obj_t * sub_obj;
    lv_obj_t * sub_obj2;
    lv_obj_t * lable;
    lv_obj_t * lable2;
    int32_t obj_x = 0;
    int32_t obj_y = 0;
    int32_t obj_x2 = 0;
    int32_t obj_y2 = 0;
    sub_obj = lv_obj_create(root_screen);
    lv_obj_set_size(sub_obj,LV_PCT(30),LV_PCT(30));
    lv_obj_align(sub_obj,LV_ALIGN_CENTER,0,0);
    // sub_obj2 = lv_obj_create(root_screen);
    // lv_obj_set_size(sub_obj2,LV_PCT(20),LV_PCT(20));
    // lv_obj_align(sub_obj2,LV_ALIGN_CENTER,0,0);

    lable = lv_label_create(sub_obj);
    lv_label_set_text_fmt(lable,"test");
    lv_obj_align(lable,LV_ALIGN_CENTER,0,0);

    lv_obj_update_layout(sub_obj);

    obj_x = lv_obj_get_x(sub_obj);
    obj_y = lv_obj_get_y(sub_obj);
    obj_x2 = lv_obj_get_x2(sub_obj);
    obj_y2 = lv_obj_get_y2(sub_obj);
    LV_LOG_USER("obj_x:obj_y --- %d:%d",obj_x,obj_y);
    LV_LOG_USER("obj_x2:obj_y2 --- %d:%d",obj_x2,obj_y2);
    LV_LOG_USER("x_align:y_align --- %d:%d",lv_obj_get_x_aligned(sub_obj),lv_obj_get_y_aligned(sub_obj));
    // lable2 = lv_label_create(sub_obj2);
    // lv_label_set_text_fmt(lable2,"test2");
    // lv_obj_align(lable2,LV_ALIGN_CENTER,0,0);

    // lv_obj_align_to(sub_obj2,sub_obj,LV_ALIGN_OUT_LEFT_MID,0,0);

    // lv_obj_set_x(sub_obj,100);
    // lv_obj_set_y(sub_obj,100);
    // lv_obj_set_pos(sub_obj,100,100);
    // lv_obj_set_align(sub_obj,LV_ALIGN_CENTER);
    // lv_obj_align(sub_obj,LV_ALIGN_CENTER,0,0);
}
/* 盒子模型 */
typedef enum{
    mid_box = 0,
    t_mid_box,
    b_mid_box,
    left_box,
    t_left_box,
    b_left_box,
    right_box,
    t_right_box,
    b_right_box,
}box_type;
void ui_box_model(void){
    uint16_t box_size = 40;
    uint8_t i = 0;
    lv_obj_t * box[9];
    static lv_style_t   box_style;
    lv_style_init(&box_style);
    lv_style_set_size(&box_style,box_size,box_size);
    lv_color_t border_color = {
        .blue = 16,
        .red  = 180,
        .green = 95,
    };
    for(i = 0;i<9;i++){
        box[i] = lv_obj_create(root_screen);
        lv_obj_add_style(box[i],&box_style,LV_PART_MAIN);
    }
    lv_obj_set_pos(box[mid_box],100,100);
    lv_obj_align_to(box[left_box],box[mid_box],LV_ALIGN_OUT_LEFT_MID,0,0);
    lv_obj_align_to(box[right_box],box[mid_box],LV_ALIGN_OUT_RIGHT_MID,0,0);

    lv_obj_align_to(box[t_mid_box],box[mid_box],LV_ALIGN_OUT_TOP_MID,0,0);
    lv_obj_align_to(box[t_left_box],box[t_mid_box],LV_ALIGN_OUT_LEFT_MID,0,0);
    lv_obj_align_to(box[t_right_box],box[t_mid_box],LV_ALIGN_OUT_RIGHT_MID,0,0);

    lv_obj_align_to(box[b_mid_box],box[mid_box],LV_ALIGN_OUT_BOTTOM_MID,0,0);
    lv_obj_align_to(box[b_left_box],box[b_mid_box],LV_ALIGN_OUT_LEFT_MID,0,0);
    lv_obj_align_to(box[b_right_box],box[b_mid_box],LV_ALIGN_OUT_RIGHT_MID,0,0);




}
/* 样式 */
void ui_style(void){
    /* 添加对象 */
    lv_obj_t * sub_obj1 = lv_obj_create(root_screen);
    lv_obj_t * sub_obj2 = lv_obj_create(root_screen);
    lv_obj_t * label1 = lv_label_create(sub_obj1);
    lv_obj_t * label2 = lv_label_create(sub_obj2);
    /* 按钮 */
    lv_obj_t * btn1 = lv_button_create(sub_obj1);
    lv_obj_t * btn2 = lv_button_create(sub_obj2);
    lv_label_set_text_fmt(label1,"label1");
    lv_label_set_text_fmt(label2,"label2");
    lv_obj_align(label1,LV_ALIGN_CENTER,0,0);
    lv_obj_align(label2,LV_ALIGN_CENTER,0,0);
    lv_obj_align(sub_obj1,LV_ALIGN_LEFT_MID,0,0);
    lv_obj_align(sub_obj2,LV_ALIGN_RIGHT_MID,0,0);
    lv_obj_align(btn1,LV_ALIGN_BOTTOM_MID,0,0);
    lv_obj_align(btn2,LV_ALIGN_BOTTOM_MID,0,0);
    /* 本地样式 */
    // lv_color_t obj1_bg_color = {
    //     .blue = 0,
    //     .green = 0xf3,
    //     .red = 0x90,
    // };
    // lv_obj_set_style_bg_color(sub_obj1,obj1_bg_color,0);
    // lv_obj_set_style_bg_color(sub_obj2,lv_color_hex(0x109254),0);
    // lv_obj_set_style_size(sub_obj1,100,100,0);
    // lv_obj_set_style_size(sub_obj2,100,100,0);

    /* 正常样式 */
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_size(&style,100,100);
    lv_style_set_bg_color(&style,lv_color_hex(0x963214));
    lv_style_set_border_width(&style,2);

    /* 添加样式到对象 */
    lv_obj_add_style(sub_obj1,&style,0);
    lv_obj_add_style(sub_obj2,&style,0);
}

/* 滚动条 */
static void slider_scroll(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* label = lv_event_get_user_data(e);
    lv_obj_t* slider = lv_event_get_target_obj(e);
    if(lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED){
        lv_label_set_text_fmt(label,"%d%%",lv_slider_get_value(slider));
    }
}
void ui_slider(void){
    /* 创建对象 */
    lv_obj_t* sub_screen;
    lv_obj_t* slider;
    lv_obj_t* label;
    sub_screen = lv_obj_create(root_screen);
    slider = lv_slider_create(sub_screen);
    label = lv_label_create(sub_screen);
    /* 设定基本属性 */
    lv_obj_align(sub_screen,LV_ALIGN_CENTER,0,0);
    lv_obj_set_size(sub_screen,LV_PCT(80),LV_PCT(80));
    lv_slider_set_mode(slider,LV_SLIDER_MODE_NORMAL);    /* 设定模式 */
    lv_slider_set_range(slider,0,100);          /* 设定范围 */
    lv_slider_set_value(slider,0,LV_ANIM_ON);   /* 设定初始值 */
    lv_label_set_text_fmt(label,"%d%%",lv_slider_get_value(slider));
    /* 设定过渡样式 */
    static const lv_style_prop_t trans_props[] = {
                                            LV_STYLE_BG_OPA, LV_STYLE_BG_COLOR,0, /*End marker*/
    };

    static lv_style_transition_dsc_t trans;
    lv_style_transition_dsc_init(&trans, trans_props, lv_anim_path_ease_out, 500, 0,NULL);



    /* 创建样式 */
    static lv_style_t slider_main_style;            /* 滚动条背景 */
    static lv_style_t slider_indicator_style;       /* 滚动条指示器 */
    static lv_style_t slider_knob_style;            /* 滚动条旋钮 */
    static lv_style_t slider_knob_press_style;      /* 滚动条旋钮按下 */

    lv_style_init(&slider_main_style);
    lv_style_init(&slider_indicator_style);
    lv_style_init(&slider_knob_style);
    lv_style_init(&slider_knob_press_style);
    /* 背景样式 */
    lv_style_set_bg_color(&slider_main_style,lv_color_hex(0x01979d));
    lv_style_set_width(&slider_main_style,LV_PCT(80));
    lv_obj_add_style(slider,&slider_main_style,LV_PART_MAIN);
    /* 指示器样式 */
    lv_style_set_bg_opa(&slider_indicator_style,LV_OPA_COVER);
    lv_style_set_bg_color(&slider_indicator_style,lv_color_hex(0x01979d));
    lv_style_set_radius(&slider_indicator_style,LV_RADIUS_CIRCLE);
    lv_obj_add_style(slider,&slider_indicator_style,LV_PART_INDICATOR);
    /* 旋钮样式 */
    lv_style_set_bg_color(&slider_knob_style,lv_color_hex(0x01979d));
    lv_style_set_border_color(&slider_knob_style,lv_color_hex(0xffffff));
    lv_style_set_border_width(&slider_knob_style,2);
    lv_style_set_border_opa(&slider_knob_style,LV_OPA_70);
    lv_style_set_radius(&slider_knob_style,LV_RADIUS_CIRCLE);
    lv_style_set_pad_all(&slider_knob_style,6);
    lv_style_set_transition(&slider_knob_style, &trans);
    lv_obj_add_style(slider,&slider_knob_style,LV_PART_KNOB);

    /*  旋钮按下和悬浮 */
    lv_style_set_bg_color(&slider_knob_press_style,lv_color_hex(0x0c548b));
    lv_style_set_transition(&slider_knob_press_style, &trans);
    lv_obj_add_style(slider,&slider_knob_press_style,LV_PART_KNOB | LV_PART_INDICATOR |LV_STATE_PRESSED);

    lv_obj_align_to(label,slider,LV_ALIGN_OUT_BOTTOM_MID,0,0);
    /* 为滚动条添加事件 */
    lv_obj_add_event_cb(slider,slider_scroll,LV_EVENT_VALUE_CHANGED,label);
}
/* 任务事件 */
static void button_event(lv_event_t * e){
    static uint16_t click_nums = 0;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* label = lv_event_get_user_data(e);
    lv_obj_t* button = lv_event_get_current_target(e);
    switch(code){
        case LV_EVENT_RELEASED:{
            lv_label_set_text_fmt(label,"%d",++click_nums);
        }
        break;
    }
}
void ui_event(void){
    lv_obj_t* sub_screen;
    lv_obj_t* button;
    static lv_obj_t* label;
    static const lv_style_prop_t trans_props[] = {
        LV_STYLE_BG_COLOR,LV_STYLE_BG_OPA,
        0,
    };
    static lv_style_transition_dsc_t button_trans;
    lv_style_transition_dsc_init(&button_trans,trans_props,lv_anim_path_ease_in,300,0,NULL);

    /* 创建对象 */
    sub_screen = lv_obj_create(root_screen);
    button = lv_button_create(sub_screen);
    label = lv_label_create(button);
    lv_obj_set_align(label,LV_ALIGN_CENTER);
    /* 设置样式 */
    /* 按键基本样式 */
    static lv_style_t button_style;
    lv_style_init(&button_style);
    lv_style_set_size(&button_style,60,40);
    lv_style_set_bg_color(&button_style,lv_color_hex(0x181818));
    lv_style_set_bg_opa(&button_style,LV_OPA_80);
    lv_style_set_align(&button_style,LV_ALIGN_CENTER);
    /* 按键按下样式 */
    static lv_style_t button_press_style;
    lv_style_init(&button_press_style);
    lv_style_set_bg_color(&button_press_style,lv_color_hex(0x0c548b));
    lv_style_set_bg_opa(&button_press_style,LV_OPA_100);
    lv_style_set_transition(&button_press_style,&button_trans);

    /* 添加样式 */
    lv_obj_add_style(button,&button_style,LV_PART_MAIN);
    lv_obj_add_style(button,&button_press_style,LV_PART_MAIN|LV_STATE_PRESSED);
    lv_label_set_text(label,"click");


    /* 为按键添加事件 */
    lv_obj_add_event_cb(button,button_event,LV_EVENT_ALL,label);
}

/* 任务冒泡 */
static void bubbing_event(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);            /* 获取事件代码 */
    lv_obj_t * now_obj = lv_event_get_current_target(e);    /* 获取当前触发对象 */
    lv_obj_t * label = lv_event_get_user_data(e);           /* 获取传过来的用户数据 */
    lv_obj_t * tar_obj = lv_event_get_target_obj(e);        /* 获取最初的触发对象 */
    switch (code){
        case LV_EVENT_PRESSED:{
            lv_obj_set_style_bg_color(now_obj,lv_color_hex(0xc2685c),0);
            lv_label_set_text(label,"bubbing event triggered");
        }
        break;
        case LV_EVENT_RELEASED:{
            lv_obj_remove_local_style_prop(now_obj,LV_STYLE_BG_COLOR,0);
            lv_label_set_text(label,"I am in root_screen");
        }
        break;
    }
}
void ui_event_bubbing(void){
    /* 创建对象 */
    lv_obj_t* s_screen = lv_obj_create(root_screen);
    lv_obj_t* ss_screen = lv_obj_create(s_screen);
    lv_obj_t* sss_screen = lv_obj_create(ss_screen);
    lv_obj_t* label = lv_label_create(root_screen);
    lv_obj_t* button = lv_button_create(sss_screen);
    lv_obj_t* b_label = lv_label_create(button);

    /* 设置控件属性 */
    lv_label_set_text(label,"I am in root_screen");
    lv_obj_align(label,LV_ALIGN_TOP_MID,0,0);
    lv_obj_set_size(button,50,20);
    lv_obj_set_align(button,LV_ALIGN_CENTER);
    lv_obj_set_align(b_label,LV_ALIGN_CENTER);
    lv_label_set_text(b_label,"click");

    /* 设置屏幕样式 */
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_align(&style,LV_ALIGN_CENTER);
    lv_style_set_size(&style,LV_PCT(80),LV_PCT(80));

    lv_obj_add_style(s_screen,&style,0);
    lv_obj_add_style(ss_screen,&style,0);
    lv_obj_add_style(sss_screen,&style,0);

    /* 为每一个屏幕启动事件冒泡 */
    lv_obj_add_flag(s_screen,LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ss_screen,LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(sss_screen,LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(button,LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_add_event_cb(root_screen,bubbing_event,LV_EVENT_ALL,label);
}

/* lv定时器 */
static void timer1_cb (lv_timer_t *timer){
    static uint16_t run_sum = 0;
    lv_obj_t* label = lv_timer_get_user_data(timer);
    LV_LOG_USER("timer1 run");
    run_sum++;
    lv_label_set_text_fmt(label,"timer1 run_sum: %d",run_sum);
}
static void timer2_cb (lv_timer_t *timer){
    lv_timer_t* user_timer = lv_timer_get_user_data(timer);
    LV_LOG_USER("timer2 run");
    lv_timer_pause(user_timer);
}
static void timer3_cb (lv_timer_t *timer){
    lv_timer_t* user_timer = lv_timer_get_user_data(timer);
    LV_LOG_USER("timer3 run");
    lv_timer_resume(user_timer);
}
void ui_timer(void){
    lv_timer_t* timer1 = NULL;
    lv_timer_t* timer2 = NULL;
    lv_timer_t* timer3 = NULL;
    lv_obj_t* label = lv_label_create(root_screen);

    timer1 = lv_timer_create(timer1_cb,1000,label);
    lv_timer_ready(timer1);     /* 在下一次的lv_task_handler中立刻执行 */
    timer2 = lv_timer_create(timer2_cb,6000,timer1);
    lv_timer_set_repeat_count(timer2,1);
    timer3 = lv_timer_create_basic();
    lv_timer_set_cb(timer3,timer3_cb);
    lv_timer_set_user_data(timer3,timer1);
    lv_timer_set_period(timer3,8000);
    lv_timer_set_repeat_count(timer3,1);


}

/* label */
void ui_label(void){
    static char text[] = "static test";
    lv_obj_t* label1 = lv_label_create(root_screen);
    lv_obj_t* label2 = lv_label_create(root_screen);
    lv_obj_t* label3 = lv_label_create(root_screen);

    lv_obj_align_to(label2,label1,LV_ALIGN_OUT_BOTTOM_MID,0,0);
    lv_obj_align_to(label3,label2,LV_ALIGN_OUT_BOTTOM_MID,0,0);

    lv_obj_set_width(label3,80);

    lv_label_set_text(label1,"test");
    lv_label_set_text_static(label2,text);
    lv_label_set_text(label3,LV_SYMBOL_WIFI "abcdefghijklmnopqrstuvwxyz");
    // lv_label_set_long_mode(label3,LV_LABEL_LONG_DOT);
    // lv_label_set_long_mode(label3,LV_LABEL_LONG_SCROLL);
    lv_label_set_long_mode(label3,LV_LABEL_LONG_SCROLL_CIRCULAR);

    lv_obj_set_style_text_font(label3,&lv_font_montserrat_30,0);
}

/* switch */
static void sw_evt_cb(lv_event_t* e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* sw = lv_event_get_target_obj(e);
    if(code == LV_EVENT_VALUE_CHANGED){
      LV_LOG_USER("sw state: %s",lv_obj_has_state(sw,LV_STATE_CHECKED)?"OPEN":"CLOSE");
    }
}
void ui_switch(void){
    lv_obj_t*sub_screen = lv_obj_create(root_screen);
    lv_obj_align(sub_screen,LV_ALIGN_CENTER,0,0);

    lv_obj_t*sw = lv_switch_create(sub_screen);
    lv_obj_align(sw,LV_ALIGN_CENTER,0,0);
    // lv_obj_remove_state(sw,LV_STATE_CHECKED);   /* 将状态变为关闭 */
    // lv_obj_add_state(sw,LV_STATE_CHECKED);   /* 将状态变为开启 */
    lv_obj_add_event_cb(sw,sw_evt_cb,LV_EVENT_ALL,NULL);

}

/* led */
static void slider_led_evt(lv_event_t* e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* led = lv_event_get_user_data(e);
    lv_obj_t*slider = lv_event_get_target_obj(e);
    int32_t slider_value = lv_slider_get_value(slider);
    if(code == LV_EVENT_VALUE_CHANGED){
        if(slider_value > 0){
            lv_led_on(led);
            lv_led_set_brightness(led,slider_value);
        }
        else{
            lv_led_off(led);
        }
    }

}
static void switch_led_evt(lv_event_t* e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* led = lv_event_get_user_data(e);
    lv_obj_t* sw = lv_event_get_target_obj(e);
    if(code == LV_EVENT_VALUE_CHANGED){
        if(lv_obj_has_state(sw,LV_STATE_CHECKED)){
            lv_led_on(led);
        }
        else{
            lv_led_off(led);
        }
    }
}
void ui_led(void){
    /* 创建对象 */
    lv_obj_t* sub_screen1 = lv_obj_create(root_screen);
    lv_obj_t* slider = lv_slider_create(root_screen);
    lv_obj_t* led1 = lv_led_create(sub_screen1);

    lv_obj_t* sub_screen2 = lv_obj_create(root_screen);
    lv_obj_t* sw = lv_switch_create(root_screen);
    lv_obj_t* led2 = lv_led_create(sub_screen2);
    /* 布局  */
    lv_obj_set_size(sub_screen1,LV_PCT(30),LV_PCT(30));
    lv_obj_set_size(sub_screen2,LV_PCT(30),LV_PCT(30));
    lv_obj_set_width(slider,lv_obj_get_width(sub_screen1) / 2);
    lv_obj_set_size(sw,40,25);
    lv_obj_update_layout(sub_screen1);
    lv_obj_update_layout(sub_screen2);
    lv_obj_update_layout(slider);
    lv_obj_update_layout(sw);
    lv_obj_align(led1,LV_ALIGN_CENTER,0,0);
    lv_obj_align(led2,LV_ALIGN_CENTER,0,0);
    lv_obj_align(sub_screen1,LV_ALIGN_LEFT_MID,30,-40);
    lv_obj_align(sub_screen2,LV_ALIGN_RIGHT_MID,-30,-40);
    lv_obj_align_to(slider,sub_screen1,LV_ALIGN_OUT_BOTTOM_MID,0,0);
    lv_obj_align_to(sw,sub_screen2,LV_ALIGN_OUT_BOTTOM_MID,-20,-10);

    /* 设置颜色 */
    lv_led_set_color(led1,lv_color_hex(0xff0000));
    lv_led_set_color(led2,lv_color_hex(0x00ff00));

    /* 设置初始状态 */
    lv_led_off(led1);
    lv_led_off(led2);
    lv_obj_remove_state(sw,LV_STATE_CHECKED);
    lv_slider_set_range(slider,0,255);
    lv_slider_set_value(slider,0,LV_ANIM_ON);

    /* 为滚动条和开关添加事件 */
    lv_obj_add_event_cb(slider,slider_led_evt,LV_EVENT_ALL,led1);
    lv_obj_add_event_cb(sw,switch_led_evt,LV_EVENT_ALL,led2);
}

/* list */
static void list_handle1(lv_event_t*e){
    lv_event_code_t code = lv_event_get_code(e);
    void* user_data = lv_event_get_user_data(e);
    lv_obj_t* current_obj = lv_event_get_current_target(e);
    lv_obj_t* tar_obj = lv_event_get_target_obj(e);
    if(code == LV_EVENT_CLICKED){
        LV_LOG_USER("CLICKED:  %s",lv_list_get_button_text((lv_obj_t*)user_data,current_obj));
    }
}
void ui_list(void){
    /* 创建列表并设置基本的布局 */
    lv_obj_t* s_screen = lv_obj_create(root_screen);
    static lv_style_t screen_style;
    lv_style_init(&screen_style);
    lv_style_set_size(&screen_style,LV_PCT(100),LV_PCT(100));
    lv_style_set_align(&screen_style,LV_ALIGN_CENTER);
    lv_obj_add_style(s_screen,&screen_style,0);

    lv_obj_t* list = lv_list_create(s_screen);
    static lv_style_t list_style;
    lv_style_init(&list_style);
    lv_style_set_size(&list_style,LV_PCT(80),LV_PCT(80));
    lv_style_set_align(&list_style,LV_ALIGN_CENTER);
    lv_obj_add_style(list,&list_style,0);

    /* 测试列表的用法 */
    lv_obj_t* btn; /* 获取列表中的按键 */
    lv_list_add_text(list,"Connectivity");
    btn = lv_list_add_button(list,LV_SYMBOL_WIFI,"WIFI");
    lv_obj_add_event_cb(btn,list_handle1,LV_EVENT_CLICKED,list);
    btn = lv_list_add_button(list,LV_SYMBOL_BLUETOOTH,"Bluetooth");
    lv_obj_add_event_cb(btn,list_handle1,LV_EVENT_CLICKED,list);
    btn = lv_list_add_button(list,LV_SYMBOL_GPS,"GPS");
    lv_obj_add_event_cb(btn,list_handle1,LV_EVENT_CLICKED,list);
    btn = lv_list_add_button(list,LV_SYMBOL_USB,"USB");
    lv_obj_add_event_cb(btn,list_handle1,LV_EVENT_CLICKED,list);
    btn = lv_list_add_button(list,LV_SYMBOL_BATTERY_FULL,"Battery");
    lv_obj_add_event_cb(btn,list_handle1,LV_EVENT_CLICKED,list);
}

/* KeyBoard */
static void ta_handle(lv_event_t*e){
    lv_event_code_t code = lv_event_get_code(e);    /* 获取事件代码 */
    lv_obj_t* user_data = lv_event_get_user_data(e);    /* 获取用户数据 */
    lv_obj_t* tar_obj = lv_event_get_target_obj(e); /* 获取最初触发对象 */
    switch(code){
        case LV_EVENT_FOCUSED:{
            lv_keyboard_set_textarea(user_data,tar_obj);
            lv_obj_remove_flag(user_data,LV_OBJ_FLAG_HIDDEN);   /* 显示键盘 */
        }
        break;
        case LV_EVENT_DEFOCUSED:{
            lv_keyboard_set_textarea(user_data,NULL);
            lv_obj_add_flag(user_data,LV_OBJ_FLAG_HIDDEN);   /* 隐藏键盘 */
        }
        break;
    }
}
static void kb_handle(lv_event_t*e){
    lv_event_code_t code = lv_event_get_code(e);    /* 获取事件代码 */
    lv_obj_t* user_data = lv_event_get_user_data(e);    /* 获取用户数据 */
    lv_obj_t* tar_obj = lv_event_get_target_obj(e); /* 获取最初触发对象 */
    switch(code){
        case LV_EVENT_READY:{
            lv_obj_t* ta = lv_keyboard_get_textarea(tar_obj);
            LV_LOG_USER("%s: %s",lv_textarea_get_placeholder_text(ta),lv_textarea_get_text(ta));
        }
        break;
        case LV_EVENT_CANCEL:{
            lv_obj_add_flag(user_data,LV_OBJ_FLAG_HIDDEN);   /* 隐藏键盘 */
        }
        break;
    }

}
void ui_key_board(void){

    lv_obj_t* key_board = lv_keyboard_create(root_screen);
    lv_obj_t* text_area = lv_textarea_create(root_screen);
    lv_obj_t* text_area2 = lv_textarea_create(root_screen);
    lv_obj_set_width(text_area,70);
    lv_obj_set_width(text_area2,70);
    lv_obj_align(text_area2,LV_ALIGN_TOP_RIGHT,0,0);
    lv_textarea_set_one_line(text_area2,true);   /* 设置单行 */
    lv_textarea_set_one_line(text_area,true);   /* 设置单行 */
    lv_textarea_set_placeholder_text(text_area,"SSID");
    lv_textarea_set_placeholder_text(text_area2,"PWD");
    lv_obj_add_event_cb(text_area,ta_handle,LV_EVENT_ALL,key_board);
    lv_obj_add_event_cb(text_area2,ta_handle,LV_EVENT_ALL,key_board);


    lv_keyboard_set_mode(key_board,LV_KEYBOARD_MODE_TEXT_LOWER); /*设置模式为小写模式 */
    lv_keyboard_set_popovers(key_board,true);   /* 按下按键后弹出对应提示框 */
    lv_obj_add_flag(key_board,LV_OBJ_FLAG_HIDDEN);  /* 隐藏键盘 */
    lv_obj_add_event_cb(key_board,kb_handle,LV_EVENT_ALL,NULL);


}
#endif

#if USE_DEMO1
static lv_obj_t* root_screen = NULL;     /*根屏幕,后续所有屏幕基于此屏幕创建 */


static void ui_init(void){
    root_screen = lv_screen_active();
}
/* demo 1 */
#include "link_list.h"
/* 页面枚举和全局变量 *//* 页面枚举和全局变量 */
typedef enum{
    top_block = 0,
    main_block,
    bottom_block,
    right_block,
    block_count,
}page_block_t;
typedef enum{
    main_screen = 0,
    wifi_screen,
    screen_count,
}screen_t;
#define BLOCK_BORDER_WIDTH        0                         /* 区块的边框宽度 */
static lv_obj_t* block_screen;                              /* 区块的屏幕 */
static lv_obj_t* page_block[block_count];                   /* 整个页面的区块 */
static lv_style_t indicator_style;                          /* 屏幕指示器的统一样式 */
static lv_obj_t**indicator;                                 /* 屏幕指示器(根据分支节点数动态创建) */
static lv_obj_t* screen[screen_count];                      /* 屏幕 */
static lv_obj_t* screen_info[screen_count];                 /* 用于显示具体信息的屏幕 */
#define current_screen  (screen_t)(screen_list.head->data)    /* 当前屏幕永远是屏幕链表的头结点的数据 */
static dlist_t  screen_list = {0};
/* 内存池 */
static uint8_t ui_mem_buffer[4096];
static mem_pool_t ui_mem_pool;
static void block_init(void){
    /* 创建page_block */
    page_block[top_block] = lv_obj_create(block_screen);
    page_block[main_block] = lv_obj_create(block_screen);
    page_block[bottom_block] = lv_obj_create(block_screen);
    page_block[right_block] = lv_obj_create(block_screen);
    /* 对页面区块进行布局 */
    /* 设置区块大小 */
    lv_obj_set_size(page_block[top_block],LV_PCT(40),LV_PCT(25));
    lv_obj_set_width(page_block[main_block],LV_PCT(40));
    lv_obj_set_flex_grow(page_block[main_block],1);
    lv_obj_set_size(page_block[bottom_block],LV_PCT(40),LV_PCT(10));
    lv_obj_set_size(page_block[right_block],LV_PCT(60),LV_PCT(100));
    /* 设置区块间距 */
    lv_obj_set_style_pad_column(root_screen, 0, 0);
    lv_obj_set_style_pad_row(root_screen, 0, 0);
    /* 设置区块透明 */
    static lv_style_t block_style;
    lv_style_init(&block_style);
    lv_style_set_border_width(&block_style,BLOCK_BORDER_WIDTH);
    lv_style_set_bg_opa(&block_style,LV_OPA_0);
    lv_style_set_pad_all(&block_style,0);
    for(uint32_t i = 0;i < block_count;i++){
        lv_obj_add_style(page_block[i],&block_style,0);
    }
}
/* 实现主区块的界面切换 */
/* 回退到上一个屏幕 */
static void main_block_out_screen(void){
    if(current_screen == main_screen){
        return;
    }
    lvgl_port_lock(0);
    lv_obj_add_flag(screen[current_screen],LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(screen_info[current_screen],LV_OBJ_FLAG_HIDDEN);
    dlist_remove(&screen_list,screen_list.head);    /* 删除头结点 */
    lv_led_on(indicator[screen_list.count-1]);
    lv_obj_delete(indicator[screen_list.count]);
    lv_obj_remove_flag(screen[current_screen],LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(screen_info[current_screen],LV_OBJ_FLAG_HIDDEN);
    lvgl_port_unlock();
}
/* 进入下一个屏幕 */
static void main_block_in_screen(screen_t in_screen){
    if(in_screen == current_screen)return;
    lvgl_port_lock(0);
    lv_obj_add_flag(screen[current_screen],LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(screen_info[current_screen],LV_OBJ_FLAG_HIDDEN);
    dlist_insert_head(&screen_list,(void*)in_screen);                   /* 插入头结点 */
    indicator = realloc(indicator,sizeof(lv_obj_t*)*screen_list.count);
    indicator[screen_list.count-1] = lv_led_create(page_block[bottom_block]);
    lv_obj_add_style(indicator[screen_list.count-1],&indicator_style,0);
    lv_led_on(indicator[screen_list.count-1]);
    lv_led_off(indicator[screen_list.count-2]);
    lv_obj_remove_flag(screen[current_screen],LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(screen_info[current_screen],LV_OBJ_FLAG_HIDDEN);
    lvgl_port_unlock();
}
/* 顶部区块的界面创建 */
/* 返回按钮的回调函数 */
static void bk_btn_cb(lv_event_t* e){
    lv_event_code_t code = lv_event_get_code(e);
    switch(code){
        case LV_EVENT_RELEASED:{
            main_block_out_screen();
        }
        break;       
        default:break;
    }
}
static void top_block_create(module_t*self){
    view_module_t *mod = (view_module_t *)self;
    lv_obj_t* back_btn = lv_button_create(page_block[top_block]);
    lv_obj_t* label = lv_label_create(back_btn);
    lv_obj_set_size(back_btn,LV_PCT(40),LV_SIZE_CONTENT);
    lv_obj_align(back_btn,LV_ALIGN_LEFT_MID,10,0);
    lv_label_set_text(label,"BACK");
    lv_obj_center(label);
    lv_obj_add_flag(back_btn,LV_OBJ_FLAG_FLOATING);
    lv_obj_add_event_cb(back_btn,bk_btn_cb,LV_EVENT_ALL,NULL);
}
/* 底部区块的界面创建 */
static void bottom_block_create(module_t*self){
    view_module_t *mod = (view_module_t *)self;
    lv_obj_set_flex_flow(page_block[bottom_block],LV_FLEX_FLOW_ROW);
    indicator = malloc(sizeof(lv_obj_t*) * 1);
    indicator[0] = lv_led_create(page_block[bottom_block]);
    lv_obj_set_flex_align(page_block[bottom_block],LV_FLEX_ALIGN_START,LV_FLEX_ALIGN_CENTER,LV_FLEX_ALIGN_CENTER);
    lv_style_init(&indicator_style);
    lv_style_set_size(&indicator_style,10,10);
    lv_style_set_radius(&indicator_style,LV_RADIUS_CIRCLE);
    lv_style_set_bg_color(&indicator_style,lv_color_hex(0x22a5f1));
    lv_obj_add_style(indicator[0],&indicator_style,0);
}
/* 主区块的界面创建 */
static void main_btn_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* btn = lv_event_get_target_obj(e);
    void* user_data = lv_event_get_user_data(e);
    screen_t next_screen;
    if(user_data){
        next_screen = (screen_t)user_data;
    }
    else{
        next_screen = main_screen;
    }
    lvgl_port_lock(0);
    switch(code){
        case LV_EVENT_PRESSING :{
             lv_obj_set_style_bg_color(btn,lv_color_hex(0x7a9fff),0);
        }
        break;
        case LV_EVENT_RELEASED:{
            
            lv_obj_remove_local_style_prop(btn,LV_STYLE_BG_COLOR,0);
            if(next_screen != main_screen)main_block_in_screen(next_screen);
        }
        break;
        default:break;
    }
    lvgl_port_unlock();
}
static void main_screen_create(module_t*self){
    view_module_t *mod = (view_module_t *)self;
    lv_obj_t* task_list = lv_list_create(screen[main_screen]);
    lv_obj_t* btn;
    lv_obj_set_style_border_width(task_list,0,0);
    lv_obj_set_size(task_list,LV_PCT(100),LV_PCT(100));
    btn = lv_list_add_button(task_list,LV_SYMBOL_WIFI,"WIFI");
    lv_obj_add_event_cb(btn,main_btn_cb,LV_EVENT_ALL,(void*)wifi_screen);
    btn = lv_list_add_button(task_list,NULL,"NONE");
    lv_obj_add_event_cb(btn,main_btn_cb,LV_EVENT_ALL,NULL);
    btn = lv_list_add_button(task_list,NULL,"NONE");
    lv_obj_add_event_cb(btn,main_btn_cb,LV_EVENT_ALL,NULL);
    btn = lv_list_add_button(task_list,NULL,"NONE");
    lv_obj_add_event_cb(btn,main_btn_cb,LV_EVENT_ALL,NULL);
    btn = lv_list_add_button(task_list,NULL,"NONE");
    lv_obj_add_event_cb(btn,main_btn_cb,LV_EVENT_ALL,NULL);
    btn = lv_list_add_button(task_list,NULL,"NONE");
    lv_obj_add_event_cb(btn,main_btn_cb,LV_EVENT_ALL,NULL);
    btn = lv_list_add_button(task_list,NULL,"NONE");
    lv_obj_add_event_cb(btn,main_btn_cb,LV_EVENT_ALL,NULL);
    btn = lv_list_add_button(task_list,NULL,"NONE");
    lv_obj_add_event_cb(btn,main_btn_cb,LV_EVENT_ALL,NULL);
}

typedef struct{
    char ssid[33];
    int8_t  rssi;
}wifi_info;
typedef struct{
    wifi_info* info;
    uint16_t  ap_nums;
}scan_res;
static void wifi_list_updata(event_t*e,void*arg){
    lvgl_port_lock(0);
    view_module_t * mod = (view_module_t*)arg;  
    event_t *e_tmp = e;
    assert(e_tmp->data);
    scan_res* res= (scan_res *)(e_tmp->data);
    uint16_t ap_nums= res->ap_nums;
    wifi_info *info = res->info;
    assert(info);
    lv_obj_clean(mod->wifi_info);
    if(e_tmp->type == 0x02){
        lv_obj_t* btn;
        for(uint16_t i = 0; i < res->ap_nums;i++){
           btn = lv_list_add_button(mod->wifi_info,LV_SYMBOL_WIFI,info[i].ssid);     
        }
    }
    lvgl_port_unlock();
}
static void wifi_list_btn_cb(lv_event_t*e){
    lvgl_port_lock(0);
    view_module_t* mod =(view_module_t*)lv_event_get_user_data(e);
    lv_obj_t* btn = lv_event_get_target_obj(e);
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_RELEASED){
        strcpy(mod->ConnectCounter.ssid,lv_list_get_button_text(mod->wifi_info,btn));
        /* 创建连接页面 */
        lv_obj_t* connect_page = lv_obj_create(root_screen);
        lv_obj_set_size(connect_page,LV_PCT(50),LV_PCT(50));
        lv_obj_set_align(connect_page,LV_ALIGN_CENTER);
        lv_obj_t* concel_btn = lv_button_create(connect_page);
        lv_obj_t* connect_btn = lv_button_create(connect_page);
        lv_obj_align(concel_btn,LV_ALIGN_BOTTOM_MID,lv_obj_get_width(concel_btn),0);
        lv_obj_align(connect_btn,LV_ALIGN_BOTTOM_MID,-lv_obj_get_width(concel_btn),0);
    }


}
static void wifi_switch_cb(lv_event_t *e){
    static bool wifi_inited = 0;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* sw = lv_event_get_target_obj(e);
    view_module_t * mod = (view_module_t*)lv_event_get_user_data(e);
    if(code == LV_EVENT_VALUE_CHANGED){
        if(lv_obj_has_state(sw,LV_STATE_CHECKED)){
            event_publish(mod->base.bus,view_wifi_start,NULL,1000);
            lv_obj_t* btn;
            btn = lv_list_add_btn(mod->wifi_info,LV_SYMBOL_WIFI,"test");
            lv_obj_add_event_cb(btn,wifi_list_btn_cb,LV_EVENT_RELEASED,mod);
        }
        else{
            event_publish(mod->base.bus,view_wifi_close,NULL,1000);
            lv_obj_clean(mod->wifi_info);
        }
    }
}
static void wifi_screen_create(module_t*self){
    view_module_t *mod = (view_module_t *)self;
    lv_obj_t* wifi_label  = lv_label_create(screen[wifi_screen]);
    lv_obj_t* wifi_switch = lv_switch_create(screen[wifi_screen]);
    lv_obj_t* wifi_tip    = lv_label_create(screen[wifi_screen]);
    lv_obj_t* btn;
    mod->wifi_info   = lv_list_create(screen_info[wifi_screen]);    
    lv_obj_set_size(mod->wifi_info,LV_PCT(100),LV_PCT(100));
    lv_obj_set_flex_flow(screen[wifi_screen],LV_FLEX_FLOW_ROW_WRAP);
    lv_label_set_text(wifi_label,LV_SYMBOL_WIFI "WIFI");
    lv_obj_set_style_text_font(wifi_label,&lv_font_montserrat_16,0);
    lv_obj_set_flex_align(screen[wifi_screen],LV_FLEX_ALIGN_SPACE_BETWEEN,LV_FLEX_ALIGN_START,LV_FLEX_ALIGN_START);
    lv_obj_center(wifi_tip);
    lv_label_set_text(wifi_tip,"WIFI disconnected");
    lv_obj_add_event_cb(wifi_switch,wifi_switch_cb,LV_EVENT_VALUE_CHANGED,mod);
}
static void main_block_create(module_t*self){
    view_module_t *mod = (view_module_t *)self;
    static lv_style_t screen_style;
    lv_style_init(&screen_style);
    lv_style_set_size(&screen_style,LV_PCT(100),LV_PCT(100));
    lv_style_set_pad_all(&screen_style,0);
    lv_style_set_border_width(&screen_style,0);
    for(uint32_t i = 0;i<screen_count;i++){
        screen[i] = lv_obj_create(page_block[main_block]);
        screen_info[i] = lv_obj_create(page_block[right_block]);
        lv_obj_add_flag(screen[i],LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_style(screen[i],&screen_style,0);
        lv_obj_add_flag(screen_info[i],LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_style(screen_info[i],&screen_style,0);
    }
    lv_obj_remove_flag(screen[main_screen],LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(screen_info[main_screen],LV_OBJ_FLAG_HIDDEN);
    main_screen_create(self);
    wifi_screen_create(self);
}


static void ui_demo1(view_module_t *mod){
    lvgl_port_lock(0); 
    ui_init();
    my_mem_init(&ui_mem_pool,ui_mem_buffer,4096);  /* 分配内存池 */
    dlist_init(&screen_list,&ui_mem_pool);      /* 初始化链表,绑定内存池 */
    dlist_insert_head(&screen_list,main_screen); /* 将当前屏幕插入链表 */
    /* 将block_screen设置为flex_col  */
    block_screen = lv_obj_create(root_screen);
    lv_obj_set_size(block_screen,LV_PCT(100),LV_PCT(100));
    lv_obj_set_flex_flow(block_screen,LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_style_pad_all(block_screen,0,0);
    /* 区块布局 */
    block_init();
    /* 创建各区块的内容 */
    top_block_create(mod->base);
    bottom_block_create(mod->base);
    main_block_create(mod->base);
    /* 以上界面初始化完毕  */
    /* 下面开始订阅事件 */
    event_subscribe(mod->base.bus,0x02,wifi_list_updata,mod,0);
    lvgl_port_unlock();
}
#endif


#if USE_DEMO2
static void ui_demo(view_module_t* mod){

}
#endif
static void view_init(module_t* self){
    view_module_t * mod = (view_module_t*)self;
    ui_demo(mod);
}



view_module_t g_view_module = {
    .base = {
        .id = 0x02,
        .init = view_init,
        .state = MODULE_STATE_ALLOCATED,
    },  
};

void lvgl_init(void){
    // view_init(&g_view_module.base);
    ui_register_screen(UI_SCREEN_HOME,g_home_ops.create,g_home_ops.show,g_home_ops.hide);
    ui_register_screen(UI_SCREEN_WIFI,g_wifi_ops.create,g_wifi_ops.show,g_wifi_ops.hide);
    ui_register_screen(UI_SCREEN_WIFI_CONNECT,g_wifi_connect_ops.create,g_wifi_connect_ops.show,g_wifi_connect_ops.hide);
    ui_init();;
}

