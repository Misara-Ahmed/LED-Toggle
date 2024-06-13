 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Misara Ahmed
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION                (1U)
#define PORT_CFG_SW_MINOR_VERSION                (0U)
#define PORT_CFG_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION        (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION        (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION        (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/*******************************************************************************
 *                              Optional APIs                                  *
 *******************************************************************************/
/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for presence of Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Pre-compile option for presence of Port_SetPinMode API */
#define PORT_SET_PIN_MODE_API                (STD_ON)

/*******************************************************************************
 *                              MCU Definitions                                *
 *******************************************************************************/
/* Number of microcontroller pins */
#define MCU_PINS                                (43U)

/* Ports*/
#define PORT_A_ID                               (0U)
#define PORT_B_ID                               (1U)
#define PORT_C_ID                               (2U)
#define PORT_D_ID                               (3U)
#define PORT_E_ID                               (4U)
#define PORT_F_ID                               (5U)

/* Pins */
#define PORT_PIN_0                              (0U)
#define PORT_PIN_1                              (1U)
#define PORT_PIN_2                              (2U)
#define PORT_PIN_3                              (3U)
#define PORT_PIN_4                              (4U)
#define PORT_PIN_5                              (5U)
#define PORT_PIN_6                              (6U)
#define PORT_PIN_7                              (7U)

/* PORT A pins*/
#define PORT_A_PIN_0                            (0U)
#define PORT_A_PIN_1                            (1U)
#define PORT_A_PIN_2                            (2U)
#define PORT_A_PIN_3                            (3U)
#define PORT_A_PIN_4                            (4U)
#define PORT_A_PIN_5                            (5U)
#define PORT_A_PIN_6                            (6U)
#define PORT_A_PIN_7                            (7U)

/* PORT B pins*/
#define PORT_B_PIN_0                            (8U)
#define PORT_B_PIN_1                            (9U)
#define PORT_B_PIN_2                            (10U)
#define PORT_B_PIN_3                            (11U)
#define PORT_B_PIN_4                            (12U)
#define PORT_B_PIN_5                            (13U)
#define PORT_B_PIN_6                            (14U)
#define PORT_B_PIN_7                            (15U)

/* PORT C pins*/
#define PORT_C_PIN_0                            (16U)
#define PORT_C_PIN_1                            (17U)
#define PORT_C_PIN_2                            (18U)
#define PORT_C_PIN_3                            (19U)
#define PORT_C_PIN_4                            (20U)
#define PORT_C_PIN_5                            (21U)
#define PORT_C_PIN_6                            (22U)
#define PORT_C_PIN_7                            (23U)

/* PORT D pins*/
#define PORT_D_PIN_0                            (24U)
#define PORT_D_PIN_1                            (25U)
#define PORT_D_PIN_2                            (26U)
#define PORT_D_PIN_3                            (27U)
#define PORT_D_PIN_4                            (28U)
#define PORT_D_PIN_5                            (29U)
#define PORT_D_PIN_6                            (30U)
#define PORT_D_PIN_7                            (31U)

/* PORT E pins*/
#define PORT_E_PIN_0                            (32U)
#define PORT_E_PIN_1                            (33U)
#define PORT_E_PIN_2                            (34U)
#define PORT_E_PIN_3                            (35U)
#define PORT_E_PIN_4                            (36U)
#define PORT_E_PIN_5                            (37U)

/* PORT F pins*/
#define PORT_F_PIN_0                            (38U)
#define PORT_F_PIN_1                            (39U)
#define PORT_F_PIN_2                            (40U)
#define PORT_F_PIN_3                            (41U)
#define PORT_F_PIN_4                            (42U)

/* Pin modes */
#define MAX_PIN_MODES                           (14U)

#endif /* PORT_CFG_H */