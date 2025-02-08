# lvgl_ui

lvgl 学习


#第一天
一. lvgl的三层屏幕
    API:
        lv_screen_active()          活动屏幕    (screen_active)
        lv_layer_top()              顶层        (top layer)
        lv_layer_sys()              系统层      (system layer)

系统层 > 顶层 > 活动屏幕
优先级高的屏幕会覆盖优先级低的屏幕


二. lvgl对象大小
    API:
        lv_obj_set_size(obj,x,y)
        lv_obj_set_width(obj,x)
        lv_obj_set_height(obj,y)

    
    LV_PCT(n)       %n
    API:    
        获取实际大小
        w = lv_obj_get_width(obj)
        h = lv_obj_get_height(obj)
        获取实际可用的大小
        content_w = lv_obj_get_content_width(obj);
        content_h = lv_obj_get_content_height(obj);


    为了提高性能,当我们设定了对象的位置、大小、布局后,LVGL不会立即更新对象的这些属性,而是将对象标记为dirty,在重新绘制屏幕之前,LVGL会检查是否有任何的dirty对象,如果有则会刷新它们的位置、大小、布局。
    所以如果要获取对象的位置、大小、布局,并且这些属性刚刚被重新设置,那么此时LVGL就需要强制刷新。
    强制刷新:   lv_obj_update_layout(obj);


三. lvgl对象位置
    API:
        设置坐标
        lv_obj_set_x(obj,x);
        lv_obj_set_y(obj,y);
        lv_obj_set_pos(obj,x,y);

    API:    
        参考父类对象对齐
        lv_obj_set_align(obj,LV_ALIGN_CENTER);
        参考父类对象对齐,并设置坐标
        lv_obj_align(obj,LV_ALIGN_CENTER,x,y);
        可以参考任何对象对齐,并设置坐标
        lv_obj_align_to(obj,base_obj,LV_ALIGN_CENTER,x,y)

        对齐后,对象坐标原点变更

    API:
        获取对象相对于父类对象LCD坐标系的左上角坐标
        lv_obj_get_x(obj);
        lv_obj_get_y(obj);
        获取对象相对于父类对象LCD坐标系的右下角坐标
        lv_obj_get_x2(obj);
        lv_obj_get_y2(obj);
        获取对象相对于自身对齐后坐标系的坐标偏移
        lv_obj_get_x_aligned(obj);
        lv_obj_get_y_aligned(obj);

三. lvgl盒子模型

    ![alt text](./image.png)


   