/* 
    Written by : W.M.Naradha
    Student ID : 20469160
    Date - Version_0: 24/Aug/2022
    Date - Version_0.1: 03/Sep/2022
    Date - Version_1.0 : 25/Sep/2022
    Date - Version_1.1 : 03/Oct/2022
    Date - Version_1.2 : 10/Oct/2022

    Contains main code
*/

#include "game.h"

/**
    *@brief Entry point of the program
    *@note  Entry point of the program
    *@retval int: success status
*/

int main(int argc, char *argv[])
{
    int i, currframe; /* for iterators */
    int game = GAME; /* holds the game state */
    
    int *pos;
    int *data = (int*)calloc(6,sizeof(int)); /* game data array */
    char *dir = (char*)calloc(1,sizeof(char)); /* direction pointer */
    char **argarray = (char**)calloc(6,sizeof(char*)); /* system arguments */

    /* handle -> pointer to dynamic mem used for linked list */
    /* currstruct -> pointer to current struct shown in game */
    GameStruct *handle, *currstruct; 

    /* datalist -> consists of all data variables read from the input file */
    /* xlist -> positions of collapsed floors from the datalist */
    /* hist -> history list of the game */
    ListHead *datalist, *xlist = makelist(), *hist;
    
    /* Required to Handle the list inside the list! - Why did i do this??*/
    ListHead *temp; /* To take data from the list inside the list */
    ListNode *node; /* To move and assign data from it */

    void (*gstructfree)(void*);
    void (*basefree)(void*);


    gstructfree = &freegamestruct;
    basefree = &free;

    currframe = 0;

    /* Initialise Random */
    initRandom();

    /* Reading from the data file. */
    if (argc == 2)
    {
        datalist = readfile(argv[1]); /* Assigning file data to datalist */
    }
    else
    {
        /* Invalid Arguments */
        game = ERROR;
        printf("ERROR: INSUFFICIENT INPUT ARGS!\n");
    }

    if (*((int*) (((ListHead*) (datalist->head)->data)->head->data)) != -1)
    {
        node = datalist->head; /* Using node to access the lists inside the datalist */
        i = 0;
        while(i < datalist->size)
        {
            temp = ((ListHead*) (node->data)); /* Casting to list type */
            if (temp->size == 3)
            {
                if (*((char*) readatlist(temp,3)) == 'P')
                {
                    /* Assigning Player Postion */
                    data[2] = *((int*) readatlist(temp,1)); 
                    data[3] = *((int*) readatlist(temp,2));
                }
                else if (*((char*) readatlist(temp,3)) == 'G')
                {
                    /* Assigning Goal Position */
                    data[4] = *((int*) readatlist(temp,1));
                    data[5] = *((int*) readatlist(temp,2));
                }
                else if (*((char*) readatlist(temp,3)) == 'X')
                {
                    /* Assigning Collapsed Floor Positions into Xlist */
                    pos = (int*)calloc(2,sizeof(int));
                    pos[0] = *((int*) readatlist(temp,1));
                    pos[1] = *((int*) readatlist(temp,2));
                    appendlist(xlist,pos);
                }
            }
            else if (temp->size == 2)
            {
                /* Defining row and col size of game map */
                data[0] = *((int*) readatlist(temp,1));
                data[1] = *((int*) readatlist(temp,2));
            }
            node = node->next;
            i++;
        }
    }
    else
    {
        game = ERROR;
        printf("ERROR: Could not open %s\n",argv[1]);
    }

    /* Error Checking to stop possible seg-faults */
    if ((data[2] >= data[0])||(data[3] >= data[1])||(data[2] < 0)||(data[3] < 0))
    {
        game = ERROR;
        printf("ERROR: Player Out of Bounds | Defined ROW:(0:%d) COL:(0:%d)!\n",(data[0]-1),(data[1]-1));
    }

    if ((data[4] >= data[0])||(data[5] >= data[1])||(data[4] < 0)||(data[5] < 0))
    {
        game = ERROR;
        printf("ERROR: Goal Out of Bounds | Defined ROW:(0:%d) COL:(0:%d)!\n",(data[0]-1),(data[1]-1));
    }

    if ((data[0] < 5)||(data[1] < 5))
    {
        game = ERROR;
        printf("ERROR: Invalid Border Size! | MIN_SIZE:5\n");
    }

    i = 0;
    while(i < xlist->size)
    {
        if ((((int*) readatlist(xlist,(i+1)))[0] > data[0]) || (((int*) readatlist(xlist,(i+1)))[0] < 0))
        {
            game = ERROR;
            printf("ERROR: X Out of Bounds | Defined POS:(%d:%d)!\n",(((int*) readatlist(xlist,(i+1)))[0]),(((int*) readatlist(xlist,(i+1)))[1]));
        }
        if ((((int*) readatlist(xlist,(i+1)))[1] > data[1]) || (((int*) readatlist(xlist,(i+1)))[1] < 0))
        {
            game = ERROR;
            printf("ERROR: X Out of Bounds | Defined POS:(%d:%d)!\n",(((int*) readatlist(xlist,(i+1)))[0]),(((int*) readatlist(xlist,(i+1)))[1]));
        }
        i++;
    }

    /* Game Start */
    if (game != ERROR)
    {
        /* make game grid */
        currstruct = (GameStruct*)calloc(1,sizeof(GameStruct));
        makegamestruct(currstruct,data);

        /* make linked list */
        hist = makelist();

        /* setup grid for start */
        currstruct->gamegrid[(data[2])][(data[3])][0] = TRUE; /* Assign Player Location */
        currstruct->gamegrid[(data[4])][(data[5])][1] = TRUE; /* Assign Goal Location */

        /* Assign Collapsed Floors from text file data */
        i = 0;
        while(i < xlist->size)
        {
            currstruct->gamegrid[((int*) readatlist(xlist,(i+1)))[0]][((int*) readatlist(xlist,(i+1)))[1]][2] = TRUE;
            i++;
        }

        /* setup grid for start */
        genstring(currstruct,&game);
        handle = GameStructHandle(currstruct);
        appendlist(hist,handle);
        currframe++;

        /* Running game until non-game condition is acheived*/
        while (game <= BLOCK)
        {
            printgame(currstruct,&game);
            readkey(dir);

            /* Check for invalid Keystrokes */
            if ((*dir == 'w')||(*dir == 'a')||(*dir == 's')||(*dir == 'd')||(*dir == 'q')||(*dir == 'u')||(*dir == 'r'))
            {
                game = GAME;
            }
            else
            {
                game = INVALID;
            }

            /* Do user input activity on grid/gamestate */
            if ((*dir == 'q') && (game != INVALID))
            {
                game = EXIT;
            }
            /* Undo Move */
            else if (*dir == 'u')
            {
                if ((currframe <= hist->size) && (currframe > 1)) /* To not undo beyond the last frame */
                {
                    currframe--; /* update currframe value */
                    gamecopy((GameStruct*) readatlist(hist,currframe),currstruct); /* Request the currframe from list */
                }
                else
                {
                    gamecopy((GameStruct*) readatlist(hist,1),currstruct); /* Request the last frame from list */
                    game = UBLOCK;
                }

            }
            /* Redo Move */
            else if (*dir == 'r') 
            {
                if ((currframe < (hist->size)) && (currframe >= 1)) /* To not redo beyond the most recent frame */
                {
                    currframe++; /* update currframe value */
                    gamecopy((GameStruct*) readatlist(hist,currframe),currstruct); /* Request the currframe from list */
                }
                else
                {
                    gamecopy((GameStruct*) readatlist(hist,hist->size),currstruct); /* Request the last frame from list */
                    game = RBLOCK;
                }
            }
            else if (game != INVALID)
            {
                /* Removing Undo-Redo Action Frames from the list */
                while(hist->size > currframe)
                {
                    freenodelast(hist, gstructfree); /* Free List Items of Undo-Redo */
                }

                /* Update Currframe pos and hist */
                update_grid(currstruct,&game,*dir);
                genstring(currstruct,&game);
                currframe++;
                handle = GameStructHandle(currstruct);
                appendlist(hist, handle);
            }
        }

        /* Generating and printing final outcome */
        genstring(currstruct,&game);
        printgame(currstruct,&game);
        
        /* Free currstruct */
        freegamestruct(currstruct);

        /* Free list */
        freelist(hist, gstructfree);
    }
    else /* In the case of an error */
    {
        printf("ERROR: Invalid input arguments or map size!\n");
        printf("Usage: ./escape datafile.txt\n");
    }
    
    /* Free Data list */
    node = datalist->tail;
    i = 0;
    while(i < datalist->size)
    {
        temp = ((ListHead*) (node->data)); /* Accessing List inside the List */
        freelist(temp,basefree); /* Free List in the list */
        node->data = NULL;  /* Release data pointer of datalist node */
        node = node->prev;  /* Move to next node */
        i++; 
    }
    freelist(datalist,basefree); /* Free Empty datalist */
    datalist = NULL;

    /* Free Xlist */
    freelist(xlist,basefree);
    xlist = NULL; 

    /* Free data */
    free(data);
    data = NULL;

    /* Free dir */
    free(dir);
    dir = NULL;

    /* Free argarray */
    free(argarray);
    argarray = NULL;

    return 0;
}