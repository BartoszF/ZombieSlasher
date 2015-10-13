#include "config.h"

void LoadConfig(char* file)
{
    Resolution.x = 1024;
    Resolution.y = 768;

    FILE* f = fopen(file,"r");
    if(f)
    {
        char c[1023];
        if(fgets(c,1023,f))
        {
            int l = strlen(c);
            if(c[l-1] == '\n') c[l-1] = '\0';
            fxVol = atoi(c);
        }
        if(fgets(c,1023,f))
        {
            int l = strlen(c);
            if(c[l-1] == '\n') c[l-1] = '\0';
            musicVol = atoi(c);
        }
        fclose(f);
    }
    else
    {
        Log("Could not load config\n");
        hFile = "default.hero";
        zFile = "default.zombie";

        fxVol = 150;
        musicVol = 165;
    }


}

void SaveConfig(char* file)
{
    FILE* f = fopen(file,"w");

    if(f)
    {
        fprintf(f,"%d\n",fxVol);
        fprintf(f,"%d\n",musicVol);
        fclose(f);
    }
    else
    {
        Log("Error\n");
    }
}

void LoadFiles()
{
    pausedFont = load_font("Data/Fonts/kh_20.pcx",default_palette,NULL);
    if(!pausedFont)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac czcionki!");
        Quit();
    }

    button = load_bitmap("Data/Bitmaps/button.bmp",default_palette);
    if(!button)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac przycisku!");
        Quit();
    }

    mouseSprite = load_bitmap("Data/Bitmaps/mouse.bmp",default_palette);
    if(!mouseSprite)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac myszki!");
        Quit();
    }

    hpBar = load_bitmap("Data/Bitmaps/hp.bmp",default_palette);
    if(!hpBar)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac hp!");
        Quit();
    }

    bgMusic = load_sample("Data/Waves/Menu/bgMusic.wav");
    if(!bgMusic)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac muzyki!");
        Quit();
    }

    swordSlash = load_sample("Data/Waves/sword slash.wav");
    if(!swordSlash)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac muzyki!");
        Quit();
    }

    zombieMoan = load_sample("Data/Waves/zombie moan.wav");
    if(!zombieMoan)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac muzyki!");
        Quit();
    }

    zombieHit = load_sample("Data/Waves/zombie hit.wav");
    if(!zombieHit)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac muzyki!");
        Quit();
    }

    zombieDead = load_sample("Data/Waves/zombie dead.wav");
    if(!zombieDead)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge zaladowac muzyki!");
        Quit();
    }

    buffer = create_bitmap(Resolution.x,Resolution.y);
    if (!buffer)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Nie moge utworzyc bufora !");
        Quit();
    }
}

void FreeFiles()
{
    destroy_font(pausedFont);
    destroy_bitmap(button);
    destroy_bitmap(mouseSprite);
    destroy_sample(swordSlash);
    destroy_sample(zombieMoan);
    destroy_sample(zombieHit);
    destroy_sample(zombieDead);
    destroy_sample(bgMusic);
    destroy_bitmap(buffer);
}

void Log(char* str)
{
    if(!logFile)
    {
        logFile = fopen("log.txt","w");
    }
    if(logFile)
    {
        fprintf(logFile,"%s",str);
        fflush(logFile);
    }
}
