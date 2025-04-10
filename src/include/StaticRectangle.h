#pragma once

#include "Types.h"

#include "raylib/raylib.h"

void createStaticRectangle( StaticRectangle* newRectangle, float x, float y, float w, float h, Color color, GameWorld *gw );
void drawStaticRectangle( StaticRectangle *rectangle );
