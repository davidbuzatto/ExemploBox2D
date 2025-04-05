#pragma once

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#define MAX_SQUARE_QUANTITY 10000

typedef struct DynamicSquare {
    Vector2 dim;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Polygon dynamicBox;
    b2ShapeDef shapeDef;
    Color color;
} DynamicSquare;

typedef struct RigidSquare {
    Vector2 dim;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Polygon rigidBox;
    b2ShapeDef shapeDef;
    Color color;
} RigidSquare;

typedef struct GameWorld {

    b2WorldDef worldDef;
    b2WorldId worldId;

    RigidSquare* ground;
    RigidSquare* leftWall;
    RigidSquare* rightWall;

    DynamicSquare* squares[MAX_SQUARE_QUANTITY];
    int squareQuantity;

} GameWorld;