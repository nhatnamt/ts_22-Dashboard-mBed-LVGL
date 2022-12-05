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

/* -------------------------------------------------------------------------- */
/*                                 CPP OBJECTS                                */
/* -------------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------------- */
/*                              STATIC VARIABLES                              */
/* -------------------------------------------------------------------------- */
static VehicleState		    vehicle_state={0,false,false,false,false,false,false,false,false};
static MotorInfo		    motor_info={0,0,0,0,0,0.0f};
static AccumulatorInfo		accum_info={0,0,0,0};
static MiscInfo			    misc_info={0,0,0,0};

int                     heartbeat_counter = 0;
/* -------------------------------------------------------------------------- */
/*                                  CALLBACKS                                 */
/* -------------------------------------------------------------------------- */
void heartbeat_cb()
{
	led1 = !led1;
	heartbeat_counter++;
    char TX_data[2] = {(char)0, (char)heartbeat_counter};
    if(can2.write(CANMessage(CAN_DASH_BASE_ADDRESS, &TX_data[0], 2))) 
    {
        //printf("Heartbeat Success! State: %d Counter: %d\n", 2, heartbeat_counter);
    }else
    {
        //printf("Hearts dead :(\r\n");
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
        case (CAN_ORION_BMS_BASE_ADDRESS):
            break;
        case (CAN_BRAKE_MODULE_BASE_ADDRESS+TS_DIGITAL_1_ID):
            vehicle_state.error_bspd = can2_msg.data[4];
            break;
        case (CAN_BRAKE_MODULE_BASE_ADDRESS+TS_ANALOGUE_1_ID):
            misc_info.brake_pct = can2_msg.data[2];
            break;
        case (CAN_MOTEC_THROTTLE_CONTROLLER_BASE_ADDRESS + TS_DIGITAL_1_ID):
            vehicle_state.precharge_pressed = can2_msg.data[0]; //buttons
            vehicle_state.drive_pressed = can2_msg.data[1];
            break;
        case (CAN_MOTEC_THROTTLE_CONTROLLER_BASE_ADDRESS + TS_ANALOGUE_1_ID):
            misc_info.throttle_pct = can2_msg.data[2];
            break;
        case (CAN_MOTEC_THROTTLE_CONTROLLER_BASE_ADDRESS + TS_ANALOGUE_2_ID):
            misc_info.lv_bus_voltage = (can2_msg.data[0]*256+(can2_msg.data[1]))/10.0f;
            break;
        case (CAN_MOTEC_THROTTLE_CONTROLLER_BASE_ADDRESS + TS_ANALOGUE_3_ID):
            motor_info.mc_temp = max(can2_msg.data[0],can2_msg.data[1]);
            motor_info.motor_temp = max(can2_msg.data[2], can2_msg.data[3]);
            break;
        case (CAN_ORION_BMS_BASE_ADDRESS + TS_ANALOGUE_3_ID):
            accum_info.pack_voltage = (can2_msg.data[0]*256 + can2_msg.data[1])/10;
            accum_info.pack_current = (can2_msg.data[4]*256 + can2_msg.data[5])/10;
            break;
        case (CAN_PRECHARGE_CONTROLLER_BASE_ADDRESS + TS_HEARTBEAT_ID):
            vehicle_state.ams_state = can2_msg.data[0];
            break;
        case (CAN_ORION_BMS_BASE_ADDRESS + TS_ANALOGUE_2_ID):
            accum_info.max_temp = can2_msg.data[2];
            break;
        default:
            break;
        }
    }
}
/* -------------------------------------------------------------------------- */
/*                              GLOBAL FUNCTIONS                              */
/* -------------------------------------------------------------------------- */
VehicleState		can_get_vehicle_state() {return vehicle_state;}
MotorInfo			can_get_motor_info() {return motor_info;}
AccumulatorInfo		can_get_accum_info() {return accum_info;}
MiscInfo			can_get_misc_info() {return misc_info;}

void backend_init()
{
    // thread_sleep_for(5000);
    // lv_init();
    	// Disable interrupts for smooth startup routine.
	thread_sleep_for(1000);
	
	__disable_irq();

    can2.frequency(500000);
    can2.attach(&can2_recv_cb);
    ticker_heartbeat.attach(&heartbeat_cb,1s);

    //printf("Hi!\r\n");
    ticker_lvgl.attach(&lv_ticker_func,TICKER_TIME);

   	// Re-enable interrupts again, now that interrupts are ready.
	__enable_irq();

	// Allow some time to settle!
	thread_sleep_for(1000);

    tft_init();
    touchpad_init();
   

}


void backend_loop()
{
	//keep the backend running
    while(1) {
        lv_task_handler();
        wait_us(TICK_DEF*1000);
    }   

}