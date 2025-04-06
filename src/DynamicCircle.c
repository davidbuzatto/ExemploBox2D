#include <stdio.h>
#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "DynamicCircle.h"
#include "Types.h"

void createDynamicCircle( DynamicCircle* newCircle, float x, float y, float r, Color color, GameWorld *gw ) {

    newCircle->radius = r;

    newCircle->bodyDef = b2DefaultBodyDef();
    newCircle->bodyDef.type = b2_dynamicBody;
    newCircle->bodyDef.position = (b2Vec2){ x, y };
    newCircle->bodyDef.fixedRotation = true;
    newCircle->bodyId = b2CreateBody( gw->worldId, &newCircle->bodyDef );
    
    newCircle->circle = (b2Circle){ { x, y }, r };

    newCircle->shapeDef = b2DefaultShapeDef();
    newCircle->shapeDef.density = 1.0f;
    newCircle->shapeDef.friction = 0.3f;

    newCircle->shapeId = b2CreateCircleShape( newCircle->bodyId, &newCircle->shapeDef, &newCircle->circle );

    newCircle->color = color;

}

void drawDynamicCircle( DynamicCircle *circle ) {

    b2Vec2 position = b2Body_GetPosition( circle->bodyId );

    DrawCircle( 
        position.x, 
        -position.y, 
        circle->radius,  
        circle->color );
    
}