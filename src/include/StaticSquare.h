#pragma once

#include "Types.h"

#include "raylib/raylib.h"

void createStaticSquare( StaticSquare* newSquare, float x, float y, float w, float h, Color color, GameWorld *gw );
void drawStaticSquare( StaticSquare *square );
