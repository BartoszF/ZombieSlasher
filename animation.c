#include "animation.h"
#include "config.h"
#include <allegro.h>

void InitAnimation(Animation* a,char* file,int add)
{
    FILE* f = fopen(file,"r");

    if(f)
    {
        Log("Animation file opened...\n");
        char* line = malloc(1023 * sizeof(char));
        if(fgets(line,1023,f)!=NULL)
        {
            char *pos;
            if ((pos=strchr(line, '\n')) != NULL)
            *pos = '\0';

            if(add > 0)
            {
                Log("Adding bitmap "); Log(line); Log("\n");
                a->bitmap = load_bitmap(line,default_palette);
                if (!a->bitmap)
                {
                    set_gfx_mode(GFX_TEXT,0,0,0,0);
                    allegro_message("Nie moge zaladowac bitmapy animacji!");
                    Quit();
                    return;
                }
            }
            else
            {
                Log("Bitmap = NULL\n");
            }
        }
        if(fgets(line,1023,f)!=NULL)
        {
            a->rowsNum = atoi(line);
            a->rows = malloc(atoi(line) * sizeof(int));
        }
        else
        {
            Error();
        }

        for(int i = 0;i<a->rowsNum;i++)
        {
            if(fgets(line,1023,f))
            {
                a->rows[i] = atoi(line);
            }
            else
            {
                Error();
            }
        }

        if(fgets(line,1023,f))
        {
            a->loopPerFrame = atoi(line);
        }
        else
        {
            Error();
        }

        if(fgets(line,1023,f))
        {
            a->loopPerAttFrame = atoi(line);
        }
        else
        {
            Error();
        }

        a->row = 0;
        a->frame = 0;
        a->timer = 0;

        free(line);
        fclose(f);
    }
    else
    {
        Log("Error opening hero animation\n");
        InitAnimation(a,"Data/Animations/player.ani",add);
    }
}

void Error()
{
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Nie moge zaladowac animacji!");
    Quit();
    return;
}

void SetRow(Animation* a,int row)
{
    a->row = row;
    a->frame = 0;
    a->timer = 0;
}

void NextFrame(Animation* a)
{
    if(a->timer >= a->loopPerFrame)
    {
        if(a->frame < a->rows[a->row]-1)
        {
            a->frame++;
        }
        else
        {
            a->frame = 0;
        }
        a->timer = 0;
    }
    else
    {
        a->timer++;
    }
}

void NextAttFrame(Animation* a)
{
    if(a->timer >= a->loopPerAttFrame)
    {
        if(a->frame < a->rows[a->row]-1)
        {
            a->frame++;
        }
        else
        {
            a->frame = 0;
        }
        a->timer = 0;
    }
    else
    {
        a->timer++;
    }
}

void FreeAnimation(Animation* a)
{
    destroy_bitmap(a->bitmap);
    free(a);
    a = NULL;
}
