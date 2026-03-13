#ifndef gamestate_h
#define gamestate_h

typedef enum {
    STATE_LOADING = 1,
    STATE_RUNNING,
    STATE_STOP
} gameState;

extern gameState* pGameState;
void initGameState();

#endif