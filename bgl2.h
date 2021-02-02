#pragma once
#include <stdio.h>

#define XRES 22
#define YRES 22
#define XOFF 0
#define YOFF 0

#define BLACK 40
#define GRAY 100
#define RED 41
#define RED_LIGHT 101
#define GREEN 42
#define GREEN_LIGHT 102
#define YELLOW 43
#define YELLOW_LIGHT 103
#define BLUE 44
#define BLUE_LIGHT 104
#define PURPLE 45
#define PURPLE_LIGHT 105
#define CYAN 46
#define CYAN_LIGHT 106
#define WHITE_DARK 47
#define WHITE 107

#define B 40
#define W 107

int out[XRES][YRES];

void draw() {
    for (int i = 0; i < XRES; i++) {
        for (int j = 0; j < YRES; j++) {
            printf("%c[%d;%df\033[%dm  \033[m", 0x1B, YOFF + 1 + j, (XOFF + 1 + i) * 2, out[i][j]);
        }
    }
    printf("%c[%d;%df", 0x1B, YOFF  + XRES + 2, 0);
}