/******************************************************************************
* Project Name      : PSoC_4_BLE_Eddystone
* File Name         : Battery.c
* Version           : 1.0
* Device Used       : CY8C4247LQI-BL483
* Software Used     : PSoC Creator 3.3 SP1
* Compiler          : ARM GCC 4.9.3, ARM MDK Generic
* Related Hardware  : CY8CKIT-042-BLE Bluetooth Low Energy Pioneer Kit
* Owner             : DEJO
*
********************************************************************************
* Copyright (2016), Cypress Semiconductor Corporation. All Rights Reserved.
********************************************************************************
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
*******************************************************************************/
#include "main.h"
#include "Battery.h"
#include "WatchdogTimer.h"

/* Stores measured battery voltage in mV */
static uint16 batteryLevelmVolts;

/*******************************************************************************
* Function Name: MeasureBattery
********************************************************************************
*
* Summary:
*   This function measures the battery voltage and stores it.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MeasureBattery(void)
{
    int16   adcResult;
    uint32  sarControlReg;

    /* Wakeup ADC from sleep for measurements. */
    ADC_Wakeup();

    /* Set the reference to 1.024V and enable reference bypass */
    sarControlReg = ADC_SAR_CTRL_REG & ~ADC_VREF_MASK;
    ADC_SAR_CTRL_REG = sarControlReg | ADC_VREF_INTERNAL1024BYPASSED;

    /* 25 ms delay for reference capacitor to charge */
    LowPowerWait(REFERENCE_CAPACITOR_CHARGE_TIME);

    /* Set the reference to VDD and disable reference bypass */
    sarControlReg = ADC_SAR_CTRL_REG & ~ADC_VREF_MASK;
    ADC_SAR_CTRL_REG = sarControlReg | ADC_VREF_VDDA;

    /* Perform a measurement. Store this value in Vref. */
    LowPowerWait(VDD_REFERENCE_SWITCH_PERIOD);
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);

    /* Set the reference to 1.024V and enable reference bypass */
    sarControlReg = ADC_SAR_CTRL_REG & ~ADC_VREF_MASK;
    ADC_SAR_CTRL_REG = sarControlReg | ADC_VREF_INTERNAL1024BYPASSED;

    adcResult = ADC_GetResult16(ADC_BATTERY_CHANNEL);
    /* Calculate input voltage by using ratio of ADC counts from reference
    *  and ADC Full Scale counts. */
    batteryLevelmVolts = ((1024 * 2048) / adcResult) ;

    /* Put ADC to sleep after measurements are done. */
    ADC_Sleep();
}

/*******************************************************************************
* Function Name: GetMeasuredBatteryVoltage
********************************************************************************
*
* Summary:
*   This function returns currently measured voltage.
*
* Parameters:
*  None
*
* Return:
*  uint16: currently measured battery voltage
*
*******************************************************************************/
uint16 GetMeasuredBatteryVoltage(void)
{
    return batteryLevelmVolts;
}

/* [] END OF FILE */
