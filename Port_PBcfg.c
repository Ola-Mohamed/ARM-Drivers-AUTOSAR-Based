/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Ola Mohamed Ahmed
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
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)



/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif


/* PB structure used with PORT_Init API */
const Port_ConfigType Port_Configuration = {
  
                                            PORTA , PIN0 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTA , PIN1 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTA , PIN2 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTA , PIN3 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTA , PIN4 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTA , PIN5 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTA , PIN6 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTA , PIN7 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                                                                                                                                             
                                            PORTB , PIN0 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTB , PIN1 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTB , PIN2 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTB , PIN3 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTB , PIN4 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTB , PIN5 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTB , PIN6 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTB , PIN7 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                                                                                                                                             
                                            PORTC , PIN0 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_DIS_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTC , PIN1 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_DIS_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTC , PIN2 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_DIS_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTC , PIN3 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_DIS_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTC , PIN4 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTC , PIN5 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTC , PIN6 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTC , PIN7 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                                                                                                                                           
                                            PORTD , PIN0 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTD , PIN1 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTD , PIN2 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTD , PIN3 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTD , PIN4 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTD , PIN5 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTD , PIN6 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTD , PIN7 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                                                                                                                                             
                                            PORTE , PIN0 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTE , PIN1 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTE , PIN2 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTE , PIN3 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTE , PIN4 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE, 
                                            PORTE , PIN5 ,PORT_PIN_IN , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            
                                            PORTF , PIN0 ,PORT_PIN_IN  , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW   ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTF , PIN1 ,PORT_PIN_OUT , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW   ,PORT_DEFAULT_MODE_GPIO,MODE_DIS_CHANGE,DIRECTION_EN_CHANGE,   //LED 
                                            PORTF , PIN2 ,PORT_PIN_IN  , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW   ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,   
                                            PORTF , PIN3 ,PORT_PIN_IN  , NO_PULL_UP_DOWN ,PORT_LEVEL_Digital , STD_LOW   ,PORT_DEFAULT_MODE_GPIO,MODE_EN_CHANGE,DIRECTION_EN_CHANGE,
                                            PORTF , PIN4 ,PORT_PIN_IN  , PULL_UP         ,PORT_LEVEL_Digital , STD_HIGH  ,PORT_DEFAULT_MODE_GPIO,MODE_DIS_CHANGE ,DIRECTION_EN_CHANGE, //BUTTON       
				         };