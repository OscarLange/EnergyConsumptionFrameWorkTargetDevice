#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_pm.h"

//have to be power of 2 for cropping
#define SIZEX 10
#define SIZEY 10

struct RGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t gray_scale;
    float gray_scale_norm;
};


void set_seed()
{
    //set random seet
    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t time_us = (uint64_t)tv_now.tv_sec * 1000000L + (uint64_t)tv_now.tv_usec;
    srand(time_us);
}

uint8_t random_rgb(void)
{
    return (uint8_t)((rand() % 10) * (rand() % 25));
}

void fill_picture(struct RGB picture[][SIZEY])
{
    for(int x = 0; x < SIZEX; x++)
    {
        for(int y = 0; y < SIZEY; y++)
        {
            picture[x][y].red = random_rgb();
            picture[x][y].green = random_rgb();
            picture[x][y].blue = random_rgb();
            picture[x][y].gray_scale = 0;
            picture[x][y].gray_scale_norm = 0;
        }
    }
}

void gray_scale_image(struct RGB picture[][SIZEY])
{
    for(int x = 0; x < SIZEX; x++)
    {
        for(int y = 0; y < SIZEY; y++)
        {
            picture[x][y].gray_scale = (0.3 * picture[x][y].red) + (0.59 * picture[x][y].green) + (0.11 * picture[x][y].blue);
        }
    }
}

void normalize_img(struct RGB picture[][SIZEY])
{
    int max = 0;
    int min = 255;
    for(int x = 0; x < SIZEX; x++)
    {
        for(int y = 0; y < SIZEY; y++)
        {
            if(picture[x][y].gray_scale > max)
            {
                max = picture[x][y].gray_scale;
            }
            if(picture[x][y].gray_scale < min)
            {
                min = picture[x][y].gray_scale;
            }
        }
    }
    for(int x = 0; x < SIZEX; x++)
    {
        for(int y = 0; y < SIZEY; y++)
        {
            picture[x][y].gray_scale_norm = (float)(picture[x][y].gray_scale - min)/(float)(max-min);
        }
    }
}

void copy_rgb(struct RGB picture[][SIZEY],struct RGB tmp, int x, int y)
{
    picture[x][y].red = tmp.red;
    picture[x][y].green = tmp.green;
    picture[x][y].blue = tmp.blue;
    picture[x][y].gray_scale = tmp.gray_scale;
    picture[x][y].gray_scale_norm = tmp.gray_scale_norm;
}

void rescale(struct RGB picture[][SIZEY],struct RGB tmp, int x, int y)
{
    copy_rgb(picture, tmp, x, y);
    copy_rgb(picture, tmp, x+1, y);
    copy_rgb(picture, tmp, x, y+1);
    copy_rgb(picture, tmp, x+1, y+1);
}

void crop_rescale(struct RGB picture[][SIZEY])
{
    int x_start = SIZEX/2;
    int y_start = SIZEY/2;
    int x_resc = 0;
    int y_resc = 0;
    for(int x = x_start; x < SIZEX; x++)
    {
        for(int y = y_start; y < SIZEY; y++)
        {
            struct RGB crop = picture[x][y];
            rescale(picture, crop, x_resc, y_resc);
            y_resc +=2;
        }
        y_resc = 0;
        x_resc +=2;
    }
}

void print_picture(struct RGB picture[][SIZEY])
{
    for(int x = 0; x < SIZEX; x++)
    {
        for(int y = 0; y < SIZEY; y++)
        {
            printf("[%d,%d,%d,%d,%f],", picture[x][y].red, picture[x][y].green, picture[x][y].blue, picture[x][y].gray_scale, picture[x][y].gray_scale_norm);
        }
        printf("\n");
    }
    printf("-----------------------\n");
}

void preprocess_img(void *arg)
{
    struct RGB picture[SIZEX][SIZEY];
    set_seed();
    while(1)
    {
        fill_picture(picture);
        //print_picture(picture);
        gray_scale_image(picture);
        //print_picture(picture);
        normalize_img(picture);
        //print_picture(picture);
        crop_rescale(picture);
        //print_picture(picture);
    }
}

void start_preproc_task(void)
{
    xTaskCreatePinnedToCore(preprocess_img, "preproc_task", 8192, NULL, 1, NULL, 1);
}