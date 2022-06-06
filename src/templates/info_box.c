#include "info_box.h"

#define MY_CLASS &lv_arc_class

// const lv_obj_class_t lv_arc_class  = {
//     //.constructor_cb = lv_arc_constructor,
//     //.event_cb = lv_arc_event,
//     .instance_size = sizeof(info_box_t),
//     .editable = LV_OBJ_CLASS_EDITABLE_TRUE,
//     .base_class = &lv_obj_class
// };

info_box_t * info_box_create(lv_obj_t * parent)
{
    info_box_t * info_box;
    lv_obj_t * bg = lv_obj_create(parent);
    lv_obj_set_size(bg, 176,84);

    lv_obj_set_style_bg_color(bg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(bg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //info_box->cont = bg;
    info_box.t = 5;
    //return info_box;
}
