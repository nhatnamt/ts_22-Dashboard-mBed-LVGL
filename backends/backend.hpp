/**
  ******************************************************************************
  * @file    driver.hpp
  * @author  Nam Tran
  * @version 1.0
  * @brief   Backend driver, defining all common structs and functions in hear. 
  * Definition of the function varries dependent on the compiling target (emulator or the disco)
  ******************************************************************************
*/

/* ---------------------------------- Guard --------------------------------- */
#pragma once
#ifdef __cplusplus
 extern "C" {
#endif

/* -------------------------------------------------------------------------- */
/*                                  INCLUDES                                  */
/* -------------------------------------------------------------------------- */
#include "stdint.h"
#include "stdbool.h"

/* -------------------------------------------------------------------------- */
/*                                   STRUCTS                                  */
/* -------------------------------------------------------------------------- */
struct VehicleState
{
	uint8_t ams_state 				= 0;
	bool 	apps_disagree 			= false;
	bool 	trailbraking_active 	= false;
	bool	precharge_pressed 		= false;
	bool	drive_pressed 			= false;
};

struct MotorInfo
{
	uint8_t motor_speed			= 0; 
	float	motor_temp 			= 0;
	uint8_t mc_voltage 			= 0;
	float	mc_temp 			= 0;
  	uint8_t coolant_flow 		= 0;
  	float 	coolant_temp 		= 0;
};

struct AccumulatorInfo
{
	uint8_t pack_voltage 		= 0;
  	int8_t  pack_current  		= 0;
	uint8_t min_cell_volt		= 0;
	float 	max_temp 			= 0; 
};

struct MiscInfo
{
	uint8_t lv_bus_voltage		= 0;
	uint8_t throttle_pct		= 0;
	uint8_t brake_pct			= 0;
	uint8_t regen_pct			= 0;
};


/* -------------------------------------------------------------------------- */
/*                              GLOBAL PROTOTYPE                              */
/* -------------------------------------------------------------------------- */
void backend_init();
void backend_loop();

VehicleState		can_get_vehicle_state();
MotorInfo			can_get_motor_info();
AccumulatorInfo		can_get_accum_info();
MiscInfo			can_get_misc_info();

/* --------------------------------- Guards --------------------------------- */
#ifdef __cplusplus
}
#endif
