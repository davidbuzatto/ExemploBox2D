#pragma once

#include "Types.h"

#include "raylib/raylib.h"

void createDynamicCapsule( DynamicCapsule *newCapsule, float x, float y, float dx, float dy, float r, Color color, GameWorld *gw );
void drawDynamicCapsule( DynamicCapsule *capsule );
void applyForceDynamicCapsule( DynamicCapsule *capsule );
