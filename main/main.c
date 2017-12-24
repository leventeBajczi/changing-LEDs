#include "header.h"


void app_main()
{
   xTaskCreatePinnedToCore(&wifi_task, "wifi task", 4096, NULL, 5, NULL, 0);
   xTaskCreatePinnedToCore(&lights_task, "lights task", 4096, NULL, 5, NULL, 0);
}
