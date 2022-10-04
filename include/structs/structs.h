#include <stdint.h>
#include "freertos/FreeRTOS.h"


#define NONE_VALUE "NONE_VALUE"  

//200 sec run time
#define RUN_TIME 200000

struct TABLE_ENTRY {
    char task_name[configMAX_TASK_NAME_LEN];
    uint32_t elapsed_time;
    uint32_t percentage_time;
};