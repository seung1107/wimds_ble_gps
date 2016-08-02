/*******************************************************************************
* File Name: ConnectableState_LED.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ConnectableState_LED_ALIASES_H) /* Pins ConnectableState_LED_ALIASES_H */
#define CY_PINS_ConnectableState_LED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ConnectableState_LED_0			(ConnectableState_LED__0__PC)
#define ConnectableState_LED_0_PS		(ConnectableState_LED__0__PS)
#define ConnectableState_LED_0_PC		(ConnectableState_LED__0__PC)
#define ConnectableState_LED_0_DR		(ConnectableState_LED__0__DR)
#define ConnectableState_LED_0_SHIFT	(ConnectableState_LED__0__SHIFT)
#define ConnectableState_LED_0_INTR	((uint16)((uint16)0x0003u << (ConnectableState_LED__0__SHIFT*2u)))

#define ConnectableState_LED_INTR_ALL	 ((uint16)(ConnectableState_LED_0_INTR))


#endif /* End Pins ConnectableState_LED_ALIASES_H */


/* [] END OF FILE */
