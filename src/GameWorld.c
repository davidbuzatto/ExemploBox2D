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
#include "DynamicSquare.h"

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
    gw->squareQuantity = 0;
    
    float cx = GetScreenWidth() / 2;
    float cy = GetScreenHeight() / 2;
    float rWidth = 10.0f;

    gw->ground = createRigidSquare( cx, -GetScreenHeight() + rWidth / 2, GetScreenWidth(), rWidth, BLACK, gw );
    gw->leftWall = createRigidSquare( rWidth / 2, -cy, rWidth, GetScreenHeight(), BLACK, gw );
    gw->rightWall = createRigidSquare( GetScreenWidth() - rWidth / 2, -cy, rWidth, GetScreenHeight(), BLACK, gw );

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {

    b2DestroyWorld( gw->worldId );

    destroyRigidSquare( gw->ground );

    for ( int i = 0; i < gw->squareQuantity; i++ ) {
        destroyDynamicSquare( gw->squares[i] );
    }

    free( gw );

}

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta ) {

    if ( gw->squareQuantity < MAX_SQUARE_QUANTITY ) {
        if ( IsMouseButtonDown( MOUSE_BUTTON_LEFT ) ) {
            gw->squares[gw->squareQuantity] = createDynamicSquare( 
                GetMouseX(), 
                -GetMouseY(), 
                8.0f, 
                8.0f, 
                ColorFromHSV( gw->squareQuantity % 360, 1.0f, 1.0f ),
                gw
            );
            gw->squareQuantity++;
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

    drawRigidSquare( gw->ground );
    drawRigidSquare( gw->leftWall );
    drawRigidSquare( gw->rightWall );

    for ( int i = 0; i < gw->squareQuantity; i++ ) {
        drawDynamicSquare( gw->squares[i] );
    }

    DrawFPS( 20, 20 );
    DrawText( TextFormat( "Squares: %d", gw->squareQuantity ), 20, 40, 20, BLACK );

    EndDrawing();

}