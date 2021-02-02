#pragma once

#include <iostream>
#include <cstring>
#include "vec.h"
#include "bgl2.h"

void setfood(vec size, vec foodpos, char* txt)
{
    out[foodpos.x][foodpos.y] = RED;
}
void setvoxeldata(int* voxel, vec size, char* txt)
{
    if(size.y % 2) size.y--;
    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            int a = voxel[x + y * size.x];
            for(int i = 0; i < 2; i++)
            {
                if(a) out[x][y] = BLUE;
                else out[x][y] = CYAN_LIGHT;
            }
        }
    }
}