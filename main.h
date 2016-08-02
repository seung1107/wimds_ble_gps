/******************************************************************************
* Project Name      : PSoC_4_BLE_Eddystone
* File Name         : main.h
* Version           : 1.0
* Device Used       : CY8C4247LQI-BL483
* Software Used     : PSoC Creator 3.3 SP1
* Compiler          : ARM GCC 4.9.3, ARM MDK Generic
* Related Hardware  : CY8CKIT-042-BLE Bluetooth Low Energy Pioneer Kit
* Owner             : DEJO
*
*******************************************************************************
* Copyright (2016), Cypress Semiconductor Corporation. All Rights Reserved.
*******************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international treaty
* provisions. Cypress hereby grants to licensee a personal, non-exclusive,
* non-transferable license to copy, use, modify, create derivative works of,
* and compile the Cypress Source Code and derivative works for the sole
* purpose of creating custom software in support of licensee product to be
* used only in conjunction with a Cypress integrated circuit as specified in
* the applicable agreement. Any reproduction, modification, translation,
* compilation, or representation of this software except as specified above
* is prohibited without the express written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges.
*
* Use of this Software may be limited by and subject to the applicable Cypress
* software license agreement.
******************************************************************************/

#ifndef __MAIN_H__
#define __MAIN_H__

#include <project.h>
#include <stdbool.h>
#include <stdio.h>
#include "debug.h"

/*******************************************************************************
* Macros and Constants
*******************************************************************************/
#define YES                             (1)
#define NO                              (0)

#define LED_ON                          (0)
#define LED_OFF                         (1)

#define TEMPERATURE_SENSOR_ENABLE       (YES)
#define BATTERY_MEASUREMENT_ENABLE      (YES)

#define WCO_STARTUP_PERIOD              ((uint32)(32767 / 2))  /* 500 msec */
#define ECO_STARTUP_PERIOD              ((uint32)(32 * 3.5))   /* 3.5 msec */

#define MAX_UART_GPS_DATA_COUNT         (512)
/******************************************************************************
* Function prototype
*******************************************************************************/
void LowPower(void);
void SetAdvPacketCount(uint32 value);
uint32 GetAdvPacketCount(void);
bool IsConnAdvStart(void);

extern CYBLE_API_RESULT_T apiResult;
extern uint8 g_u8GPSData[MAX_UART_GPS_DATA_COUNT];
extern uint16 g_u16GPSDataCount;
extern uint8 GPS_DATA[16];

#endif  /* __MAIN_H__   */
/* [] END OF FILE */
