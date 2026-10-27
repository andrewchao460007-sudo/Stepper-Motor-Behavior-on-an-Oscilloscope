#include "EXTI.h"
#include "LED.h"

// Motor direction variable defined in main.c
// 0 = Counterclockwise, 1 = Clockwise
extern volatile int direction;

// Push button = PC13
#define EXTI_PIN 13

void EXTI_Init(void){

    // GPIO Configuration
    // Enable the clock to GPIOC
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // GPIO Mode: Input(00), Output(01),
    // AlterFunc(10), Analog(11)
    // Set PC13 to input
    GPIOC->MODER &= ~(3UL << (2 * EXTI_PIN));

    // GPIO PUPDR: No pull-up, pull-down (00),
    // Pull-up (01), Pull-down (10)
    // Set to no pull-up, no pull-down
    GPIOC->PUPDR &= ~(3UL << (2 * EXTI_PIN));

    // Enable SYSCFG clock
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Map PC13 to EXTI13
    SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

    // Interrupt Mask Register (IMR)
    // Enable EXTI13 interrupt
    EXTI->IMR1 |= EXTI_IMR1_IM13;

    // Falling trigger selection register (FTSR)
    // Enable falling-edge trigger
    EXTI->FTSR1 |= EXTI_FTSR1_FT13;

    // Disable rising-edge trigger
    EXTI->RTSR1 &= ~EXTI_RTSR1_RT13;

    // Clear any pending EXTI13 interrupt
    EXTI->PR1 = EXTI_PR1_PIF13;

    // EXTI Interrupt Enable
    // Enable NVIC entry for EXTI13
    NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
    NVIC_SetPriority(EXTI15_10_IRQn, 0);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

// EXTI interrupt handler
void EXTI15_10_IRQHandler(void){

    // PR: Pending register
    if ((EXTI->PR1 & EXTI_PR1_PIF13) == EXTI_PR1_PIF13){

        // Clear pending flag by writing 1
        EXTI->PR1 = EXTI_PR1_PIF13;

        // Toggle green LED (PA5)
        LED_Toggle();

        // Something Cool: Reverse motor direction
        direction = !direction;
    }
}