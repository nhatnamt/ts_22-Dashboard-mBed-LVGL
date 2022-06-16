/********************************************************************************
* @file    warning.h
* @author  Nam Tran
* @date    16/06/2022
* @brief   Quick function to draw and hide warning/error
*********************************************************************************
*/

/* -------------------------------------------------------------------------- */
/*                                   INCLUDE                                  */
/* -------------------------------------------------------------------------- */
#include "warning_error.h"

/* -------------------------------------------------------------------------- */
/*                              STATICS FUNCTIONS                             */
/* -------------------------------------------------------------------------- */
static lv_obj_t * get_error_label(lv_obj_t * obj)
{
    return lv_obj_get_child(lv_obj_get_child(obj,0),0);
}
/* -------------------------------------------------------------------------- */
/*                              GLOBAL FUNCTIONS                              */
/* -------------------------------------------------------------------------- */
lv_obj_t * button_warning_create(lv_obj_t * parent)
{
    /*Init style*/
    static lv_style_t warning_line_style;
    lv_style_init(&warning_line_style);
    lv_style_set_line_width(&warning_line_style, 20);
    lv_style_set_line_color(&warning_line_style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_line_rounded(&warning_line_style, true);


    lv_obj_t * warning_line = lv_line_create(parent);
    
    static lv_point_t line_points[] = {{0,0},{800,0},{800, 480},{0, 480},{0,0}};
    lv_line_set_points(warning_line,line_points,5);

    lv_obj_add_style(warning_line,&warning_line_style,0);
    lv_obj_add_flag(warning_line, LV_OBJ_FLAG_HIDDEN);

    return warning_line;
}

void show_precharge_warning(lv_obj_t * obj)
{
    lv_obj_set_style_line_color(obj,lv_palette_main(LV_PALETTE_ORANGE),0);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);

}

void show_drive_warning(lv_obj_t * obj)
{
    lv_obj_set_style_line_color(obj,lv_palette_darken(LV_PALETTE_LIGHT_BLUE,4),0);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

void hide_warning(lv_obj_t * obj)
{
    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

/* --------------------------------- Errors --------------------------------- */
lv_obj_t * critical_error_create(lv_obj_t * parent)
{
    lv_obj_t * outter_cont = lv_obj_create(parent);
    //lv_obj_set_style_bg_color(outter_cont,)
}