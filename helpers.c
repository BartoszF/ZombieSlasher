#include "helpers.h"
#include <allegro.h>

// Check if Point a is "in" Rectangle b
bool ABB(Point a,Rect b)
{
    if(a.x > b.x && a.x < b.x + b.w)
    {
        if(a.y > b.y && a.y < b.y + b.h)
        {
            return true;
        }
    }
    return false;
}

// Check if Rectangle a intersects, or is "in" Rectangle b
bool AABB(Rect a,Rect b)
{
    int stala = 1;
    if((a.x > b.x && a.x < b.x + b.w) || (b.x > a.x && b.x < a.x + a.w))
    {
        if((a.y > b.y && a.y < b.y + b.h) || (b.y > a.y && b.y < a.y + a.h))
        {
            return true;
        }
    }
    return false;
}

// Check side of collision
ColSide CheckColSide(Rect a, Rect b, double speed)
{
    ColSide colInfo;

    if(a.x + a.w <= b.x + speed) colInfo = LEFT;
    if(b.x + b.w <= a.x + speed) colInfo = RIGHT;
    if(a.y + a.h <= b.y + speed) colInfo = UP;
    if(b.y + b.h <= a.y + speed) colInfo = DOWN;

    return colInfo;
}

int KeyRel(int k)
{
    static int initialized = 0;
    static int keyp[KEY_MAX];

    if(!initialized)
    {
        int i;
        for(i = 0; i < KEY_MAX; i++) keyp[i] = 0;
        initialized = 1;
    }
    if(key[k] && !keyp[k])
    {
        keyp[k] = 1;
        return 0;
    }
    else if(!key[k] && keyp[k])
    {
        keyp[k] = 0;
        return 1;
    }

    return 0;
}

int Clamp(int minn, int n,int maxn)
{
    n = n>maxn ? maxn : n;
    return n<minn ? minn : n;
}
