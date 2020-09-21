#ifndef LED_H
#define LED_H

#include "mcu_support_package/inc/stm32f4xx.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define LED_GREEN    0
#define LED_YELLOW   1
#define LED_RED      2
#define LED_BLUE     3

typedef struct Led {
/*
private:
*/
	uint32_t periphPort;
	GPIO_TypeDef *gpioPort;
	uint16_t gpioPin;
	uint16_t gpioPinSrc;
/*
public:
*/	
	void (*turnOn)(const struct Led *led);
	void (*turnOff)(const struct Led *led);
} Led;

Led *initLed(void);

void turnOnLed(const Led *led);
void turnOffLed(const Led *led);

#endif //LED_H
