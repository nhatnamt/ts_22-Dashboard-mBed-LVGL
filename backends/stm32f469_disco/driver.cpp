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
#include "tft/tft.h"

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