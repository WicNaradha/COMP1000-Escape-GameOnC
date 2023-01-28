#ifndef GRID_H
#define GRID_H

#include "random.h"
#include "struct.h"
#include "macros.h"

/* Forward Declerations */
void update_grid(GameStruct *gstruct, int *game, char dir);
void genstring(GameStruct* gstruct, int* game);

#endif