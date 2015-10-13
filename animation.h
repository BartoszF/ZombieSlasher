#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <allegro.h>

typedef struct
{
    int rowsNum;
    int* rows;
    int row;
    int frame;
    int loopPerFrame;
    int loopPerAttFrame;
    int timer;
    BITMAP* bitmap;
}Animation;

void InitAnimation(Animation* a,char* file,int add);
void SetRow(Animation* a,int row);
void NextFrame(Animation* a);
void NextAttFrame(Animation* a);
void FreeAnimation(Animation* a);
#endif // ANIMATION_H_INCLUDED
