#ifndef STATUSLED_MANAGER_H
#define STATUSLED_MANAGER_H

namespace StatusLED_Manager
{
    void SetStatusLEDInterval(float interval);
    void SetStatusLEDInterval(float interval, float seconds);
    void init();
}

#endif // STATUSLED_MANAGER_H