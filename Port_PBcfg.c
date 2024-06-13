 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Misara Ahmed
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION        (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION        (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION        (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_ALT_FUNC_REG_ALT_OFFSET)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */
Port_ConfigType Port_Configurations = {
                                            PORT_A_ID,PORT_PIN_0,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_A_ID,PORT_PIN_1,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_A_ID,PORT_PIN_2,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_A_ID,PORT_PIN_3,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_A_ID,PORT_PIN_4,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_A_ID,PORT_PIN_5,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_A_ID,PORT_PIN_6,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_A_ID,PORT_PIN_7,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,

                                            PORT_B_ID,PORT_PIN_0,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_B_ID,PORT_PIN_1,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_B_ID,PORT_PIN_2,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_B_ID,PORT_PIN_3,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_B_ID,PORT_PIN_4,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_B_ID,PORT_PIN_5,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_B_ID,PORT_PIN_6,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_B_ID,PORT_PIN_7,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,

                                            PORT_C_ID,PORT_PIN_0,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_C_ID,PORT_PIN_1,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_C_ID,PORT_PIN_2,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_C_ID,PORT_PIN_3,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_C_ID,PORT_PIN_4,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_C_ID,PORT_PIN_5,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_C_ID,PORT_PIN_6,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_C_ID,PORT_PIN_7,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,

                                            PORT_D_ID,PORT_PIN_0,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_D_ID,PORT_PIN_1,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_D_ID,PORT_PIN_2,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_D_ID,PORT_PIN_3,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_D_ID,PORT_PIN_4,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_D_ID,PORT_PIN_5,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_D_ID,PORT_PIN_6,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_D_ID,PORT_PIN_7,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,

                                            PORT_E_ID,PORT_PIN_0,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_E_ID,PORT_PIN_1,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_E_ID,PORT_PIN_2,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_E_ID,PORT_PIN_3,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_E_ID,PORT_PIN_4,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_E_ID,PORT_PIN_5,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            
                                            PORT_F_ID,PORT_PIN_0,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_F_ID,PORT_PIN_1,PORT_PIN_OUT,STD_ON,OFF,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_F_ID,PORT_PIN_2,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_F_ID,PORT_PIN_3,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON,
                                            PORT_F_ID,PORT_PIN_4,PORT_PIN_IN,STD_ON,PULL_UP,STD_LOW,DIGITAL,ALT_OFF,STD_ON
                                            };