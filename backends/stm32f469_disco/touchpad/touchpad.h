/********************************************************************************
* @file    tft.h
* @author  Nam Tran
* @version 2.0
* @date    19/04/2022
* @brief   tft driver to interface between lvgl and mbed stm bsp drivers
*********************************************************************************
*/

/* --------------------------------- GUARDS --------------------------------- */
#ifndef INDEV_H
#define INDEV_H
#ifdef __cplusplus
 extern "C" {
#endif

/* -------------------------------------------------------------------------- */
/*                                   INCLUDES                                 */
/* -------------------------------------------------------------------------- */
#include <stdbool.h>
#include <stdint.h>


/* -------------------------------------------------------------------------- */
/*                              GLOBAL PROTOTYPES                             */
/* -------------------------------------------------------------------------- */
void touchpad_init(void);

/* --------------------------------- GUARDS --------------------------------- */
#ifdef __cplusplus
}
#endif
#endif