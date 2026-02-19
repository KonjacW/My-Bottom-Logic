#include "led.h"
#include "gpio.h"
#include "main.h"
void LED(uint16_t pin) {
    if((pin & 0xFF00) == 0) return;  // ?C8-C15??,???
    
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);  // ???
    HAL_GPIO_WritePin(GPIOC, 0xFF00, GPIO_PIN_SET);     // ?C8-15
    HAL_GPIO_WritePin(GPIOC, pin, GPIO_PIN_RESET);      // ????
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);  // ???
}
void LED_clear(){
    
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);  // ???
    HAL_GPIO_WritePin(GPIOC, 0xFF00, GPIO_PIN_SET);    
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);  // ??
}
