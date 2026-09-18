#ifndef STATUSLED_MANAGER_H
#define STATUSLED_MANAGER_H

#pragma once

#include <stdint.h>

namespace StatusLED_Manager
{
    void SetInterval(uint32_t interval);
    void SetInterval(uint32_t interval, uint32_t seconds);
    void init();
}

#endif // STATUSLED_MANAGER_H