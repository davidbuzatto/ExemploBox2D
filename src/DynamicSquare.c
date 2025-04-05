#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "Types.h"

DynamicSquare* createDynamicSquare( float x, float y, float w, float h, Color color, GameWorld *gw ) {

    DynamicSquare* newSquare = (DynamicSquare*) malloc( sizeof( DynamicSquare ) );
    newSquare->dim = (Vector2){ w, h };

    newSquare->bodyDef = b2DefaultBodyDef();
    newSquare->bodyDef.type = b2_dynamicBody;
    newSquare->bodyDef.position = (b2Vec2){ x, y };
    newSquare->bodyId = b2CreateBody( gw->worldId, &newSquare->bodyDef );

    newSquare->dynamicBox = b2MakeBox( w/2, h/2 );

    newSquare->shapeDef = b2DefaultShapeDef();
    newSquare->shapeDef.density = 1.0f;
    newSquare->shapeDef.friction = 0.3f;

    b2CreatePolygonShape( newSquare->bodyId, &newSquare->shapeDef, &newSquare->dynamicBox );

    newSquare->color = color;

    return newSquare;

}

void destroyDynamicSquare( DynamicSquare *s ) {
    free( s );
}

void drawDynamicSquare( DynamicSquare *s ) {

    b2Vec2 position = b2Body_GetPosition( s->bodyId );
    b2Rot rotation = b2Body_GetRotation( s->bodyId );

    Rectangle rect = (Rectangle){ 
        position.x - s->dim.x / 2, 
        -position.y - s->dim.y / 2, 
        s->dim.x, 
        s->dim.y
    };

    Rectangle rot = rect;
    rot.x += rot.width / 2;
    rot.y += rot.height / 2;

    DrawRectanglePro( 
        rot, 
        (Vector2) { rot.width / 2, rot.height / 2 }, 
        RAD2DEG * atan2( rotation.c, rotation.s ),   // ângulo do número complexo (rotation)
        s->color
    );
    
}