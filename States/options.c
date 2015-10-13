#include "options.h"
#include <math.h>
#include <stdio.h>
#include "../tinydir.h"
#include "../loop.h"
#include "../GameManager.h"
#include "../config.h"
#include "../list.h"

void InitOptions()
{
    backButt.x = Resolution.x/2 - 64; backButt.y = Resolution.y - 128; backButt.w = 128; backButt.h = 64;
    fxMinus.x = Resolution.x/2 - 128-33;fxMinus.y = Resolution.y/2 - 128;fxMinus.w = 32;fxMinus.h = 32;
    fxPlus.x = Resolution.x/2 + 128;fxPlus.y = Resolution.y/2 - 128;fxPlus.w = 32;fxPlus.h = 32;
    musMinus.x = Resolution.x/2 - 128-33;musMinus.y = Resolution.y/2 - 64;musMinus.w = 32;musMinus.h = 32;
    musPlus.x = Resolution.x/2 + 128;musPlus.y = Resolution.y/2 - 64;musPlus.w = 32;musPlus.h = 32;
    zombiePrev.x = Resolution.x/2 - 128-33;zombiePrev.y = Resolution.y/2+24;zombiePrev.w = 32;zombiePrev.h = 32;
    zombieNext.x = Resolution.x/2 + 128;zombieNext.y = Resolution.y/2+24;zombieNext.w = 32;zombieNext.h = 32;
    heroPrev.x = Resolution.x/2 - 128-33;heroPrev.y = Resolution.y/2 + 88;heroPrev.w = 32;heroPrev.h = 32;
    heroNext.x = Resolution.x/2 + 128;heroNext.y = Resolution.y/2 + 88;heroNext.w = 32;heroNext.h = 32;

    fxAm.x = Resolution.x/2 - 128;fxAm.y = Resolution.y/2 - 128+2; fxAm.w = fxVol; fxAm.h = 24;
    musAm.x = Resolution.x/2 - 128;musAm.y = Resolution.y/2 - 64+2; musAm.w = musicVol; musAm.h = 24;
    zombiePath.x = Resolution.x/2 - 100;zombiePath.y = Resolution.y/2+38;
    heroPath.x = Resolution.x/2 - 100;heroPath.y = Resolution.y/2 + 100;
    zombieErr.x = Resolution.x/2 - 256;zombieErr.y = Resolution.y - 256;
    heroErr.x = Resolution.x/2 - 256;heroErr.y = Resolution.y - 248;

    tinydir_dir heroDir,zombieDir;

    heroesF = NULL;

    if(tinydir_open(&heroDir,"Data/Hero/") == -1)
    {
        Log("Can't browse Hero\n");
        goto bailhero;
    }

    while(heroDir.has_next)
    {
        tinydir_file file;
        if (tinydir_readfile(&heroDir, &file) == -1)
        {
                Log("Error getting file\n");
                goto bailhero;
        }

        if(!file.is_dir)
        {
            char* temp;
            temp = malloc(strlen(file.name)*sizeof(char));
            strcpy(temp,file.name);
            Log("Found hero : "); Log(temp); Log("\n");
            AddToList(&heroesF,NULL,temp);
        }

        tinydir_next(&heroDir);
    }
    bailhero:
    tinydir_close(&heroDir);

    if(tinydir_open(&zombieDir,"Data/Zombie/") == -1)
    {
        Log("Can't browse Zombie\n");
        goto bailzombie;
    }

    while(zombieDir.has_next)
    {
        tinydir_file file;
        if (tinydir_readfile(&zombieDir, &file) == -1)
        {
                Log("Error getting file\n");
                goto bailzombie;
        }

        if(!file.is_dir)
        {
            char* temp;
            temp = malloc(strlen(file.name)*sizeof(char));
            strcpy(temp,file.name);
            Log("Found zombie : "); Log(temp); Log("\n");
            AddToList(&zombiesF,NULL,temp);
        }

        tinydir_next(&zombieDir);
    }
    bailzombie:
    tinydir_close(&zombieDir);

    HeroF = heroesF;
    ZombieF = zombiesF;

    hFile = HeroF->str;
    zFile = ZombieF->str;
            //SaveConfig("config.cfg");

    optionsInit = true;
}

void UpdateOptions()
{
    if(optionsInit)
    {
        mouse.x = mouse_x;mouse.y = mouse_y;
        mouseBPrev = mouseB;
        mouseB = mouse_b;

        if(ABB(mouse,backButt) && mouseB == 1)
        {
            hFile = HeroF->str;
            zFile = ZombieF->str;
            SaveConfig("config.cfg");

            GameState = MAINMENU;
        }
        if(ABB(mouse,fxPlus) && mouseB == 1)
        {
            fxVol = Clamp(0,fxVol+1,255);
            fxAm.w = fxVol;
        }
        if(ABB(mouse,fxMinus) && mouseB == 1)
        {
            fxVol = Clamp(0,fxVol-1,255);
            fxAm.w = fxVol;
        }
        if(ABB(mouse,musPlus) && mouseB == 1)
        {
            musicVol = Clamp(0,musicVol+1,255);
            adjust_sample(bgMusic,musicVol,127,1000,1);
            musAm.w = musicVol;
        }
        if(ABB(mouse,musMinus) && mouseB == 1)
        {
            musicVol = Clamp(0,musicVol-1,255);
            adjust_sample(bgMusic,musicVol,127,1000,1);
            musAm.w = musicVol;
        }

        if(ABB(mouse,zombieNext) && mouseB == 0 && mouseBPrev == 1)
        {
            if(ZombieF->next) ZombieF = ZombieF->next;
        }
        if(ABB(mouse,zombiePrev) && mouseB == 0 && mouseBPrev == 1)
        {
            if(ZombieF->prev) ZombieF = ZombieF->prev;
        }
        if(ABB(mouse,heroNext) && mouseB == 0 && mouseBPrev == 1)
        {
            if(HeroF->next) HeroF = HeroF->next;
        }
        if(ABB(mouse,heroPrev) && mouseB == 0 && mouseBPrev == 1)
        {
            if(HeroF->prev) HeroF = HeroF->prev;
        }
    }
    else
    {
        InitOptions();
    }
}

void DrawOptions()
{
    if(Running)
    {
        clear_to_color(buffer,makecol(200,180,200));

        masked_blit(button,buffer,0,0,backButt.x,backButt.y,backButt.w,backButt.h);
        textout_ex(buffer,font,"BACK",backButt.x+48,backButt.y+28,makecol(0,0,0),-1);
        masked_blit(button,buffer,0,0,fxPlus.x,fxPlus.y,fxPlus.w,fxPlus.h);
        textout_ex(buffer,font,"+",fxPlus.x+fxPlus.w/2-4,fxPlus.y+fxPlus.h/2-4,makecol(0,0,0),-1);
        masked_blit(button,buffer,0,0,fxMinus.x,fxMinus.y,fxMinus.w,fxMinus.h);
        textout_ex(buffer,font,"-",fxMinus.x+fxMinus.w/2-4,fxMinus.y+fxMinus.h/2-4,makecol(0,0,0),-1);
        masked_blit(button,buffer,0,0,musPlus.x,musPlus.y,musPlus.w,musPlus.h);
        textout_ex(buffer,font,"+",musPlus.x+musPlus.w/2-4,musPlus.y+musPlus.h/2-4,makecol(0,0,0),-1);
        masked_blit(button,buffer,0,0,musMinus.x,musMinus.y,musMinus.w,musMinus.h);
        textout_ex(buffer,font,"-",musMinus.x+musMinus.w/2-4,musMinus.y+musMinus.h/2-4,makecol(0,0,0),-1);
        masked_blit(button,buffer,0,0,zombieNext.x,zombieNext.y,zombieNext.w,zombieNext.h);
        textout_ex(buffer,font,">",zombieNext.x+zombieNext.w/2-4,zombieNext.y+zombieNext.h/2-4,makecol(0,0,0),-1);
        masked_blit(button,buffer,0,0,zombiePrev.x,zombiePrev.y,zombiePrev.w,zombiePrev.h);
        textout_ex(buffer,font,"<",zombiePrev.x+zombiePrev.w/2-4,zombiePrev.y+zombiePrev.h/2-4,makecol(0,0,0),-1);
        masked_blit(button,buffer,0,0,heroNext.x,heroNext.y,heroNext.w,heroNext.h);
        textout_ex(buffer,font,">",heroNext.x+heroNext.w/2-4,heroNext.y+heroNext.h/2-4,makecol(0,0,0),-1);
        masked_blit(button,buffer,0,0,heroPrev.x,heroPrev.y,heroPrev.w,heroPrev.h);
        textout_ex(buffer,font,"<",heroPrev.x+heroPrev.w/2-4,heroPrev.y+heroPrev.h/2-4,makecol(0,0,0),-1);

        masked_stretch_blit(button,buffer,0,0,128,64,fxAm.x,fxAm.y,fxAm.w,fxAm.h);
        masked_stretch_blit(button,buffer,0,0,128,64,musAm.x,musAm.y,musAm.w,musAm.h);

        char tx[512] = "FX VOLUME : ";
        char temp[10];
        strcat(tx,itoa(fxVol,temp,10));
        textout_ex(buffer,font,tx,fxAm.x + 10,fxAm.y+10,makecol(255,220,255),-1);
        strcpy(tx,"MUSIC VOLUME : ");
        strcpy(temp,"");
        strcat(tx,itoa(musicVol,temp,10));
        textout_ex(buffer,font,tx,musAm.x + 10,musAm.y+10,makecol(255,220,255),-1);

        textout_ex(buffer,font,HeroF->str,heroPath.x,heroPath.y,makecol(10,20,10),-1);
        textout_ex(buffer,font,ZombieF->str,zombiePath.x,zombiePath.y,makecol(10,20,10),-1);

        masked_blit(mouseSprite,buffer,0,0,mouse.x,mouse.y,32,32);

        blit(buffer,screen,0,0,0,0,Resolution.x,Resolution.y);
    }
}
