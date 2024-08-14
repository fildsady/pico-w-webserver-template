#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

// SSI tags - tag length limited to 8 bytes by default
const char *ssi_tags[] = {"volt", "temp", "led"};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {
    size_t printed = 0;

    switch (iIndex) {
    case 0: // volt
        {
            float raw_voltage = adc_read();
            float voltage = raw_voltage * 3.3f / (1 << 12);
            printed = snprintf(pcInsert, iInsertLen, "%.2f V", voltage);
        }
        break;
    case 1: // temp
        {
            float raw_voltage = adc_read();
            float tempC = 27.0f - (raw_voltage * 3.3f / (1 << 12) - 0.706f) / 0.001721f;
            printed = snprintf(pcInsert, iInsertLen, "%.2f C", tempC);
        }
        break;
    case 2: // led
        {
            bool led_status = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
            printed = snprintf(pcInsert, iInsertLen, led_status ? "ON" : "OFF");
        }
        break;
    default:
        printed = snprintf(pcInsert, iInsertLen, "N/A");
        break;
    }

    return (u16_t)printed;
}

// Initialise the SSI handler
void ssi_init() {
    // Initialise ADC (internal pin)
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    // Register SSI handler
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}
