#include <iostream>
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"

#define GREEN_LED_PIN 0
#define YELLOW_LED_PIN 1
#define RED_LED_PIN 3
#define BUZZER_PIN 4
#define ECHO_PIN 18
#define TRIGGER_PIN 17

using namespace std;

void init_led();
void set_led();
void init_sensor();
void set_sensor();
void init_buzzer();
void set_buzzer();
void openLed(int green, int yellow, int red);
void buzzer_low();
void buzzer_mid();
void buzzer_high();
uint64_t getDistance();

int main(){
    stdio_init_all();
    init_led();
    set_led();
    init_sensor();
    set_sensor();
    init_buzzer();
    set_buzzer();

    int distance;

    while(1){
        distance = getDistance() / 29;
        cout << "Distance : " << getDistance()/29 << endl;
        
        if(distance < 10){
            openLed(0, 0, 1);
            buzzer_high();
        }
        else if(distance < 20){
            openLed(0, 1, 0);
            buzzer_mid();
        }
        else if(distance < 30){
            openLed(1, 0, 0);
            buzzer_low();
        }
        else{
            openLed(0, 0, 0);
            gpio_put(BUZZER_PIN, 0);
        }
        
    }
    return 0;
}
void buzzer_low(){
    gpio_put(BUZZER_PIN, 1);
    sleep_ms(500);
    gpio_put(BUZZER_PIN, 0);
    sleep_ms(500);
}
void buzzer_mid(){
    gpio_put(BUZZER_PIN, 1);
    sleep_ms(250);
    gpio_put(BUZZER_PIN, 0);
    sleep_ms(250);
}
void buzzer_high(){
    gpio_put(BUZZER_PIN, 1);
}
uint64_t getDistance(){

    gpio_put(TRIGGER_PIN, 1);
    sleep_us(10);
    gpio_put(TRIGGER_PIN, 0);
    absolute_time_t startTime, endTime;

    while(gpio_get(ECHO_PIN) == 0){

    }
    startTime = get_absolute_time();
    while(gpio_get(ECHO_PIN) == 1){
        sleep_us(1);
    }
    endTime = get_absolute_time();

    return absolute_time_diff_us(startTime, endTime) /2;
}
void init_buzzer(){
    gpio_init(BUZZER_PIN);
}
void set_buzzer(){
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}
void init_sensor(){
    gpio_init(TRIGGER_PIN);
    gpio_init(ECHO_PIN);
}
void set_sensor(){
    gpio_set_dir(TRIGGER_PIN, GPIO_OUT);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
}
void init_led(){
    gpio_init(GREEN_LED_PIN);
    gpio_init(YELLOW_LED_PIN);
    gpio_init(RED_LED_PIN);
}
void set_led(){
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_set_dir(YELLOW_LED_PIN, GPIO_OUT);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
}
void openLed(int green, int yellow, int red){
    gpio_put(GREEN_LED_PIN, green);
    gpio_put(YELLOW_LED_PIN, yellow);
    gpio_put(RED_LED_PIN, red);
}
