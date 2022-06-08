#include "info_box.h"

#define MY_CLASS &lv_arc_class



/* -------------------------------------------------------------------------- */
/*                              GLOBAL FUNCTIONS                              */
/* -------------------------------------------------------------------------- */
lv_obj_t * info_box_create (lv_obj_t * parent, char name[])
{
    //background
    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_size(cont, 176,84);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    //label
    lv_obj_t * label = lv_label_create(cont);
    lv_label_set_text_static(label,name);
    printf(label);

    return cont;
}
// info_box_t * info_box_create(lv_obj_t * parent, char name[], char unit[])
// {
//     info_box_t * info_box = lv_mem_alloc(sizeof(info_box)); //create and allocate memory for box instance
    
//     //background
//     lv_obj_t * bg = lv_obj_create(parent);
//     lv_obj_set_size(bg, 176,84);
//     lv_obj_set_style_bg_color(bg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(bg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     info_box->cont = bg;

//     //label
//     lv_obj_t * label = lv_label_create(bg);
//     lv_label_set_text_static(label,name);
//     info_box->label = label;

//     //value
//     lv_obj_t * value = lv_label_create(bg);
//     lv_label_set_text(value,"0");
//     lv_obj_set_pos(value,70,20);
//     info_box->value = value;

//     return info_box;
// }

// void info_box_set_value(info_box_t * info_box, char val[]) 
// {
//     lv_label_set_text(info_box->value,"50F");
// }
