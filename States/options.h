#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

#include "../helpers.h"
#include "../list.h"

Rect backButt;
Rect fxPlus;
Rect fxMinus;
Rect musPlus;
Rect musMinus;
Rect zombieNext;
Rect zombiePrev;
Rect heroNext;
Rect heroPrev;

Rect fxAm;
Rect musAm;
Point zombiePath;
Point heroPath;
Point zombieErr;
Point heroErr;

List* heroesF;
List* zombiesF;

List* HeroF;
List* ZombieF;

int mouseB;
int mouseBPrev;

void InitOptions();
void UpdateOptions();
void DrawOptions();

bool optionsInit;

#endif // OPTIONS_H_INCLUDED
