#include "loop.h"
#include <allegro.h>
#include <stdio.h>
#include "helpers.h"
#include "config.h"
#include "level.h"
#include "hero.h"
#include "zombie.h"
#include "States/options.h"
#include "GameManager.h"

void Start()
{
    Log("ZombieSlasher v. 0.9\nLogger is working...\n");
    Log("Loading config file...\n");
    LoadConfig("config.cfg");
    allegro_init();

    install_timer();
    install_int_ex(IncSpeed, BPS_TO_TIMER(120));

    install_keyboard();
    install_mouse();

    show_mouse(buffer);
    unscare_mouse();

    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,"");
    set_volume(200,200);

    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,Resolution.x,Resolution.y,0,0) != 0)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        char error[80];
        char licz[16];
        strcpy(error,"Nie moge przelaczyc trybu graficznego!\n");
        itoa((int)Resolution.x,licz,10);
        strcat(error,licz);
        itoa((int)Resolution.y,licz,10);
        strcat(error,licz);
        Log(error);
        Log("\n");
        allegro_message(error);
        Quit();
    }

    set_palette(default_palette);

    Log("Init options\n");
    InitOptions();

    Log("\nLoading files...\n");
    LoadFiles();

    Log("GameManager initialization...\n");
    InitGameManager();

    Running = true;
}

void InitGame()
{
    Log("Loading level...\n");
    LoadLevel("Data/Bitmaps/level.bmp");
    Log("Loading hero : ");
    LoadHero("Data/Animations/player.ani");
    Log("ZombieManager initialization...\n");
    InitZombieManager(512,"Data/Animations/zombie.ani");

    Scores = false;

    camera.x = 0;camera.y=0;camera.w=Resolution.x;camera.h=Resolution.y;

    name = malloc(16*sizeof(char));
    nameI = 0;

    GameInit = true;
}

int Loop()
{
    while(Running)
    {
        while(speed > 0)
        {
            UpdateGameManager();
            DrawGameManager();
            speed--;
        }
    }
    return 0;
}

void Quit()
{
    Running = false;

    FreeFiles();
    if(GameInit)
    {
        Log("\nFreeing level...\n");
        FreeLevel();
        Log("Disabling and freeing ZombieManager...\n");
        FreeZombieManager();

        FreeHero(player);
    }

    remove_int(IncSpeed);

    Log("Exitting allegro...\n");
    allegro_exit();

    fclose(logFile);
}

void Update()
{
    if(GameInit)
    {
        if(Running)
        {
            if(!Paused && player.hp > 0)
            {
                if(KeyRel(KEY_ESC)) Pause();

                UpdateHero(player);
                UpdateZombieManager();
                UpdateZombies();
            }
            else if(player.hp <= 0)
            {
                if(!Scores)
                {
                    int v = readkey();
                    if(((v & 0xff)>= 'a') && ((v & 0xff)<= 'z') && nameI < 31)
                    {
                        name[nameI++] = toupper(v & 0xff);
                    }
                    if((v >> 8) == KEY_BACKSPACE)
                    {
                        name[--nameI] = ' ';
                        if(nameI < 0) nameI = 0;
                    }
                    if((v >> 8) == KEY_ENTER)
                    {
                        Scores = true;
                    }
                }
                else
                {
                    if(!LoadedScores) LoadScores();

                    if(KeyRel(KEY_Q)) Quit();
                }
            }
            else
            {
                if(KeyRel(KEY_ESC)) UnPause();
                if(KeyRel(KEY_Q)) Quit();
            }
        }
    }
    else
    {
        InitGame();
    }
}

void Draw()
{
    if(Running)
    {
        if(!Paused) clear_to_color(buffer, makecol(200,180,200));

        DrawLevel();
        DrawZombies();
        DrawHero(player);

        if(Paused)
        {
            textout_ex(buffer,font,"PAUSED",Resolution.x/2 - 45,Resolution.y/2 - 10,makecol(0,0,0),-1);
            textout_ex(buffer,font,"Press Q to quit",Resolution.x/2 - 80,Resolution.y/2 + 10,makecol(0,0,0),-1);
        }
        else if(player.hp <= 0 && !Scores)
        {
            textout_ex(buffer,font, "NAME : ",Resolution.x/2 - 60, Resolution.y/2 - 10, makecol(20,20,20),-1);
            textout_ex(buffer,font, name, Resolution.x/2 - 20, Resolution.y/2 - 10,makecol(180,180,180),-1);
        }
        else if(Scores && LoadedScores)
        {
            for(int i=0; i<10;i++)
            {
                textout_ex(buffer,font, scores[i], Resolution.x/2 - 60, 100 + (20*i),makecol(255,60,65),-1);
            }

            textout_ex(buffer, font, "Press Q to quit", Resolution.x / 2 - 65, 100 + 300, makecol(255,255,255), -1);
        }

        blit(buffer,screen,camera.x,camera.y,0,0,camera.w,camera.h);
    }
}

void Pause()
{
    Paused= true;
}

void UnPause()
{
    Paused = false;
}

void LoadScores()
{
    Log("Loading scores\n");
    int msc = player.xp;
    bool added = false;
    FILE *f = fopen("Data/scores.txt","r");
    if(f)
    {
        scores = malloc(10 * sizeof(char*));
        for(int i =0; i<10;i++)
        {
            scores[i] = malloc(128 * sizeof(char));
        }

        for(int i =0; i<10;i++)
        {
            if(fgets(scores[i],127,f) != NULL)
            {
                char *pos;
                if ((pos=strchr(scores[i], '\n')) != NULL)
                *pos = '\0';

                char *token;
                char *line = malloc(128*sizeof(char));
                strcpy(line,scores[i]);
                char *search = " ";

                token = strtok(line, search);
                token = strtok(NULL, search);

                int sc = atoi(token);

                if(msc >= sc && !added && msc != 0)
                {
                    strcat(name, " ");
                    char* temp = malloc(100 * sizeof(char));
                    strcat(name, itoa(msc,temp,10));
                    scores[i+1] = scores[i];
                    scores[i] = name;
                    added = true;
                    i++;
                }

                Log(scores[i]);
            }
            else
            {
                strcat(name, " ");
                char* temp = malloc(100 * sizeof(char));
                strcat(name, itoa(msc,temp,10));
                scores[i] = name;
                break;
            }
        }
        fclose(f);
    }

    f = fopen("Data/scores.txt","w");
    if(f)
    {
        for(int i=0;i<10;i++)
        {
            fputs(scores[i],f);
            fputs("\n",f);
        }

        fclose(f);
    }

    LoadedScores = true;
}

void IncSpeed()
{
    speed++;
}END_OF_FUNCTION(IncSpeed);

LOCK_VARIABLE(speed);
LOCK_FUNCTION(increment_speed);
