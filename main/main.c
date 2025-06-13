#include <stdint.h>
#include <system_stm32f1xx.h>
#include <stm32f1xx.h>

static void clock_config() {
    // Set PLL source to HSI / 2; set PLL multiplier to 16
    RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC);
    RCC->CFGR |= RCC_CFGR_PLLMULL16;

    // Set HSE to bypass mode (8 MHz signal from ST-Link), and enable it
    RCC->CR |= RCC_CR_HSEBYP | RCC_CR_HSEON;

    while (!(RCC->CR & RCC_CR_HSERDY)) {
        // Wait until HSE is ready
    }

    // Set flash 2 wait state, because SYSCLK is fast
    FLASH->ACR &= ~(FLASH_ACR_LATENCY);
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    // AHB  = SYSCLK / 1 = 64 MHz
    // APB1 = SYSCLK / 2 = 32 MHz
    // APB2 = SYSCLK / 1 = 64 MHz
    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_HPRE_DIV1;

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;

    while (!(RCC->CR & RCC_CR_PLLRDY)) {
        // Wait until PLL is ready
    }

    // Select PLL as SYSCLK source
    RCC->CFGR &= ~(RCC_CFGR_SW);
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)) {
        // Wait until PLL is set as SYSCLK
    }

    // Update SystemCoreClock variable
    SystemCoreClockUpdate();
}

int main(void) {
    clock_config();

    // Enable clock on the GPIO A port
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Set output mode on pin 5
    GPIOA->CRL |= GPIO_CRL_MODE5;
    // Set push-pull function on pin 5
    GPIOA->CRL &= ~(GPIO_CRL_CNF5);
    // Bring pin 5 up
    GPIOA->BSRR = GPIO_BSRR_BS5;

    while(1) {
        // Enter sleep mode while waiting for interrupts
        __WFI();
    }
}
