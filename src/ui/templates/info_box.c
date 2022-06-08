#include "info_box.h"

#define MY_CLASS &lv_arc_class



/* -------------------------------------------------------------------------- */
/*                              GLOBAL FUNCTIONS                              */
/* -------------------------------------------------------------------------- */

/*  Due to memory leak when creating a custom object, 
    accessing children's will now be done through lv_obj_get_child(parent, idx)
*/
lv_obj_t * info_box_create (lv_obj_t * parent, char name[])
{
    //background
    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_size(cont, 176,84);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    //label
    lv_obj_t * box_label = lv_label_create(cont);
    lv_label_set_text_static(box_label,name);

    // display value
    lv_obj_t * box_value = lv_label_create(cont);
    lv_label_set_text(box_value,"0");
    lv_obj_set_pos(box_value,70,20);

    return cont;
}

void info_box_set_value(lv_obj_t * info_box, char value[]) 
{
    lv_obj_t * child = lv_obj_get_child(info_box,1); //get second created child
    lv_label_set_text(child,value);
    //lv_label_set_text_fmt(child,)
    
}
