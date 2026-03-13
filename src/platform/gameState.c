#include "platform/gameState.h"
gameState currentGameState;
gameState* pGameState;

void initGameState()
{
    currentGameState = STATE_LOADING;
    pGameState = &currentGameState;
}