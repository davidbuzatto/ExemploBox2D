#pragma once

#include "Types.h"

#include "raylib/raylib.h"

void createStaticCircle( StaticCircle* newCircle, float x, float y, float r, Color color, GameWorld *gw );
void drawStaticCircle( StaticCircle *circle );
