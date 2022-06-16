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
  *-----------------------------
  *!Look at mbed json for more info
  ******************************************************************************
*/
/* -------------------------------------------------------------------------- */
/*                                  INCLUDES                                  */
/* -------------------------------------------------------------------------- */
#include "driver.hpp"
#include "lvgl.h"
#include "bsp_drivers/stm32469i_discovery_lcd.h"
#include "lv_conf.h"
#include "tft/tft.h"
#include "mbed.h"

#include "touchpad/touchpad.h"

#include "bsp_drivers\stm32469i_discovery.h"
#include "bsp_drivers\stm32469i_discovery_ts.h"


/* -------------------------------------------------------------------------- */
/*                                   DEFINES                                  */
/* -------------------------------------------------------------------------- */
#define DASH_HEARTRATE 1.0
#define TICK_DEF 5
#define TICKER_TIME 5ms


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

//VehicleInfo vehicle_info;

/* -------------------------------------------------------------------------- */
/*                              STATIC VARIABLES                              */
/* -------------------------------------------------------------------------- */

static int16_t mc_temp = 0;
/* -------------------------------------------------------------------------- */
/*                                  CALLBACKS                                 */
/* -------------------------------------------------------------------------- */
void heartbeat_cb()
{
    if (mc_temp >= 100)
    {
        mc_temp = 0;
    }
    else
    {
        mc_temp++;
    }
	led1 = !led1;
	
}

void lv_ticker_func()
{
    lv_tick_inc(TICK_DEF);

}

/* -------------------------------------------------------------------------- */
/*                              GLOBAL FUNCTIONS                              */
/* -------------------------------------------------------------------------- */
int16_t can_get_mc_temp(void)
{
    return mc_temp;
}

void backend_init()
{
    //printf("Hi!\r\n");
    ticker_lvgl.attach(&lv_ticker_func,TICKER_TIME);
    ticker_heartbeat.attach(&heartbeat_cb,10ms);


    tft_init();
    touchpad_init();
    //wait_us(1000000);
}


void backend_loop()
{
	//keep the backend running
    while(1) {
        lv_task_handler();
        wait_us(TICK_DEF*1000);
    }   

}

// void touchpad_init(void)
// {
//     BSP_TS_Init(TFT_HOR_RES, TFT_VER_RES);
//     static lv_indev_drv_t indev_drv;
//     lv_indev_drv_init(&indev_drv);            /*Basic initialization*/
//     indev_drv.type = LV_INDEV_TYPE_POINTER;
//     indev_drv.read_cb = touchpad_read;       /*This function will be called periodically (by the library) to get the mouse position and state*/
//     lv_indev_drv_register(&indev_drv);
// }
 
// static void touchpad_read(lv_indev_drv_t *indev, lv_indev_data_t *data)
// {
//     // Read your touchpad
//     printf("I'm in here\r\n");
//     //printf(" Don't Touch me you pervert! Points touched: %d \r\n",TS_State.touchDetected);
//     BSP_TS_GetState(&TS_State);
//     if(TS_State.touchDetected) {
//         data->point.x = TS_State.touchX[0];
//         data->point.y = TS_State.touchY[0];
//         data->state = LV_INDEV_STATE_PR;
//         printf(" Don't Touch me you pervert! Touched at %d, %d \r\n",data->point.x,data->point.y);
//     } else {
//         data->point.x = 0;
//         data->point.y = 0;
//         data->state = LV_INDEV_STATE_REL;
//     }
//     //return false;   //false: no more data to read because we are no buffering
// }