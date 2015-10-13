#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <allegro.h>
#include <stdbool.h>
#include "../helpers.h"

Rect newGameButt;
Rect optionsButt;
Rect quitButt;
bool MenuInit;

void InitMenu();
void UpdateMenu();
void DrawMenu();


#endif // MAINMENU_H_INCLUDED
