#ifndef STRUCT_H
#define STRUCT_H

#include "macros.h"
/* Struct Declerations */
typedef struct GameStruct{
    int *spec;
    int ***gamegrid;
    char **strgrid;
} GameStruct;


/* Forward Declerations */
void makegamestruct(void *input, int *data);
void freegamestruct(void *gstruct);
void gamecopy(GameStruct* source, GameStruct* destination);
GameStruct* GameStructHandle(GameStruct* gstruct);
GameStruct* readasGstruct(void* gstruct);

#endif