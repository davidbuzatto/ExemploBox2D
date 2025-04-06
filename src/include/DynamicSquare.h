#pragma once

#include "Types.h"

#include "raylib/raylib.h"

void createDynamicSquare( DynamicSquare *newSquare, float x, float y, float w, float h, Color color, GameWorld *gw );
void drawDynamicSquare( DynamicSquare *square );
