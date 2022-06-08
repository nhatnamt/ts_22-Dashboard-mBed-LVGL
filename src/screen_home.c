/********************************************************************************
* @file    screen_home.c
* @author  Nam Tran
* @version 2.0
* @date    20/05/2022
* @brief   Home screen header
*********************************************************************************
* @details 
* ----------------------------
* Definitions and declarations
* 
* ----------------------------
* Functions
*   load_home() prototype
*********************************************************************************
*/


/* -------------------------------------------------------------------------- */
/*                                   INCLUDES                                 */
/* -------------------------------------------------------------------------- */
#include "lvgl.h"
#include "templates/info_box.h"
#include <stdio.h>
#include "screen_home.h"


/* -------------------------------------------------------------------------- */
/*                                   DEFINES                                  */
/* -------------------------------------------------------------------------- */
 
/* -------------------------------------------------------------------------- */
/*                                   STRUCTS                                  */
/* -------------------------------------------------------------------------- */
 

int16_t temp = 0;
/* -------------------------------------------------------------------------- */
/*                             STATIC PROTOTYPES                              */
/* -------------------------------------------------------------------------- */
lv_obj_t * mc_temp;
lv_obj_t * ui_main_gauge;
/* -------------------------------------------------------------------------- */
/*                              STATIC FUNCTIONS                              */
/* -------------------------------------------------------------------------- */
void gauge_update_timer(lv_timer_t * timer)
{
    if (temp >= 100)
    {
        temp = 0;
    }
    else
    {
        temp++;
    }
    lv_obj_t * child = lv_obj_get_child(mc_temp,1);
    lv_label_set_text_fmt(child,"%dF",temp);
    lv_arc_set_value(ui_main_gauge, temp);
    //info_box_set_value(mc_temp,"20F");
}

/* -------------------------------------------------------------------------- */
/*                              GLOBAL FUNCTIONS                              */
/* -------------------------------------------------------------------------- */

/**
 * @brief Function to load the home screen
 * 
 * TODO: change to a common style instead of setting individual elements
 * @param parent 
 */
void load_home(lv_obj_t* parent)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    /* ------------------------------- main gauge ------------------------------- */
    ui_main_gauge = lv_arc_create(parent);
    uint16_t gauge_radius = 350;

    // throttle arc
    lv_obj_set_size(ui_main_gauge, gauge_radius,gauge_radius);
    lv_obj_center(ui_main_gauge);
    
    lv_arc_set_range(ui_main_gauge, 0, 100); /*Set range, value and angle limit of the arc*/
    lv_arc_set_value(ui_main_gauge, 50);
    lv_arc_set_bg_angles(ui_main_gauge, 120, 310);

    lv_obj_remove_style(ui_main_gauge, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(ui_main_gauge, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/

    lv_obj_set_style_arc_width(ui_main_gauge, 30, LV_PART_MAIN | LV_STATE_DEFAULT); /*remove round border background*/
    lv_obj_set_style_arc_rounded(ui_main_gauge, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_main_gauge, 30, LV_PART_INDICATOR | LV_STATE_DEFAULT); /*remove round border indicator*/
    lv_obj_set_style_arc_rounded(ui_main_gauge, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // brake arcs
    lv_obj_t * ui_brake_arc = lv_arc_create(ui_main_gauge);

    lv_obj_set_size(ui_brake_arc, gauge_radius,gauge_radius);
    lv_obj_center(ui_brake_arc);
    lv_arc_set_mode(ui_brake_arc, LV_ARC_MODE_REVERSE);

    
    lv_arc_set_range(ui_brake_arc, 0, 100); /*Set range, value and angle limit of the arc*/
    lv_arc_set_value(ui_brake_arc, 50);
    lv_arc_set_bg_angles(ui_brake_arc, 315, 60);

    lv_obj_remove_style(ui_brake_arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(ui_brake_arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/

    lv_obj_set_style_arc_width(ui_brake_arc, 12, LV_PART_MAIN | LV_STATE_DEFAULT); /*remove round border background*/
    lv_obj_set_style_arc_rounded(ui_brake_arc, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_brake_arc, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT); /*remove round border indicator*/
    lv_obj_set_style_arc_rounded(ui_brake_arc, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // regen arcs
    // lv_obj_t * ui_regen_arc = lv_arc_create(ui_main_gauge);

    // lv_obj_set_size(ui_regen_arc, 312,312);
    // lv_obj_center(ui_regen_arc);
    // lv_arc_set_mode(ui_regen_arc, LV_ARC_MODE_REVERSE);
    
    // lv_arc_set_range(ui_regen_arc, 0, 100); /*Set range, value and angle limit of the arc*/
    // lv_arc_set_value(ui_regen_arc, 50);
    // lv_arc_set_bg_angles(ui_regen_arc, 315, 60);

    // lv_obj_remove_style(ui_regen_arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    // lv_obj_clear_flag(ui_regen_arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/

    // lv_obj_set_style_arc_width(ui_regen_arc, 12, LV_PART_MAIN | LV_STATE_DEFAULT); /*remove round border background*/
    // lv_obj_set_style_arc_rounded(ui_regen_arc, false, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_set_style_arc_width(ui_regen_arc, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT); /*remove round border indicator*/
    // lv_obj_set_style_arc_rounded(ui_regen_arc, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    /* ------------------------------- Mc Temp box ------------------------------ */
    mc_temp = info_box_create(parent,"MC Temp");
    info_box_set_value(mc_temp,"50F");
    //lv_label_set_text(mc_temp->value,"50C");

    //info_box_set_value(mc_temp, "50");

    lv_timer_t * timer = lv_timer_create(gauge_update_timer,10,NULL);
}
