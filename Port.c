 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ola Mohamed
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"


#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif


STATIC const PIN_ConfigType  * PORT_PTR = NULL_PTR; /* point to the required Port Registers base address */
STATIC uint8 PORT_Status = PORT_NOT_INITIALIZED;

volatile uint32 * PortGpio_Ptr = NULL_PTR;  /* point to the required Port Registers base address */

/********************************************************************************
Service name: Port_Init
void Port_Init(
 const Port_ConfigType* ConfigPtr
)
Syntax:
Service ID[hex]: 0x00
Sync/Async: Synchronous
Reentrancy: Non Reentrant
Parameters (in): ConfigPtr Pointer to configuration set.
Parameters(inout): None
Parameters (out): None
Return value: None
Description: Function to Setup the pin configuration:
*              - Setup the pin as Digital or Analog GPIO pin
*              - Setup the direction of the port pin
*              - Provide initial value for o/p pin
*              - Setup the internal resistor for i/p pin
               - Setup the Alt function for pin
******************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr){

  #if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{


    PORT_Status = PORT_INITIALIZED ;
    PORT_PTR = ConfigPtr -> PORT_Channels ; /* address of the first PORT_PTR structure --> PORT_PORT_PTR */
    volatile uint32 delay = 0;
    uint8 i ;

     for( i= 0 ; i < PORT_CONFIGURED_PIN  ; i++)
     {
    switch(PORT_PTR[i].PORT_ID)
    {
        case  PORTA : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  PORTB : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  PORTC : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  PORTD : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  PORTE : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  PORTF : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }

    /* Enable clock for PORT and allow time for clock to start*/
    SYSCTL_REGCGC2_REG |= (1<<PORT_PTR[i].PORT_ID);
    delay = SYSCTL_REGCGC2_REG;


  if( ((PORT_PTR[i].PORT_ID == 3) && (PORT_PTR[i].PORT_PIN == 7)) || ((PORT_PTR[i].PORT_ID == 5) && (PORT_PTR[i].PORT_PIN == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , PORT_PTR[i].PORT_PIN );  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (PORT_PTR[i].PORT_ID == 2) && (PORT_PTR[i].PORT_PIN  <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
        /* Do Nothing ... No need to unlock the commit register for this pin */
    }


   switch(PORT_PTR[i].PORT_DIRECTION)
   {
     case PORT_PIN_IN:
         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PORT_PTR[i].PORT_PIN );
            /*SET PULL UP RESISTOR */
             if((PORT_PTR[i].PORT_Resistor)==PULL_UP)
          {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PORT_PTR[i].PORT_PIN );
          }
            /*SET PULL DOWN RESISTOR */
             else if ((PORT_PTR[i].PORT_Resistor)== PULL_DOWN)
          {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PORT_PTR[i].PORT_PIN );
          }
              else { /* Error */ }
               break ;
       /* Set the corresponding bit in the GPIODIR register to configure it as Output pin */
       case PORT_PIN_OUT :
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PORT_PTR[i].PORT_PIN );
            /*INITAL Value is 0 */
            if((PORT_PTR[i].Init_value)==STD_LOW){
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , PORT_PTR[i].PORT_PIN );
            }
               /*INITAL Value is 0 */
            else if ((PORT_PTR[i].Init_value)==STD_HIGH){
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , PORT_PTR[i].PORT_PIN );
            }
     }

     /*   Pin mode changeable during runtime (STD_ON/STD_OFF) – configuration is  MCU dependent  */
       if( PORT_PTR[i].PORT_MODE == PORT_DEFAULT_MODE_GPIO)
           {
       /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,PORT_PTR[i].PORT_PIN);
               /* Clear the PMCx bits for this pin */
             *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((PORT_PTR[i].PORT_PIN) * 4));
          }

               /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
       else  {
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PORT_PTR[i].PORT_PIN );
       /* ALT_FUNC VALUE the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((PORT_PTR[i].PORT_MODE) << ((PORT_PTR[i].PORT_PIN) * 4));
     }

      switch(PORT_PTR[i].Level)
    {

         /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      case PORT_LEVEL_Digital :
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PORT_PTR[i].PORT_PIN);
                   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PORT_PTR[i].PORT_PIN);
      break;
       /* SET the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
      case PORT_LEVEL_Analog :
        SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PORT_PTR[i].PORT_PIN);
          break;
        }
    }
  }
}

/*********************************************************
Service name: Port_SetPinDirection
void Port_SetPinDirection(
 Port_PinType Pin,
 Port_PinDirectionType Direction
)
Syntax:
Service ID[hex]: 0x01
Sync/Async: Synchronous
Reentrancy: Reentrant
Pin Port Pin ID number Parameters (in): Direction Port Pin Direction
Parameters (inout):None
Parameters (out): None
Return value: None
Description: Sets the port pin direction
************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin ,Port_PinDirectionType Direction){

	boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == PORT_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SETPINDIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (PORT_CONFIGURED_PIN <= Pin)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,PORT_SETPINDIRECTION_SID , PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
	}

        if (PORT_PIN_DIR_CHANGEABLE  == PORT_PTR[Pin].DIRECTION_CHANGEABLE)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SETPINDIRECTION_SID , PORT_E_DIRECTION_UNCHANGEABLE);
		error = TRUE;
	}
	else
	{

	}


#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{

    switch(PORT_PTR[Pin].PORT_ID)
     {
        case  PORTA : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  PORTB : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  PORTC : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  PORTD : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  PORTE : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  PORTF : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
     switch(Direction)
        {
       /* Set the corresponding bit in the GPIODIR register to configure it as input pin */
         case PORT_PIN_IN :
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,PORT_PTR[Pin].PORT_PIN );
          break;
        /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        case PORT_PIN_OUT :
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PORT_PTR[Pin].PORT_PIN);
         break;
      }
   }
}
#endif


/*************************************************************
Service name: Port_RefreshPortDirection
void Port_RefreshPortDirection(
 void
)
Syntax:
Service ID[hex]: 0x02
Sync/Async: Synchronous
Reentrancy: Non Reentrant
Parameters (in): None
Parameters (inout):None
Parameters (out): None
Return value: None
Description: Refreshes port direction.
*************************************************************/
void Port_RefreshPortDirection(void){

  boolean error = FALSE;
  uint8 i ;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == PORT_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_REFRESHPORTDIRECTION_SID , PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

#endif
/* In-case there are no errors */

	if(FALSE == error)
	{

     for( i= 0 ; i <= PORT_CONFIGURED_PIN  ; i++)
        {

    switch(PORT_PTR[i].PORT_ID)
    {
        case  PORTA : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  PORTB : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  PORTC : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  PORTD : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  PORTE : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  PORTF : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
 //Check if it Could be changeable or not
    if(PORT_PTR[i].MODE_CHANGEABLE == MODE_DIS_CHANGE)
    {
 //Read the Directon Of pin if it   out put set it again
     if(BIT_IS_SET(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET),PORT_PTR[i].PORT_PIN))
     {
       SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PORT_PTR[i].PORT_PIN );
     }
 //Read the Directon Of pin if it   in  put set it again
     else if (BIT_IS_CLEAR(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET),PORT_PTR[i].PORT_PIN))
     {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), PORT_PTR[i].PORT_PIN );
     }

    else {  /*Do No THING  */  }
      }
    }
  }
}
/************************************************************
Service name: Port_SetPinMode
void Port_SetPinMode(
 Port_PinType Pin,
 Port_PinModeType Mode
)
Syntax:
Service ID[hex]: 0x04
Sync/Async: Synchronous
Reentrancy: Reentrant
Pin Port Pin ID number Parameters (in): Mode New Port Pin mode to be set on port pin.
Parameters(inout): None
Parameters (out): None
Return value: None
Description: Sets the port pin mode.
***********************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode){

	boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == PORT_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SETPINMODE_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{

	}
	/* Check if the used channel is within the valid range */
	if (PORT_CONFIGURED_PIN <= Pin)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                                PORT_SETPINMODE_SID , PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{

	}

        /* Check if the Pin changable  or not  */
        if (PORT_PIN_DIR_CHANGEABLE == PORT_PTR[Pin].MODE_CHANGEABLE)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SETPINMODE_SID , PORT_E_MODE_UNCHANGEABLE);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        /* Check if the Mode valid or not valid  */
         if (!((Mode<=9)||(Mode == 14) ||(Mode == 11))
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SETPINMODE_SID , PORT_E_PARAM_INVALID_MODE);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}



#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{

        switch(PORT_PTR[Pin].PORT_ID)
    {
        case  PORTA : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  PORTB : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  PORTC : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  PORTD : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  PORTE : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  PORTF : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }



    if(Mode ==PORT_DEFAULT_MODE_GPIO ){
       CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Pin);
         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Pin);
               
      /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Pin);
               /* Clear the PMCx bits for this pin */
             *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((Pin) * 4)); 
    }
    else if(Mode == PORT_ADC_MODE ){
      SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Pin);
         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Pin);
               
      /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Pin);
      
    }
    else{
      
      /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
           SEt_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Pin);
               /* Clear the PMCx bits for this pin */
             *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((Pin) * 4));
    }
  
}
}
#endif

/*************************************************************
Service name: Port_GetVersionInfo
void Port_GetVersionInfo(
 Std_VersionInfoType* versioninfo
)
Syntax:
Service ID[hex]: 0x03
Sync/Async: Synchronous
Reentrancy: Non Reentrant
Parameters (in): None
Parameters (inout): None
Parameters (out): versioninfo Pointer to where to store the version information of this module.
Return value: None
Description: Returns the version information of this module.
*************************************************************/

#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType * versioninfo){
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif
