 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Misara Ahmed
 ******************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_registers.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/* Static global variables */
STATIC const Pin_Config *Port_Configuration = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/*******************************************************************************
 *                      Function Definitions                                   *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
    /* point to the required Port Registers base address */
    volatile uint32 * Port_Ptr = NULL_PTR;
    volatile uint32 delay = 0;

    #if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* check if the input configuration pointer is not a NULL_PTR */
        if (NULL_PTR == ConfigPtr)
        {
            /* Report an error to the Det module */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
        }
        else
    #endif
        {
            /* Change the status of the module */
            Port_Status = PORT_INITIALIZED;

            /* Make the global pointer points to the first structure in the Pins structure --> Pins[0]*/
            Port_Configuration = ConfigPtr -> Pins;

            /* Loop on all the pins to configure them */
            for(Port_PinType Pin = 0; Pin < MCU_PINS; Pin++)
            {
                switch(Port_Configuration[Pin].port_num)
                {
                    case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                        break;
                    case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                        break;
                    case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                        break;
                    case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                        break;
                    case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                        break;
                    case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                        break;
                }

                /* Enable clock for PORT and allow time for clock to start */
                SYSCTL_REGCGC2_REG |= (1<<Port_Configuration[Pin].port_num);
                delay = SYSCTL_REGCGC2_REG;

                /* PD7 or PF0 */
                if( ((Port_Configuration[Pin].port_num == PORT_D_ID) && (Port_Configuration[Pin].pin_num == PORT_PIN_7)) || ((Port_Configuration[Pin].port_num == PORT_F_ID) && (Port_Configuration[Pin].pin_num == PORT_PIN_0)) )
                {
                    /* Unlock the GPIOCR register */ 
                    *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;  

                    /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Configuration[Pin].port_num);
                }
                 /* PC0 to PC3 (JTAG pins) */
                else if( (Port_Configuration[Pin].port_num == PORT_PIN_2) && (Port_Configuration[Pin].port_num <= PORT_PIN_3) )
                {
                    /* Do Nothing */
                }
                else
                {
                    /* Do Nothing ... No need to unlock the commit register for this pin */
                }

                switch (Port_Configuration[Pin].mode)
                {
                    case ANALOG:
                        /* Enalble the ANALOG functionality for this pin setting the corresponding bit in the GPIOAMSEL register */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                        /* Disable Alternative function for this pin by clearing the corresponding bit in GPIOAFSEL register */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                        /* Clear the PMCx bits for this pin */
                        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configuration[Pin].pin_num * 4));
                        break;

                    case DIGITAL:
                        /*Disable ANALOG functionality for this pin by clearing the corresponding bit in the GPIOAMSEL */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                        /* Disable ALTERNATIVE function for this pin by clearing the corresponding bit in GPIOAFSEL register */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                        /* Clear the PMCx bits for this pin */
                        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configuration[Pin].pin_num * 4));

                        /* Enable DIGITAL functionality for this pin by setting the corresponding bit in the GPIODEN register */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                        break;

                    case ALTERNATE:
                        /*Disable ANALOG functionality for this pin by clearing the corresponding bit in the GPIOAMSEL */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                        /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                        
                        /* Clear the PMCx bits for this pin */
                        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configuration[Pin].pin_num * 4));

                        /* Set the PMCx bits for this pin to the required mode */
                        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Port_Configuration[Pin].alternate << (Port_Configuration[Pin].pin_num * 4));
                        break;
                }

                switch (Port_Configuration[Pin].direction)
                {
                    case PORT_PIN_OUT:
                        /* Configuring the pin to be an OUTPUT pin by setting the corresponding bit in the GPIODIR register */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                        if(Port_Configuration[Pin].initial_value == STD_HIGH)
                        {
                            /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                        }
                        else
                        {
                            /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                        }
                        break;

                    case PORT_PIN_IN:
                        /* Configuring the pin to be an INPUT pin by setting the corresponding bit in the GPIODIR register */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                        if(Port_Configuration[Pin].resistor == PULL_UP)
                        {
                            /* Enable the internal PULL UP by setting the corresponding bit in the GPIOPUR register */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                        }
                        else if(Port_Configuration[Pin].resistor == PULL_DOWN)
                        {
                            /* Enable the internal PULL DOWN by setting the corresponding bit in the GPIOPDR register */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                        }
                        else
                        {
                            /* Disable the internal PULL UP by clearing the corresponding bit in the GPIOPUR register */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                            /* Disable the internal PULL DOWN by clearing the corresponding bit in the GPIOPDR register */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                        }
                        break;
                }
            }
        }
}

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in):  Pin - Port Pin ID number
*                   Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin direction.
************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    /* point to the required Port Registers base address */
    volatile uint32 * Port_Ptr = NULL_PTR;
    volatile uint32 delay = 0;
    boolean error = FALSE;

    #if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* Check if the Port module is already initialised */
        if (Port_Status == PORT_NOT_INITIALIZED)
        {
            /* Report an error to the Det module */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_UNINIT);
            error = TRUE;
        }
        else
        {
            /* Do Nothing */
        }

        /* Check if the needed pin is within the valid range */
        if(Pin >= MCU_PINS)
        {
            /* Report an error to the Det module */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_PIN);
            error = TRUE;
        }
        else
        {
            /* Do Nothing */
        }

        /* Check if the Direction is configured as changable */
        if(Port_Configuration[Pin].direction_changeable == STD_OFF)
        {
            /* Report an error to the Det module */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_DIRECTION_UNCHANGEABLE);
            error = TRUE;
        }
        else
        {
            /* Do Nothing */
        }
    #endif

    if(error == FALSE)
    {
        switch(Port_Configuration[Pin].port_num)
        {
            case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
        }

        /* Enable clock for PORT and allow time for clock to start */
        SYSCTL_REGCGC2_REG |= (1<<Port_Configuration[Pin].port_num);
        delay = SYSCTL_REGCGC2_REG;

        switch (Direction)
        {
            case PORT_PIN_OUT:
                /* Configuring the pin to be an OUTPUT pin by setting the corresponding bit in the GPIODIR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                break;

            case PORT_PIN_IN:
                /* Configuring the pin to be an INPUT pin by setting the corresponding bit in the GPIODIR register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                break;
        }
    }
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
    /* point to the required Port Registers base address */
    volatile uint32 * Port_Ptr = NULL_PTR;
    volatile uint32 delay = 0;

    #if (PORT_DEV_ERROR_DETECT == STD_ON)

        /* check if the Port module is already initialised */
        if (Port_Status == PORT_NOT_INITIALIZED)
        {
            /* Report an error to the Det module */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_UNINIT);
        }
        else
    #endif
        {
            /* Loop on all the configured pins */
            for(Port_PinType Pin = 0; Pin < MCU_PINS; Pin++)
            {
                switch(Port_Configuration[Pin].port_num)
                {
                    case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                        break;
                    case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                        break;
                    case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                        break;
                    case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                        break;
                    case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                        break;
                    case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                        break;
                }

                /* Enable clock for PORT and allow time for clock to start */
                SYSCTL_REGCGC2_REG |= (1<<Port_Configuration[Pin].port_num);
                delay = SYSCTL_REGCGC2_REG;

                /* Check the configured direction changeability for this pin */
                if(Port_Configuration[Pin].direction_changeable == STD_OFF)
                {
                    switch (Port_Configuration[Pin].direction)
                    {
                        case PORT_PIN_OUT:
                            /* Refresh the pin to be an OUTPUT pin by setting the corresponding bit in the GPIODIR register */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                            break;
                        case PORT_PIN_IN:
                            /* Refresh the pin to be an INPUT pin by setting the corresponding bit in the GPIODIR register */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                            break;
                    }
                }
                else
                {
                    /* Do Nothing */
                }
            }
        }
}

#if (PORT_VERSION_INFO_API == STD_ON)
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    boolean error = FALSE;

    #if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* check if input pointer is not Null pointer */
        if (NULL_PTR == versioninfo)
        {
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_POINTER);
            error = TRUE;
        }
        else
        {
            /* Do Nothing*/
        }
    #endif

    /* Chedk if there are no errors */
    if(error == FALSE)
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
    else
    {
        /* Do Nothing */
    }
}
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in):  Pin - Port Pin ID number
*                   Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    /* point to the required Port Registers base address */
    volatile uint32 * Port_Ptr = NULL_PTR;
    volatile uint32 delay = 0;
    boolean error = FALSE;

    #if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* check if the Port module is already initialised */
        if (Port_Status == PORT_NOT_INITIALIZED)
        {
            /* Report an error to the Det module */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_UNINIT);
            error = TRUE;
        }
        else
        {
            /* Do Nothing */
        }

        /* Check if the needed pin is within the valid range */
        if(Pin >= MCU_PINS)
        {
            /* Report an error to the Det module */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_PIN);
            error = TRUE;
        }
        else
        {
            /* Do Nothing */
        }

        /* Check if the Mode is configured as changable */
        if(Port_Configuration[Pin].mode_changeable == STD_OFF)
        {
            /* Report an error to the Det module */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_MODE_UNCHANGEABLE);
            error = TRUE;
        }
        else
        {
            /* Do Nothing */
        }

        /* Check if the mode needed is valid */
        if(Port_Configuration[Pin].mode > MAX_PIN_MODES)
        {
            /* Report an error to the Det module */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_INVALID_MODE);
            error = TRUE;
        }
        else
        {
            /* Do Nothing */
        }
    #endif

    if(error == FALSE)
    {
        switch(Port_Configuration[Pin].port_num)
        {
            case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
        }

        /* Enable clock for PORT and allow time for clock to start */
        SYSCTL_REGCGC2_REG |= (1<<Port_Configuration[Pin].port_num);
        delay = SYSCTL_REGCGC2_REG;

        switch (Mode)
        {
            case ANALOG:
                /* Enalble the ANALOG functionality for this pin setting the corresponding bit in the GPIOAMSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                /* Disable Alternative function for this pin by clearing the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configuration[Pin].pin_num * 4));
                break;

            case DIGITAL:
                /*Disable ANALOG functionality for this pin by clearing the corresponding bit in the GPIOAMSEL */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                /* Disable ALTERNATIVE function for this pin by clearing the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configuration[Pin].pin_num * 4));

                /* Enable DIGITAL functionality for this pin by setting the corresponding bit in the GPIODEN register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                break;

            case ALTERNATE:
                /*Disable ANALOG functionality for this pin by clearing the corresponding bit in the GPIOAMSEL */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configuration[Pin].pin_num);

                /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configuration[Pin].pin_num);
                
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configuration[Pin].pin_num * 4));

                /* Set the PMCx bits for this pin to the required mode */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << (Port_Configuration[Pin].pin_num * 4));
                break;
        }
    }
}
#endif