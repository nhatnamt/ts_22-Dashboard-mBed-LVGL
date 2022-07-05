/********************************************************************************
* @file    screen_home.c
* @author  Nam Tran
* @version 2.0
* @date    20/05/2022
* @brief   Home screen header
*********************************************************************************
*/


/* -------------------------------------------------------------------------- */
/*                                   INCLUDES                                 */
/* -------------------------------------------------------------------------- */
#include "screen_home.h"
#include "backend.hpp"

#include "templates/info_box.h"
#include "templates/warning_error.h"




/* -------------------------------------------------------------------------- */
/*                                   DEFINES                                  */
/* -------------------------------------------------------------------------- */
#define GAUGE_DIA_BIG 320
#define GAUGE_WIDTH_BIG 30

/* -------------------------------------------------------------------------- */
/*                              STATIC VARIABLES                              */
/* -------------------------------------------------------------------------- */
//gaue and info box
lv_obj_t * ui_main_gauge;
lv_obj_t * ui_brake_arc;
lv_obj_t * ui_mc_temp;
lv_obj_t * ui_motor_temp;
lv_obj_t * ui_accum_temp;
lv_obj_t * ui_accum_volt;
lv_obj_t * ui_accum_current;
lv_obj_t * ui_coolant_temp;
lv_obj_t * ui_coolant_flow;
lv_obj_t * ui_low_voltage_sys;
lv_obj_t * ui_ams_state;

lv_obj_t * button_warning;
lv_obj_t * critical_error;

/* -------------------------------------------------------------------------- */
/*                             STATIC PROTOTYPES                              */
/* -------------------------------------------------------------------------- */
void gauge_update_task(lv_timer_t * timer);
/* -------------------------------------------------------------------------- */
/*                              STATIC FUNCTIONS                              */
/* -------------------------------------------------------------------------- */
void gauge_update_task(lv_timer_t * timer)
{
    /*Static variable to save the previous value*/
    static VehicleState		    vehicle_state;
    static MotorInfo		    motor_info;
    static AccumulatorInfo		accum_info;
    static MiscInfo			    misc_info;

    VehicleState    new_vehicle_state  = can_get_vehicle_state();
    MotorInfo       new_motor_info     = can_get_motor_info();
    AccumulatorInfo new_accum_info     = can_get_accum_info();
    MiscInfo        new_misc_info      = can_get_misc_info();

    /* Set value for the info boxes */
    if (motor_info.mc_temp != new_motor_info.mc_temp)
    {
        motor_info.mc_temp = new_motor_info.mc_temp;
        lv_obj_t * label_value = lv_obj_get_child(ui_mc_temp,INFO_BOX_VALUE_CHILD_ID);
        lv_label_set_text_fmt(label_value,"%d C",motor_info.mc_temp);
    }

    if (motor_info.motor_temp != new_motor_info.motor_temp)
    {
        motor_info.motor_temp = new_motor_info.motor_temp;
        lv_obj_t * label_value = lv_obj_get_child(ui_motor_temp,INFO_BOX_VALUE_CHILD_ID);
        lv_label_set_text_fmt(label_value,"%d C",motor_info.motor_temp);
    }

    if (accum_info.max_temp != new_accum_info.max_temp)
    {
        accum_info.max_temp = new_accum_info.max_temp;
        lv_obj_t * label_value = lv_obj_get_child(ui_accum_temp,INFO_BOX_VALUE_CHILD_ID);
        lv_label_set_text_fmt(label_value,"%.1f C",accum_info.max_temp);
    }

    if (motor_info.coolant_temp != new_motor_info.coolant_temp)
    {
        motor_info.coolant_temp = new_motor_info.coolant_temp;
        lv_obj_t * label_value = lv_obj_get_child(ui_coolant_temp,INFO_BOX_VALUE_CHILD_ID);
        lv_label_set_text_fmt(label_value,"%.1f C",motor_info.coolant_temp);
    }

    if (motor_info.coolant_flow != new_motor_info.coolant_flow)
    {
        motor_info.coolant_flow = new_motor_info.coolant_flow;
        lv_obj_t * label_value = lv_obj_get_child(ui_coolant_flow,INFO_BOX_VALUE_CHILD_ID);
        lv_label_set_text_fmt(label_value,"%d Lpm",motor_info.coolant_flow);
    }

    if (misc_info.lv_bus_voltage != new_misc_info.lv_bus_voltage)
    {
        misc_info.lv_bus_voltage = new_misc_info.lv_bus_voltage;
        lv_obj_t * label_value = lv_obj_get_child(ui_low_voltage_sys,INFO_BOX_VALUE_CHILD_ID);
        lv_label_set_text_fmt(label_value,"%.1f V", misc_info.lv_bus_voltage);
    }

    /* Main gauge update */
    if (misc_info.throttle_pct != new_misc_info.throttle_pct)
    {
        misc_info.throttle_pct = new_misc_info.throttle_pct;
        lv_arc_set_value(ui_main_gauge,misc_info.throttle_pct);
    }

    if (misc_info.brake_pct != new_misc_info.brake_pct)
    {
        misc_info.brake_pct = new_misc_info.brake_pct;
        lv_arc_set_value(ui_brake_arc,100-misc_info.brake_pct); //invert the value
    }

    if (accum_info.pack_voltage != new_accum_info.pack_voltage)
    {
        accum_info.pack_voltage = new_accum_info.pack_voltage;
        lv_label_set_text_fmt(ui_accum_volt,"%d V",accum_info.pack_voltage);
    }

    if (accum_info.pack_current != new_accum_info.pack_current)
    {
        accum_info.pack_current = new_accum_info.pack_current;
        lv_label_set_text_fmt(ui_accum_current,"%d A",accum_info.pack_current);
    }

    if (vehicle_state.ams_state != new_vehicle_state.ams_state)
    {
        vehicle_state.ams_state = new_vehicle_state.ams_state;
        switch (vehicle_state.ams_state)
        {
        case 0:
            lv_label_set_text(ui_ams_state, "State 0:\nCritical Error");
            break;
        case 1:
            lv_label_set_text(ui_ams_state, "State 1: Idle");
            break;
        case 3:
            lv_label_set_text(ui_ams_state, "State 3: Precharging");
            break;       
        case 4:
            lv_label_set_text(ui_ams_state, "State 4: Precharged");
            break;
        case 5:
            lv_label_set_text(ui_ams_state, "State 5: Ready to Drive");
            break;
        default:
            break;
        }
    }
    
    /* Update warning and LATCH errors */
    if (new_vehicle_state.precharge_pressed) 
    {
        show_precharge_warning(button_warning);
    } 
    else if (new_vehicle_state.drive_pressed) 
        {
            show_drive_warning(button_warning);
        } 
        else 
        {
            hide_warning(button_warning);
        }

    if (new_vehicle_state.error_ams) {
        show_AMS_error(critical_error,new_vehicle_state.error_ams);
    } 
       
    if (new_vehicle_state.error_bspd) {
        show_BSPD_error(critical_error);
    }

    if (new_vehicle_state.error_imd) {
        show_IMD_error(critical_error);
    }

    if (new_vehicle_state.error_pdoc_precharge) {
        show_PDOC_error(critical_error,0);
    }

    if (new_vehicle_state.error_pdoc_discharge) {
        show_PDOC_error(critical_error,1);
    }
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
    lv_disp_t * disp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(disp, theme);

    /* ------------------------------- main gauge ------------------------------- */
    ui_main_gauge = lv_arc_create(parent);

    // throttle arc
    lv_obj_set_size(ui_main_gauge, GAUGE_DIA_BIG,GAUGE_DIA_BIG);
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
    ui_brake_arc = lv_arc_create(ui_main_gauge);

    lv_obj_set_size(ui_brake_arc, GAUGE_DIA_BIG,GAUGE_DIA_BIG);
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

    // HV Voltage
    ui_accum_volt = lv_label_create(ui_main_gauge);
    lv_label_set_text(ui_accum_volt, "600 V");

    lv_obj_center(ui_accum_volt);
    lv_obj_set_y(ui_accum_volt, -30);
    lv_obj_set_style_text_font(ui_accum_volt,&lv_font_montserrat_40,LV_PART_MAIN | LV_STATE_DEFAULT);

    // A small line seperating voltage and current
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 3);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_line_rounded(&style_line, true);

    static lv_point_t line_points[] = { {0, 0}, {150, 0}};
    lv_obj_t * line = lv_line_create(ui_main_gauge);
    
    lv_line_set_points(line, line_points, 2); 
    lv_obj_add_style(line, &style_line, 0);
    lv_obj_center(line);
    lv_obj_set_y(line, 8);
    // HV Current
    ui_accum_current = lv_label_create(ui_main_gauge);
    lv_label_set_text(ui_accum_current, "100 A");

    lv_obj_center(ui_accum_current);
    lv_obj_set_y(ui_accum_current, 45);
    lv_obj_set_style_text_font(ui_accum_current,&lv_font_montserrat_36,LV_PART_MAIN | LV_STATE_DEFAULT);

    /* ------------------------------- info boxes ------------------------------- */
    ui_mc_temp = info_box_create(parent,"MC Temp");
    lv_obj_set_pos(ui_mc_temp,-255,-165);

    ui_motor_temp = info_box_create(parent,"Motor Temp");
    lv_obj_set_pos(ui_motor_temp,-290,0);

    ui_accum_temp = info_box_create(parent,"Accum Temp");
    lv_obj_set_pos(ui_accum_temp,-255,165);

    ui_coolant_temp = info_box_create(parent,"Coolant Temp");
    lv_obj_set_pos(ui_coolant_temp,255,-165);

    ui_coolant_flow = info_box_create(parent,"Coolant Flow");
    lv_obj_set_pos(ui_coolant_flow,290,0);

    ui_low_voltage_sys = info_box_create(parent,"Low Voltage Sys");
    lv_obj_set_pos(ui_low_voltage_sys,255, 165);

    /* -------------------------------- AMS State ------------------------------- */
    ui_ams_state = lv_label_create(parent);
    lv_label_set_text(ui_ams_state, "AMS State 1: Idle");

    lv_obj_center(ui_ams_state);
    lv_obj_set_y(ui_ams_state, 190);
    lv_obj_set_style_text_font(ui_ams_state,&lv_font_montserrat_20,LV_PART_MAIN | LV_STATE_DEFAULT);

    /* --------------------------- Warning and errors --------------------------- */
    button_warning = button_warning_create(parent); // for when a button is pressed
    //show_precharge_warning(button_warning);
    //show_drive_warning(button_warning);

    //lv_obj_clear_flag(precharge_warning,LV_OBJ_FLAG_HIDDEN);
    critical_error = critical_error_create(parent);
    //show_BSPD_error(critical_error);
    /* --------------------------------- Timers --------------------------------- */
    lv_timer_create(gauge_update_task,10,NULL);
}
