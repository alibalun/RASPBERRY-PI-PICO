#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

#define YELLOW_LED_PIN_Y 19
#define GREEN_LED_PIN_Y 18
#define YELLOW_LED_PIN_X 20
#define GREEN_LED_PIN_X 21
#define X_AXIS 26
#define Y_AXIS 27

void init_func();
void set_func();

int main(){

    init_func();
    set_func();
    
    uint adc_x_raw, adc_y_raw;

    while(1){
        adc_select_input(0);
        adc_x_raw = adc_read();
    
        adc_select_input(1);
        adc_y_raw = adc_read();

        if(adc_x_raw > 2200){
            gpio_put(YELLOW_LED_PIN_X, 1);
            sleep_ms(500);
        }
        else if(adc_x_raw < 1800){
            gpio_put(GREEN_LED_PIN_X, 1);
            sleep_ms(500);
        }
        if(adc_y_raw > 2200){
            gpio_put(GREEN_LED_PIN_Y, 1);
            sleep_ms(500);
        }
        else if(adc_y_raw < 1800){
            gpio_put(YELLOW_LED_PIN_Y, 1);
            sleep_ms(500);
        }
        gpio_put(YELLOW_LED_PIN_X, 0);
        gpio_put(GREEN_LED_PIN_Y, 0);
        gpio_put(YELLOW_LED_PIN_Y, 0);
        gpio_put(GREEN_LED_PIN_X, 0);
       
        printf("X_AXIS : %d, Y_AXIS : %d \n",adc_x_raw,adc_y_raw);
       // sleep_ms(250);
    }

}
void init_func(){
    stdio_init_all();

    gpio_init(YELLOW_LED_PIN_X);
    gpio_init(GREEN_LED_PIN_X);
    gpio_init(YELLOW_LED_PIN_Y);
    gpio_init(GREEN_LED_PIN_Y);

    adc_init();

    adc_gpio_init(X_AXIS);
    adc_gpio_init(Y_AXIS);
}
void set_func(){
    gpio_set_dir(YELLOW_LED_PIN_X, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN_X, GPIO_OUT);
    gpio_set_dir(YELLOW_LED_PIN_Y, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN_Y, GPIO_OUT);
}
