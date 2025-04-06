#pragma once

#include "Types.h"

#include "raylib/raylib.h"

void createDynamicCircle( DynamicCircle *newCircle, float x, float y, float r, Color color, GameWorld *gw );
void drawDynamicCircle( DynamicCircle *circle );
