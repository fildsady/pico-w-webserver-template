#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"

#define LED_PIN_0       0
#define LED_PIN_1       1

// CGI handler which is run when a request for /led.cgi is detected
const char *cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    // Loop through each parameter to find "led" and its corresponding value
    for (int i = 0; i < iNumParams; i++) {
        if (strcmp(pcParam[i], "led") == 0) {
            // Check the value of the "led" parameter and control the LED accordingly
            if (strcmp(pcValue[i], "0") == 0) {
                cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
            } else if (strcmp(pcValue[i], "1") == 0) {
                cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            }
        }

         if (strcmp(pcParam[i], "led2") == 0){
            // Check the value of the "led" parameter and control the LED accordingly
            if (strcmp(pcValue[i], "0") == 0) {
                  gpio_put(LED_PIN_0, 0);
            }
            else if  (strcmp(pcValue[i], "1") == 1) {
                gpio_put(LED_PIN_0, 1);
            }
         }

         if (strcmp(pcParam[i], "led3") == 0){
            // Check the value of the "led" parameter and control the LED accordingly
            if (strcmp(pcValue[i], "0") == 0) {
                  gpio_put(LED_PIN_1, 0);
            }
            else if  (strcmp(pcValue[i], "1") == 1) {
                gpio_put(LED_PIN_1, 1);
            }
         }
         
    }
    
    // Send the index page back to the user
    return "/index.shtml";
}

// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    {
        // Html request for "/led.cgi" triggers cgi_led_handler
        "/led.cgi", cgi_led_handler
    },
};

void cgi_init(void) {


    http_set_cgi_handlers(cgi_handlers, 1);

}
