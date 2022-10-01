/* 
    This code originates from the Getting started with Raspberry Pi Pico document
    https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
    CC BY-ND Raspberry Pi (Trading) Ltd
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "console.h"

const uint LED_PIN = 25;

uint32_t timerFlag = 0;

bool timerCallback(repeating_timer_t *rt){
    timerFlag = 1;
}

int main() {
    repeating_timer_t timer;

    stdio_init_all();
    ConsoleInit();
    add_repeating_timer_ms(20, timerCallback, NULL, &timer);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(1) {
        if( timerFlag == 1 ){
            ConsoleProcess();
            timerFlag = 0;
        }
        sleep_ms(1);
    }
}