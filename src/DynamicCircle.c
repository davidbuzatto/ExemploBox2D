#include <stdio.h>
#include <stdlib.h>

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#include "DynamicCircle.h"
#include "Types.h"

/*

Na Box2D (tanto na versão original C++ quanto nessa reimplementada em C), as formas (b2Polygon, b2Circle, etc.) são posicionadas relativamente ao centro do corpo ao qual elas estão associadas.

Ou seja, quando você define:

b2BodyDef cBodyDef = b2DefaultBodyDef();
cBodyDef.position = (b2Vec2){ WORLD_SIZE / 2 + 40, WORLD_SIZE / 2 };
Você está dizendo: "meu corpo está no mundo, nessa posição global".

E depois, ao fazer:
b2Circle cCircle = (b2Circle){ { cBodyDef.position.x, cBodyDef.position.y }, cRad };
Você acaba definindo o centro da forma (o círculo) como estando ainda mais longe, porque esse centro é relativo ao corpo. Então no fim, a forma acaba posicionada no mundo em:

posição do corpo + posição do centro do círculo
E isso desloca o círculo para um ponto bem longe do que você vê na tela. Por isso não colidia com nada — a colisão até estava acontecendo, mas em um lugar invisível!

Qual é o jeito certo?
Se você quiser que a forma fique centralizada no corpo (caso mais comum), deve passar { 0.0f, 0.0f } como centro do b2Circle. Assim:

b2Circle cCircle = (b2Circle){ { 0.0f, 0.0f }, cRad };
Então a Box2D entende: "ok, vou colocar o círculo no mesmo lugar que o corpo", e aí ele se comporta como esperado.

Dica conceitual
Você pode imaginar o b2Body como uma "origem de coordenadas local" para as formas.
Então sempre que você cria uma forma, está dizendo "coloque essa forma a X unidades à direita/esquerda e Y unidades acima/abaixo do centro do corpo".

Isso permite que um corpo tenha várias formas, em posições diferentes, compondo coisas mais complexas — tipo um boneco com tronco, cabeça, braços etc.

https://chatgpt.com/share/67f41f8c-e3d4-8012-8545-b5cf40f5ef70

*/
void createDynamicCircle( DynamicCircle* newCircle, float x, float y, float r, Color color, GameWorld *gw ) {

    newCircle->radius = r;

    // posição global
    newCircle->bodyDef = b2DefaultBodyDef();
    newCircle->bodyDef.type = b2_dynamicBody;
    newCircle->bodyDef.position = (b2Vec2){ x, y };
    newCircle->bodyDef.fixedRotation = true;
    newCircle->bodyId = b2CreateBody( gw->worldId, &newCircle->bodyDef );
    
    // posição local relativa ao corpo
    newCircle->circle = (b2Circle){ { 0.0f, 0.0f }, r };

    newCircle->shapeDef = b2DefaultShapeDef();
    newCircle->shapeDef.density = 1.0f;
    newCircle->shapeDef.friction = 0.3f;

    newCircle->shapeId = b2CreateCircleShape( newCircle->bodyId, &newCircle->shapeDef, &newCircle->circle );

    newCircle->color = color;

}

void drawDynamicCircle( DynamicCircle *circle ) {

    b2Vec2 position = b2Body_GetPosition( circle->bodyId );

    DrawCircle( 
        position.x, 
        -position.y, 
        circle->radius,  
        circle->color );
    
}