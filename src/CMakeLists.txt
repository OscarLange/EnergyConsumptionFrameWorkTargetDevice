set(SOURCES main.cpp
            work/work.c tcp/tcp.cpp wifi/wifi.c http/http.c)
            
idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS . ../include/tcp ../include/structs
                    REQUIRES esp_wifi nvs_flash esp_event esp_netif lwip esp_http_client esp-tls)