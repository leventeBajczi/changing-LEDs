#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "tcpip_adapter.h"
#include "lwip/api.h"
#include "driver/ledc.h"
#include "string.h"

void app_main();


void wifi_task();
static void http_server_netconn_serve(struct netconn *);
static void http_server_task();
void build_form(char**);
void parse_form(char*);

void lights_task();
void displayLeds(int, int, int);
void doTraverseStep();

#endif