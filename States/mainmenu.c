#include "mainmenu.h"
#include "../GameManager.h"
#include "../loop.h"
#include "../config.h"

void InitMenu()
{
    newGameButt.x = Resolution.x/2 - 64; newGameButt.y = Resolution.y/2 - 128; newGameButt.w = 128; newGameButt.h = 64;
    optionsButt.x = Resolution.x/2 - 64; optionsButt.y = Resolution.y/2-48;  optionsButt.w = 128; optionsButt.h = 64;
    quitButt.x = Resolution.x/2 - 64; quitButt.y = Resolution.y/2 + 52;  quitButt.w = 128; quitButt.h = 64;

    MenuInit = true;
    //quitButt;
}

void UpdateMenu()
{
    if(MenuInit)
    {
        mouse.x = mouse_x;mouse.y = mouse_y;
        int b = mouse_b;
        if(ABB(mouse,newGameButt) && b ==1)
        {
            GameState = GAME;
            stop_sample(bgMusic);
        }
        if(ABB(mouse,optionsButt) && b ==1)
        {
            GameState = OPTIONS;
            //stop_sample(bgMusic);
        }
        if(ABB(mouse,quitButt) && b ==1)
        {
            stop_sample(bgMusic);
            Quit();
        }
    }
    else
    {
        InitMenu();
        play_sample(bgMusic,musicVol,127,1000,1);
    }
}

void DrawMenu()
{
    if(Running)
    {
        clear_to_color(buffer,makecol(200,180,200));
        masked_blit(button,buffer,0,0,newGameButt.x,newGameButt.y,newGameButt.w,newGameButt.h);
        textout_ex(buffer,font,"NEW GAME",newGameButt.x + 33,newGameButt.y + 28,makecol(10,0,10),-1);
        masked_blit(button,buffer,0,0,optionsButt.x,optionsButt.y,optionsButt.w,optionsButt.h);
        textout_ex(buffer,font,"OPTIONS",optionsButt.x + 36,optionsButt.y + 28,makecol(10,0,10),-1);
        masked_blit(button,buffer,0,0,quitButt.x,quitButt.y,quitButt.w,quitButt.h);
        textout_ex(buffer,font,"EXIT",quitButt.x + 49,quitButt.y + 28,makecol(10,0,10),-1);
        textout_ex(buffer,font,"Strzalki - poruszanie, Spacja - atak",10,10,makecol(100,100,80),-1);
        masked_blit(mouseSprite,buffer,0,0,mouse.x,mouse.y,32,32);

        blit(buffer,screen,0,0,0,0,Resolution.x,Resolution.y);
    }
}
