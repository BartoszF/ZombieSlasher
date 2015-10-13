#include "GameManager.h"
#include "loop.h"
#include "States/mainmenu.h"
#include "States/options.h"

void InitGameManager()
{
    GameState = 1;
}

void UpdateGameManager()
{
    if(GameState == 1)  UpdateMenu();
    if(GameState == 2)  Update();
    if(GameState == 3)  UpdateOptions();
}

void DrawGameManager()
{
    if(GameState == 1)  DrawMenu();
    if(GameState == 2)  Draw();
    if(GameState == 3)  DrawOptions();
}
