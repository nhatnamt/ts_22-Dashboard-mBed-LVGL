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
#include "backend.hpp"
#include "lvgl.h"
#include "bsp_drivers/stm32469i_discovery_lcd.h"
#include "lv_conf.h"
#include "tft/tft.h"
#include "mbed.h"

#include "touchpad/touchpad.h"

#include "can_addresses.h"

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

CAN                     can1(PB_8, PB_9);
//CAN                     can1(PB_9, PB_13);
CANMessage              can1_msg;

CAN                     can2(PB_5, PB_13);
// DigitalOut              can2_rx_led(LED3);
// DigitalOut              can2_tx_led(LED4);
CANMessage              can2_msg;

Ticker                  ticker_heartbeat;
Ticker                  ticker_can_transmit;
Ticker					ticker_lvgl;

//VehicleInfo vehicle_info;

/* -------------------------------------------------------------------------- */
/*                              STATIC VARIABLES                              */
/* -------------------------------------------------------------------------- */
static int16_t mc_temp = 0;
static int16_t motor_temp = 0;
static int16_t accum_temp = 0;
static int16_t coolant_temp = 0;
static int16_t coolant_flow = 0;
static int16_t lowest_cell_volt = 0;
static uint8_t throttle_pct = 0;
static int16_t accum_volt = 0;
static int16_t accum_current = 0;
static uint8_t ams_state = 0;
static int16_t precharge_pressed = 0;
static uint8_t drive_pressed = 0;
static uint8_t bspd_error = 0;

int                     heartbeat_counter = 0;
/* -------------------------------------------------------------------------- */
/*                                  CALLBACKS                                 */
/* -------------------------------------------------------------------------- */
void heartbeat_cb()
{
    if (mc_temp >= 100)
    {
        mc_temp = 0;
        motor_temp = 0;
        accum_temp = 0;
        coolant_temp = 0;
        coolant_flow = 0;
        lowest_cell_volt = 0;
        throttle_pct = 0;
        accum_volt = 0;
        accum_current = 0;
        ams_state = 0;
    }
    else
    {
        mc_temp++;
        motor_temp++;
        accum_temp++;
        coolant_temp++;
        coolant_flow++;
        lowest_cell_volt++;
        throttle_pct++;
        accum_volt++;
        accum_current++;
        ams_state++;
    }
	led1 = !led1;
	heartbeat_counter++;
    char TX_data[2] = {(char)0, (char)heartbeat_counter};
    if(can2.write(CANMessage(CAN_DASH_BASE_ADDRESS, &TX_data[0], 2))) 
    {
        printf("Heartbeat Success! State: %d Counter: %d\n", 2, heartbeat_counter);
    }else
    {
        printf("Hearts dead :(\r\n");
    }
}

void lv_ticker_func()
{
    lv_tick_inc(TICK_DEF);

}

void can2_recv_cb()
{
    if (can2.read(can2_msg))
    {
        switch (can2_msg.id)
        {
        case (CAN_MOTEC_THROTTLE_CONTROLLER_BASE_ADDRESS + TS_DIGITAL_1_ID):
            bspd_error = can2_msg.data[0];
            break;
        
        default:
            break;
        }
    }
}
/* -------------------------------------------------------------------------- */
/*                              GLOBAL FUNCTIONS                              */
/* -------------------------------------------------------------------------- */
int16_t can_get_mc_temp() {return mc_temp;}
int16_t can_get_motor_temp() {return motor_temp;}
int16_t can_get_accum_temp() {return accum_temp;}
int16_t can_get_coolant_temp() {return coolant_temp;}
int16_t can_get_coolant_flow() {return coolant_flow;}
int16_t can_get_lowest_cell_volt() {return lowest_cell_volt;}
uint8_t can_get_throttle_pct() {return throttle_pct;}
int16_t can_get_accum_volt() {return accum_volt;}
int16_t can_get_accum_current() {return accum_current;}
uint8_t can_get_ams_state() {return ams_state;}
uint8_t can_get_precharge_button() {return precharge_pressed;}
uint8_t can_get_drive_button() {return drive_pressed;}
uint8_t can_get_bspd_error() {return bspd_error;}

void backend_init()
{
    can2.frequency(500000);
    can2.attach(&can2_recv_cb);
    ticker_heartbeat.attach(&heartbeat_cb,1s);

    //printf("Hi!\r\n");
    ticker_lvgl.attach(&lv_ticker_func,TICKER_TIME);


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