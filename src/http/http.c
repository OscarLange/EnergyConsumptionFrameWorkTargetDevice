#include "esp_http_client.h"
#include "esp_log.h"
#include "esp_tls.h"
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>

#define MAX 100

static const char *TAG = "HTTP_CLIENT";
esp_http_client_handle_t client;

esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    static char *output_buffer;  // Buffer to store response of http request from event handler
    static int output_len;       // Stores number of bytes read
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            /*
             *  Check for chunked encoding is added as the URL for chunked encoding used in this example returns binary data.
             *  However, event handler can also be used in case chunked encoding is used.
             */
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // If user_data buffer is configured, copy the response into the buffer
                if (evt->user_data) {
                    memcpy(evt->user_data + output_len, evt->data, evt->data_len);
                } else {
                    if (output_buffer == NULL) {
                        output_buffer = (char *) malloc(esp_http_client_get_content_length(evt->client));
                        output_len = 0;
                        if (output_buffer == NULL) {
                            ESP_LOGE(TAG, "Failed to allocate memory for output buffer");
                            return ESP_FAIL;
                        }
                    }
                    memcpy(output_buffer + output_len, evt->data, evt->data_len);
                }
                output_len += evt->data_len;
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            if (output_buffer != NULL) {
                // Response is accumulated in output_buffer. Uncomment the below line to print the accumulated response
                // ESP_LOG_BUFFER_HEX(TAG, output_buffer, output_len);
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            int mbedtls_err = 0;
            esp_err_t err = esp_tls_get_and_clear_last_error((esp_tls_error_handle_t)evt->data, &mbedtls_err, NULL);
            if (err != 0) {
                ESP_LOGI(TAG, "Last esp error code: 0x%x", err);
                ESP_LOGI(TAG, "Last mbedtls failure: 0x%x", mbedtls_err);
            }
            if (output_buffer != NULL) {
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            break;
    }
    return ESP_OK;
}

void init_client()
{
    char local_response_buffer[2048] = {0};
    esp_http_client_config_t config = {0};
    config.url = "https://google.com";
    config.event_handler = http_event_handler;
    config.user_data = local_response_buffer;
    config.buffer_size_tx = 4096;
    config.buffer_size = 2048;
    client = esp_http_client_init(&config);
}

void putData(float temp,int humidity, float heat_index, int index)
{
    char temp_s[MAX], humidity_s[MAX], heat_index_s[MAX], index_s[MAX];
    char post_data[MAX] = "{\"Temperature\": ";
    const char *post_data2 = ", \"Humidity\": ";
    const char *post_data3 = ", \"Heat Index\": ";
    const char *post_data4 = "}";
    sprintf(temp_s, "%f", temp);
    strcat(post_data, temp_s);
    strcat(post_data, post_data2);
    sprintf(humidity_s, "%d", humidity);
    strcat(post_data, humidity_s);
    strcat(post_data, post_data3);
    sprintf(heat_index_s, "%f", heat_index);
    strcat(post_data, heat_index_s);
    strcat(post_data, post_data4);

    char url[MAX] = "https://esp-idf-default-rtdb.europe-west1.firebasedatabase.app/measurement";
    const char *url2 = ".json";
    sprintf(index_s, "%d", index);
    strcat(url, index_s);
    strcat(url, url2);

    ESP_ERROR_CHECK(esp_http_client_set_header(client, "Content-Type", "application/json"));
    ESP_ERROR_CHECK(esp_http_client_set_url(client, url));
    ESP_ERROR_CHECK(esp_http_client_set_method(client, HTTP_METHOD_PUT));
    ESP_ERROR_CHECK(esp_http_client_set_post_field(client, post_data, strlen(post_data)));
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
    }
}


void msg_task(void *arg)
{
    //init http client
    init_client();

    //set random seet
    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t time_us = (uint64_t)tv_now.tv_sec * 1000000L + (uint64_t)tv_now.tv_usec;
    srand(time_us);

    //some contants
    float max_temp = 16.0;
    float c[9] = {-42.379, 2.04901523, 10.14333127,-0.22475541,-0.00683783,-0.05481717, 0.00122874,0.00085282,-0.00000199};
    
    int index = 0;
    while(true)
    {
        //get random celsius and conver to fahrenheit for heat index
        float t = 27 + (((float)rand()/(float)(RAND_MAX)) * max_temp);
        float tf = t*1.8+32;
        int h = (rand() % 60)+40;

        //calc heat index
        float heat_index = c[0] + c[1]*tf + c[2]*h + c[3]*tf*h + c[4]*tf*tf + c[5]*h*h + c[6]*tf*tf*h + c[7]*tf*h*h + c[8]*tf*tf*h*h;
        //turn into celsius
        heat_index = (heat_index - 32)/1.8;

        putData(t, h, heat_index, index);
        index++;
        if(index > 20)
        {
            index = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(1200));
    }
    

    //stop client
    esp_http_client_cleanup(client);
}

void start_msg_task(void)
{
    xTaskCreatePinnedToCore(msg_task, "http_test_task", 8192, NULL, 1, NULL, 1);
}