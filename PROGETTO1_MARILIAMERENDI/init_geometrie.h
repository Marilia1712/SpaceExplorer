/*
#pragma once //: È una direttiva che indica al compilatore di includere il file una sola volta per unità di compilazione.
//  Il meccanismo esatto varia a seconda del compilatore, ma in generale si basa su un meccanismo interno per tenere traccia dei file già inclusi.
//Non è parte dello standard C++, quindi la sua disponibilità e il comportamento preciso possono variare tra diversi compilatori. Tuttavia, è supportata dalla maggior parte dei compilatori moderni.
*/

#pragma once

#include "strutture.h"

void INIT_PIANO(Figura* fig);
Curva INIT_FORMA(std::string nomefile, vec4 color_top, vec4 color_bot, eltype type);
void INIT_STAR(float cx, float cy, float raggioInterno, float raggioEsterno, Figura* fig);