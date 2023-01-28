/* 
    Written by : W.M.Naradha
    Student ID : 20469160
    Date - Version_0: 24/Aug/2022
    Date - Version_0.1: 03/Sep/2022

    Contains input and output functions
*/

#include "inout.h"

static void borderprint()
{
    #ifdef BORDERLESS
    setForeground("blue",'0');
    printf("*");
    setForeground("reset",0);
    #else
    setForeground("red",'0');
    printf("*");
    setForeground("reset",0);
    #endif
}

/**
    *@brief Function to print the game char in color
    *@note  The function is called by the print game to pring game char
    *@param string : array of string
    *@param r : current row of char
    *@param c : current col of char
    *@retval void
*/

static void printchar(char **string,int r,int c)
{
    if (string[r][c] == 'P')
    {
        setForeground("blue",'0');
    }
    else if (string[r][c] == 'G')
    {
        setForeground("green",'0');
    }
    else if (string[r][c] == 'W')
    {
        setForeground("magenta",'1');
    }
    else if (string[r][c] == 'L')
    {
        setForeground("red",'1');
    }
    else if (string[r][c] == 'X')
    {
        setForeground("yellow",'0');
    }
    else if (string[r][c] == 'x')
    {
        setForeground("yellow",'0');
        setBackground("red");
        string[r][c] = 'X';
    /* TODO: Add the BG Colour Changing Code! */   
    }
    printf("%c",string[r][c]);
    setForeground("reset",0);
}

ListHead* readfile(char* filename)
{
    FILE* file;
    int r = 0, c = 0, eof = 0;
    char t;
    int *pntnum;
    char *pnttxt; 
    ListHead *inlist = makelist(), *datalist = makelist();
    void (*freefunc)(void*);
    freefunc = &free;
    file = fopen(filename,"r");

    if (file == NULL)
    {
        /* printf("ERROR: Could not open %s\n",filename); */
        pntnum = (int*)calloc(1,sizeof(int));
        *pntnum = -1;
        appendlist(inlist,pntnum);

        appendlist(datalist,movelistdata(inlist));
        clearlist(inlist);
    }
    else
    {
        eof = fscanf(file, "%d %d", &r, &c);
        
        pntnum = (int*)calloc(1,sizeof(int));
        *pntnum = r;
        appendlist(inlist,pntnum);

        pntnum = (int*)calloc(1,sizeof(int));
        *pntnum = c;
        appendlist(inlist,pntnum);

        appendlist(datalist,movelistdata(inlist));
        clearlist(inlist);

        eof = fscanf(file,"%d %d %c", &r, &c, &t);  
        while (eof == 3)
        {          
            pntnum = (int*)calloc(1,sizeof(int));
            *pntnum = r;
            appendlist(inlist,pntnum);

            pntnum = (int*)calloc(1,sizeof(int));
            *pntnum = c;
            appendlist(inlist,pntnum);
            
            pnttxt = (char*)calloc(1,sizeof(char));
            *pnttxt = t;
            appendlist(inlist,pnttxt);

            appendlist(datalist,movelistdata(inlist));
            clearlist(inlist);
            eof = fscanf(file,"%d %d %c", &r, &c, &t);
        }

        if(ferror(file)) {
            perror("Error reading from file!\n");
        }

        fclose(file);

    }

    freelist(inlist,freefunc);
    inlist = NULL;
    
    return (datalist);
}

/**
    *@brief Function to array of string numbers to integers
    *@note  The function is used to change sys args to an array of int
    *@param string : array of string
    *@param outint : integer array to capture output
    *@param len : length of string array
    *@retval void
*/

void strint(char **string, int *outint, int len)
{
  int i;

  /* Uses scanf to capture strings into the int array */
  for (i=0;i<len;i++)
  {
    sscanf(string[i],"%d",&outint[i]);
  }
}

/**
    *@brief Function to print game on screen
    *@note  The function is used to print the game screen
    *@param strgrid : game array in string
    *@param data : array with game info
    *@param game : game state
    *@retval void
*/

void printgame(GameStruct *gstruct, int *game)
{
    int r;
    int c;
    char **strgrid = gstruct->strgrid;
    
    /* Print first border row of stars */
    system("clear");
    for (c=0;c<=(gstruct->spec[1]+1);c++)
    {
        borderprint();
        if (c == (gstruct->spec[1]+1))
        {
            printf("\n");
        }
    }

    /* Print game grid and charackters */
    for (r=0;r<gstruct->spec[0];r++)
    {
        borderprint();
        for (c = 0;c<gstruct->spec[1];c++)
        {
            printchar(strgrid,r,c);
        }
        borderprint();
        printf("\n");
    }

    /* Print last border row of stars */
    for (c=0;c<=(gstruct->spec[1]+1);c++)
    {
        borderprint();
        if (c == (gstruct->spec[1]+1))
        {
            printf("\n");
        }
    }

    /* Print game legend and controls */
    setForeground("blue",'0');
    printf("*");
    setForeground("reset",0);
    printf(" - Unrestricted Border\n");

    setForeground("red",'0');
    printf("*");
    setForeground("reset",0);
    printf(" - Restricted Border\n");

    printf("Game Controls:\n");
    printf(CTRL_STRNG);
    
    /* Print game result and state */
    printf("Game Out: ");
    switch (*game)
    {
    case WIN: /* game win state */
        setForeground("magenta",'1');
        printf("Congratulations You Win!\n");
        setForeground("reset",0);
        break;
    case LOSE: /* game loose state */
        setForeground("red",'1');
        printf("You have Lost!\n");
        setForeground("reset",0);
        break;
    case UBLOCK: /* game blocked state */
        setForeground("yellow",'1');
        printf("Cannot Undo Further!\n");
        setForeground("reset",0);
        *game = GAME;
        break;    
    case RBLOCK: /* game blocked state */
        setForeground("yellow",'1');
        printf("Cannot Redo Further!\n");
        setForeground("reset",0);
        *game = GAME;
        break;
    case BLOCK: /* game blocked state */
        setForeground("yellow",'1');
        printf("You cannot move that way!\n");
        setForeground("reset",0);
        *game = GAME;
        break;
    case INVALID: /* game Invalid user input */
        setForeground("yellow",'1');
        printf("Invalid input please refer controls!\n");
        setForeground("reset",0);
        break;
    case EXIT: /* user prompted exit */
        setForeground("yellow",'1');
        printf("USER PROMPTED QUIT!\n");
        setForeground("reset",0);
        break;        
    default:
        break;
    }
}

/**
    *@brief Function to read user in-game input
    *@note  Function to read user in-game input
    *@param dir : pointer to store char input.
    *@retval void
*/

void readkey(char *dir)
{
    disableBuffer();
    scanf(" %c",dir);
    enableBuffer();
}
