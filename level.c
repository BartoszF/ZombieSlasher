#include "level.h"
#include "loop.h"
#include "config.h"
#include "zombie.h"

void SetLevelSize(Rect s)
{
    levelSize = s;
}

void LoadLevel(char* file)
{
    level = load_bmp(file,default_palette);
    if(!level)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac poziomu !");
        Quit();
    }

    wall = load_bmp("Data/Bitmaps/Wall.bmp",default_palette);
    if(!wall)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac sciany!");
        Quit();
    }

    Rect s; s.x = 0;s.y=0;s.w=1024;s.h=768;
    SetLevelSize(s);

    wallsNum = 8;
    walls = malloc(wallsNum * sizeof(Rect));

    walls[0].x = 0;                     walls[0].y = 0;                 walls[0].w = 32;                walls[0].h = Resolution.y/2-14;
    walls[1].x = 0;                     walls[1].y = 0;                 walls[1].w = Resolution.x/2-14; walls[1].h = 32;
    walls[2].x = Resolution.x/2+38;     walls[2].y = 0;                 walls[2].w = Resolution.x/2+14; walls[2].h = 32;
    walls[3].x = Resolution.x - 32;     walls[3].y = 0;                 walls[3].w = 32;                walls[3].h = Resolution.y/2 - 14;
    walls[4].x = Resolution.x - 32;     walls[4].y = Resolution.y/2+38; walls[4].w = 32;                walls[4].h = Resolution.y/2 - 14;
    walls[5].x = Resolution.x/2+38;     walls[5].y = Resolution.y-32;   walls[5].w = Resolution.x/2+14; walls[5].h = 32;
    walls[6].x = 0;                     walls[6].y = Resolution.y-32;   walls[6].w = Resolution.x/2-14; walls[6].h = 32;
    walls[7].x = 0;                     walls[7].y = Resolution.y/2+38; walls[7].w = 32;                walls[7].h = Resolution.x/2+14;
}

void FreeLevel()
{
    destroy_bitmap(level);
    destroy_bitmap(wall);
}

void DrawLevel()
{
    if(level)
    {
        blit(level,buffer,0,0,0,0,levelSize.w,levelSize.h);
    }
    if(wall)
    {
        for(int i =0;i<wallsNum;i++)
        {
            masked_stretch_blit(wall,buffer,0,0,32,32,walls[i].x,walls[i].y,walls[i].w,walls[i].h);
        }
    }
}
