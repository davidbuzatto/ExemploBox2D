#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "DynamicSquare.h"
#include "Types.h"

void createDynamicSquare( DynamicSquare *newSquare, float x, float y, float w, float h, Color color, GameWorld *gw ) {

    newSquare->dim = (Vector2){ w, h };

    newSquare->bodyDef = b2DefaultBodyDef();
    newSquare->bodyDef.type = b2_dynamicBody;
    newSquare->bodyDef.position = (b2Vec2){ x, y };
    newSquare->bodyId = b2CreateBody( gw->worldId, &newSquare->bodyDef );

    newSquare->polygon = b2MakeBox( w/2, h/2 );

    newSquare->shapeDef = b2DefaultShapeDef();
    newSquare->shapeDef.density = 1.0f;
    newSquare->shapeDef.friction = 0.3f;

    newSquare->shapeId = b2CreatePolygonShape( newSquare->bodyId, &newSquare->shapeDef, &newSquare->polygon );

    newSquare->color = color;

}

void drawDynamicSquare( DynamicSquare *square ) {

    b2Vec2 position = b2Body_GetPosition( square->bodyId );
    b2Rot rotation = b2Body_GetRotation( square->bodyId );

    Rectangle rect = (Rectangle){ 
        position.x, 
        -position.y, 
        square->dim.x, 
        square->dim.y
    };

    DrawRectanglePro( 
        rect, 
        (Vector2) { rect.width / 2, rect.height / 2 }, 
        RAD2DEG * atan2( rotation.c, rotation.s ),   // ângulo do número complexo (rotation)
        //RAD2DEG * b2Rot_GetAngle( rotation ),   // ângulo do número complexo (rotation)
        square->color
    );
    
}