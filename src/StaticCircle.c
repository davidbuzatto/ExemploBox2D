#include <stdio.h>
#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "StaticCircle.h"
#include "Types.h"

void createStaticCircle( StaticCircle* newCircle, float x, float y, float r, Color color, GameWorld *gw ) {

    newCircle->radius = r;

    newCircle->bodyDef = b2DefaultBodyDef();
    newCircle->bodyDef.position = (b2Vec2){ x, y };
    newCircle->bodyDef.type = b2_staticBody;
    newCircle->bodyId = b2CreateBody( gw->worldId, &newCircle->bodyDef );
    
    newCircle->circle = (b2Circle){ { x, y }, r };

    newCircle->shapeDef = b2DefaultShapeDef();
    newCircle->shapeId = b2CreateCircleShape( newCircle->bodyId, &newCircle->shapeDef, &newCircle->circle );

    newCircle->color = color;

}

void drawStaticCircle( StaticCircle *circle ) {

    DrawCircle( 
        circle->circle.center.x, 
        -circle->circle.center.y, 
        circle->circle.radius,  
        circle->color );

    /*DrawCircle( 
        circle->bodyDef.position.x, 
        -circle->bodyDef.position.y, 
        circle->radius,  
        circle->color );*/
    
}