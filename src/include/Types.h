#pragma once

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#define MAX_RIGID_SQUARES 100
#define MAX_RIGID_CIRCLES 100
#define MAX_DYNAMIC_SQUARES 5000
#define MAX_DYNAMIC_CIRCLES 5000

typedef struct DynamicSquare {
    Vector2 dim;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Polygon polygon;
    b2ShapeDef shapeDef;
    b2ShapeId shapeId;
    Color color;
} DynamicSquare;

typedef struct DynamicCircle {
    float radius;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Circle circle;
    b2ShapeDef shapeDef;
    b2ShapeId shapeId;
    Color color;
} DynamicCircle;

typedef struct RigidSquare {
    Vector2 dim;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Polygon polygon;
    b2ShapeDef shapeDef;
    b2ShapeId shapeId;
    Color color;
} RigidSquare;

typedef struct RigidCircle {
    float radius;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Circle circle;
    b2ShapeDef shapeDef;
    b2ShapeId shapeId;
    Color color;
} RigidCircle;

typedef struct GameWorld {

    b2WorldDef worldDef;
    b2WorldId worldId;

    RigidSquare rigidSquares[MAX_RIGID_SQUARES];
    int rigidSquareQuantity;
    
    DynamicSquare dynamicSquares[MAX_DYNAMIC_SQUARES];
    int dynamicSquareQuantity;

    DynamicCircle dynamicCircles[MAX_DYNAMIC_CIRCLES];
    int dynamicCircleQuantity;

} GameWorld;