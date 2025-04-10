#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "StaticRectangle.h"
#include "Types.h"

void createStaticRectangle( StaticRectangle* newRectangle, float x, float y, float w, float h, Color color, GameWorld *gw ) {

    newRectangle->dim = (Vector2){ w, h };

    newRectangle->bodyDef = b2DefaultBodyDef();
    newRectangle->bodyDef.position = (b2Vec2){ x, y };
    newRectangle->bodyDef.type = b2_staticBody;
    newRectangle->bodyId = b2CreateBody( gw->worldId, &newRectangle->bodyDef );
    
    newRectangle->rect = b2MakeBox( w/2, h/2 );

    newRectangle->shapeDef = b2DefaultShapeDef();
    newRectangle->shapeId = b2CreatePolygonShape( newRectangle->bodyId, &newRectangle->shapeDef, &newRectangle->rect );

    newRectangle->color = color;

}

void drawStaticRectangle( StaticRectangle *rectangle ) {

    DrawRectangle( 
        rectangle->bodyDef.position.x - rectangle->dim.x / 2, 
        -rectangle->bodyDef.position.y - rectangle->dim.y / 2, 
        rectangle->dim.x, 
        rectangle->dim.y, 
        rectangle->color );
    
}