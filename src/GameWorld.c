/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Types.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "StaticRectangle.h"
#include "StaticCircle.h"
#include "DynamicRectangle.h"
#include "DynamicCircle.h"
#include "DynamicCapsule.h"

#include "raylib/raylib.h"
#include "raylib/rlgl.h"

#include "box2d/box2d.h"

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    float lengthUnitsPerMeter = 128.0f;
	b2SetLengthUnitsPerMeter( lengthUnitsPerMeter );

    gw->worldDef = b2DefaultWorldDef();
    //gw->worldDef.gravity = (b2Vec2){ 0.0f, -10.0f };
    gw->worldDef.gravity = (b2Vec2){ 0.0f, -9.8f * lengthUnitsPerMeter };
    gw->worldId = b2CreateWorld( &gw->worldDef );

    gw->staticRectanglesQuantity = 0;
    gw->staticCirclesQuantity = 0;

    gw->dynamicRectanglesQuantity = 0;
    gw->dynamicCirclesQuantity = 0;
    gw->dynamicCapsulesQuantity = 0;

    gw->chainPointsQuantity = 0;
    gw->finishedChain = false;
    
    float cx = GetScreenWidth() / 2;
    float cy = GetScreenHeight() / 2;
    float rWidth = 10.0f;

    createStaticRectangle( &gw->staticRectangles[gw->staticRectanglesQuantity], cx, rWidth / 2, GetScreenWidth(), rWidth, BLACK, gw );
    gw->staticRectanglesQuantity++;
    createStaticRectangle( &gw->staticRectangles[gw->staticRectanglesQuantity], rWidth / 2, cy, rWidth, GetScreenHeight(), BLACK, gw );
    gw->staticRectanglesQuantity++;
    createStaticRectangle( &gw->staticRectangles[gw->staticRectanglesQuantity], GetScreenWidth() - rWidth / 2, cy, rWidth, GetScreenHeight(), BLACK, gw );
    gw->staticRectanglesQuantity++;

    /*createStaticCircle( &gw->staticCircles[gw->staticCircleQuantity], cx, cy, 30, BLACK, gw );
    gw->staticCirclesQuantity++;*/

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    b2DestroyWorld( gw->worldId );
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta ) {

    tests( gw );
    
    tryToCreateChain( gw );
    //createStaticEntities( gw );
    //createDynamicEntities( gw );

    int subStepCount = 4;
    b2World_Step( gw->worldId, delta, subStepCount );

    // eventos aqui depois de b2World_Step

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    rlTranslatef( 0, GetScreenHeight(), 0 );
    //rlScalef( 2, 2, 1 );

    for ( int i = 0; i < gw->staticRectanglesQuantity; i++ ) {
        drawStaticRectangle( &gw->staticRectangles[i] );
    }

    for ( int i = 0; i < gw->staticCirclesQuantity; i++ ) {
        drawStaticCircle( &gw->staticCircles[i] );
    }

    for ( int i = 0; i < gw->dynamicRectanglesQuantity; i++ ) {
        drawDynamicRectangle( &gw->dynamicRectangles[i] );
    }
    
    for ( int i = 0; i < gw->dynamicCirclesQuantity; i++ ) {
        drawDynamicCircle( &gw->dynamicCircles[i] );
    }

    for ( int i = 0; i < gw->dynamicCapsulesQuantity; i++ ) {
        drawDynamicCapsule( &gw->dynamicCapsules[i] );
    }

    if ( gw->finishedChain ) {
        /*for ( int i = 1; i < gw->chainPointsQuantity - 2; i++ ) {
            DrawTriangle( 
                (Vector2) { gw->chainPoints[0].x, -gw->chainPoints[0].y },
                (Vector2) { gw->chainPoints[i].x, -gw->chainPoints[i].y },
                (Vector2) { gw->chainPoints[i+1].x, -gw->chainPoints[i+1].y },
                BLACK );
        }*/
        for ( int i = 0; i < gw->chainPointsQuantity - 1; i++ ) {
            DrawLine( gw->chainPoints[i].x, -gw->chainPoints[i].y, gw->chainPoints[i+1].x, -gw->chainPoints[i+1].y, BLACK  );
        }
    } else {
        for ( int i = 0; i < gw->chainPointsQuantity - 1; i++ ) {
            DrawLine( gw->chainPoints[i].x, -gw->chainPoints[i].y, gw->chainPoints[i+1].x, -gw->chainPoints[i+1].y, BLACK  );
        }
    }

    DrawFPS( 20, -GetScreenHeight() + 20 );
    DrawText( TextFormat( "Rectangles: %d", gw->dynamicRectanglesQuantity ), 20, -GetScreenHeight() + 40, 20, BLACK );
    DrawText( TextFormat( "Circles: %d", gw->dynamicCirclesQuantity ), 20, -GetScreenHeight() + 60, 20, BLACK );
    DrawText( TextFormat( "Capsules: %d", gw->dynamicCapsulesQuantity ), 20, -GetScreenHeight() + 80, 20, BLACK );

    EndDrawing();

}

void createStaticEntities( GameWorld *gw ) {

    if ( IsMouseButtonPressed( MOUSE_BUTTON_RIGHT ) ) {
        if ( IsKeyDown( KEY_LEFT_CONTROL ) ) {
            if ( gw->staticRectanglesQuantity < MAX_STATIC_BODIES ) {
                if ( gw->staticCirclesQuantity < MAX_STATIC_BODIES ) {
                    createStaticCircle( 
                        &gw->staticCircles[gw->staticCirclesQuantity],
                        GetMouseX(), 
                        GetScreenHeight() - GetMouseY(), 
                        8.0f, 
                        BLACK,
                        gw
                    );
                    gw->staticCirclesQuantity++;
                }
            }
        } else {
            createStaticRectangle( 
                &gw->staticRectangles[gw->staticRectanglesQuantity],
                GetMouseX(), 
                GetScreenHeight() - GetMouseY(), 
                16.0f, 
                16.0f, 
                BLACK,
                gw
            );
            gw->staticRectanglesQuantity++;
        }
    }

}

void createDynamicEntities( GameWorld *gw ) {

    if ( IsMouseButtonDown( MOUSE_BUTTON_LEFT ) ) {

        if ( IsKeyDown( KEY_LEFT_CONTROL ) ) {
            if ( gw->dynamicRectanglesQuantity < MAX_DYNAMIC_BODIES ) {
                createDynamicRectangle( 
                    &gw->dynamicRectangles[gw->dynamicRectanglesQuantity],
                    GetMouseX(), 
                    GetScreenHeight() - GetMouseY(), 
                    //8.0f, 
                    //8.0f,
                    GetRandomValue( 8, 28 ),
                    GetRandomValue( 8, 28 ),
                    ColorFromHSV( 360 - gw->dynamicRectanglesQuantity % 360, 1.0f, 1.0f ),
                    gw
                );
                gw->dynamicRectanglesQuantity++;
            }
        } else if ( IsKeyDown( KEY_LEFT_ALT ) ) {
            if ( gw->dynamicCapsulesQuantity < MAX_DYNAMIC_BODIES ) {
                createDynamicCapsule( 
                    &gw->dynamicCapsules[gw->dynamicCapsulesQuantity],
                    GetMouseX(), GetScreenHeight() - GetMouseY(), 
                    20, 0,
                    10,
                    ColorFromHSV( gw->dynamicCapsulesQuantity % 360, 1.0f, 1.0f ),
                    gw
                );
                gw->dynamicCapsulesQuantity++;
            }
        } else {
            if ( gw->dynamicCirclesQuantity < MAX_DYNAMIC_BODIES ) {
                createDynamicCircle( 
                    &gw->dynamicCircles[gw->dynamicCirclesQuantity],
                    GetMouseX(), 
                    GetScreenHeight() - GetMouseY(), 
                    4, 
                    //GetRandomValue( 4, 20 ),
                    ColorFromHSV( gw->dynamicCirclesQuantity % 360, 1.0f, 1.0f ),
                    gw
                );
                gw->dynamicCirclesQuantity++;
            }
        }
        
    }

}

void tryToCreateChain( GameWorld *gw ) {

    if ( !gw->finishedChain ) {

        if ( IsMouseButtonPressed( MOUSE_BUTTON_RIGHT ) ) {
            int q = gw->chainPointsQuantity;
            gw->chainPoints[q].x = GetMouseX();
            gw->chainPoints[q].y = GetScreenHeight() - GetMouseY();
            gw->chainPointsQuantity++;
        }

        if ( IsKeyPressed( KEY_ENTER ) ) {

            int q = gw->chainPointsQuantity;
            gw->chainPoints[q].x = gw->chainPoints[0].x;
            gw->chainPoints[q].y = gw->chainPoints[0].y;
            gw->chainPointsQuantity++;

            b2BodyDef bodyDef = b2DefaultBodyDef();
            bodyDef.type = b2_staticBody;
            b2BodyId bodyId = b2CreateBody( gw->worldId, &bodyDef );
            b2ChainDef chainDef = b2DefaultChainDef();

            chainDef.points = gw->chainPoints;
            chainDef.count = gw->chainPointsQuantity;
            b2CreateChain( bodyId, &chainDef );

            gw->finishedChain = true;

        }

    }

}

void tests( GameWorld *gw ) {

    if ( IsKeyDown( KEY_RIGHT ) ) {
        for ( int i = 0; i < gw->dynamicCapsulesQuantity; i++ ) {
            applyForceDynamicCapsule( &gw->dynamicCapsules[i] );
        }
    }

    if ( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
        if ( gw->dynamicCapsulesQuantity < MAX_DYNAMIC_BODIES ) {
            createDynamicCapsule( 
                &gw->dynamicCapsules[gw->dynamicCapsulesQuantity],
                GetMouseX(), GetScreenHeight() - GetMouseY(), 
                20, 0,
                10,
                ColorFromHSV( gw->dynamicCapsulesQuantity % 360, 1.0f, 1.0f ),
                gw
            );
            gw->dynamicCapsulesQuantity++;
        }
    }

}