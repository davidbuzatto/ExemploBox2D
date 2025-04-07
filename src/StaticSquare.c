#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "StaticSquare.h"
#include "Types.h"

void createStaticSquare( StaticSquare* newSquare, float x, float y, float w, float h, Color color, GameWorld *gw ) {

    newSquare->dim = (Vector2){ w, h };

    newSquare->bodyDef = b2DefaultBodyDef();
    newSquare->bodyDef.position = (b2Vec2){ x, y };
    newSquare->bodyDef.type = b2_staticBody;
    newSquare->bodyId = b2CreateBody( gw->worldId, &newSquare->bodyDef );
    
    newSquare->polygon = b2MakeBox( w/2, h/2 );

    newSquare->shapeDef = b2DefaultShapeDef();
    newSquare->shapeId = b2CreatePolygonShape( newSquare->bodyId, &newSquare->shapeDef, &newSquare->polygon );

    newSquare->color = color;

}

void drawStaticSquare( StaticSquare *square ) {

    DrawRectangle( 
        square->bodyDef.position.x - square->dim.x / 2, 
        -square->bodyDef.position.y - square->dim.y / 2, 
        square->dim.x, 
        square->dim.y, 
        square->color );
    
}