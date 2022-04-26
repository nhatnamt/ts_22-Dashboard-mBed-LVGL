/**
  ******************************************************************************
  * @file    driver.hpp
  * @author  Nam Tran
  * @version 1.0
  * @brief   Hardware backen driver source for the STM32469I-Discovery with custom "disco" board
  *          - TEAM SWINBURNE
  ******************************************************************************
  * @details Ultilising the mbed platform, ported from the TS_19 dash code
  * ----------------------------
  * Definitions and declarations
  *     CAN objects
  * 	Tickers
  * ----------------------------
  * Functions
  *     fafa
  *
  ******************************************************************************
*/
/* -------------------------------------------------------------------------- */
/*                                  INCLUDES                                  */
/* -------------------------------------------------------------------------- */
#include "driver.hpp"
#include "lvgl.h"
#include "bsp_drivers/stm32469i_discovery_lcd.h"
#include "lv_conf.h"
//#include "tft/tft.h"

/* -------------------------------------------------------------------------- */
/*                                   DEFINES                                  */
/* -------------------------------------------------------------------------- */
#define DASH_HEARTRATE 1.0
#define TICK_DEF 10
#define TICKER_TIME 0.001 * TICK_DEF


DigitalOut 				led1(LED1);
DigitalOut 				led2(LED2);

// CAN                     can1(PB_5, PB_13);
// CANMessage              can1_msg;

// CAN                     can2(PB_8, PB_9);
// DigitalOut              can2_rx_led(LED3);
// DigitalOut              can2_tx_led(LED4);
// CANMessage              can2_msg;

Ticker                  ticker_heartbeat;
Ticker                  ticker_can_transmit;
Ticker					ticker_lvgl;

//cause mBed has to make things complicated
BufferedSerial pc(PB_10, PB_11,115200);
FILE* pcStream = fdopen(&pc, "r+");

VehicleInfo vehicle_info;

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
    disp_drv.flush_cb = tft_flush;        /*Set a flush callback to draw to the display*/
    disp_drv.hor_res = LV_HOR_RES_MAX;                 /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = LV_VER_RES_MAX;               /*Set the vertical resolution in pixels*/

    // lv_area_t area;
	// lv_color_t c = lv_color_hex(0xFF00FF00);

    // area.x1 = 0;
	// area.y1 = 0;
	// area.x2 = 300;
	// area.y2 = 400;
    // //tft_flush(&disp_drv,&area, &c);
    
    lv_disp_drv_register(&disp_drv); 
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

/* -------------------------------------------------------------------------- */
/*                                  CALLBACKS                                 */
/* -------------------------------------------------------------------------- */
void heartbeat_cb()
{
	vehicle_info.dash_heartbeat_counter++;
	//can2_rx_led = led1;
	led1 = !led1;
	
}

void lv_ticker_func()
{
    lv_tick_inc(TICK_DEF);
}

void backend_init()
{
  	ticker_lvgl.attach(&lv_ticker_func,TICKER_TIME);
      
    tft_init();
	//ticker_heartbeat.attach(&heartbeat_cb, DASH_HEARTRATE);
	
}

void backend_loop()
{
	//keep the backend running
    while(1) {
    // put your main code here, to run repeatedly:
        lv_task_handler(); /*Call lv_task_handler() periodically every few milliseconds. It will redraw the screen if required, handle input devices etc.*/
        wait_us(10000);
    }
}