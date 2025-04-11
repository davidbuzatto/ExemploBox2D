#include <stdio.h>
#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "DynamicCapsule.h"
#include "Types.h"

void createDynamicCapsule( DynamicCapsule* newCapsule, float x, float y, float dx, float dy, float r, Color color, GameWorld *gw ) {

    newCapsule->radius = r;

    newCapsule->bodyDef = b2DefaultBodyDef();
    newCapsule->bodyDef.type = b2_dynamicBody;
    newCapsule->bodyDef.position = (b2Vec2){ x, y };
    newCapsule->bodyId = b2CreateBody( gw->worldId, &newCapsule->bodyDef );
    
    newCapsule->capsule.center1 = (b2Vec2){ 0.0f, 0.0f };
    newCapsule->capsule.center2 = (b2Vec2){ dx, dy };
    newCapsule->capsule.radius = r;

    newCapsule->shapeDef = b2DefaultShapeDef();
    newCapsule->shapeDef.density = 1.0f;
    newCapsule->shapeDef.friction = 0.3f;
    //newCapsule->shapeDef.restitution = 1.0f;

    newCapsule->shapeId = b2CreateCapsuleShape( newCapsule->bodyId, &newCapsule->shapeDef, &newCapsule->capsule );

    newCapsule->color = color;

}

void drawDynamicCapsule( DynamicCapsule *capsule ) {

    b2Capsule c = b2Shape_GetCapsule( capsule->shapeId );

    b2Transform t = b2Body_GetTransform( capsule->bodyId );
    b2Vec2 c1 = b2TransformPoint( t, c.center1 );
    b2Vec2 c2 = b2TransformPoint( t, c.center2 );

    b2Vec2 vt1 = b2TransformPoint( t, (b2Vec2){ c.center1.x, c.center1.y - c.radius } );
    b2Vec2 vb1 = b2TransformPoint( t, (b2Vec2){ c.center1.x, c.center1.y + c.radius } );

    b2Vec2 vt2 = b2TransformPoint( t, (b2Vec2){ c.center2.x, c.center2.y - c.radius } );
    b2Vec2 vb2 = b2TransformPoint( t, (b2Vec2){ c.center2.x, c.center2.y + c.radius } );

    DrawCircle( 
        c1.x, 
        c1.y, 
        capsule->radius,  
        capsule->color );

    DrawCircle( 
        c2.x, 
        c2.y, 
        capsule->radius,  
        capsule->color );

    DrawTriangle( (Vector2){ vb1.x, vb1.y }, (Vector2){ vt2.x, vt2.y }, (Vector2){ vt1.x, vt1.y }, capsule->color );
    DrawTriangle( (Vector2){ vb2.x, vb2.y }, (Vector2){ vt2.x, vt2.y }, (Vector2){ vb1.x, vb1.y }, capsule->color );
    
}

void applyForceDynamicCapsule( DynamicCapsule *capsule ) {

    //b2Vec2 position = b2Body_GetPosition( capsule->bodyId );

    //b2Body_ApplyForce(myBodyId, force, worldPoint, wake);
    //b2Body_ApplyForce( capsule->bodyId, (b2Vec2){ 100000.0f, 0.0f }, position, true );
    
    //b2Body_ApplyTorque(myBodyId, torque, wake);
    //b2Body_ApplyTorque( capsule->bodyId, 100000.0f, true );

    //b2Body_ApplyLinearImpulse(myBodyId, linearImpulse, worldPoint, wake);
    //b2Body_ApplyAngularImpulse(myBodyId, angularImpulse, wake);
    //b2Body_ApplyForceToCenter(myBodyId, force, wake);
    if ( b2Body_GetLinearVelocity( capsule->bodyId ).x < 200 ) {
        b2Body_ApplyForceToCenter( capsule->bodyId, (b2Vec2){ 1000000, 0 }, true );
    }
    
    //b2Body_ApplyLinearImpulseToCenter(myBodyId, linearImpulse, wake);
    //b2Body_ApplyLinearImpulseToCenter( capsule->bodyId, (b2Vec2){ 100000, 0 }, true );
    //b2Body_SetLinearVelocity( capsule->bodyId, (b2Vec2){ 200, 0 } );
    //b2Body_SetLinearDamping( capsule->bodyId, 300 );

}