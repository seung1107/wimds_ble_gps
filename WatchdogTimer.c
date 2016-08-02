/******************************************************************************
* Project Name      : PSoC_4_BLE_Eddystone
* File Name         : WatchDogTimer.c
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
*******************************************************************************/

#include <Project.h>
#include "main.h"
#include "WatchdogTimer.h"

#define SEC_CNT_INC_PER_2SEC        (20u)

/*******************************************************************************
* Global variables
*******************************************************************************/
/* This flag when true indicates the BLE stack is on. */
static bool enableSecCnt = false;

/* True when counter1 interrupt is triggred atleast once */
static bool counter1TimedOut;

/* Keeps track of SEC_CNT feild of TLM packet. */
static uint32 SecCnt = 0;

/*******************************************************************************
* Function Name: SetEnableSecCnt
********************************************************************************
*
* Summary:
*  Enable or disable the increment of SEC_CNT feild of TLM packet.
*
* Parameters:
*  bool: 0 - Disable the counter
*        1 - Enable the counter
*
* Return:
*  None
*
*******************************************************************************/
void SetEnableSecCnt(bool value)
{
    enableSecCnt = value;
}

/*******************************************************************************
* Function Name: SetSecCnt
********************************************************************************
*
* Summary:
*  Sets value of SEC_CNT feild of TLM packet.
*
* Parameters:
*  uint32: value to initialize SecCnt
*
* Return:
*  None
*
*******************************************************************************/
void SetSecCnt(uint32 value)
{
    SecCnt = value;
}

/*******************************************************************************
* Function Name: GetSecCnt
********************************************************************************
*
* Summary:
*  Returns value of SEC_CNT feild of TLM packet.
*
* Parameters:
*  None
*
* Return:
*  uint32: value of SecCnt
*
*******************************************************************************/
uint32 GetSecCnt(void)
{
    return SecCnt;
}

/*******************************************************************************
* Function Name: WDT_Handler
********************************************************************************
*
* Summary:
*  Watchdog timer(WDT) interrupt handler routine. WDT is used to wakeup the
*  device after WCO or ECO has started and for advertisement payload updates.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(WDT_Handler)
{
    uint32 tempCnt;

    /* WDT interrupt is only used as a source of wakeup for PSoC 4 BLE device
    *  in this example project. Clearing the WDT interrupt status is all that is
    *  required in this example project
    */
    if(CySysWdtGetInterruptSource() & CY_SYS_WDT_COUNTER0_INT)
    {
        /* WDT counter is configured to trigger interrupt at every 2 seconds */
        if(enableSecCnt == true)
        {
            /* Time should be of 0.1 seconds(100ms) resolution. As interrupt
            *  triggers at every ~2 seconds, hence 2000 / 100 = 20 */
            tempCnt = SecCnt + SEC_CNT_INC_PER_2SEC;

            /* On timer overflow reset both timer and packet count */
            if(tempCnt < SecCnt)
            {
                /* timeSincePowerOn is reset */
                SecCnt = 0;
                /* advPacketCount is reset */
                SetAdvPacketCount(0);
            }
            else
            {
                SecCnt = tempCnt;
            }
        }

        CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
    }

    if(CySysWdtGetInterruptSource() & CY_SYS_WDT_COUNTER1_INT)
    {
        CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER1_INT);
        counter1TimedOut = true;
    }
}

/*******************************************************************************
* Function Name: WDT_Initialize
********************************************************************************
*
* Summary:
*  Configures a watchdog counter with the given count and interrupt period.
*
* Parameters:
*  uint32: counter number
*  uint32: set the period for the counter interrupt
*
* Return:
*  None
*
*******************************************************************************/
void WDT_Initialize(uint32 counterNum, uint32 period)
{
    /* Unlock the WDT registers for modification. Note that WDT is running from
    *  ILO now */
    CySysWdtUnlock();

    /* Configure counter # in interrupt mode */
    CySysWdtWriteMode(counterNum, CY_SYS_WDT_MODE_INT);

    /* counter # with specified period */
    CySysWdtWriteClearOnMatch(counterNum, COUNTER_ENABLE);

    /* counter # with specified period */
    CySysWdtWriteMatch(counterNum, period);

    /* Lock WDT timer */
    CySysWdtLock();
}

/*******************************************************************************
* Function Name: WDT_EnableCounter
********************************************************************************
*
* Summary:
*  Enables WDT counter #
*
* Parameters:
*  uint32: counter mask
*
* Return:
*  None
*
*******************************************************************************/
void WDT_EnableCounter(uint32 counterMask)
{
    CySysWdtUnlock();

    CySysWdtEnable(counterMask);

    CySysWdtLock();
}

/*******************************************************************************
* Function Name: WDT_DisableCounter
********************************************************************************
*
* Summary:
*  Disable WDT counter #
*
* Parameters:
*  uint32: counter mask
*
* Return:
*  None
*
*******************************************************************************/
void WDT_DisableCounter(uint32 counterMask)
{
    CySysWdtUnlock();

    CySysWdtDisable(counterMask);

    CySysWdtLock();
}

/*******************************************************************************
* Function Name: LowPowerWait
********************************************************************************
*
* Summary:
*   This function waits in low power for a certain period.
*
* Parameters:
*  uint32: period to wait for while in low power state
*
* Return:
*  None
*
*******************************************************************************/
void LowPowerWait(uint32 period)
{
    /* Reset timeout flag */
    counter1TimedOut = false;

    /* Setup counter0 for ECO startup */
    WDT_Initialize(CY_SYS_WDT_COUNTER1, period);

    /* Enable WDT counter 1 */
    WDT_EnableCounter(CY_SYS_WDT_COUNTER1_MASK);

    do
    {
        /* Put CPU and BLESS to low power mode */
        LowPower();
    } while(counter1TimedOut == false);

    /* Disable counter 1 */
    WDT_DisableCounter(CY_SYS_WDT_COUNTER1_MASK);
}

/* [] END OF FILE */
