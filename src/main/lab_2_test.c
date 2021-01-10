#include "lab_2_test.h"

uint8_t initTest(const char *lastName)
{
    return Lab2_Test_ini((char *)lastName);
}

uint32_t getChecksum(void)
{
    return read_flag();
}
