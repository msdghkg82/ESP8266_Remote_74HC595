#ifndef RF_REMOTE_DRIVER_H
#define RF_REMOTE_DRIVER_H

struct RemoteButton
{
    uint16_t Code;
    void (*Action)();
};

class RF_Remote
{
    public:
    void init();
    void loop();

    private:
    RemoteButton _buttons[4];
    void Actions(unsigned long data);
    unsigned long CheckData(unsigned long value);
    bool CheckCode(unsigned long value);
};

extern RF_Remote remote;

#endif // REMOTE_DRIVER_H