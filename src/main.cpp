
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

// #define LED_PIN 2
constexpr gpio_num_t LED_PIN = GPIO_NUM_2;
constexpr gpio_num_t PUSH_BUTTON_PIN = GPIO_NUM_4;

extern "C" void app_main();

void app_main()
{
    // setup
    gpio_config_t config;
    config.pin_bit_mask = (1 << LED_PIN);
    config.mode = GPIO_MODE_OUTPUT;
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config);

    gpio_config_t config2;
    config2.pin_bit_mask = (1 << PUSH_BUTTON_PIN);
    config2.mode = GPIO_MODE_INPUT;
    config2.pull_up_en = GPIO_PULLUP_DISABLE;
    config2.pull_down_en = GPIO_PULLDOWN_ENABLE;
    config2.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&config2);

    // Loop
    while (1)
    {
        if (gpio_get_level(PUSH_BUTTON_PIN))
        {
            for (int i = 0; i < 3; i++)
            {
                gpio_set_level(LED_PIN, 1);
                vTaskDelay(pdMS_TO_TICKS(50));
                gpio_set_level(LED_PIN, 0);
                vTaskDelay(pdMS_TO_TICKS(50));
            }
            vTaskDelay(pdMS_TO_TICKS(700));
        }
        else
        {
            gpio_set_level(LED_PIN, 0);
        }
    }
}