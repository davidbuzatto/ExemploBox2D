#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "Types.h"

RigidSquare* createRigidSquare( float x, float y, float w, float h, Color color, GameWorld *gw ) {

    RigidSquare* newSquare = (RigidSquare*) malloc( sizeof( RigidSquare ) );
    newSquare->dim = (Vector2){ w, h };

    newSquare->bodyDef = b2DefaultBodyDef();
    newSquare->bodyDef.position = (b2Vec2){ x, y };
    newSquare->bodyId = b2CreateBody( gw->worldId, &newSquare->bodyDef );
    newSquare->rigidBox = b2MakeBox( w/2, h/2 );

    newSquare->shapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape( newSquare->bodyId, &newSquare->shapeDef, &newSquare->rigidBox );

    newSquare->color = color;

    return newSquare;

}

void destroyRigidSquare( RigidSquare *s ) {
    free( s );
}

void drawRigidSquare( RigidSquare *s ) {

    DrawRectangle( 
        s->bodyDef.position.x - s->dim.x / 2, 
        -s->bodyDef.position.y - s->dim.y / 2, 
        s->dim.x, 
        s->dim.y, 
        s->color );
    
}