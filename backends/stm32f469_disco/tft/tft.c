// /********************************************************************************
// * @file    tft.c
// * @author  Nam Tran
// * @version 2.0
// * @date    19/04/2022
// * @brief   tft driver to interface between lvgl and mbed stm bsp drivers
// *********************************************************************************
// * @details 
// * ----------------------------
// * Definitions and declarations
// * 
// * ----------------------------
// * Functions*
// * 
// *********************************************************************************
// */
 
// /* -------------------------------------------------------------------------- */
// /*                                   INCLUDES                                 */
// /* -------------------------------------------------------------------------- */
#include "tft.h"
#include "lvgl.h"
#include "stm32f4xx.h"
#include "bsp_drivers/stm32469i_discovery.h"
#include "bsp_drivers/stm32469i_discovery_lcd.h"
#include "bsp_drivers/stm32469i_discovery_sdram.h"
// /* -------------------------------------------------------------------------- */
// /*                                   DEFINES                                  */
// /* -------------------------------------------------------------------------- */

// /* -------------------------------------------------------------------------- */
// /*                                  PROTOTYPE                                 */
// /* -------------------------------------------------------------------------- */
void tft_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
/* -------------------------------------------------------------------------- */
/*                                  FUNCTIONS                                 */
/* -------------------------------------------------------------------------- */
void tft_init() 
{
    BSP_LCD_Init();
	BSP_LCD_InitEx(LCD_ORIENTATION_LANDSCAPE);
	BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER_BACKGROUND, LCD_FB_START_ADDRESS);
  	BSP_LCD_SetFont(&Font20);
  	BSP_LCD_Clear(LCD_COLOR_BLACK);

    /*A static or global variable to store the buffers*/
    static lv_disp_draw_buf_t disp_buf;

    /*Static or global buffer(s)*/
    static lv_color_t buf[LV_HOR_RES_MAX * 10];
    
    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX*10);
    
    static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/

    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
    disp_drv.flush_cb = tft_flush;        	/*Set a flush callback to draw to the display*/
    disp_drv.hor_res = LV_HOR_RES_MAX;   	/*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = LV_VER_RES_MAX;    	/*Set the vertical resolution in pixels*/
    
    lv_disp_drv_register(&disp_drv); 
    /*Set default screen to black*/
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_PART_MAIN);

}

void tft_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
    uint16_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            //put_px(x, y, *color_p)
            BSP_LCD_DrawPixel(x, y, color_p->full);
            color_p++;
        }
    }

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}
