#ifndef MOTOR_H
#define MOTOR_H

#include "stm32l476xx.h"

// Initialize motor GPIO pins
void Motor_Init(void);

// Half stepping functions
void Half_Stepping_Clockwise(void);
void Half_Stepping_CounterClockwise(void);

#endif