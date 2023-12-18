#include "drive_Ringtones.h"
#include "zf_gpio.h"

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
    rin          = 1;
}
