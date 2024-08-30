#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#define LED0 DT_ALIAS(led0)

#define SLEEP_TIME_MS (500)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0, gpios);

int main(void)
{
    if (!gpio_is_ready_dt(&led0)) {
        return -ENXIO;
    }

    int ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret != 0) {
        return ret;
    }

    while (1) {
        ret = gpio_pin_toggle_dt(&led0);
        if (ret != 0) {
            return ret;
        }
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}
