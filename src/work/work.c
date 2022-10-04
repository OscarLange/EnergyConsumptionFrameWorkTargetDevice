/*
* https://github.com/espressif/esp-idf/blob/master/examples/system/freertos/real_time_stats/main/real_time_stats_example_main.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include <stdint.h>
#include <string.h>
#include <structs.h>

//Actual CPU cycles used will depend on compiler optimization
#define SPIN_ITER           50000000  
#define SPIN_TASK_PRIO      1
#define STATS_TASK_PRIO     2
#define STATS_TICKS         pdMS_TO_TICKS(100000)
//Increase this if print_real_time_stats returns ESP_ERR_INVALID_SIZE
#define ARRAY_SIZE_OFFSET   5 

static char task_name[configMAX_TASK_NAME_LEN] = "work_task";
static SemaphoreHandle_t sync_spin_task;

struct node
{
  int data;
  struct node *next;
};

static int values[] = { 48796,87654,50135,68155,68593,84851,42453,72011,50840,6606,76255,8621,89251,11404,59997,23566};
static int values_len = 16;

int a=48796,b=87654 ,c=50135,d=68155,
            e=68593,f=84851,g=42453,h=72011,i=50840,
            j=6606,k=76255,l=8621,m=89251,n=11404,o=59997, p=23566;

float f_a=48796.234,f_b=87654.346737 ,f_c=50135.56447,f_d=68155.67345,
            f_e=68593.34678,f_f=84851.85421,f_g=42453.3467,f_h=72011.7534,f_i=50840.236,
            f_j=6606.73456,f_k=76255.8653,f_l=8621.2346,f_m=89251.567,f_n=11404.756,f_o=59997.8245, f_p=23566.452;

static struct node* insert_list(struct node* new, struct node* sorted)
{
    if(sorted == NULL || sorted->data >= new->data)
    {
        new->next = sorted;
        sorted = new;
    } else {
        struct node* current = sorted;
        while(current->next != NULL && current->next->data < new->data)
        {
            current = current->next;
        }
        new->next = current->next;
        current->next = new;
    }
    return sorted;
}

static struct node* insertion_sort(struct node head, struct node* sorted)
{
    struct node* current = &head;
    while(current != NULL)
    {
        struct node* next = current->next;
        sorted = insert_list(current, sorted);
        current = next;
    }
    return sorted;
}

static void simulate_list()
{
    struct node* nodes = heap_caps_malloc(values_len * sizeof(struct node), MALLOC_CAP_DEFAULT);
    //free(nodes);
    for(int i = 0; i < values_len; i++)
    {
        nodes[i].data = values[i];
        nodes[i].next = NULL;
    }
    for(int i = 0; i < values_len - 1; i++)
    {
        nodes[i].next = &nodes[i+1];
    }
    struct node* tmp = NULL;
    tmp = insertion_sort(nodes[0], tmp);
    heap_caps_free(nodes);
    
}

static void linked_list_task(void *arg)
{
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    while(true)
    {
        simulate_list();
    }
}

static void spin_task(void *arg)
{
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    while(true)
    {
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
        __asm__ __volatile__("NOP");
    }
}

static void add_task(void *arg)
{
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    while(true)
    {
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+k;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = p+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
        a = a+b;
        c = c+d;
        e = e+f;
        g = g+h;
        i = i+j;
    }
}

static void sub_task(void *arg)
{
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    while(true)
    {
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
        a = a-b;
        c = c-d;
        e = e-f;
        g = g-h;
        i = i-j;
    }
}

static void mul_task(void *arg)
{
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    while(true)
    {
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
        a = a*b;
        c = c*d;
        e = e*f;
        g = g*h;
        i = i*j;
    }
}
static void div_task(void *arg)
{
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    while(true)
    {
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
        a = a/b;
        c = c/d;
        e = e/f;
        g = g/h;
        i = i/j;
    }
}

static void addf_task(void *arg)
{
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    while(true)
    {
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
        f_a = f_a+f_b;
        f_c = f_c+f_d;
        f_e = f_e+f_f;
        f_g = f_g+f_h;
        f_i = f_i+f_j;
    }
}

static void subf_task(void *arg)
{
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    while(true)
    {
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
        f_a = f_a-f_b;
        f_c = f_c-f_d;
        f_e = f_e-f_f;
        f_g = f_g-f_h;
        f_i = f_i-f_j;
    }
}

static void mulf_task(void *arg)
{
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    while(true)
    {
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
        f_a = f_a*f_b;
        f_c = f_c*f_d;
        f_e = f_e*f_f;
        f_g = f_g*f_h;
        f_i = f_i*f_j;
    }
}
static void divf_task(void *arg)
{
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    while(true)
    {
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
        f_a = f_a/f_b;
        f_c = f_c/f_d;
        f_e = f_e/f_f;
        f_g = f_g/f_h;
        f_i = f_i/f_j;
    }
}

/*
* Wrapper function for uxTaskGetSystemState
* Internal esp function to get info from task scheduler
*/
uint32_t get_real_time_stats(TaskStatus_t *array, UBaseType_t array_size)
{
    uint32_t run_time;

    //Allocate array to store current task states
    if (array == NULL) {
        printf("Malloc failed\n");
        return UINT32_MAX;
    }
    //Get current task states
    array_size = uxTaskGetSystemState(array, array_size, &run_time);
    if (array_size == 0) {
        printf("No tasks to get\n");
        return UINT32_MAX;
    }
    return run_time;
}

/*
* reorder and calculate run time statistics for tasks
*/
void calculate_real_time_stats(uint32_t start_run_time, TaskStatus_t *start_array, UBaseType_t start_array_size,
    uint32_t end_run_time, TaskStatus_t *end_array, UBaseType_t end_array_size, 
    struct TABLE_ENTRY entries[])
{
    //Calculate total_elapsed_time in units of run time stats clock period.
    uint32_t total_elapsed_time = (end_run_time - start_run_time);
    if (total_elapsed_time == 0) {
        printf("Total elapsed time does not make sense, %d, %d\n", start_run_time, end_run_time);
        return;
    }

    //Match each task in start_array to those in the end_array
    for (int i = 0; i < start_array_size; i++) {
        int k = -1;
        for (int j = 0; j < end_array_size; j++) {
            if (end_array[j].xHandle != NULL && start_array[i].xHandle == end_array[j].xHandle) {
                k = j;
                //Mark that task have been matched by overwriting their handles
                start_array[i].xHandle = NULL;
                end_array[j].xHandle = NULL;
                break;
            }
        }
        //Check if matching task found
        if (k >= 0) {
            uint32_t task_elapsed_time = end_array[k].ulRunTimeCounter - start_array[i].ulRunTimeCounter;
            uint32_t percentage_time = (task_elapsed_time * 100UL) / (total_elapsed_time);

            //create entry in struct
            memcpy(entries[i].task_name, start_array[i].pcTaskName, configMAX_TASK_NAME_LEN * sizeof(char));
            entries[i].elapsed_time = task_elapsed_time;
            entries[i].percentage_time = percentage_time;
        } else {
            memcpy(entries[i].task_name, NONE_VALUE, 10 * sizeof(char));
        }
    }

    return;
}

/*
* Main collect stats function that starts tasks and collects data
*/
void collect_stats(struct TABLE_ENTRY entries[], int work_mode, int cpu_util)
{
    //cpu util 0-100
    int work_time = (RUN_TIME / 100) * cpu_util;
    int suspended_time = RUN_TIME - work_time;

    //Allow other core to finish initialization
    vTaskDelay(pdMS_TO_TICKS(100));
    xTaskHandle work_handle;

    //Create semaphores to synchronize
    sync_spin_task = xSemaphoreCreateBinary();

    if(work_mode == 0)
    {
        xTaskCreatePinnedToCore(spin_task, task_name, 1024, NULL, SPIN_TASK_PRIO, &work_handle, 1);
    } else if(work_mode == 1)
    {
        xTaskCreatePinnedToCore(add_task, task_name, 1024, NULL, SPIN_TASK_PRIO, &work_handle, 1);
    } else if(work_mode == 2)
    {
        xTaskCreatePinnedToCore(sub_task, task_name, 1024, NULL, SPIN_TASK_PRIO, &work_handle, 1);
    } else if(work_mode == 3)
    {
        xTaskCreatePinnedToCore(mul_task, task_name, 1024, NULL, SPIN_TASK_PRIO, &work_handle, 1);
    } else if(work_mode == 4)
    {
        xTaskCreatePinnedToCore(div_task, task_name, 1024, NULL, SPIN_TASK_PRIO, &work_handle, 1);
    }else if(work_mode == 5)
    {
        xTaskCreatePinnedToCore(addf_task, task_name, 1024, NULL, SPIN_TASK_PRIO, &work_handle, 1);
    } else if(work_mode == 6)
    {
        xTaskCreatePinnedToCore(subf_task, task_name, 1024, NULL, SPIN_TASK_PRIO, &work_handle, 1);
    } else if(work_mode == 7)
    {
        xTaskCreatePinnedToCore(mulf_task, task_name, 1024, NULL, SPIN_TASK_PRIO, &work_handle, 1);
    } else if(work_mode == 8)
    {
        xTaskCreatePinnedToCore(divf_task, task_name, 1024, NULL, SPIN_TASK_PRIO, &work_handle, 1);
    } else {
        xTaskCreatePinnedToCore(linked_list_task, task_name, 1024, NULL, SPIN_TASK_PRIO, &work_handle, 1);
    }

    //allocate stats values
    TaskStatus_t *start_array = NULL, *end_array = NULL;
    UBaseType_t start_array_size, end_array_size;
    uint32_t start_run_time = UINT32_MAX;
    uint32_t end_run_time = UINT32_MAX;

    //Allocate array to store current task states
    start_array_size = uxTaskGetNumberOfTasks() + ARRAY_SIZE_OFFSET;
    start_array = malloc(sizeof(TaskStatus_t) * start_array_size);

    //Start the spin task
    xSemaphoreGive(sync_spin_task);

    //Try until succesfully gotten real time stats
    start_run_time = get_real_time_stats(start_array, start_array_size);
    while (start_run_time == UINT32_MAX) {
        start_run_time = get_real_time_stats(start_array, start_array_size);
        printf("Error getting real time stats\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    //the following part is to achieve different cpu utilizations
    //actuall work time for other processor/task
    vTaskDelay(pdMS_TO_TICKS(work_time/2));
    vTaskSuspend( work_handle );

    //suspended time
    vTaskDelay(pdMS_TO_TICKS(suspended_time));

    //second work time
    vTaskResume( work_handle );
    vTaskDelay(pdMS_TO_TICKS(work_time/2));

    //Allocate array to store current task states
    end_array_size = uxTaskGetNumberOfTasks() + ARRAY_SIZE_OFFSET;
    end_array = malloc(sizeof(TaskStatus_t) * end_array_size);

    ///Try until succesfully gotten real time stats
    end_run_time = get_real_time_stats(end_array, end_array_size);
    while (end_run_time == UINT32_MAX) {
        end_run_time = get_real_time_stats(end_array, end_array_size);
        printf("Error getting real time stats\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    //calculate the real_time_stats
    calculate_real_time_stats(start_run_time, start_array, start_array_size, end_run_time, end_array, end_array_size, entries);

    //stop the working task to be done
    vTaskDelete(work_handle);
}