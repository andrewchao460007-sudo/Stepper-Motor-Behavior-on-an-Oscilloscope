#include "stm32l476xx.h"
#include "motor.h"

// These are the Hexadecimal values for coil magnetic excitation.
// The rotor tries to keep up with the changing magnetic field.
unsigned char FullStep[4] = {0xa, 0x9, 0x5, 0x6};
unsigned char HalfStep[8] = {0xa, 0x8, 0x9, 0x1, 0x5, 0x4, 0x6, 0x2};

// Four pins to control the stepper motor: PC5, PC6, PC8, and PC9
#define PIN1 5
#define PIN2 6
#define PIN3 8
#define PIN4 9

#define MPORT GPIOC

// Counter-clock-wise
// 1000, 1100, 0100, 0110, 0010, 0011, 0001, 1001

// Clockwise
// 0001, 0011, 0010, 0110, 0100, 1100, 1000, 1001

#define DELAY 4100

void Full_Stepping_Clockwise(void){
    int i;
    volatile int j;
    uint32_t output;

    for(i = 0; i < 4; i++){
        for(j = 0; j < DELAY; j++); // delay

        output = MPORT->ODR;
        output &= ~(1U << PIN1 | 1U << PIN2 |
                    1U << PIN3 | 1U << PIN4);

        output |= ((FullStep[i] & 0x8) >> 3) << PIN4;
        output |= ((FullStep[i] & 0x4) >> 2) << PIN3;
        output |= ((FullStep[i] & 0x2) >> 1) << PIN2;
        output |= (FullStep[i] & 0x1) << PIN1;

        MPORT->ODR = output;
    }
}

// Full stepping counter-clockwise
void Full_Stepping_CounterClockwise(void){
    int i;
    volatile int j;
    uint32_t output;

    for(i = 3; i >= 0; i--){
        for(j = 0; j < DELAY; j++); // delay

        output = MPORT->ODR;
        output &= ~(1U << PIN1 | 1U << PIN2 |
                    1U << PIN3 | 1U << PIN4);

        output |= ((FullStep[i] & 0x8) >> 3) << PIN4;
        output |= ((FullStep[i] & 0x4) >> 2) << PIN3;
        output |= ((FullStep[i] & 0x2) >> 1) << PIN2;
        output |= (FullStep[i] & 0x1) << PIN1;

        MPORT->ODR = output;
    }
}

// Full stepping counter-clockwise (alternative)
void Full_Stepping_CounterClockwise2(void){
    int i;
    volatile int j;
    uint32_t output;

    for(i = 0; i < 4; i++){
        for(j = 0; j < DELAY; j++);

        output = MPORT->ODR;
        output &= ~(1U << PIN1 | 1U << PIN2 |
                    1U << PIN3 | 1U << PIN4);

        output |= ((FullStep[i] & 0x8) >> 3) << PIN2;
        output |= ((FullStep[i] & 0x4) >> 2) << PIN3;
        output |= ((FullStep[i] & 0x2) >> 1) << PIN4;
        output |= (FullStep[i] & 0x1) << PIN1;

        MPORT->ODR = output;
    }
}

// Half stepping clockwise
void Half_Stepping_Clockwise(void){
    int i;
    volatile int j;
    uint32_t output;

    for(i = 0; i < 8; i++){
        for(j = 0; j < DELAY; j++); // delay

        output = MPORT->ODR;
        output &= ~(1U << PIN1 | 1U << PIN2 |
                    1U << PIN3 | 1U << PIN4);

        output |= ((HalfStep[i] & 0x8) >> 3) << PIN4;
        output |= ((HalfStep[i] & 0x4) >> 2) << PIN3;
        output |= ((HalfStep[i] & 0x2) >> 1) << PIN2;
        output |= (HalfStep[i] & 0x1) << PIN1;

        MPORT->ODR = output;
    }
}

// Half stepping counter-clockwise
void Half_Stepping_CounterClockwise(void){
    int i;
    volatile int j;
    uint32_t output;

    for(i = 7; i >= 0; i--){
        for(j = 0; j < DELAY; j++); // delay

        output = MPORT->ODR;
        output &= ~(1U << PIN1 | 1U << PIN2 |
                    1U << PIN3 | 1U << PIN4);

        output |= ((HalfStep[i] & 0x8) >> 3) << PIN4;
        output |= ((HalfStep[i] & 0x4) >> 2) << PIN3;
        output |= ((HalfStep[i] & 0x2) >> 1) << PIN2;
        output |= (HalfStep[i] & 0x1) << PIN1;

        MPORT->ODR = output;
    }
}

// Half stepping counter-clockwise (alternative)
void Half_Stepping_CounterClockwise2(void){
    int i;
    volatile int j;
    uint32_t output;

    for(i = 0; i < 8; i++){
        for(j = 0; j < DELAY; j++);

        output = MPORT->ODR;
        output &= ~(1U << PIN1 | 1U << PIN2 |
                    1U << PIN3 | 1U << PIN4);

        output |= ((HalfStep[i] & 0x8) >> 3) << PIN2;
        output |= ((HalfStep[i] & 0x4) >> 2) << PIN3;
        output |= ((HalfStep[i] & 0x2) >> 1) << PIN4;
        output |= (HalfStep[i] & 0x1) << PIN1;

        MPORT->ODR = output;
    }
}

// Initialize motor GPIO pins
void Motor_Init(void){

    // Enable GPIOC clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // GPIO Mode: Input(00), Output(01),
    // AlterFunc(10), Analog(11)
    MPORT->MODER &= ~(3U << (2*PIN1) |
                      3U << (2*PIN2) |
                      3U << (2*PIN3) |
                      3U << (2*PIN4));

    MPORT->MODER |= (1U << (2*PIN1) |
                     1U << (2*PIN2) |
                     1U << (2*PIN3) |
                     1U << (2*PIN4));

    // GPIO Speed: Fast speed (10)
    MPORT->OSPEEDR &= ~(3U << (2*PIN1) |
                        3U << (2*PIN2) |
                        3U << (2*PIN3) |
                        3U << (2*PIN4));

    MPORT->OSPEEDR |= (2U << (2*PIN1) |
                       2U << (2*PIN2) |
                       2U << (2*PIN3) |
                       2U << (2*PIN4));

    // Output type: Push-pull (0)
    MPORT->OTYPER &= ~(1U << PIN1 |
                       1U << PIN2 |
                       1U << PIN3 |
                       1U << PIN4);

    // No pull-up, no pull-down (00)
    MPORT->PUPDR &= ~(3U << (2*PIN1) |
                      3U << (2*PIN2) |
                      3U << (2*PIN3) |
                      3U << (2*PIN4));
}

// Full CW: forward array, normal pin order
// Full CCW: reverse array, normal pin order
// Full CCW2: forward array, changed pin order
// Half CCW: reverse array, normal pin order
// Half CCW2: forward array, changed pin order

// Original Lab 2 delay values:
// Full step = 7500
// Half step = 4100