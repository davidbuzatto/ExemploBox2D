#pragma once

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#define MAX_STATIC_SQUARES 100
#define MAX_STATIC_CIRCLES 100
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

typedef struct StaticSquare {
    Vector2 dim;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Polygon polygon;
    b2ShapeDef shapeDef;
    b2ShapeId shapeId;
    Color color;
} StaticSquare;

typedef struct StaticCircle {
    float radius;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Circle circle;
    b2ShapeDef shapeDef;
    b2ShapeId shapeId;
    Color color;
} StaticCircle;

typedef struct GameWorld {

    b2WorldDef worldDef;
    b2WorldId worldId;

    StaticSquare staticSquares[MAX_STATIC_SQUARES];
    int staticSquareQuantity;
    
    DynamicSquare dynamicSquares[MAX_DYNAMIC_SQUARES];
    int dynamicSquareQuantity;

    StaticCircle staticCircles[MAX_STATIC_CIRCLES];
    int staticCircleQuantity;

    DynamicCircle dynamicCircles[MAX_DYNAMIC_CIRCLES];
    int dynamicCircleQuantity;

} GameWorld;