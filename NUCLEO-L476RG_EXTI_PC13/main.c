
#include "stm32l476xx.h"
#include "SysClock.h"
#include "EXTI.h"
#include "LED.h"
#include "motor.h"

// Motor direction
// 0 = CCW, 1 = CW
volatile int direction = 0;

int main(void){

    System_Clock_Init(); // 80 MHz

    // Initialize LED
    LED_Init();

    // Initialize stepper motor
    Motor_Init();

    // Initialize EXTI interrupt
    EXTI_Init();

    while(1){

        if(direction == 0){
            Half_Stepping_CounterClockwise();
        }
        else{
            Half_Stepping_Clockwise();
        }
    }
}