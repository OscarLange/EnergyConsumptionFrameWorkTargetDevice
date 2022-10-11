#include <string>
#include <sstream>
#include <iostream>

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_pm.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "tcp.h"
#include "structs.h"
#include "esp_http_client.h"

class Main final
{
private:
public:
    /*
        * Main loop that runs continously
        */
        void run(void);
        /*
        * One time execution that sets up imortant functionalities such as the WiFi
        */
        void setup(void);
        /*
        * Sending a msg over tcp
        */
        void send_msg(char *payload, bool get_info, bool get_work);
        EnergyConsumptionFramework::TCPClient TCPClient;
};