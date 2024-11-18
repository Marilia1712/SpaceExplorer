#pragma once
#include "strutture.h"
#include "lib.h"

vec2 randomPosition(int width, int height);
void findBB(Figura* fig);
bool checkCollision(Figura* obj1, Figura* obj2);
void updateBB(Figura* fig);
void update_angle(Figura* fig);
void update_position(Figura* fig);
void create_meteor(Curva* meteor, unsigned int programId);
void create_star(Figura* star, unsigned int programId);