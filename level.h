#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <allegro.h>
#include "helpers.h"
#include "config.h"


Rect levelSize;
Rect *walls;
int wallsNum;
Rect camera;
BITMAP *level;
BITMAP *wall;

void MoveCamera(Point p);
void SetCamera(Rect r);
void SetLevelSize(Rect s);
void LoadLevel(char* file);
void FreeLevel();
void DrawLevel();


#endif // LEVEL_H_INCLUDED
