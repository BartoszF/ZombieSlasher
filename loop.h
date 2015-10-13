#ifndef LOOP_H_INCLUDED
#define LOOP_H_INCLUDED

#include <stdbool.h>
#include <allegro.h>
#include "helpers.h"

volatile long speed;
Rect camera;
bool Running;
bool Paused;
bool Scores;
bool LoadedScores;
bool GameInit;

char* name;
char** scores;
int nameL;
int nameI;

void Start();
void InitGame();
void LoadScores();
int Loop();
void Pause();
void UnPause();
void Quit();

void Update();
void Draw();

void IncSpeed();

#endif // LOOP_H_INCLUDED
