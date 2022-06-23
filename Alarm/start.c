#include<stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

#define RED_LED_PIN 18
#define GREEN_LED_PIN 19
#define BUZZER_PIN 20
#define OPEN_BUTTON_PIN 16
#define CLOSE_BUTTON_PIN 17
#define MOTION_SENSOR_PIN 28

void MOTION_SENSOR();

int main(){

    stdio_init_all();

    gpio_init(RED_LED_PIN);
    gpio_init(GREEN_LED_PIN);
    gpio_init(BUZZER_PIN);
    gpio_init(OPEN_BUTTON_PIN);
    gpio_init(CLOSE_BUTTON_PIN);

    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    
    gpio_set_dir(OPEN_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(OPEN_BUTTON_PIN);

    gpio_set_dir(CLOSE_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(CLOSE_BUTTON_PIN);

    adc_init();
    adc_gpio_init(MOTION_SENSOR_PIN);
    adc_select_input(2);

    int open_close = 0; // 0 --> close // 1 --> open

    while(1){
        if(gpio_get(OPEN_BUTTON_PIN) == false){
            open_close = 1;
            printf("OPEN_BUTTON is true\n");
        }
        else if(gpio_get(CLOSE_BUTTON_PIN) == false){
            open_close = 0;
            printf("CLOSE_BUTTON is true\n");
        }
        if(open_close == 1){
            gpio_put(RED_LED_PIN, 1);
            gpio_put(GREEN_LED_PIN, 0);
            MOTION_SENSOR();
        }
        else if(open_close == 0){
            gpio_put(GREEN_LED_PIN, 1);
            gpio_put(RED_LED_PIN, 0);
        }


        printf("Working\n");
        sleep_ms(250);
    }

    return 0;
}
void MOTION_SENSOR(){
    int deger = adc_read();
    if(deger > 4000){
        gpio_put(BUZZER_PIN, 1);
    }
    else{
        gpio_put(BUZZER_PIN, 0);
    }
}
