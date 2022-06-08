/********************************************************************************
* @file    info.h
* @author  Nam Tran
* @version 2.0
* @date    22/05/2022
* @brief   Custom component - Info box template on the home screen inheritated from lv_obj_t
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

/* --------------------------------- GUARDS --------------------------------- */
#pragma once
#ifdef __cplusplus
 extern "C" {
#endif

/* -------------------------------------------------------------------------- */
/*                                   INCLUDES                                 */
/* -------------------------------------------------------------------------- */
#include "lvgl.h"

/* -------------------------------------------------------------------------- */
/*                                   DEFINES                                  */
/* -------------------------------------------------------------------------- */
 
/* -------------------------------------------------------------------------- */
/*                                   TYPEDEFS                                 */
/* -------------------------------------------------------------------------- */
 
typedef struct {
    lv_obj_t * cont;
    lv_obj_t * label;
    lv_obj_t * value;
} info_box_t;
/* -------------------------------------------------------------------------- */
/*                                  PROTOTYPE                                 */
/* -------------------------------------------------------------------------- */

// Followed this tutorial https://blog.lvgl.io/2018-12-13/extend-lvgl-objects

lv_obj_t * info_box_create (lv_obj_t * parent,  char name[]);
/**
 * @brief Create info box
 * 
 * @param parent The parrent object
 * @param name Display name of the box
 * @param unit Unit of the display value
 * @return info_box_t* 
 */
// info_box_t * info_box_create(lv_obj_t * parent, char name[], char unit[]);

// void info_box_set_value(info_box_t * info_box, char value[]);
/* --------------------------------- GUARDS --------------------------------- */
#ifdef __cplusplus
}
#endif