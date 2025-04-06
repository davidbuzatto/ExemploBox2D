#pragma once

#include "Types.h"

#include "raylib/raylib.h"

void createRigidSquare( RigidSquare* newSquare, float x, float y, float w, float h, Color color, GameWorld *gw );
void drawRigidSquare( RigidSquare *square );
