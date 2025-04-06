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
#include "RigidSquare.h"
#include "RigidCircle.h"
#include "DynamicSquare.h"
#include "DynamicCircle.h"

#include "raylib/raylib.h"
#include "raylib/rlgl.h"

#include "box2d/box2d.h"

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->worldDef = b2DefaultWorldDef();
    gw->worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    gw->worldId = b2CreateWorld( &gw->worldDef );

    gw->rigidSquareQuantity = 0;
    gw->dynamicSquareQuantity = 0;
    gw->dynamicCircleQuantity = 0;
    
    float cx = GetScreenWidth() / 2;
    float cy = GetScreenHeight() / 2;
    float rWidth = 10.0f;

    createRigidSquare( &gw->rigidSquares[gw->rigidSquareQuantity], cx, -GetScreenHeight() + rWidth / 2, GetScreenWidth(), rWidth, BLACK, gw );
    gw->rigidSquareQuantity++;
    createRigidSquare( &gw->rigidSquares[gw->rigidSquareQuantity], rWidth / 2, -cy, rWidth, GetScreenHeight(), BLACK, gw );
    gw->rigidSquareQuantity++;
    createRigidSquare( &gw->rigidSquares[gw->rigidSquareQuantity], GetScreenWidth() - rWidth / 2, -cy, rWidth, GetScreenHeight(), BLACK, gw );
    gw->rigidSquareQuantity++;

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

    if ( IsMouseButtonDown( MOUSE_BUTTON_LEFT ) ) {
        /*if ( gw->dynamicSquareQuantity < MAX_DYNAMIC_SQUARES ) {
            createDynamicSquare( 
                &gw->dynamicSquares[gw->dynamicSquareQuantity],
                GetMouseX(), 
                -GetMouseY(), 
                //8.0f, 
                //8.0f,
                GetRandomValue( 8, 28 ),
                GetRandomValue( 8, 28 ),
                ColorFromHSV( gw->dynamicSquareQuantity % 360, 1.0f, 1.0f ),
                gw
            );
            gw->dynamicSquareQuantity++;
        }*/
        if ( gw->dynamicCircleQuantity < MAX_DYNAMIC_CIRCLES ) {
            createDynamicCircle( 
                &gw->dynamicCircles[gw->dynamicCircleQuantity],
                GetMouseX(), 
                -GetMouseY(), 
                //GetRandomValue( 4, 14 ), 
                4, 
                ColorFromHSV( gw->dynamicCircleQuantity % 360, 1.0f, 1.0f ),
                gw
            );
            gw->dynamicCircleQuantity++;
        }
    }

    if ( IsMouseButtonPressed( MOUSE_BUTTON_RIGHT ) ) {
        if ( gw->rigidSquareQuantity < MAX_RIGID_SQUARES ) {
            createRigidSquare( 
                &gw->rigidSquares[gw->rigidSquareQuantity],
                GetMouseX(), 
                -GetMouseY(), 
                8.0f, 
                8.0f, 
                BLACK,
                gw
            );
            gw->rigidSquareQuantity++;
        }
    }

    int subStepCount = 4;
    b2World_Step( gw->worldId, delta, subStepCount );

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    //rlTranslatef( 200, 200, 0 );
    //rlScalef( 2, 2, 1 );

    for ( int i = 0; i < gw->rigidSquareQuantity; i++ ) {
        drawRigidSquare( &gw->rigidSquares[i] );
    }

    for ( int i = 0; i < gw->dynamicSquareQuantity; i++ ) {
        drawDynamicSquare( &gw->dynamicSquares[i] );
    }

    for ( int i = 0; i < gw->dynamicCircleQuantity; i++ ) {
        drawDynamicCircle( &gw->dynamicCircles[i] );
    }

    DrawFPS( 20, 20 );
    DrawText( TextFormat( "Squares: %d", gw->dynamicSquareQuantity ), 20, 40, 20, BLACK );

    EndDrawing();

}