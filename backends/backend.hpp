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
typedef struct 
{
	uint8_t ams_state;
	bool 	apps_disagree;
	bool 	trailbraking_active;
	bool	precharge_pressed;
	bool	drive_pressed;
	/* error */
	bool	error_bspd;
	bool 	error_imd;
	bool 	error_pdoc_precharge;
	bool 	error_pdoc_discharge;
	uint8_t	error_ams;
} VehicleState;

typedef struct
{
	uint8_t motor_speed; 
	float	motor_temp;
	uint8_t mc_voltage;
	float	mc_temp;
  	uint8_t coolant_flow;
  	float 	coolant_temp;
} MotorInfo;

typedef struct
{
	uint8_t pack_voltage;
  	int8_t  pack_current;
	float 	min_cell_volt;
	float 	max_temp; 
} AccumulatorInfo;

typedef struct
{
	uint8_t lv_bus_voltage;
	uint8_t throttle_pct;
	uint8_t brake_pct;
	uint8_t regen_pct;
} MiscInfo;


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
