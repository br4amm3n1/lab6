#include "DigitalOut.h"
#include "InterruptIn.h"
#include "PinNames.h"
#include "mbed.h"
#include "BME280.h"
#include "mbed_wait_api.h"
#include <cstdio>

BME280 sens(PB_9, PB_8);
DigitalOut oled1(LED1);
InterruptIn btn(BUTTON1);
int i = 0;

void pressed()
{
    i = i + 1;
}

// main() runs in its own thread in the OS
int main()
{
    btn.rise(&pressed);
    while (true) {

        if (i == 1) {

            printf("%d degC\n", 
            (int)sens.getTemperature());
            wait_us(1000000);

        } else if (i == 2) {

            printf("%d PA\n", 
            (int)sens.getPressure());
            wait_us(1000000);

        } else if (i == 3) {

            printf("%d %%\n", 
            (int)sens.getHumidity());
            wait_us(1000000);
        }
        //два режима темп меньше 32 гореть, больше мигать, нажатие на кнопку - смена режима
        if((int)sens.getTemperature() > 30)
        {
            if (oled1 == false) oled1 = true;
            i = 0;

        } else
        {
            oled1 = !oled1;
        }
    }
}

