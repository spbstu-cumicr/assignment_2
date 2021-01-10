#pragma once

#include "stm32f4xx.h"
#include "stdio.h"

uint8_t Lab2_Test_ini(char *name);
uint32_t read_flag(void);

uint8_t initTest(const char *lastName);
uint32_t getChecksum(void);
