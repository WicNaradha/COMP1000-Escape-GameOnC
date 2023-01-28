/* 
    Written by : W.M.Naradha
    Student ID : 20469160
    Date - Version_0: 24/Aug/2022
    Date - Version_0.1: 03/Sep/2022

    Handle Grids in the game
    Grid Player Updates
    Random Floor falling in Grid
*/

#include "grids.h"

/**
    *@brief The moving function (Both Borderless and Border is inside)
    *@note  Last function called within this file to move the player
    *@param grid : pointer to 3d grid of the game
    *@param game : pointer to game state
    *@param row : row size
    *@param col : col size
    *@param r : player row position
    *@param c : player col position
    *@param dir : movement direction
    *@retval void
*/

static void move_pos(int ***grid, int *game, int row, int col, int r, int c, char dir)
{
    int old_row = r;
    int old_col = c;

    /* This TODO was not attempted as of now */
    /* TODO: Change this to a function pointer which chooses between the border types!*/

    /* Bordereless Move
        The switch case will alter the r and c variable to the new position
    */
    #ifdef BORDERLESS
    switch (dir)
    {
       case 'w' : 
            if (r > 0)
            {
                r--;
            }
            else
            {
                r = (row-1);
            }
            break;
        case 's' :
            if (r < (row-1))
            {
                r++;        
            }
            else
            {
                r = 0;
            }
            break;
        case 'a' :
            if (c > 0)
            {
                c--;        
            }
            else
            {
                c = (col-1);
            }
            break;
        case 'd' :
            if (c < (col-1))
            {
                c++;        
            }
            else
            {
                c = 0;
            }
            break;
    }
    /* Bordered Move
        The switch case will alter the r and c variable to the new position
    */
    #else
    switch(dir)
    {
        case 'w' : 
            if (r > 0)
            {
                r--;
            }
            else
            {
                *game = BLOCK;
            }
            break;
        case 's' :
            if (r < (row-1))
            {
                r++;        
            }
            else
            {
                *game = BLOCK;
            }
            break;
        case 'a' :
            if (c > 0)
            {
                c--;        
            }
            else
            {
                *game = BLOCK;
            }
            break;
        case 'd' :
            if (c < (col-1))
            {
                c++;        
            }
            else
            {
                *game = BLOCK;
            }
            break;
    }
    #endif

    /* For Debugging Purposes: */
    /* printf("%d,%d ",r,c); */

    /* Moving the player */
    /* Checking for a collapsed floor */
    if (grid[r][c][2] == TRUE)
    {
        *game = BLOCK;
    }
    /* Changing Player Position in a winning move to new position */
    else if (grid[r][c][1] == TRUE)
    {
        *game = WIN;
        grid[old_row][old_col][0] = FALSE;
        grid[r][c][0] = TRUE;
    }
    /* Changing Player Position in a regular move to new one */
    else
    {
        grid[old_row][old_col][0] = FALSE;
        grid[r][c][0] = TRUE;
    }
}

/**
    *@brief Function to acheive randomly collapsing floor
    *@note  It collapses the floor when called by checking for player and goal.
    *@param grid : pointer to 3d grid of the game
    *@param row : row size
    *@param col : col size
    *@retval void
*/

static void collapse_floor(GameStruct *gstruct, int row, int col)
{
    int r;
    int c;
    int ***grid = gstruct->gamegrid;
    int collapsed = FALSE;

    /* Checking for if a floor was collapsed*/
    while (collapsed == FALSE)
    {
        /* Generating random row and col */
        r = random(0,row-1);
        c = random(0,col-1);

        /* Checking for player, goal or already collapsed floor in random cell */
        if ((grid[r][c][0] == FALSE)&&(grid[r][c][1] == FALSE)&&(grid[r][c][2] == FALSE))
        {
            /* If non collpsing the floor */
            grid[r][c][2] = TRUE;
            gstruct->spec[6] = r;
            gstruct->spec[7] = c;
            collapsed = TRUE;
        }
    }
}

/**
    *@brief Function to check loosing condition
    *@note  The function checks for player and goal based loosing cond
    *@param grid : pointer to 3d grid of the game
    *@param game : pointer to game state
    *@param row : row size
    *@param col : col size
    *@param r : player row position
    *@param c : player col position
    *@retval void
*/

static void gamecheck(int ***grid, int *game, int r, int c, int row, int col)
{
    int i;
    int count = 0;

    /* The iterator checks for the four sides */
    for (i=0;i<4;i++)
    {
        /* BORDERLESS: Check
            In this condition it checks across borders
        */
        #ifdef BORDERLESS
        switch (i)
        {
        case 0:
            if ((r-1)<0)
            {
                if (grid[row-1][c][2] == TRUE)
                {
                    count++;
                }
            }
            else if (grid[r-1][c][2] == TRUE)
            {
                count++;
            }
            break;
        case 1:
            if ((c-1)<0)
            {
                if (grid[r][col-1][2] == TRUE)
                {
                    count++;
                }
            }
            else if (grid[r][c-1][2] == TRUE)
            {
                count++;
            }
            break;
        case 2:
            if ((r+1)>(row-1))
            {
                if (grid[0][c][2] == TRUE)
                {
                    count++;
                }
            }
            else if (grid[r+1][c][2] == TRUE)
            {
                count++;
            }
            break;
        case 3:
            if ((c+1)>(col-1))
            {
                if (grid[r][0][2] == TRUE)
                {
                    count++;
                }
            }
            else if (grid[r][c+1][2] == TRUE)
            {
                count++;
            }
            break;
        default:
            break;
        }
        /* BORDERED: Check
            In this condition the border itself satisfies a blocked face.
        */
        #else
        switch (i)
        {
        case 0:
            if ((r-1)<0)
            {
                count++;
            }
            else if (grid[r-1][c][2] == TRUE)
            {
                count++;
            }
            break;
        case 1:
            if ((c-1)<0)
            {
                count++;
            }
            else if (grid[r][c-1][2] == TRUE)
            {
                count++;
            }
            break;
        case 2:
            if ((r+1)>(row-1))
            {
                count++;
            }
            else if (grid[r+1][c][2] == TRUE)
            {
                count++;
            }
            break;
        case 3:
            if ((c+1)>(col-1))
            {
                count++;
            }
            else if (grid[r][c+1][2] == TRUE)
            {
                count++;
            }
            break;
        default:
            break;
        }
        #endif
    }

    /* Provides tha game condition of Defeat */
    if (count==4)
    {
        *game = LOSE;
    }
}

/**
    *@brief Function called by game to update the gamegrid
    *@note  The function updates the gamegrid for every user input
    *@param grid : pointer to 3d grid of the game
    *@param game : pointer to game state
    *@param data : array consisting of grid size, player and goal loc
    *@param dir : movement direction
    *@retval void
*/

void update_grid(GameStruct *gstruct, int *game, char dir)
{
    /* TODO: Use data and update its player and goal position directly */
    int row = gstruct->spec[0];
    int col = gstruct->spec[1]; 

    int r; /* row iterator */
    int c; /* col iterator */

    int move = FALSE; /* Control Variable to make move only happen once */

    /*  Loop to Update Grid
        Finding Player to update Player
        Finding Goal to Update Goal
        Checking for Game Condition as well
    */
    for(r = 0; r < row; r++)
    {
        for (c=0; c < col; c++)
        {
            /* For player update player postion and check game state */
            if ((gstruct->gamegrid[r][c][0] == TRUE)&&(move == FALSE))
            {
                move_pos(gstruct->gamegrid,game,row,col,r,c,dir);
                gamecheck(gstruct->gamegrid,game,r,c,row,col);
                move = TRUE;
            }
            /* For goal check game state */
            if (gstruct->gamegrid[r][c][1] == TRUE)
            {
                gamecheck(gstruct->gamegrid,game,r,c,row,col);
            }
        }
    }

    /* For game not in Block condition (Moving into collapsed floor or wall) */
    if (*game < BLOCK)
    {
        collapse_floor(gstruct,row,col);
    }
}

/**
    *@brief Function called by game to update the grid string
    *@note  The function recreates the grid string to be shown to user
    *@param grid : pointer to 3d grid of the game
    *@param strgrid : pointer to game grid string (To Be Displayed)
    *@param data : array consisting of grid size, player and goal loc
    *@retval void
*/

void genstring(GameStruct* gstruct, int* game)
{
    int r; /* row iterator */
    int c; /* col iterator */
    int ***grid = gstruct->gamegrid;
    char **strgrid = gstruct->strgrid;
    int *data = gstruct->spec;

    for (r=0;r<data[0];r++)
    {
        for (c=0;c<data[1];c++)
        {
            /* Showing the win on the grid */
            if ((grid[r][c][0] == TRUE)&&(grid[r][c][1] == TRUE))
            {
                strgrid[r][c] = 'W';                
            }
            /* Showing the Player on the grid */
            else if (grid[r][c][0] == TRUE)
            {
                strgrid[r][c] = 'P';
            }
            /* Showing the Goal on the grid */
            else if ((grid[r][c][1] == TRUE) && (*game == LOSE))
            {
                strgrid[r][c] = 'L';
            }
            else if (grid[r][c][1] == TRUE)
            {
                strgrid[r][c] = 'G';
            }            
            /* Showing the Collapsed Floor on the grid */
            else if (grid[r][c][2] == TRUE)
            {
                if ((gstruct->spec[6] == r) && (gstruct->spec[7] == c))
                {
                    strgrid[r][c] = 'x';
                }
                else
                {
                    strgrid[r][c] = 'X';
                }
            }
            /* Showing an empty space for empty grid locations */
            else
            {
                strgrid[r][c] = ' ';
            }
        }
    }
}