#include "tcp.h"

/*
* https://github.com/espressif/esp-idf/blob/v4.2/examples/protocols/sockets/tcp_client/main/tcp_client.c
*/

namespace EnergyConsumptionFramework {

    TCPClient::TCPClient(void)
    {

    }

    //Send msg via tcp and wait for acknowledge
    void TCPClient::tcp_client_task(char *payload, bool get_info, bool get_work) {
        char rx_buffer[128];

        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = inet_addr(host_ip);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(host_port);

        int addr_family = AF_INET;
        int ip_protocol = IPPROTO_IP;

        int sock =  socket(addr_family, SOCK_STREAM, ip_protocol);
        if(sock < 0) {
            std::cout << "Could not create Socket\n";
            return;
        }

        int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in6));
        if (err != 0) {
            std::cout << "Socket unable to connect";
            return;
        }

        int send_err = send(sock, payload, strlen(payload), 0);
        if(send_err < 0) {
            std::cout << "Could not send msg\n";
            return;
        }

        std::cout << "Waiting on recv msg\n";
        int len =  recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);

        if(send_err < 0) {
            std::cout << "Could not recv msg\n";
            return;
        }
        else {
            rx_buffer[len] = 0;
            std::cout << "Msg: " << rx_buffer << "\n";
            std::string config(rx_buffer);
            if(get_info)
            {
                //Set work and frequency
                //TODO switch work with light sleep mode
                std::string work = config.substr(0, config.find(","));
                this->work = work;
                std::string freq = config.substr(config.find(",")+1, config.find(";") - config.find(",") - 1);
                this->freq = std::stoi(freq);
            } else if(get_work)
            {
                //set work and utilization
                std::string work = config.substr(0, config.find(","));
                this->work_mode = std::stoi(work);
                std::string cpu_util = config.substr(config.find(",")+1, config.find(";") - config.find(",") - 1);
                this->cpu_util = std::stoi(cpu_util);
            } else {
                //setup potential switch in config
                std::string ack("Acknowledged");
                if (config.find(ack) == std::string::npos) {
                    std::string freq_switch("Freq Switch");
                    std::string config_switch("Config Switch");
                    if(config.find(freq_switch) != std::string::npos)
                    {
                        this->mode = 2;
                    } else if(config.find(config_switch) != std::string::npos)
                    {
                        this->mode = 1;
                    }
                } 
            }
        }

        if (sock != -1) {
            std::cout << "Shutting down socket and restarting...\n";
            shutdown(sock, 0);
            close(sock);
        }
    }

}