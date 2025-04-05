#pragma once

#include "Types.h"

#include "raylib/raylib.h"

DynamicSquare* createDynamicSquare( float x, float y, float w, float h, Color color, GameWorld *gw );
void destroyDynamicSquare( DynamicSquare *s );
void drawDynamicSquare( DynamicSquare *s );
