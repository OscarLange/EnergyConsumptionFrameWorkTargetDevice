#pragma once

#include <cstring>
#include <mutex>

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_system.h"
#include "esp_netif.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include <iostream>
#include <string>

namespace EnergyConsumptionFramework
{
    #define host_ip "192.168.178.23"
    #define host_port 8090


    class TCPClient
    {
        public:
            TCPClient(void);
            void tcp_client_task(char *payload, bool get_info, bool get_work);

            //config vars that are set through the TCP connection are stored here
            //Frequency, type of work function, utilization
            int freq = 0;
            int work_mode = 0;
            int cpu_util = 0;
            //this is for automisation so the program can switch configs without restarting the server/client software
            // 0 => do nothing; 1 => get work; => 2 get freq;
            int mode = 0;
            bool light_sleep_enable = false;
            std::string work;

        private:
    };
}