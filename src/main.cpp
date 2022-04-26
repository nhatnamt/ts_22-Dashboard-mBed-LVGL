/********************************************************************************
* @file    main.cpp
* @author  Nam Tran
* @version 1.0
* @date    19-04-2020
* @brief   D
*********************************************************************************
* @details 
* ----------------------------
* Definitions and declarations
* 
* ----------------------------
* Functions*
* 
*********************************************************************************
*/
 
// /* -------------------------------------------------------------------------- */
// /*                                   INCLUDES                                 */
// /* -------------------------------------------------------------------------- */
// #include "common.h"
// #include "lvgl.h"
// #include "demos/lv_demos.h"
// #include "lv_conf.h"

// #include "screen_splash.h"
// /* -------------------------------------------------------------------------- */
// /*                                   DEFINES                                  */
// /* -------------------------------------------------------------------------- */
 
// /* -------------------------------------------------------------------------- */
// /*                                   TYPEDEF                                  */
// /* -------------------------------------------------------------------------- */
 
// /* -------------------------------------------------------------------------- */
// /*                                  FUNCTIONS                                 */
// /* -------------------------------------------------------------------------- */
 
// /* -------------------------------------------------------------------------- */
// /*                                  PROTOTYPE                                 */
// /* -------------------------------------------------------------------------- */

// int wait_counter = 0;
// lv_timer_t * wait_iterator_task;

// //this function iterates a timer oncer per second 
// void wait_iterator(lv_timer_t * t){
// 	wait_counter++;
// }

// int main() {
// 	lv_init();
// 	backend_init();
	
// 	//wait_iterator_task = lv_timer_create(wait_iterator,1000,NULL);

// 	// lv_obj_t * label1 = lv_label_create(lv_scr_act());
// 	// lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
// 	// lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
// 	// lv_label_set_text(label1, "#0000ff Hello# #ff00ff world# #ff0000 - the LVGL and MbedOS#");
// 	// lv_obj_set_width(label1, 150);
// 	// lv_obj_align(label1, LV_ALIGN_TOP_MID, 0, 20);

// 	// lv_obj_t * label2 = lv_label_create(lv_scr_act());
// 	// lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
// 	// lv_obj_set_width(label2, 150);
// 	// lv_label_set_text(label2, "It is a circularly scrolling text. ");
// 	// lv_obj_align(label2, LV_ALIGN_BOTTOM_MID, 0, 0);

// 	// lv_obj_set_size(lv_scr_act(),400,400);

// 	//lv_demo_widgets();
// 	load_splash();

// 	//while (wait_counter < 5) {
// 	//	lv_timer_handler();
// 	//}
// 	//lv_timer_del(wait_iterator_task);
	
	
// 	backend_loop();
// }
 
#include <mbed.h>
#include "bsp_drivers/stm32469i_discovery_lcd.h"
#include "lvgl.h"
#include "lv_conf.h"

#define TICK_DEF 10
#define TICKER_TIME 0.001 * TICK_DEF

Ticker ticker;                                             /*Initialize your system tick*/
//LCD_DISCO_F469NI lcd;                      /*Initialize your display driver*/
//TS_DISCO_F469NI ts;                          /*Initialize your touchpad driver*/                      
//TS_StateTypeDef TS_State;                   /*Initialize your touch state sctruct*/

void lv_ticker_func();
void my_disp_flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p);
//bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data);
//static void event_handler(lv_obj_t * obj, lv_event_t event);

int main() {

  // put your setup code here, to run once:
  //printf("Example of MbedOS5 with LittlevGL on Disco F746NI \n");
  //lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"LittlevGL DEMO", CENTER_MODE);

  lv_init(); 
  wait_us(500000);

  ticker.attach(&lv_ticker_func,TICKER_TIME);
                                /*Initialize the LittlevGL*/

  BSP_LCD_Init();
	BSP_LCD_InitEx(LCD_ORIENTATION_LANDSCAPE);
	BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER_BACKGROUND, LCD_FB_START_ADDRESS);
  BSP_LCD_SetFont(&Font20);
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /*A static or global variable to store the buffers*/
  static lv_disp_draw_buf_t disp_buf;

  /*Static or global buffer(s)*/
  static lv_color_t buf[LV_HOR_RES_MAX * 10];//**strong text**; /*Declare a buffer for 10 lines*/

  lv_disp_draw_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10); /*Initialize the display buffer*/

  /*Implement and register a function which can copy a pixel array to an area of your display*/
  static lv_disp_drv_t disp_drv;               /*Descriptor of a display driver*/
  
  lv_disp_drv_init(&disp_drv);          /*Basic initialization*/
  disp_drv.flush_cb = my_disp_flush;    /*Set your driver function*/
  disp_drv.draw_buf = &disp_buf;          /*Assign the buffer to the display*/
  disp_drv.hor_res = LV_HOR_RES_MAX;                 /*Set the horizontal resolution in pixels*/
  disp_drv.ver_res = LV_VER_RES_MAX;
  lv_disp_drv_register(&disp_drv);      /*Finally register the driver*/

  lv_obj_t * label1 = lv_label_create(lv_scr_act());
  lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
  lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
  lv_label_set_text(label1, "#0000ff Hello# #ff00ff world# #ff0000 - the LVGL and MbedOS#");
  lv_obj_set_width(label1, 150);
  lv_obj_align(label1, LV_ALIGN_TOP_MID, 0, 20);

  lv_obj_t * label2 = lv_label_create(lv_scr_act());
  lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
  lv_obj_set_width(label2, 150);
  lv_label_set_text(label2, "It is a circularly scrolling text. ");
  lv_obj_align(label2, LV_ALIGN_BOTTOM_MID, 0, 0);

  lv_obj_set_size(lv_scr_act(),400,400);
  while(1) {
    // put your main code here, to run repeatedly:
    lv_task_handler(); /*Call lv_task_handler() periodically every few milliseconds. It will redraw the screen if required, handle input devices etc.*/
    wait_us(10000);
  }
}


void lv_ticker_func(){
    lv_tick_inc(TICK_DEF); /*Call lv_tick_inc(x) every x milliseconds in a Timer or Task (x should be between 1 and 10). It is required for the internal timing of LittlevGL.*/
}

void my_disp_flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
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

// bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
// {
//     static lv_coord_t last_x = 0;
//     static lv_coord_t last_y = 0;

//     /*Save the state and save the pressed coordinate*/
//     ts.GetState(&TS_State);

//     if(TS_State.touchDetected == 0){
//         data->state = LV_INDEV_STATE_PR;
//     }else{
//         data->state = LV_INDEV_STATE_REL;
//     }
    
//     //data->state = tttt ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL; 
//     if(data->state == LV_INDEV_STATE_PR){
//          //touchpad_get_xy(&last_x, &last_y);
//         last_x = TS_State.touchX[0];
//         last_y = TS_State.touchY[0];
//     }
   
//     /*Set the coordinates (if released use the last pressed coordinates)*/
//     data->point.x = last_x;
//     data->point.y = last_y;
    

//     return false; /*Return `false` because we are not buffering and no more data to read*/
// }

// static void event_handler(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED) {
//         printf("Clicked\n");
//     }
//     else if(event == LV_EVENT_VALUE_CHANGED) {
//         printf("Toggled\n");
//     }
// }