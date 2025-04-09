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
#include "StaticSquare.h"
#include "StaticCircle.h"
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
    gw->worldDef.gravity = (b2Vec2){ 0.0f, -10.0f };
    gw->worldId = b2CreateWorld( &gw->worldDef );

    gw->staticSquareQuantity = 0;
    gw->dynamicSquareQuantity = 0;

    gw->staticCircleQuantity = 0;
    gw->dynamicCircleQuantity = 0;
    
    float cx = GetScreenWidth() / 2;
    float cy = GetScreenHeight() / 2;
    float rWidth = 10.0f;

    createStaticSquare( &gw->staticSquares[gw->staticSquareQuantity], cx, rWidth / 2, GetScreenWidth(), rWidth, BLACK, gw );
    gw->staticSquareQuantity++;
    createStaticSquare( &gw->staticSquares[gw->staticSquareQuantity], rWidth / 2, cy, rWidth, GetScreenHeight(), BLACK, gw );
    gw->staticSquareQuantity++;
    createStaticSquare( &gw->staticSquares[gw->staticSquareQuantity], GetScreenWidth() - rWidth / 2, cy, rWidth, GetScreenHeight(), BLACK, gw );
    gw->staticSquareQuantity++;

    /*createStaticCircle( &gw->staticCircles[gw->staticCircleQuantity], cx, cy, 30, BLACK, gw );
    gw->staticCircleQuantity++;*/

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
        //if ( IsKeyDown( KEY_LEFT_CONTROL ) ) {
            if ( gw->dynamicCircleQuantity < MAX_DYNAMIC_CIRCLES ) {
                createDynamicCircle( 
                    &gw->dynamicCircles[gw->dynamicCircleQuantity],
                    GetMouseX(), 
                    GetScreenHeight() - GetMouseY(), 
                    //4, 
                    GetRandomValue( 4, 20 ),
                    ColorFromHSV( gw->dynamicCircleQuantity % 360, 1.0f, 1.0f ),
                    gw
                );
                gw->dynamicCircleQuantity++;
            }
        //} else {
            if ( gw->dynamicSquareQuantity < MAX_DYNAMIC_SQUARES ) {
                createDynamicSquare( 
                    &gw->dynamicSquares[gw->dynamicSquareQuantity],
                    GetMouseX(), 
                    GetScreenHeight() - GetMouseY(), 
                    //8.0f, 
                    //8.0f,
                    GetRandomValue( 8, 28 ),
                    GetRandomValue( 8, 28 ),
                    ColorFromHSV( 360 - gw->dynamicSquareQuantity % 360, 1.0f, 1.0f ),
                    gw
                );
                gw->dynamicSquareQuantity++;
            }
        //}
    }

    if ( IsMouseButtonPressed( MOUSE_BUTTON_RIGHT ) ) {
        if ( IsKeyDown( KEY_LEFT_CONTROL ) ) {
            if ( gw->staticSquareQuantity < MAX_STATIC_SQUARES ) {
                if ( gw->staticCircleQuantity < MAX_STATIC_CIRCLES ) {
                    createStaticCircle( 
                        &gw->staticCircles[gw->staticCircleQuantity],
                        GetMouseX(), 
                        GetScreenHeight() - GetMouseY(), 
                        8.0f, 
                        BLACK,
                        gw
                    );
                    gw->staticCircleQuantity++;
                }
            }
        } else {
            createStaticSquare( 
                &gw->staticSquares[gw->staticSquareQuantity],
                GetMouseX(), 
                GetScreenHeight() - GetMouseY(), 
                16.0f, 
                16.0f, 
                BLACK,
                gw
            );
            gw->staticSquareQuantity++;
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

    rlTranslatef( 0, GetScreenHeight(), 0 );
    //rlScalef( 2, 2, 1 );

    for ( int i = 0; i < gw->staticSquareQuantity; i++ ) {
        drawStaticSquare( &gw->staticSquares[i] );
    }

    for ( int i = 0; i < gw->staticCircleQuantity; i++ ) {
        drawStaticCircle( &gw->staticCircles[i] );
    }

    for ( int i = 0; i < gw->dynamicSquareQuantity; i++ ) {
        drawDynamicSquare( &gw->dynamicSquares[i] );
    }
    
    for ( int i = 0; i < gw->dynamicCircleQuantity; i++ ) {
        drawDynamicCircle( &gw->dynamicCircles[i] );
    }

    DrawFPS( 20, -GetScreenHeight() + 20 );
    DrawText( TextFormat( "Squares: %d", gw->dynamicSquareQuantity ), 20, -GetScreenHeight() + 40, 20, BLACK );
    DrawText( TextFormat( "Circles: %d", gw->dynamicCircleQuantity ), 20, -GetScreenHeight() + 60, 20, BLACK );

    EndDrawing();

}