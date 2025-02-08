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
    lv_style_set_border_color(&box_style,border_color); /* 边框颜色 */

    lv_style_set_border_width(&box_style,5);    /* 边框宽度 */

    lv_style_set_outline_width(&box_style,5);   /* 轮廓 */


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

void lv_example_get_started_1(void)
{
    lv_obj_t * sub_obj;
    lv_obj_t * lable;
    sub_obj = lv_obj_create(main_screen);
    lv_obj_set_size(sub_obj,LV_PCT(50),LV_PCT(50));
    lv_obj_align(sub_obj,LV_ALIGN_CENTER,0,0);
    lable = lv_label_create(sub_obj);
    lv_label_set_text_fmt(lable,"first\nsecond ");
    lv_obj_align(lable,LV_ALIGN_CENTER,0,0);
}




void lvgl_ui(void){
    ui_init();
    //lv_example_get_started_1();
    //ui_size();
    //ui_pos();
    ui_box_model();
}
