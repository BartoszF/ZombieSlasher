#include "hero.h"
#include "level.h"
#include <allegro.h>
#include "animation.h"
#include "zombie.h"
#include "config.h"

void LoadHero(char * file)
{
    inited = 0;
    player.position.x = Resolution.x/2-1;
    player.position.y = Resolution.y/2-1;
    player.position.w = 32;
    player.position.h = 32;
    player.level = 1;
    player.xp = 0;
    player.damage = 2;
    player.hp = 25;
    player.maxHp = player.hp;
    player.speed = 1;
    player.dir = 3;
    heroFile = malloc(1023 * sizeof(char));
    player.a = malloc(sizeof(Animation));
    lvlUp = malloc(sizeof(Animation));
    strcpy(heroFile,"Data/Hero/");
    strcat(heroFile,hFile);
    FILE* f = fopen(heroFile,"r");
    char c[1023];
    if(fgets(c,1023,f))
    {
        strcpy(heroFile,"");
        strcpy(heroFile,"Data/Animations/");
        strcat(heroFile,c);
        int l = strlen(heroFile);
        if(heroFile[l-1] == '\n') heroFile[l-1] = '\0';
        Log(heroFile);Log("\n");
    }
    else
    {
        strcpy(heroFile,"");
        Log("Can't open hero file\n");
        strcpy(heroFile,file);
    }

    Log("\nLoading player animation\n");
    InitAnimation(player.a,heroFile,1);
    InitAnimation(lvlUp,"Data/Animations/levelUp.ani",1);

    inited = 1;
}

void AddXP(int xp)
{
    player.xp += xp;

    if(player.xp > player.level*250)
    {
        if(player.level%2 == 0)
        {
            player.damage += 0.05f;
            player.speed += 0.07f;
            player.hp = 25 + (player.level*2);
            player.maxHp = player.hp;
        }
        xp -= player.level*100;
        player.level++;
        levelUp=1;
        UpTimer = 200;
        UpPos.x = player.position.x-5;
        UpPos.y = player.position.y;
    }
}

void UpdateHero(Hero h)
{
    if(levelUp)
    {
        if(lvlUp->frame < lvlUp->rows[lvlUp->row]-1)
        {
            NextFrame(lvlUp);
        }
        else
        {
            levelUp=0;
        }
    }

    if(UpTimer)
    {
        UpTimer--;
        UpPos.x = player.position.x-5;
        UpPos.y -= 0.05f + (UpTimer) * 0.001f;
    }

    if(player.attacking == 0)
    {
        if(KeyRel(KEY_LEFT) || KeyRel(KEY_RIGHT) || KeyRel(KEY_UP) || KeyRel(KEY_DOWN)) return;
        player.col = NONE;
        test = 0;
        for(int i = 0;i<wallsNum;i++)
        {
            if(AABB(player.position,walls[i]))
            {
                test = 1;
                player.col |= CheckColSide(walls[i],player.position,player.speed);
            }
        }

        if(key[KEY_LEFT] && player.col != LEFT)
        {
            if(player.a->row != 4+player.dir)
            {
                SetRow(player.a,4+player.dir);
                player.dir = 2;
            }
            else
            {
                NextFrame(player.a);
            }

            player.position.x -= player.speed;
        }
        else if(key[KEY_RIGHT] && player.col != RIGHT)
        {
            if(player.a->row != 4+player.dir)
            {
                SetRow(player.a,4+player.dir);
                player.dir = 0;
            }
            else
            {
                NextFrame(player.a);
            }

            player.position.x += player.speed;
        }
        else if(key[KEY_UP] && player.col != UP)
        {
            if(player.a->row != 4+player.dir)
            {
                SetRow(player.a,4+player.dir);
                player.dir = 1;
            }
            else
            {
                NextFrame(player.a);
            }

            player.position.y -= player.speed;
        }
        else if(key[KEY_DOWN] && player.col != DOWN)
        {
            if(player.a->row != 4+player.dir)
            {
                SetRow(player.a,4+player.dir);
                player.dir = 3;
            }
            else
            {
                NextFrame(player.a);
            }

            player.position.y += player.speed;
        }
        else
        {
            if(player.a->row != player.dir)
            {
                SetRow(player.a,player.dir);
            }
            else
            {
                NextFrame(player.a);
            }
        }

        if(KeyRel(KEY_SPACE))
        {
            player.attacking = 1;
        }
    }
    else
    {
        if(player.a->row != 8+player.dir)
        {
            SetRow(player.a,8+player.dir);
        }
        else
        {
            if(player.a->frame == 1)
            {
                Point hDir;

                switch(player.dir)
                {
                case 0:
                    hit.x = player.position.x + player.position.w;
                    hit.y = player.position.y;
                    hDir.x = 1;
                    hDir.y = 0;
                    break;
                case 1:
                    hit.x = player.position.x;
                    hit.y = player.position.y - player.position.h;
                    hDir.x = 0;
                    hDir.y = -1;
                    break;
                case 2:
                    hit.x = player.position.x - player.position.w;
                    hit.y = player.position.y;
                    hDir.x = -1;
                    hDir.y = 0;
                    break;
                case 3:
                    hit.x = player.position.x;
                    hit.y = player.position.y + player.position.h;
                    hDir.x = 0;
                    hDir.y = 1;
                    break;
                }

                hit.w = player.position.w;
                hit.h = player.position.h;

                play_sample(swordSlash,fxVol,(player.position.x/Resolution.x)*255,1000,0);

                Zombie** z = &zombies;

                while((*z)!= NULL )
                {
                    if((*z)->hp >= 0 && AABB(hit,(*z)->position))
                    {
                        HitZombie(z,player.damage);
                        if(z!=NULL && (*z)!= NULL && (*z)->next != NULL)
                        {
                            (*z)->position.x += hDir.x * player.damage*2;
                            (*z)->position.y += hDir.x * player.damage*2;
                        }

                    }

                    if((*z) != NULL && (*z)->next != NULL) z = &(*z)->next;
                    else
                    {
                        break;
                    }
                }
            }

            if(player.a->frame < player.a->rows[player.a->row]-1)
            {
                NextAttFrame(player.a);
            }
            else
            {
                player.attacking = 0;
            }
        }
    }
}

void DrawHero(Hero h)
{
    if(inited)
    {
        if(levelUp) masked_blit(lvlUp->bitmap,buffer,(lvlUp->frame*player.position.w)+lvlUp->frame+1,(lvlUp->row*player.position.h)+lvlUp->row+1,player.position.x,player.position.y+8,player.position.w,player.position.h);
        masked_blit(player.a->bitmap,buffer,(player.a->frame*player.position.w)+player.a->frame+1,(player.a->row*player.position.h)+player.a->row+1,player.position.x,player.position.y,player.position.w,player.position.h);
        int percent = (player.maxHp > 0) ? (int)(48 * (player.hp / player.maxHp)) : 0;
        masked_stretch_blit(hpBar,buffer,0,0,32,32,player.position.x-9,player.position.y - 9, percent , 6);
        if(UpTimer) textout_ex(buffer,font,"LEVEL UP",UpPos.x,UpPos.y,makecol(0,0,0),-1);

        if(player.hp > 0 && player.maxHp > 0)
        {
            char *t = malloc(32 * sizeof(char));
            itoa((int)player.hp,t,10);
            textout_ex(buffer,font,t,player.position.x,player.position.y+35,makecol(0,0,0),-1);
        }
    }
}

void AttackHero(double damage)
{
    player.hp -= damage;
}

void FreeHero(Hero h)
{
    FreeAnimation(h.a);
}
