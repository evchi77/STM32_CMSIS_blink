/**
 ******************************************************************************
 * @file           : clock.c
 * @author         : Vsevolod
 * @brief          : 
 * @date           : 04.05.2020 19:06
 ******************************************************************************
 */

/* Includes -----------------------------------------------------------------*/
#include "main.h"
#include "clock.h"

/* Public variables definitions ---------------------------------------------*/
uint32_t	HCLK			= HSE_VALUE,
            cortex_sys_tim	= HSE_VALUE/8,
            APB1_periph     = HSE_VALUE,
            APB1_tim        = HSE_VALUE,
            APB2_periph     = HSE_VALUE,
            APB2_tim        = HSE_VALUE;

/* Private types ------------------------------------------------------------*/


/* Private variables --------------------------------------------------------*/


/* Private functions prototypes ---------------------------------------------*/
// Reset RCC registers
static void __clock_reset_all(void); 

// Set system clock
static void __clock_set_sys(void);

// Set peripheral clocks
static void __clock_set_periph(void);

/* Private defines ----------------------------------------------------------*/
// HSE_VALUE, HSI_VALUE, LSE_VALUE, LSI_VALUE defined in system_stm32f4xx.h

#define HSE_STARTUP_TIMEOUT		1000
#define LSE_STARTUP_TIMEOUT		5000

/* Private macros -----------------------------------------------------------*/


/* Public functions ---------------------------------------------------------*/
// Clocks initialization
void clock_init(void)
{
    static uint8_t init_completed = 0;

    if(!init_completed)
    {
        __clock_reset_all();
        __clock_set_sys();
        __clock_set_periph();

        init_completed = 1;
    }

    return;
}

// Update variables containing clocks' frequencies
void clock_update(void)
{
	// Update SYSCLK using CMSIS funcion
    SystemCoreClockUpdate();

	// ToDo: Update the rest of clocks!

    return;
}

/* Private functions --------------------------------------------------------*/
// Reset RCC registers
static void __clock_reset_all(void)
{
    /* Reset the RCC clock configuration to the default reset state ------------*/
    /* Set HSION bit */
    RCC->CR |= 0x00000001UL;

    /* Reset CFGR register */
    RCC->CFGR = 0x00000000UL;

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= 0xFEF6FFFFUL;

    /* Reset PLLCFGR register */
    RCC->PLLCFGR = 0x24003010UL;

    /* Reset HSEBYP bit */
    RCC->CR &= 0xFFFBFFFFUL;

    /* Disable all interrupts */
    RCC->CIR = 0x00000000UL;

    clock_update();

    return;
}

// Set system clock
static void __clock_set_sys(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* Enable HSE */
    RCC->CR |= RCC_CR_HSEON;

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = 0x01UL;
    }
    else
    {
        HSEStatus = 0x00UL;
    }

    if (HSEStatus == 0x01UL)
    {
        /* Select regulator voltage output Scale 1 mode, System frequency up to 168 MHz */
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;  // ToDo: а на что это влияет?..
        PWR->CR |= PWR_CR_VOS;              // Это вообще по умолчанию стоит

        /* HCLK = SYSCLK / 1*/
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
            
        /* PCLK2 = HCLK / 1*/
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK / 1*/
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;

        /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
        FLASH->ACR = FLASH_ACR_PRFTEN |FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_0WS;

        /* Select the HSE as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= RCC_CFGR_SW_HSE;

        /* Wait till the HSE is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_HSE);
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock
        configuration. User can add here some code to deal with this error */
    }

    clock_update();

    return;
}

// Set peripheral clocks
static void __clock_set_periph(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	// Enable clock on GPIO port A
    return;
}
