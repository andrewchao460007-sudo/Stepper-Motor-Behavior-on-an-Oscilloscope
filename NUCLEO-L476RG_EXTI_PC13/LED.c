#include "LED.h"


//-------------------------------------------------------------------------------------------
// User LED = LD2 Green LED = PA.5
//-------------------------------------------------------------------------------------------
#define LED_PIN 5

void LED_Init(void){
	
	// Enable the peripheral clock of GPIO Port. Check the stm32l476xx.h file for the GPIOAEN constant. Remember to Use bitwise or | .
 RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	//Set GPIOA MODE Reg to output.
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOA->MODER &= ~(3UL << (2 * LED_PIN));//clear first 
	GPIOA->MODER |= (1UL << (2 * LED_PIN)); //  Output(01)
	
	//Set GPIO Output Speed to High speed.
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIOA->OSPEEDR &= ~(3UL << (2 * LED_PIN)); //Clear first
	 GPIOA->OSPEEDR |= (3UL << (2 * LED_PIN)); // High speed
	
	//Set GPIO Output Type Reg to Push Pull
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	 GPIOA->OTYPER &= ~(1UL << LED_PIN); // Push-pull
	
	//Set GPIO PUPDR to No Pull up and No pull down mode.
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	 GPIOA->PUPDR &= ~(3UL << (2 * LED_PIN)); // No pull-up, no pull-down
	
}

//-------------------------------------------------------------------------------------------
// Turn LED On
//-------------------------------------------------------------------------------------------
void LED_On(void){
	GPIOA->ODR |= (1UL<<LED_PIN);  //Use either of the bit wise &, |, ^  to turn on the LED
}

//-------------------------------------------------------------------------------------------
// Turn LED Off
//-------------------------------------------------------------------------------------------
void LED_Off(void){
	GPIOA->ODR &= ~(1UL<<LED_PIN); //Use either of the bit wise &, |, ^  to turn off the LED
  
}

//-------------------------------------------------------------------------------------------
// Toggle LED 
//-------------------------------------------------------------------------------------------
void LED_Toggle(void){
	GPIOA->ODR ^= (1UL<<LED_PIN); //Use either of the bit wise &, |, ^  to toggle theLED
}
