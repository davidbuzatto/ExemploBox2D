#pragma once

#include "Types.h"

#include "raylib/raylib.h"

void createRigidCircle( RigidCircle* newCircle, float x, float y, float r, Color color, GameWorld *gw );
void drawRigidCircle( RigidCircle *circle );
