#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

#include "helpers.h"
#include "animation.h"
#include <allegro.h>

typedef struct StructZombie
{
    Rect position;
    double damage;
    int level;
    double speed;
    int hp;
    int maxhp;
    int escapeTime;
    ColSide col;
    int animRow;
    int animFrame;
    int dir;
    Animation* anim;
    struct StructZombie* next;
} Zombie;

Zombie* zombies;
Animation* archetype;
Point spawns[4];
char* animFile;
int zombieCount;
int zombieAlive;
int prepareWave;
int addedZombie;
int maxZombie;
int maxZombieAtWave;
int wave;
int gLevel;
int framesBetween;

int random;
int played;
int timer;

void InitZombieManager(int i, char * file);
void FreeZombieManager();
void AddZombie(Zombie** z, Rect pos,double damage,double speed,int hp, int level);
void KillZombie(Zombie** z, int x);
void HitZombie(Zombie** a, int damage);
void ClearZombies();
void UpdateZombies();
void DrawZombies();
void UpdateZombieManager();


#endif // ZOMBIE_H_INCLUDED
