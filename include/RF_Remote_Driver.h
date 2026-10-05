#ifndef RF_REMOTE_DRIVER_H
#define RF_REMOTE_DRIVER_H

struct RemoteButton
{
    uint16_t Code;
    uint8_t Action;
};

class RF_Remote
{
    public:
    void init();
    void loop();

    private:
    RemoteButton buttons[4];
};

extern RF_Remote remote;

#endif // REMOTE_DRIVER_H