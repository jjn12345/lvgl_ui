#include "ui.h"
#include "lvgl/lvgl.h"

static lv_obj_t * main_screen = NULL;

static void ui_init(void){
    main_screen = lv_screen_active();
}

void ui_size(void){
    lv_obj_t * sub_obj;
    int32_t obj_h = 0;
    int32_t obj_w = 0;
    int32_t content_w;
    int32_t content_h;
    sub_obj = lv_obj_create(main_screen);
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

void ui_pos(void){
    lv_obj_t * sub_obj;
    lv_obj_t * sub_obj2;
    lv_obj_t * lable;
    lv_obj_t * lable2;
    int32_t obj_x = 0;
    int32_t obj_y = 0;
    int32_t obj_x2 = 0;
    int32_t obj_y2 = 0;
    sub_obj = lv_obj_create(main_screen);
    lv_obj_set_size(sub_obj,LV_PCT(30),LV_PCT(30));
    lv_obj_align(sub_obj,LV_ALIGN_CENTER,0,0);
    // sub_obj2 = lv_obj_create(main_screen);
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
        box[i] = lv_obj_create(main_screen);
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

void ui_style(void){
    /* 添加对象 */
    lv_obj_t * sub_obj1 = lv_obj_create(main_screen);
    lv_obj_t * sub_obj2 = lv_obj_create(main_screen);
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


static lv_obj_t* sub_screen;
static lv_obj_t* slider;
static lv_obj_t* label;
static void slider_scroll(lv_event_t * e){
    if(lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED){
        lv_label_set_text_fmt(label,"%d%%",lv_slider_get_value(slider));
    }
}
void ui_slider(void){
    /* 创建对象 */
    sub_screen = lv_obj_create(main_screen);
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

    lv_obj_align_to(label,slider,LV_ALIGN_CENTER,0,20);
    /* 为滚动条添加事件 */
    lv_obj_add_event_cb(slider,slider_scroll,LV_EVENT_VALUE_CHANGED,NULL);
}

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
    sub_screen = lv_obj_create(main_screen);
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


static void bubbing_event(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);            /* 获取事件代码 */
    lv_obj_t * now_obj = lv_event_get_current_target(e);    /*  获取当前触发对象 */
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
            lv_label_set_text(label,"I am in main_screen");
        }
        break;
    }
}
void ui_event_bubbing(void){
    /* 创建对象 */
    lv_obj_t* s_screen = lv_obj_create(main_screen);
    lv_obj_t* ss_screen = lv_obj_create(s_screen);
    lv_obj_t* sss_screen = lv_obj_create(ss_screen);
    lv_obj_t* label = lv_label_create(main_screen);
    lv_obj_t* button = lv_button_create(sss_screen);
    lv_obj_t* b_label = lv_label_create(button);

    /* 设置控件属性 */
    lv_label_set_text(label,"I am in main_screen");
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

    lv_obj_add_event_cb(main_screen,bubbing_event,LV_EVENT_ALL,label);
}


void lvgl_ui(void){
    ui_init();
    //ui_size();
    //ui_pos();
    //ui_style();
    //ui_slider();
    //ui_event();
    ui_event_bubbing();
}
