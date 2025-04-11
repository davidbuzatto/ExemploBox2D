#include <stdio.h>
#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "StaticCircle.h"
#include "Types.h"

void createStaticCircle( StaticCircle* newCircle, float x, float y, float r, Color color, GameWorld *gw ) {

    newCircle->radius = r;

    // posição global (no mundo)
    newCircle->bodyDef = b2DefaultBodyDef();
    newCircle->bodyDef.position = (b2Vec2){ x, y };
    newCircle->bodyDef.type = b2_staticBody;
    newCircle->bodyId = b2CreateBody( gw->worldId, &newCircle->bodyDef );
    
    // posição local relativa ao corpo
    newCircle->circle = (b2Circle){ { 0.0f, 0.0f }, r };

    newCircle->shapeDef = b2DefaultShapeDef();
    newCircle->shapeId = b2CreateCircleShape( newCircle->bodyId, &newCircle->shapeDef, &newCircle->circle );

    newCircle->color = color;

}

void drawStaticCircle( StaticCircle *circle ) {

    b2Vec2 position = b2Body_GetPosition( circle->bodyId );

    DrawCircle( 
        position.x, 
        position.y, 
        circle->circle.radius,  
        circle->color );

    /*DrawCircle( 
        circle->bodyDef.position.x, 
        circle->bodyDef.position.y, 
        circle->radius,  
        circle->color );*/
    
}