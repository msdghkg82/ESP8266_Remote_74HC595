#ifndef _74HC595_DRIVER_H
#define _74HC595_DRIVER_H

#pragma once

#include <stdint.h>

namespace HC595_Driver
{
    void HC595_Write(uint8_t data);
    void init();
}

#endif // _74HC595_DRIVER_H