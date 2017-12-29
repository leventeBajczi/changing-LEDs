#include "header.h"

int red = 0, green = 0, blue = 0, manual = 0;


static const char* webpage = "<form action=\"/leds\"><table><tr><td>Red:</td><td><input type=\"range\" name=\"red\" value=", *webpage1 = "></td></tr><tr><td>Green:</td><td><input type=\"range\" name=\"green\" value=", *webpage2 = "></td></tr><tr><td>Blue:</td><td><input type=\"range\" name=\"blue\" value=", *webpage3 = "></td></tr></table><input type=\"radio\" name=\"type\" value=\"0\" checked> Auto <input type=\"radio\" name=\"type\" value=\"1\"", *webpage4 = "> Manual<br><input type=\"submit\"></form>";

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

void wifi_task()
{
    nvs_flash_init();
    printf("Started wifi task...\n");
    tcpip_adapter_init();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    wifi_config_t sta_config = {
        .sta = {
            .ssid = "UPC",
            .password = "19670227",
            .bssid_set = false
        }
    };
    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
    ESP_ERROR_CHECK( esp_wifi_connect() );
    vTaskDelay(500);
    printf("Connected to WiFi network.\n");
    http_server_task();
    while(1) vTaskDelay(1000);
}
static void http_server_task()
{   
    struct netconn *conn, *newconn;
    err_t err;
    conn = netconn_new(NETCONN_TCP);
    netconn_bind(conn, NULL, 80);
    netconn_listen(conn);
    do {
        err = netconn_accept(conn, &newconn);
        if (err == ERR_OK) {
            http_server_netconn_serve(newconn);
            netconn_delete(newconn);
        }
    } while (err == ERR_OK);
    netconn_close(conn);
    netconn_delete(conn);
}

static void http_server_netconn_serve(struct netconn *conn)
{
    struct netbuf *inbuf;
    char *buf;
    u16_t buflen;
    err_t err;
    char data[10];
    err = netconn_recv(conn, &inbuf);

    if (err == ERR_OK) {
        netbuf_data(inbuf, (void**) &buf, &buflen);
        parse_form(buf);
        netconn_write(conn, "<html><body>", strlen("<html><body>"), NETCONN_NOCOPY);
        netconn_write(conn, webpage, strlen(webpage), NETCONN_COPY);
        sprintf(data, "%d", red);
        netconn_write(conn, data, strlen(data), NETCONN_COPY);
        netconn_write(conn, webpage1, strlen(webpage1), NETCONN_COPY);
        sprintf(data, "%d", green);
        netconn_write(conn, data, strlen(data), NETCONN_COPY);
        netconn_write(conn, webpage2, strlen(webpage2), NETCONN_COPY);
        sprintf(data, "%d", blue);
        netconn_write(conn, data, strlen(data), NETCONN_COPY);
        netconn_write(conn, webpage3, strlen(webpage3), NETCONN_COPY);
        if(manual)  netconn_write(conn, " checked", strlen(" checked"), NETCONN_NOCOPY);
        netconn_write(conn, webpage4, strlen(webpage4), NETCONN_COPY);
        netconn_write(conn, "</body></html>", strlen("</body></html>"), NETCONN_NOCOPY);

    }
    netconn_close(conn);

    netbuf_delete(inbuf);
}

void parse_form(char* header)
{
    printf("Parsing input...\n");
    sscanf(header, "GET /leds?red=%d&green=%d&blue=%d&type=%d", &red, &green, &blue, &manual);
    printf("%d\t%d\t%d\t%d\n", red, green, blue, manual);
    printf("Form parsed.\n");
}

void build_form(char** form)
{
    char* checked = (manual) ? "checked" : "";
    printf("Building form....\n");
    free(*form);
    *form = (char*) malloc(sizeof(char)*(strlen(webpage) + strlen(webpage1) + strlen(webpage2) + strlen(webpage3) + strlen(webpage4) + 20));
    sprintf(*form, "%s%d%s%d%s%d%s%s%s", webpage, red, webpage1, green, webpage2, blue, webpage3, checked, webpage4);
    printf("Form built: %s\n", *form);
}