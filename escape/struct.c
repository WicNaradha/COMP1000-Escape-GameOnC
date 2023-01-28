/* 
    Written by : W.M.Naradha
    Student ID : 20469160
    Date - Version_0: 03/Oct/2022 (Game Struct Implemented)
    Date - Version_0.1: 09/Oct/2022

    Handle Game Data Structs in the game
*/

#include "struct.h"

/**
    *@brief Function called to construct the game struct
    *@note  The function allocates memory and assigns it to the pointer given
    *@param input : pointer of to make game struct
    *@param data : pointer to array with game data
    *@retval void
*/

void makegamestruct(void *input, int *data)
{
    int r;
    int c;
    GameStruct *gstruct = (GameStruct*) input;

    /* Creating 3d-gamegrid array for game struct */
    gstruct->gamegrid = (int***)calloc(data[0],sizeof(int**));
    for (r=0; r<data[0]; r++)
    {
        gstruct->gamegrid[r] = (int**)calloc(data[1],sizeof(int*));
        for (c=0; c<data[1]; c++)
        {
            gstruct->gamegrid[r][c] = (int*)calloc(3,sizeof(int));
        }
    }

    /* Creating 2d-gamegrid char array for game struct */
    gstruct->strgrid = (char**)calloc(data[0],sizeof(char*));
    for (r=0; r<data[0]; r++)
    {
        gstruct->strgrid[r] = (char*)calloc(data[1],sizeof(char));
    }

    /* Creating data int array for game struct */
    gstruct->spec = (int*)calloc(8,sizeof(int));
    gstruct->spec[6] = NONE;
    gstruct->spec[7] = NONE;
    for (c=0; c < 6; c++)
    {
        gstruct->spec[c] = data[c];
    }
}

/**
    *@brief Function called to free the game struct
    *@note  The function frees allocated memory
    *@param input : pointer of to free game struct
    *@retval void
*/

void freegamestruct(void* input)
{
    int r;
    int c;
    GameStruct *gstruct = (GameStruct*) input;

    /* Free gamegrid array */
    for (r=0; r<gstruct->spec[0]; r++)
    {
        for (c=0; c<gstruct->spec[1]; c++)
        {
            free(gstruct->gamegrid[r][c]);
            gstruct->gamegrid[r][c] = NULL;
        }
        free(gstruct->gamegrid[r]);
        gstruct->gamegrid[r] = NULL;
    }
    free(gstruct->gamegrid);
    gstruct->gamegrid = NULL;

    /* Free strgrid array */
    for (r=0; r<gstruct->spec[0]; r++)
    {
        free(gstruct->strgrid[r]);
        gstruct->strgrid[r] = NULL;
    }
    free(gstruct->strgrid);
    gstruct->strgrid = NULL;

    free(gstruct->spec);
    gstruct->spec = NULL;

    free(gstruct);
    gstruct = NULL;
}

/**
    *@brief The function copies source struct data to the destination struct
    *@note  The function copies source struct data to the destination struct
    *@param source : pointer of to source game struct
    *@param destination : pointer of to destination game struct
    *@retval void
*/

void gamecopy(GameStruct* source, GameStruct* destination)
{
    int r;
    int c;
    int i;

    /* Copying 3d-gamegrid array for destination struct */
    for (r=0; r<source->spec[0]; r++)
    {
        for (c=0; c<source->spec[1]; c++)
        {
            for (i=0; i<3; i++)
            {
                destination->gamegrid[r][c][i] = source->gamegrid[r][c][i];
            }
        }
    }

    /* Copying 2d-strgrid array for destination struct */
    for (r=0; r<source->spec[0]; r++)
    {
        for (c=0; c<source->spec[1]; c++)
        {
            destination->strgrid[r][c] = source->strgrid[r][c];
        }
    }

    /* Copying data variables to destination data array */
    for (i = 0; i < 8; i++)
    {
        destination->spec[i] = source->spec[i];
    }
}

/**
    *@brief The function to complete repitive actions in game.c
    *@note  The function to complete repitive actions in game.c
    *@param source : pointer to game struct
    *@retval GameStruct*
*/

GameStruct* GameStructHandle(GameStruct* gstruct)
{
    GameStruct* dest = (GameStruct*)calloc(1,sizeof(GameStruct));
    
    makegamestruct(dest,gstruct->spec);
    gamecopy(gstruct,dest);

    return(dest);
}

/**
    *@brief The function to read as game struct in game.c
    *@note  The function to read as game struct in game.c
    *@param source : pointer to game struct
    *@retval GameStruct*
*/

/* PERF: NOT USED IN THE GAME (MEANINGLESS) */

GameStruct* readasGstruct(void* gstruct)
{
    return ((GameStruct*) gstruct);
}
