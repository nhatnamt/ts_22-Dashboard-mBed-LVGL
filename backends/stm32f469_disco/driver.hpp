/**
  ******************************************************************************
  * @file    driver.hpp
  * @author  Nam Tran
  * @version 1.0
  * @brief   Hardware driver header for the STM32469I-Discovery with custom "disco" board
  *          - TEAM SWINBURNE
  ******************************************************************************
*/
/* --------------------------------- GUARDS --------------------------------- */
#ifndef DRIVER_H
#define DRIVER_H

/* -------------------------------------------------------------------------- */
/*                                  INCLUDES                                  */
/* -------------------------------------------------------------------------- */
#include "mbed.h"

/* -------------------------------------------------------------------------- */
/*                                   TYPEDEF                                  */
/* -------------------------------------------------------------------------- */
struct VehicleState
{
	uint8_t ams_state 			= 0;
	bool apps_disagree 			= false;
	bool trailbraking_active 	= false;
	bool precharge_pressed 		= false;
	bool drive_pressed 			= false;
};
struct MotorInfo
{
	uint8_t speed				= 0; 
	float	temp 				= 0;
	uint8_t mc_voltage 			= 0;
	float	mc_temp 			= 0;
};
struct AccumulatorInfo
{
	uint8_t pack_voltage 		= 0; 
	uint8_t cell_voltage 		= 0;
	float 	temp 				= 0; 
};
struct MiscInfo
{
	uint8_t lv_bus_voltage		= 0;
};
typedef struct
	{
		uint8_t dash_heartbeat_state 	= 0;
        uint8_t dash_heartbeat_counter 	= 0;
		struct VehicleState 	vehicle_state;
		struct MotorInfo 		motor;
		struct AccumulatorInfo 	accumulator;
		struct MiscInfo 		misc;
	}
	VehicleInfo;

/* -------------------------------------------------------------------------- */
/*                              GLOBAL PROTOTYPE                              */
/* -------------------------------------------------------------------------- */
void backend_init();
void backend_loop();

/* --------------------------------- GUARDS --------------------------------- */
#endif
