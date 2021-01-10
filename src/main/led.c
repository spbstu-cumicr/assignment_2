#include "led.h"

static Led led[] = {
	{
		.turnOn     = turnOnLed,
		.turnOff    = turnOffLed,
		.periphPort = RCC_AHB1Periph_GPIOD,
		.gpioPort   = GPIOD,
		.gpioPin    = GPIO_Pin_12,
		.gpioPinSrc = GPIO_PinSource12
	},
	
	{
        .turnOn     = turnOnLed,
		.turnOff    = turnOffLed,
		.periphPort = RCC_AHB1Periph_GPIOD,
		.gpioPort   = GPIOD,
		.gpioPin    = GPIO_Pin_13,
		.gpioPinSrc = GPIO_PinSource13
	},
	
	{
		.turnOn     = turnOnLed,
		.turnOff    = turnOffLed,
		.periphPort = RCC_AHB1Periph_GPIOD,
		.gpioPort   = GPIOD,
		.gpioPin    = GPIO_Pin_14,
		.gpioPinSrc = GPIO_PinSource14

	},
	
	{
		.turnOn     = turnOnLed,
		.turnOff    = turnOffLed,
		.periphPort = RCC_AHB1Periph_GPIOD,
		.gpioPort   = GPIOD,
		.gpioPin    = GPIO_Pin_15,
		.gpioPinSrc = GPIO_PinSource15,
	}
};

Led *initLed(void)
{
	for (uint8_t ledNumber = 0; ledNumber < ARRAY_SIZE(led); ledNumber++)
	{
		// Подаём питание на порт ввода-вывода общего назначения GPIOD
		RCC_AHB1PeriphClockCmd(led[ledNumber].periphPort, ENABLE);
		
		// Устанавливаем светодиода в режим вывода c двухтактным каскадом с частотой 50 МГц
		GPIO_InitTypeDef newLed;
		GPIO_StructInit(&newLed);

		newLed.GPIO_Pin   = led[ledNumber].gpioPin;
		newLed.GPIO_Mode  = GPIO_Mode_OUT;
		newLed.GPIO_Speed = GPIO_Low_Speed;
		newLed.GPIO_OType = GPIO_OType_PP;
		
		GPIO_Init(led[ledNumber].gpioPort, &newLed);
	}
	
	return led;
}

void turnOnLed(const Led *led)
{
	GPIO_SetBits(led->gpioPort, led->gpioPin);
}

void turnOffLed(const Led *led)
{
	GPIO_ResetBits(led->gpioPort, led->gpioPin);
}
