#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "loop.h"

typedef enum state
{
    MAINMENU = 1,
    GAME = 2,
    OPTIONS = 3,
    QUIT = 4
}State;

State GameState;

void InitGameManager();
void UpdateGameManager();
void DrawGameManager();

#endif // GAMEMANAGER_H_INCLUDED
