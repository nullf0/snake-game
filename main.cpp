#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include "voxel.h"
#include "vec.h"
#include "bgl2.h"

int delta = 100;
int defaultsnakestrength = 2;
int snakestrength;
int score = 0;
int direction = 3;

vec size = vec(22, 22);

int* voxel;
char* txt;
vec crnt;

vec food;
int key;

int quit = 0;
int lost = 0;

int h;

void getsize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
int random(int seed)
{
    return (int)(sqrtf(seed) * 1000000.0f);
}
void setvoxelpos(int* voxel, vec a, int value, vec start, vec end)
{
    while(a.x < start.x || a.y < start.y) return;
    if(a.x >= end.x || a.y >= end.y) return;
    voxel[a.x + a.y * end.x] = value;
}
void drawsqrline(int*voxel, vec start, vec end, vec size)
{
    for(int x = 0; x < size.x; x++)
    {
        for(int y = 0; y < size.y; y++)
        {
            if(x == start.x || x == end.x)
            {
                if(y >= start.y && y <= end.y)
                {
                    voxel[x + y * size.x] = 1;
                }
            }
            if(y == start.y || y == end.y)
            {
                if(x >= start.x && x <= end.x)
                {
                    voxel[x + y * size.x] = 1;
                }
            }
        }
    }
}
void instantupdate()
{
    if(_kbhit())
    {
        key = _getch();
        if(key == 'x')
        {
            printf("Do you want to quit? [y/n]\n");
            scanf_s("%1s", &key);
            if(key == 'y')
            {
                quit = 1;
                return;
            }
        }
    }
}
void update()
{
    for(int i = 0; i < size.x * size.y; i++)
    {
        if(voxel[i] > 0) voxel[i]--;
    }
    if(key == 'w' && direction != 0) direction = 2;
    if(key == 'd' && direction != 3) direction = 1;
    if(key == 's' && direction != 2) direction = 0;
    if(key == 'a' && direction != 1) direction = 3;
    drawsqrline(voxel, vec(), size - vec(1, 1), size);
    crnt = crnt + vec(0, 1).rotate90(direction);
    while(crnt.x < 1) crnt.x += size.x - 2;
    while(crnt.y < 1) crnt.y += size.y - 2;
    while(crnt.x >= size.x - 1) crnt.x -= size.x - 2;
    while(crnt.y >= size.y - 1) crnt.y -= size.y - 2;
    if(crnt.x == food.x && crnt.y == food.y)
    {
        for(int y = 1; y < size.y - 1; y++)
        {
            for(int x = 1; x < size.x - 1; x++)
            {
                if(voxel[x + y * size.x] > 0) voxel[x + y * size.x]++;
            }
        }
        score++;
        snakestrength++;
        int rng = rand();
        if(rng < 0) rng = -rng;
        food.x = random(rng) % (size.x - 2) + 1;
        food.y = random(rng) % (size.y - 2) + 1;
        while(voxel[food.x + food.y * size.x] > 0)
        {
            rng = rand();
            food.x = random(rng) % (size.x - 2) + 1;
            food.y = random(rng) % (size.y - 2) + 1;
        }
    }
    else if(voxel[crnt.x + crnt.y * size.x])
    {
        lost = 1;
        return;
    }
    voxel[crnt.x + crnt.y * size.x] = snakestrength;
    voxel[food.x + food.y * size.x] = snakestrength;
    setvoxeldata(voxel, size, txt);
    setfood(size, food, txt);
    draw();
    printf("Score: %d\n", score);
    printf("\nPress x to quit\n");
    if(lost)
    {
        printf("\nGame Over!\nTry again? [y/n]\n");
        scanf_s("%1s", &key);
        if(key == 'n')
        {
            quit = 1;
            return;
        }
        else
        {
            lost = 0;
            int rng = rand();
            if(rng < 0) rng = -rng;
            food = vec(rng % (size.x - 2) + 1, (int)(sqrtf(rng) * 1000000.0f) % (size.y - 2) + 1);
            crnt = size / 2 + vec(1, 1);
            snakestrength = defaultsnakestrength;
            for(int i = 0; i < size.x * size.y; i++)
            {
                voxel[i] = 0;
            }
            update();
        }
    }
}
int main(int argc, char** argv)
{
    snakestrength = defaultsnakestrength;
    srand(time(NULL));
    int rng = rand();
    if(rng < 0) rng = -rng;
    food = vec(rng % (size.x - 2) + 1, (int)(sqrtf(rng) * 1000000.0f) % (size.y - 2) + 1);
    voxel = (int*)malloc(size.x * size.y * sizeof(int));
    txt = (char*)malloc((size.x * 2 + 1) * size.y + 1);
    crnt = size / 2 + vec(1, 1);
    for(int i = 0; i < size.x * size.y; i++)
    {
        voxel[i] = 0;
    }
    clock_t a = clock();
    while(1)
    {
        instantupdate();
        if(quit)
        {
            free(voxel);
            free(txt);
            return 0;
        }
        if(clock() > a)
        {
            a = clock() + delta;
            update();
        }
    }
}