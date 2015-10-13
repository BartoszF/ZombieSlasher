#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include "helpers.h"
#include "animation.h"
#include <allegro.h>

typedef struct hero
{
    Rect position;
    double hp;
    double maxHp;
    int level;
    int xp;
    double damage;
    double speed;
    ColSide col;
    int dir;
    int attacking;
    Animation* a;
} Hero;

Hero player;
Animation* lvlUp;
Point UpPos;
int UpTimer;
char* heroFile;
int test;
int inited;

int levelUp;

Rect hit;

void AddXp(int xp);

void AttackHero(double damage);
void LoadHero(char * file);
void UpdateHero(Hero h);
void DrawHero(Hero h);
void FreeHero(Hero h);

#endif // HERO_H_INCLUDED
