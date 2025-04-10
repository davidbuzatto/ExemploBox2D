#pragma once

#include "Types.h"

#include "raylib/raylib.h"

void createDynamicRectangle( DynamicRectangle *newRectangle, float x, float y, float w, float h, Color color, GameWorld *gw );
void drawDynamicRectangle( DynamicRectangle *rectangle );
