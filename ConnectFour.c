#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

int i;
/*This struct holds the information for every tile on the game board.*/
struct Tile
{
    char symbol;
};

struct Tile board[49];//This is the game board, made of 49 tiles. 7x7 = 49.

/*Useful "column" variables*/
int c_array[7]; //This array holds up to 7 column positions.
int c_iterator; //This is the interator for the c_array.
int c_current; //This is the current index we are currently looking at.

/*Useful "lenght" variables*/
int l_array[7]; //This array holds up to 7 lenghts of columns.
int l_iterator; //This is the interator for l_array.
int l_current; //This is the current lenght of the column on the board. Changes as needed.
int l_temp; //This is a temporary holder for a temporary column lenght.

/*Useful "force" variables*/
int f_array[7]; //This array holds up to 7 force amounts.
int f_iterator; //This is the interator for f_array.
int f_counter; //This accumulates force.
int f_temp; //This is a temporary holder for a force amount.

/*Other useful variables (temps, counters, etc)*/
int inc; //Number to iterator by.
int dec; //Number to decrement by.
char buffer;
bool win = false;
bool full = false;
char player;
int column;
char direction;
int force;


/*We need a function to print the board*/
void print_board()
{

    for(i = 0; i < 49; i++)
    {
        printf("%c", board[i].symbol);
        printf(" ");

        if(((i+1) % 7) == 0)
        {
            printf("\n");
        }
    }
}

/*This function handles place of chips entering from North*/
void placeNorth(int f, int i, int l, int start, char p)
{
        l_array[l_iterator] = l;
        l_iterator++;
        /*If i = lenght then exit but save the lenght and prepare to restore previous values */
        if(i == l)
        {
            l = l - 7;
            l_array[l_iterator] = l;
            l_iterator++;
            c_iterator--;
            i = c_array[c_iterator];
            return; //end of array
        }

        /* if force = 0 then we have used up all our moves, save the lenght and prepare to restore previous values */
        if(f == 0)
        {
            if(i == l)
            {
                l = l - 7;
                l_array[l_iterator] = l;
                l_iterator++;
            }

            c_iterator--;

            if(c_iterator >= 0)
            {
                i = c_array[c_iterator];
            }
            return; //end of array
        }
        else
        {
            if(board[i].symbol == '-')
            {

                if(i == start)
                {
                    board[i].symbol = p;
                    f_counter++;
                }
                else
                {
                    f_counter++;
                    board[i].symbol = board[i - 7].symbol;
                    board[i - 7].symbol = '-';
                }

                i = i + 7;
                f--;
            }
            else
            {
                /* Store previous data in proper spots for when returning from a future function */
                c_array[c_iterator] = i;
                c_iterator++;
                f_array[f_iterator] = f;
                f_iterator++;
                f = f_temp - f_counter;
                f_temp = f;
                f_counter = 0;
                i = i + 7;

                /* Call next function */
                placeNorth(f,i,l_temp, start,p);

                /* Restore data after function above exits */
                l_iterator--;
                f_iterator--;
                f = f_array[f_iterator];
                l = l_array[l_iterator];
                i = c_array[c_iterator];
            }

        }

        /* Make a recursion call to solve the next index */
        return placeNorth(f,i,l, start,p);
}

/*This function handles place of chips entering from South*/
void placeSouth(int f, int i, int l, int start, char p)
{
        l_array[l_iterator] = l;
        l_iterator++;

      /*If i = lenght then exit but save the lenght and prepare to restore previous values */
        if(i == l)
        {
            l = l + 7;
            l_array[l_iterator] = l;
            l_iterator++;
            c_iterator--;
            i = c_array[c_iterator];
            return; //end of array
        }

        /* if force = 0 then we have used up all our moves, save the lenght and prepare to restore previous values */
        if(f == 0)
        {
            if(i == l)
            {
                l = l + 7;
                l_array[l_iterator] = l;
                l_iterator++;
            }

            c_iterator--;

            if(c_iterator >= 0)
            {
                i = c_array[c_iterator];
            }
            return; //end of array
        }
        else
        {
            if(board[i].symbol == '-')
            {

                if(i == start)
                {
                    board[i].symbol = p;
                    f_counter++;
                }
                else
                {
                    f_counter++;
                    board[i].symbol = board[i + 7].symbol;
                    board[i + 7].symbol = '-';
                }

                i = i - 7;
                f--;
            }
            else
            {
                /* Store previous data in proper spots for when returning from a future function */
                c_array[c_iterator] = i;
                c_iterator++;
                f_array[f_iterator] = f;
                f_iterator++;
                f = f_temp - f_counter;
                f_temp = f;
                f_counter = 0;
                i = i - 7;

                /* Call next function */
                placeSouth(f,i,l_temp, start,p);

                /* Restore data after function above exits */
                l_iterator--;
                f_iterator--;
                f = f_array[f_iterator];
                l = l_array[l_iterator];
                i = c_array[c_iterator];
            }

        }

        /* Make a recursion call to solve the next index */
        return placeSouth(f,i,l, start,p);
}

/*This function handles place of chips entering from West*/
void placeEast(int f, int i, int l, int start, char p)
{
    l_array[l_iterator] = l;
    l_iterator++;
    /*If i = lenght then exit but save the lenght and prepare to restore previous values */
        if(i == l)
        {
            l = l + 1;
            l_array[l_iterator] = l;
            l_iterator++;
            c_iterator--;
            i = c_array[c_iterator];
            return; //end of array
        }

        /* if force = 0 then we have used up all our moves, save the lenght and prepare to restore previous values */
        if(f == 0)
        {
            if(i == l)
            {
                l = l + 1;
                l_array[l_iterator] = l;
                l_iterator++;
            }

            c_iterator--;

            if(c_iterator >= 0)
            {
                i = c_array[c_iterator];
            }
            return; //end of array
        }
        else
        {
            if(board[i].symbol == '-')
            {

                if(i == start)
                {
                    board[i].symbol = p;
                    f_counter++;
                }
                else
                {
                    f_counter++;
                    board[i].symbol = board[i + 1].symbol;
                    board[i + 1].symbol = '-';
                }

                i = i - 1;
                f--;
            }
            else
            {
                /* Store previous data in proper spots for when returning from a future function */
                c_array[c_iterator] = i;
                c_iterator++;
                f_array[f_iterator] = f;
                f_iterator++;
                f = f_temp - f_counter;
                f_temp = f;
                f_counter = 0;
                i = i - 1;

                /* Call next function */
                placeEast(f,i,l_temp, start,p);

                /* Restore data after function above exits */
                l_iterator--;
                f_iterator--;
                f = f_array[f_iterator];
                l = l_array[l_iterator];
                i = c_array[c_iterator];
            }

        }

        /* Make a recursion call to solve the next index */
        return placeEast(f,i,l, start,p);
}

/*This function handles place of chips entering from West*/
void placeWest(int f, int i, int l, int start, char p)
{
        l_array[l_iterator] = l;
        l_iterator++;
            /*If i = lenght then exit but save the lenght and prepare to restore previous values */
        if(i == l)
        {
            l--;
            l_array[l_iterator] = l;
            l_iterator++;
            c_iterator--;
            i = c_array[c_iterator];
            return; //end of array
        }

        /* if force = 0 then we have used up all our moves, save the lenght and prepare to restore previous values */
        if(f == 0)
        {
            if(i == l)
            {
                l--;
                l_array[l_iterator] = l;
                l_iterator++;
            }

            c_iterator--;

            if(c_iterator >= 0)
            {
                i = c_array[c_iterator];
            }
            return; //end of array
        }
        else
        {
            if(board[i].symbol == '-')
            {

                if(i == start)
                {
                    board[i].symbol = p;
                    f_counter++;
                }
                else
                {
                    f_counter++;
                    board[i].symbol = board[i - 1].symbol;
                    board[i - 1].symbol = '-';
                }

                i++;
                f--;
            }
            else
            {
                /* Store previous data in proper spots for when returning from a future function */
                c_array[c_iterator] = i;
                c_iterator++;
                f_array[f_iterator] = f;
                f_iterator++;
                f = f_temp - f_counter;
                f_temp = f;
                f_counter = 0;
                i++;

                /* Call next function */
                placeWest(f,i,l_temp, start,p);

                /* Restore data after function above exits */
                l_iterator--;
                f_iterator--;
                f = f_array[f_iterator];
                l = l_array[l_iterator];
                i = c_array[c_iterator];
            }

        }

        /* Make a recursion call to solve the next index */
        return placeWest(f,i,l, start,p);
}

/*This function handles the placement of chips */
void placeChip(char direction, int column, int force, char player)
{
    f_temp = force;

    if(direction == 'N' || direction == 'n')
    {
        f_counter = 0;
        c_iterator = 0;
        l_iterator = 0;
        l_current = (column + 42) + 7;
        l_temp = (column + 42) + 7;
        c_current = column;
        placeNorth(force, c_current, l_current, column, player);

    }
    if(direction == 'S' || direction == 's')
    {
        f_counter = 0;
        c_iterator = 0;
        l_iterator = 0;
        l_current = (column - 7);
        l_temp = (column - 7);
        column = column + 42;
        c_current = column;
        placeSouth(force, c_current, l_current, column, player);
    }
    if(direction == 'E' || direction == 'e')
    {
        f_counter = 0;
        c_iterator = 0;
        l_iterator = 0;
        l_current = (column * 7) - 1;
        l_temp = (column * 7) - 1;
        column = (column * 7) + 6;
        c_current = column;
        placeEast(force, c_current, l_current, column, player);
    }
    if(direction == 'W' || direction == 'w')
    {
        f_counter = 0;
        c_iterator = 0;
        l_iterator = 0;
        column = column * 7;
        l_current = column + 7;
        l_temp = column + 7;
        c_current = column;
        placeWest(force, c_current, l_current, column, player);
    }

}

/*This function handles testing for if a column is full*/
bool testFull(char side, int column)
{
    int i;
    int full_count = 0;

    if(side == 'w' || side == 'W' || side == 'E' || side == 'e')
    {
        column = column * 7;

        for(i = column; i < (column + 7) + 1; i++)
        {

                if(full_count == 7)
                {
                    printf("Invalid Move, that column is full! \n\n");
                    return true;
                }

                if(board[i].symbol != '-')
                {
                    full_count++;
                }
                else
                {
                    full_count = 0;
                }

        }
    }

    full_count = 0;
    i = 0;

    if(side == 'N' || side == 'n' || side == 's' || side == 'S')
    {

        for(i = column; i < (column + 49) + 7; i = i + 7)
        {

                if(full_count == 7)
                {
                    printf("Invalid Move, that column is full! \n\n");
                    return true;
                }

                if(board[i].symbol != '-')
                {
                    full_count++;
                }
                else
                {
                    full_count = 0;
                }

        }
    }

    return false;
}

/*This function handles the testing for winner */
bool testWinner()
{
    int i;
    int j;
    int r_count = 0;
    int g_count = 0;

    for(i = 0; i < 55; i = i+7)
    {
        for(j = i; j < (i+7); j++)
        {
            if(g_count == 4)
            {
                printf("Green wins! \n\n");
                return true;
            }

            if(r_count == 4)
            {
                printf("Red wins! \n\n");
                return true;
            }

            if(board[j].symbol != '-')
            {
                if(board[j].symbol == 'G')
                {
                    g_count++;
                    r_count = 0;
                }
                if(board[j].symbol == 'R')
                {
                    r_count++;
                    g_count = 0;
                }
            }
            else
            {
                g_count = 0;
                r_count = 0;
            }
        }
    }

    i = 0;
    j = 0;
    g_count = 0;
    r_count = 0;

    for(i = 0; i < 7; i++)
    {
        for(j = i; j < (i + 49); j = j + 7)
        {
            if(g_count == 4)
            {
                printf("Green wins! \n\n");
                return true;
            }

            if(r_count == 4)
            {
                printf("Red wins! \n\n");
                return true;
            }

            if(board[j].symbol != '-')
            {
                if(board[j].symbol == 'G')
                {
                    g_count++;
                    r_count = 0;
                }
                if(board[j].symbol == 'R')
                {
                    r_count++;
                    g_count = 0;
                }
            }
            else
            {
                g_count = 0;
                r_count = 0;
            }
        }
    }

    /*The loops past this point handle diagonals */
    int lenght = -4;
    i = 0;
    j = 0;
    g_count = 0;
    r_count = 0;

    for(i = 21; i < 49; i = i + 7)
    {
        lenght++;

        for(j = i; j > lenght; j = j - 6)
        {
            if(g_count == 4)
            {
                printf("Green wins! \n\n");
                return true;
            }

            if(r_count == 4)
            {
                printf("Red wins! \n\n");
                return true;
            }

            if(board[j].symbol != '-')
            {
                if(board[j].symbol == 'G')
                {
                    g_count++;
                    r_count = 0;
                }
                if(board[j].symbol == 'R')
                {
                    r_count++;
                    g_count = 0;
                }
            }
            else
            {
                g_count = 0;
                r_count = 0;
            }

        }

    }

    lenght = 0;
    i = 0;
    j = 0;
    g_count = 0;
    r_count = 0;

    for(i = 43; i < 46; i++)
    {
        lenght = lenght + 7;

        for(j = i; j > lenght; j = j - 6)
        {
            if(g_count == 4)
            {
                printf("Green wins! \n\n");
                return true;
            }

            if(r_count == 4)
            {
                printf("Red wins! \n\n");
                return true;
            }

            if(board[j].symbol != '-')
            {
                if(board[j].symbol == 'G')
                {
                    g_count++;
                    r_count = 0;
                }
                if(board[j].symbol == 'R')
                {
                    r_count++;
                    g_count = 0;
                }
            }
            else
            {
                g_count = 0;
                r_count = 0;
            }

        }

    }

    lenght = 62;
    i = 0;
    j = 0;
    g_count = 0;
    r_count = 0;

    for(i = 0; i < 4; i++)
    {
        lenght = lenght - 7;

        for(j = i; j < lenght; j = j + 8)
        {
            if(g_count == 4)
            {
                printf("Green wins! \n\n");
                return true;
            }

            if(r_count == 4)
            {
                printf("Red wins! \n\n");
                return true;
            }

            if(board[j].symbol != '-')
            {
                if(board[j].symbol == 'G')
                {
                    g_count++;
                    r_count = 0;
                }
                if(board[j].symbol == 'R')
                {
                    r_count++;
                    g_count = 0;
                }
            }
            else
            {
                g_count = 0;
                r_count = 0;
            }

        }

    }

    lenght = 52;
    i = 0;
    j = 0;
    g_count = 0;
    r_count = 0;

    for(i = 7; i < 28; i = i + 7)
    {
        lenght++;

        for(j = i; j < lenght; j = j + 8)
        {
            if(g_count == 4)
            {
                printf("Green wins! \n\n");
                return true;
            }

            if(r_count == 4)
            {
                printf("Red wins! \n\n");
                return true;
            }

            if(board[j].symbol != '-')
            {
                if(board[j].symbol == 'G')
                {
                    g_count++;
                    r_count = 0;
                }
                if(board[j].symbol == 'R')
                {
                    r_count++;
                    g_count = 0;
                }
            }
            else
            {
                g_count = 0;
                r_count = 0;
            }

        }

    }

    return false;

}

/*This function handles the green players moves*/
void playerGreen()
{
        printf("It is greens turn! \n\n");
        player = 'G';
        direction = '\n';
        column = 7;
        force = 8;
        full = true;
        win = true;

        while(((direction == 'N' || direction == 'n') ||
              (direction == 'S' || direction == 's') ||
              (direction == 'E' || direction == 'e') ||
              (direction == 'W' || direction == 'w')) == false)
        {
            printf("Enter side: ");
            scanf(" %c", &direction);
            printf("\n");

            if(((direction == 'N' || direction == 'n') ||
              (direction == 'S' || direction == 's') ||
              (direction == 'E' || direction == 'e') ||
              (direction == 'W' || direction == 'w')) == false)
            printf("Invalid side. \n\n");

        }

        while(column < 0 || column > 6)
        {
            printf("Enter column: ");
            scanf("%d", &column);
            printf("\n");

            if(column < 0 || column > 6)
            {
              printf("Invalid column. \n\n");
            }
        }

        full = testFull(direction, column);

        if(full == true)
        {
            return playerGreen();
        }

        while(force < 0 || force > 7)
        {
            printf("Enter force: ");
            scanf("%d", &force);
            printf("\n");

            if(force < 0 || force > 6)
            {
              printf("Invalid force. \n\n");
            }
        }

    return;
}

/* This function handles the red players moves */
void playerRed()
{
        printf("It is reds turn! \n\n");
        player = 'R';
        direction = '\n';
        column = 7;
        force = 8;
        full = true;
        win = true;

        while(((direction == 'N' || direction == 'n') ||
              (direction == 'S' || direction == 's') ||
              (direction == 'E' || direction == 'e') ||
              (direction == 'W' || direction == 'w')) == false)
        {
            printf("Enter side: ");
            scanf(" %c", &direction);
            printf("\n");

            if(((direction == 'N' || direction == 'n') ||
              (direction == 'S' || direction == 's') ||
              (direction == 'E' || direction == 'e') ||
              (direction == 'W' || direction == 'w')) == false)
            printf("Invalid side. \n\n");

        }

        while(column < 0 || column > 6)
        {
            printf("Enter column: ");
            scanf("%d", &column);
            printf("\n");

            if(column < 0 || column > 6)
            {
              printf("Invalid column. \n\n");
            }
        }

        full = testFull(direction, column);

        if(full == true)
        {
            return playerRed();
        }

        while(force < 0 || force > 7)
        {
            printf("Enter force: ");
            scanf("%d", &force);
            printf("\n");

            if(force < 0 || force > 6)
            {
              printf("Invalid force. \n\n");
            }
        }

    return;
}



int main()
{


    for(i = 0; i < 49; i++) // Make sure that all symbols are initialized to '-'
    {
        board[i].symbol = '-';
    }

    print_board();
    while(1)
    {

        playerGreen();
        placeChip(direction, column, force, player);
        printf("\n");
        printf("\n");

        print_board();
        printf("\n");
        printf("\n");

        win = testWinner();
        if(win == true)
            return 0;

        playerRed();
        placeChip(direction, column, force, player);
        printf("\n");
        printf("\n");

        print_board();
        printf("\n");
        printf("\n");

        win = testWinner();

        if(win == true)
            return 0;


    }


    return 0;
}
