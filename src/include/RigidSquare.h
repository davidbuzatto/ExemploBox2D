#pragma once

#include "Types.h"

#include "raylib/raylib.h"

RigidSquare* createRigidSquare( float x, float y, float w, float h, Color color, GameWorld *gw );
void destroyRigidSquare( RigidSquare *s );
void drawRigidSquare( RigidSquare *s );
