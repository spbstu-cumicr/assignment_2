#include "mcu_support_package/inc/stm32f4xx.h"
#include "led.h"
#include "timer.h"
#include "main/Lab2_Test.h"

#include <stdint.h>

// Последовательность загорания светодиодов
// Укажите последовательность в соответствии с вариантом
// Используйте макроопределения цветом светодиодов:
// LED_GREEN — зелёный
// LED_YELLOW — жёлтый
// LED_RED — красный
// LED_BLUE — синий
static const uint8_t ledColour[] = {
	LED_BLUE,
	LED_GREEN,
	LED_BLUE,
	LED_YELLOW,
	LED_RED,
	LED_YELLOW,
	LED_BLUE,
	LED_GREEN
};

// Длительность горения светодиодов
const uint32_t period_ms = 200;

// Фамилия
const char *lastName = "Pankov";

int main(void)
{
	// Вариант задания
	static uint8_t variant = 0;	
	variant = Lab2_Test_ini((char *)lastName);	

	// Контрольная сумма
	static uint32_t checksum = 0;
	
	// Инициализируем клавиатуру
	static Led *led;
	led = initLed();
	
	// Инициализируем таймер
	initTimer(period_ms);
	
	while(1)
	{
		// Номер светодиода
		static uint8_t ledNumber = 0;
	
		// Если счётчик таймера переполнился, зажигаем следующий светодиод
		if (TIM_GetFlagStatus(TIM3, TIM_FLAG_Update) == SET)
		{
			// Цвет светодиода
			static uint8_t colour = 0;
			
			// Гасим предыдущий светодиод и зажигаем следующий
			led[colour].turnOff(&led[colour]);
			colour = ledColour[ledNumber];
			led[colour].turnOn(&led[colour]);
			
			// Переходим к следующему светодиоду
			ledNumber++;
			ledNumber %= ARRAY_SIZE(ledColour);
			
			// Сбрасываем флаг таймера
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
			
			// Считаем контрольную сумму
			checksum = read_flag();
		}
	}
	
	return 0;
}

#ifdef USE_FULL_ASSERT

// эта функция вызывается, если assert_param обнаружил ошибку
void assert_failed(uint8_t *file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
	ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	
	(void)file;
	(void)line;
	
	__disable_irq();
	while(1)
	{
		// это ассемблерная инструкция "отладчик, стой тут"
		// если вы попали сюда, значит вы ошиблись в параметрах вызова функции из SPL. 
		// Смотрите в call stack, чтобы найти ее
		__BKPT(0xAB);
	}
}

#endif
