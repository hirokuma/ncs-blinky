#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include "drivers/led.h"

#define SLEEP_TIME_MS (500)

int main(void)
{
    int ret = led_init();

    while (1) {
        ret = led_toggle();
        if (ret != 0) {
            return ret;
        }
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}
