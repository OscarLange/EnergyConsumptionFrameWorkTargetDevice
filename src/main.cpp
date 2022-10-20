#include "main.h"


Main App;

//persistent variable
static RTC_NOINIT_ATTR  int max_freq;

char config_msg[] = "Request config";
char work_msg[] = "Get work";
char bo_msg[] = "Brownout";
int restart = 0;
int work_mode = 0;
int cpu_utilization = 0;

extern "C" void collect_stats(struct TABLE_ENTRY entries[], int work_mode, int cpu_util);
extern "C" void init_wifi();
extern "C" void restart_wifi();
extern "C" void start_msg_task(void);
extern "C" void start_preproc_task(void);
//send msg over tcp
void Main::send_msg(char *payload, bool get_info, bool get_work)
{
    vTaskDelay(pdMS_TO_TICKS(100));
    TCPClient.tcp_client_task(payload, get_info, get_work);
}

void Main::run(void)
{
    //get frequency
    esp_pm_config_esp32_t pm_config;
    esp_pm_get_configuration(&pm_config);

    //msgs
    char end_msg[] = "Stop collecting";
    std::stringstream start_stream{};
    //send frequency back to make sure the server and client are in sync
    start_stream << "Start collecting:" << pm_config.min_freq_mhz << "," << TCPClient.cpu_util << "," << TCPClient.work_mode;
    auto start = start_stream.str();

    //send msg to rasberry to start collecting
    App.send_msg(start.data(), false, false);

    //stop wifi for stat collection
    esp_wifi_stop();
    
    //collect stats
    struct TABLE_ENTRY entries[11] = {};
    collect_stats(entries, TCPClient.work_mode, TCPClient.cpu_util);

    //start wifi again
    restart_wifi();

    //send msg to rasberry to stop collecting
    std::cout << end_msg << "\n";
    App.send_msg(end_msg, false, false);

    //building string
    //encode the collected metrics to be sent to the server
    std::stringstream entries_stream{};
    for(auto &entry: entries)
    {
        std::string s_entry = std::string(entry.task_name);
        if(s_entry.substr(0, sizeof(NONE_VALUE)) != std::string(NONE_VALUE))
        {
            entries_stream << entry.task_name << "," << entry.elapsed_time << "," << entry.percentage_time <<";";
        }
        entries_stream << "MIN_FREQ," << pm_config.min_freq_mhz << ";MAX_FREQ," <<pm_config.max_freq_mhz << ";";
    }
    auto final = entries_stream.str();
 

    //send values
    App.send_msg(final.data(), false, false);

    if(TCPClient.mode == 1)
    {
        //retrieve new work (type of operation, work utilization)
        //Seting work
        App.send_msg(work_msg, false, true);

    } else if(TCPClient.mode == 2)
    {
        //retrieve new frequency
        //send msg to rasberry to get config values
        App.send_msg(config_msg, true, false);
        
        //stop the wifi 
        esp_wifi_stop();
        max_freq = TCPClient.freq;
        vTaskDelay(pdMS_TO_TICKS(500));
        esp_restart();
    }
}

void Main::setup(void)
{
    //get the reason for the reset of esp
    esp_reset_reason_t reason = esp_reset_reason();


    //if its a software reset then setup frequency and wifi
    if(reason == ESP_RST_SW)
    {
        esp_pm_config_esp32_t pm_config = {
                .max_freq_mhz = max_freq,
                .min_freq_mhz = max_freq,
                .light_sleep_enable = false
            };
        ESP_ERROR_CHECK( esp_pm_configure(&pm_config) );
        vTaskDelay(pdMS_TO_TICKS(1000));

        //connect to WiFi
        init_wifi();

        //Seting work
        std::cout << work_msg << "\n";
        App.send_msg(work_msg, false, true);
    } 
    else if(reason == ESP_RST_BROWNOUT) {
        esp_pm_config_esp32_t pm_config = {
                .max_freq_mhz = max_freq,
                .min_freq_mhz = max_freq,
                .light_sleep_enable = false
            };
        ESP_ERROR_CHECK( esp_pm_configure(&pm_config) );
        vTaskDelay(pdMS_TO_TICKS(1000));

        //connect to WiFi
        init_wifi();

        App.send_msg(bo_msg, false, false);
        vTaskDelay(pdMS_TO_TICKS(1000));

        //Seting work
        std::cout << work_msg << "\n";
        App.send_msg(work_msg, false, true);
    } else {
        vTaskDelay(pdMS_TO_TICKS(1000));

        //connect to WiFi
        init_wifi();
        
        std::cout << "Getting Frequency\n";
        //send msg to rasberry to get config values
        App.send_msg(config_msg, true, false);

        //Stop wifi to reset frequency
        esp_wifi_stop();
        std::cout << "Stopping Wifi\n";
        //store frequency for reset
        max_freq = TCPClient.freq;
        std::cout << "Storing Frequency: " << max_freq << ", and reseting esp\n";
        vTaskDelay(pdMS_TO_TICKS(500));
        esp_restart();
    }
}

extern "C" void app_main(void)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
    esp_pm_config_esp32_t pm_config = {
                .max_freq_mhz = 240,
                .min_freq_mhz = 240,
                .light_sleep_enable = false
            };
    ESP_ERROR_CHECK( esp_pm_configure(&pm_config) );
    vTaskDelay(pdMS_TO_TICKS(1000));
    //connect to WiFi
    init_wifi();
    start_msg_task();
    // start_preproc_task();
    // App.setup();
    // while (true)
    // {
    //     vTaskDelay(pdMS_TO_TICKS(1000));
    //     App.run();
    // }
}
