#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "DynamicRectangle.h"
#include "Types.h"

void createDynamicRectangle( DynamicRectangle *newRectangle, float x, float y, float w, float h, Color color, GameWorld *gw ) {

    newRectangle->dim = (Vector2){ w, h };

    newRectangle->bodyDef = b2DefaultBodyDef();
    newRectangle->bodyDef.type = b2_dynamicBody;
    newRectangle->bodyDef.position = (b2Vec2){ x, y };
    newRectangle->bodyId = b2CreateBody( gw->worldId, &newRectangle->bodyDef );

    newRectangle->rect = b2MakeBox( w/2, h/2 );

    newRectangle->shapeDef = b2DefaultShapeDef();
    newRectangle->shapeDef.density = 1.0f;
    newRectangle->shapeDef.friction = 0.3f;

    newRectangle->shapeId = b2CreatePolygonShape( newRectangle->bodyId, &newRectangle->shapeDef, &newRectangle->rect );

    newRectangle->color = color;

}

void drawDynamicRectangle( DynamicRectangle *rectangle ) {

    b2Vec2 position = b2Body_GetPosition( rectangle->bodyId );
    b2Rot rotation = b2Body_GetRotation( rectangle->bodyId );

    Rectangle rect = (Rectangle){ 
        position.x, 
        -position.y, 
        rectangle->dim.x, 
        rectangle->dim.y
    };

    DrawRectanglePro( 
        rect, 
        (Vector2) { rect.width / 2, rect.height / 2 }, 
        RAD2DEG * atan2( rotation.c, rotation.s ),   // ângulo do número complexo (rotation)
        //RAD2DEG * b2Rot_GetAngle( rotation ),   // ângulo do número complexo (rotation)
        rectangle->color
    );
    
}