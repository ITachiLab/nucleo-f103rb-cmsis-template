#include <stdint.h>
#include <system_stm32f1xx.h>
#include <stm32f1xx.h>

#include "main.h"

int main(void) {
    clock_config();

    // Light up green LD2
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN);

    GPIOA->CRL |= (GPIO_CRL_MODE5);
    GPIOA->CRL &= ~(GPIO_CRL_CNF5);

    GPIOA->BSRR = (GPIO_BSRR_BS5);

    while(1) {}
}

void clock_config() {
    // Set PLL source to HSI / 2; set PLL multiplier to 16
    RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC);
    RCC->CFGR |= (RCC_CFGR_PLLMULL16);

    // Set HSE to bypass mode (8 MHz signal from ST-Link), and enable it
    RCC->CR |= (RCC_CR_HSEBYP | RCC_CR_HSEON);

    // Wait until HSE is ready
    while (!(RCC->CR & RCC_CR_HSERDY));

    // Set flash 2 wait state, because SYSCLK is fast
    FLASH->ACR &= ~(FLASH_ACR_LATENCY);
    FLASH->ACR |= (FLASH_ACR_LATENCY_2);

    // AHB  = SYSCLK / 1 = 64 MHz
    // APB1 = SYSCLK / 2 = 32 MHz
    // APB2 = SYSCLK / 1 = 64 MHz
    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
    RCC->CFGR |= (RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_HPRE_DIV1);

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;

    // Wait until PLL is ready
    while (!(RCC->CR & RCC_CR_PLLRDY));

    // Select PLL as SYSCLK source
    RCC->CFGR &= ~(RCC_CFGR_SW);
    RCC->CFGR |= (RCC_CFGR_SW_PLL);

    // Wait until PLL is set as SYSCLK
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL));

    // Update SystemCoreClock variable
    SystemCoreClockUpdate();
}