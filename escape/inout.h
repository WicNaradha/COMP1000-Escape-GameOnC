#ifndef INOUT_H
#define INOUT_H

#include "terminal.h"
#include "list.h"
#include "color.h"
#include "struct.h"
#include "macros.h"

#define CTRL_STRNG "w - move up\ns - move down\na - move left\nd - move right\n"

/* Forward Declerations */
void strint(char **string, int *outint, int len);
ListHead* readfile(char* filename);
void printgame(GameStruct *gstruct, int *game);
void readkey(char *dir);

#endif