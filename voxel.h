#pragma once

#include <iostream>
#include <cstring>
#include "vec.h"
#define fullblock (char)219
#define foodchar (char)178

void setfood(vec size, vec foodpos, char* txt)
{
    int idx = foodpos.x * 2 + foodpos.y * (size.x * 2 + 1);
    txt[idx] = foodchar;
    txt[idx + 1] = foodchar;
}
void setvoxeldata(int* voxel, vec size, char* txt)
{
    if(size.y % 2) size.y--;
    int idx = 0;
    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            int a = voxel[x + y * size.x];
            for(int i = 0; i < 2; i++)
            {
                if(a) txt[idx] = fullblock;
                else txt[idx] = ' ';
                idx++;
            }
        }
        txt[idx] = '\n';
        idx++;
    }
    txt[idx] = '\0';
}