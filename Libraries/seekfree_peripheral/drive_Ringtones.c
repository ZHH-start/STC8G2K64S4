#include "drive_Ringtones.h"
#include "zf_gpio.h"

sbit GND_ringtone = P4 ^ 0;
sbit rin          = P4 ^ 7;

void Ringtones_open()
{
    rin = 0;
}

void Ringtones_close()
{
    rin = 1;
}

void Ringtones_init()
{
    gpio_mode(P40, GPO_PP);
    GND_ringtone = 0;
    rin          = 0;
}
