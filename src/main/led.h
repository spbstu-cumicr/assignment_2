#pragma once

#include "mcu_support_package/inc/stm32f4xx.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

enum LED_COLOUR
{
    GREEN   = 0,
    YELLOW  = 1,
    RED     = 2,
    BLUE    = 3,
    COLOURS = 4
};

typedef struct Led {
/*
public:
*/	
	void (*turnOn)(const struct Led *led);
	void (*turnOff)(const struct Led *led);
/*
private:
*/
	uint32_t periphPort;
	GPIO_TypeDef *gpioPort;
	uint16_t gpioPin;
	uint16_t gpioPinSrc;
} Led;

Led *initLed(void);

void turnOnLed(const Led *led);
void turnOffLed(const Led *led);
