#include "zombie.h"
#include "hero.h"
#include "config.h"
#include <math.h>
#include "level.h"
#include <stdlib.h>

void InitZombieManager(int i, char * file)
{
    zombies = 0;
    archetype = malloc(sizeof(Animation));
    Log("Init zombie archetype animation\n");
    InitAnimation(archetype,file,1);
    animFile = file;

    maxZombie = i;
    maxZombieAtWave = 12;
    wave = 0;
    addedZombie = 0;
    framesBetween = 20;

    spawns[0].x = 8;                spawns[0].y = Resolution.y/2;
    spawns[1].x = Resolution.x /2;  spawns[1].y = 8;
    spawns[2].x = Resolution.x-8;     spawns[2].y = Resolution.y/2;
    spawns[3].x = Resolution.x/2;   spawns[3].y = Resolution.y-8;
}

void FreeZombieManager()
{
    FreeAnimation(archetype);
    free(zombies);
}

void AddZombie(Zombie** z, Rect pos,double damage,double speed,int hp, int level)
{
    if((*z) == NULL)
    {
        (*z) = (Zombie*)calloc(1,sizeof(Zombie));
        (*z)->position = pos;
        (*z)->level = level;
        (*z)->speed = speed;
        (*z)->hp = hp;
        (*z)->maxhp = hp;
        (*z)->damage = damage;
        (*z)->dir = 3;
        (*z)->col = NONE;
        (*z)->escapeTime = 0;
        (*z)->anim = malloc(sizeof(Animation));
        (*z)->anim->loopPerAttFrame = archetype->loopPerAttFrame;
        (*z)->anim->loopPerFrame = archetype->loopPerFrame;
        (*z)->anim->rows = archetype->rows;
        (*z)->anim->rowsNum = archetype->rowsNum;

        (*z)->next = NULL;

        zombieCount++;
        zombieAlive++;
    }
    else
    {
        AddZombie(&(*z)->next,pos,damage,speed,hp,level);
    }
}

void HitZombie(Zombie** a, int damage)
{
    (*a)->hp -= damage;
    play_sample(zombieHit,fxVol-10,((*a)->position.x/Resolution.x)*255,1000,0);
    if((*a)->hp <= 0)
    {
        play_sample(zombieDead,fxVol+10,((*a)->position.x/Resolution.x)*255,1000,0);
        KillZombie(&(*a), 1);
    }
}

void KillZombie(Zombie** z, int x)
{
    Zombie** temp;

    for(temp = &zombies; *temp != NULL; temp = &(*temp)->next)
    {
		if(*temp == *z)
        {
            if(x)
            {
                int xp = Clamp(10,((*temp)->level * 10) - (*temp)->escapeTime,INT_MAX);
                AddXP(xp);
            }

            if((*temp)->next == NULL)
            {
                *temp = NULL;
            }
            else
            {
                (*temp) = (*temp)->next;
            }
             --zombieAlive;
            break;
        }
    }
}

void UpdateZombies()
{
    Zombie** z = &zombies;
    while((*z) != NULL)
    {
        if((*z)->hp > 0)
        {
            (*z)->col = NONE;

            if(!timer)
            {
                random = rand() % 100;
                if(random > 85)
                    play_sample(zombieMoan,fxVol-40 + rand() % 50,((*z)->position.x/Resolution.x)*255,985+rand()%150,0);
                    timer = 350;
            }
            else
            {
                timer--;
            }

            if(!AABB((*z)->position,levelSize))
            {
                KillZombie(&(*z), 0);
                z = &(*z)->next;
                continue;
            }

            if(!AABB((*z)->position,player.position) || (*z)->hp < (*z)->maxhp * 0.25f)
            {
                for(int i = 0; i<wallsNum; i++)
                {
                    if(AABB((*z)->position,walls[i]))
                    {
                        (*z)->col |= CheckColSide(walls[i],(*z)->position,(*z)->speed);
                    }
                }

                float dx, dy;
                if((*z)->hp > (*z)->maxhp * 0.25f)
                {
                    dx = player.position.x - (*z)->position.x;
                    dy = player.position.y - (*z)->position.y;
                    (*z)->escapeTime++;
                }
                else
                {
                    dx = (*z)->position.x - player.position.x;
                    dy = (*z)->position.y - player.position.y;
                }

                int sx,sy;

                if (dx != 0) sx = dx / fabs(dx);
                else sx = 0;

                if (dy != 0) sy = dy / fabs(dy);
                else sy = 0;

                dx = fabs(dx);
                dy = fabs(dy);

                if(dx > dy)
                {
                    float a = dy/dx;

                    dy = a;
                    dx = 1-a;

                    if(sx > 0) (*z)->dir = 0;
                        else (*z)->dir = 2;
                }
                else if (dy > dx)
                {
                    float a = dx/dy;
                    dx = a;
                    dy = 1-a;

                    if(sy > 0) (*z)->dir = 3;
                        else (*z)->dir = 1;
                }
                else
                {
                    dx = 0.5f;
                    dy = 0.5f;

                    if(sx > 0) (*z)->dir = 0;
                        else (*z)->dir = 2;
                }

                if((*z)->anim->row != 4+(*z)->dir)
                {
                    SetRow((*z)->anim,4+(*z)->dir);
                }
                else
                {
                    NextFrame((*z)->anim);
                }

                if(!((sx > 0 && (*z)->col != RIGHT) || (sx < 0 && (*z)->col != LEFT)))
                {
                    dy += dx;
                    dx = 0;
                }

                if(!((sy > 0 && (*z)->col != DOWN) || (sy < 0 && (*z)->col != UP)))
                {
                    dx += dy;
                    dy = 0;
                }

                (*z)->position.x += (dx * (*z)->speed) * sx;
                (*z)->position.y += (dy * (*z)->speed) * sy;
            }
            else
            {
                if((*z)->anim->row != 8+(*z)->dir)
                {
                    SetRow((*z)->anim,8+(*z)->dir);
                }
                else
                {
                    if((*z)->anim->frame == (*z)->anim->rows[8+(*z)->dir]-1)
                    {
                        AttackHero((*z)->damage);
                    }

                    NextAttFrame((*z)->anim);
                }
            }
        }
        else
        {
            return;
        }
        z = &(*z)->next;
    }

}

void DrawZombies()
{
    Zombie** z = &zombies;
    while((*z) != NULL)
    {
        if((*z)->hp > 0)
        {
            masked_blit(archetype->bitmap,buffer,((*z)->anim->frame*(*z)->position.w)+(*z)->anim->frame+1,((*z)->anim->row*(*z)->position.h)+(*z)->anim->row+1,(*z)->position.x,(*z)->position.y,(*z)->position.w,(*z)->position.h);
            //char h[32];
            //itoa((*z)->hp,h,10);
            //textout_ex(buffer,font,h,(*z)->position.x,(*z)->position.y-3,makecol(0,0,0),-1);
        }

        z = &(*z)->next;
    }
}

void UpdateZombieManager()
{
    if(prepareWave || zombieAlive <= 4)
    {
        if(!prepareWave)
        {
            addedZombie = 0;
            prepareWave = 1;
            wave++;
            if(wave%2 == 0)
            {
                maxZombieAtWave += 4;
            }
            if(wave%4 == 0)
            {
                gLevel++;
            }
            if(player.level%3 == 0)
            {
                maxZombieAtWave += 4;
            }

        }
        else if(addedZombie >= maxZombieAtWave)
        {
            prepareWave = 0;
            return;
        }
        else if(framesBetween == 0)
        {
            Rect z;
            for(int i = 0;i<4;i++)
            {
                if(zombieAlive <= maxZombieAtWave)
                {
                    z.x = spawns[i].x;  z.y = spawns[i].y;
                    z.w = 32;           z.h = 32;

                    double sp = 0.2 + (player.level/4)*0.1;
                    double dmg = 0.1 + (player.level/4)*0.15;
                    int h = 5 + (player.level/2);

                    AddZombie(&zombies,z,dmg,sp,h,gLevel);
                    addedZombie++;
                }
            }
            framesBetween = 120;
        }
        else
        {
            framesBetween--;
        }
    }
}
