#include "header.h"

extern int red, green, blue, manual;

double localred = 0.0, localgreen = 0.0, localblue = 1023.0, alpha = 0.0, beta = 0.0;
double corr = 2 * 3.14159265 / 360;
int speeda = 1, speedb = 2;
int brightness = 1023;


#define LEDC_HS_TIMER          LEDC_TIMER_0
#define LEDC_HS_MODE           LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_GPIO       (5)
#define LEDC_HS_CH0_CHANNEL    LEDC_CHANNEL_0
#define LEDC_HS_CH1_GPIO       (18)
#define LEDC_HS_CH1_CHANNEL    LEDC_CHANNEL_1
#define LEDC_HS_CH2_GPIO       (19)
#define LEDC_HS_CH2_CHANNEL    LEDC_CHANNEL_2
#define LEDC_TEST_CH_NUM       (3)


ledc_channel_config_t ledc_channel[LEDC_TEST_CH_NUM] = {
        {
            .channel    = LEDC_HS_CH0_CHANNEL,
            .duty       = 0,
            .gpio_num   = LEDC_HS_CH0_GPIO,
            .speed_mode = LEDC_HS_MODE,
            .timer_sel  = LEDC_HS_TIMER
        },
        {
            .channel    = LEDC_HS_CH1_CHANNEL,
            .duty       = 0,
            .gpio_num   = LEDC_HS_CH1_GPIO,
            .speed_mode = LEDC_HS_MODE,
            .timer_sel  = LEDC_HS_TIMER
        },
        {
            .channel    = LEDC_HS_CH2_CHANNEL,
            .duty       = 0,
            .gpio_num   = LEDC_HS_CH2_GPIO,
            .speed_mode = LEDC_HS_MODE,
            .timer_sel  = LEDC_HS_TIMER
        }
};


void lights_task()
{
    printf("Started lights task...\n");

    ledc_timer_config_t ledc_timer = {
        .bit_num = 10, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_HS_MODE,           // timer mode
        .timer_num = LEDC_HS_TIMER            // timer index
    };
    // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer);

    
    
    for (int ch = 0; ch < LEDC_TEST_CH_NUM; ch++) {
        ledc_channel_config(&ledc_channel[ch]);
    }


    while(1)
    {
        if(manual) displayLeds(red*1023/100, green*1023/100, blue*1023/100);
        else doTraverseStep();
        vTaskDelay(5);
    } 
}

void displayLeds(int red_d, int green_d, int blue_d)
{

    ledc_set_duty(ledc_channel[0].speed_mode, ledc_channel[0].channel, red_d);
    ledc_update_duty(ledc_channel[0].speed_mode, ledc_channel[0].channel);
    ledc_set_duty(ledc_channel[1].speed_mode, ledc_channel[1].channel, green_d);
    ledc_update_duty(ledc_channel[1].speed_mode, ledc_channel[1].channel);
    ledc_set_duty(ledc_channel[2].speed_mode, ledc_channel[2].channel, blue_d);
    ledc_update_duty(ledc_channel[2].speed_mode, ledc_channel[2].channel);
}

void doTraverseStep()
{
    localred    = (brightness / 2) + (brightness / 2)*cos((alpha+=(double)speeda / 100) * corr)*sin((beta+=(double)speedb / 100) * corr);
    localgreen  = (brightness / 2) + (brightness / 2)*sin((alpha+=(double)speeda / 100) * corr)*cos((beta+=(double)speedb / 100) * corr);
    localblue   = (brightness / 2) + (brightness / 2)*cos((beta+=(double)speedb / 100) * corr); 
    displayLeds(localred, localgreen, localblue);
}