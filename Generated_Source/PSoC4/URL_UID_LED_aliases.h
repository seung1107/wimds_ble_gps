/*******************************************************************************
* File Name: URL_UID_LED.h  
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

#if !defined(CY_PINS_URL_UID_LED_ALIASES_H) /* Pins URL_UID_LED_ALIASES_H */
#define CY_PINS_URL_UID_LED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define URL_UID_LED_0			(URL_UID_LED__0__PC)
#define URL_UID_LED_0_PS		(URL_UID_LED__0__PS)
#define URL_UID_LED_0_PC		(URL_UID_LED__0__PC)
#define URL_UID_LED_0_DR		(URL_UID_LED__0__DR)
#define URL_UID_LED_0_SHIFT	(URL_UID_LED__0__SHIFT)
#define URL_UID_LED_0_INTR	((uint16)((uint16)0x0003u << (URL_UID_LED__0__SHIFT*2u)))

#define URL_UID_LED_INTR_ALL	 ((uint16)(URL_UID_LED_0_INTR))


#endif /* End Pins URL_UID_LED_ALIASES_H */


/* [] END OF FILE */
