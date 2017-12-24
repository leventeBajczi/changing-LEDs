#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main();
void wifi_task();
void lights_task();

#endif