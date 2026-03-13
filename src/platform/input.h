#ifndef input_h
#define input_h

#include <stdbool.h>
#include <core/vector.h>
#include "platform/gameState.h"

typedef struct {
    bool hasChanged;
    Vector3 keyMovement;
    Vector2 mouseMovement;
} inputData;

extern inputData* pInput;
void initInput();
void updateInput();

#endif