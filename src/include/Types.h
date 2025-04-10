#pragma once

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#define MAX_STATIC_BODIES 100
#define MAX_DYNAMIC_BODIES 5000

typedef struct DynamicRectangle {
    Vector2 dim;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Polygon rect;
    b2ShapeDef shapeDef;
    b2ShapeId shapeId;
    Color color;
} DynamicRectangle;

typedef struct DynamicCircle {
    float radius;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Circle circle;
    b2ShapeDef shapeDef;
    b2ShapeId shapeId;
    Color color;
} DynamicCircle;

typedef struct DynamicCapsule {
    float radius;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Capsule capsule;
    b2ShapeDef shapeDef;
    b2ShapeId shapeId;
    Color color;
} DynamicCapsule;

typedef struct StaticRectangle {
    Vector2 dim;
    b2BodyDef bodyDef;
    b2BodyId bodyId;
    b2Polygon rect;
    b2ShapeDef shapeDef;
    b2ShapeId shapeId;
    Color color;
} StaticRectangle;

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

    StaticRectangle staticRectangles[MAX_STATIC_BODIES];
    int staticRectanglesQuantity;
    
    StaticCircle staticCircles[MAX_STATIC_BODIES];
    int staticCirclesQuantity;

    DynamicRectangle dynamicRectangles[MAX_DYNAMIC_BODIES];
    int dynamicRectanglesQuantity;

    DynamicCircle dynamicCircles[MAX_DYNAMIC_BODIES];
    int dynamicCirclesQuantity;

    DynamicCapsule dynamicCapsules[MAX_DYNAMIC_BODIES];
    int dynamicCapsulesQuantity;

    b2Vec2 chainPoints[100];
    int chainPointsQuantity;
    bool finishedChain;

} GameWorld;