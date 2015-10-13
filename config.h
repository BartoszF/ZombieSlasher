#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "helpers.h"
#include "dictionary.h"
#include <allegro.h>
#include <stdio.h>

BITMAP * buffer;
BITMAP * mouseSprite;
BITMAP * button;
BITMAP * hpBar;
FONT * pausedFont;
Point Resolution;

SAMPLE * bgMusic;
SAMPLE * swordSlash;
SAMPLE * zombieMoan;
SAMPLE * zombieDead;
SAMPLE * zombieHit;

int fxVol;
int musicVol;

Point mouse;

char* hFile;
char* zFile;

FILE *logFile;

void LoadConfig(char* file);
void SaveConfig(char* file);
void LoadFiles();
void FreeFiles();
void Log(char* str);

#endif // CONFIG_H_INCLUDED
