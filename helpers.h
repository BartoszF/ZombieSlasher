#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <stdbool.h>

typedef struct Struct_Rect
{
    double x,y,w,h;
} Rect;

typedef struct Struct_Point
{
    double x,y;
} Point;

typedef enum
{
    NONE = 0,
    LEFT = (1 << 0),
    RIGHT = (1 << 1),
    UP = (1 << 2),
    DOWN = (1 << 3)
}ColSide;

bool ABB(Point a,Rect b);
bool AABB(Rect a,Rect b);
ColSide CheckColSide(Rect a, Rect b, double speed);
int KeyRel(int k);
int Clamp(int minn, int n, int maxn);

#endif // HELPERS_H_INCLUDED
