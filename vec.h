#pragma once

#include <cmath>
typedef struct vec
{
    int x, y;
    vec(int x, int y) : x(x), y(y) {}
    vec(int x) : x(x), y(0) {}
    vec() : x(0), y(0) {}

    vec operator +(vec a) {return vec(x + a.x, y + a.y);}
    vec operator -(vec a) {return vec(x - a.x, y - a.y);}
    vec operator /(int a) {return vec(x / a, y / a);}
    vec operator *(int a) {return vec(x * a, y * a);}
    
    vec operator -() {return vec(-x, -y);}

    float sqrmag()
    {
        return x*x + y*y;
    }
    float mag()
    {
        return sqrtf(sqrmag());
    }
    vec rotate90(int direction)
    {
        if(direction < 0) direction = -direction;
        direction %= 4;
        vec a = *this;
        switch (direction)
        {
            case 1:
                a = vec(y, -x);
                break;
            case 2:
                a = -*this;
                break;
            case 3:
                a = vec(-y, x);
                break;
        }
        return a;
    }
}vec;