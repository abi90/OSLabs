/*
 * File:   tictactoetomek.c
 * Author: Abisai Ramos
 *
 * Created on August 22, 2016, 2:02 PM
 */

#include <stdio.h>
#include <stdlib.h>

char *winner(int X1, int X2, int O1, int O2, int T1, int T2);
char *showStatus(char board[4][4]);

/*
 * Verifies the given Tic-Tac-Toe-Tomek input file and outputs its game status
 */
int main(int argc, char** argv)
{
    FILE *input;

    int T, i;
    char board[4][4];

    if(argc < 2)
    {
        printf("Input file missing!\n");
        exit(EXIT_FAILURE);
    }

    input = fopen(argv[1], "r");

    if(input != NULL)
    {
        fscanf(input, "%d\n", &T);

        for(i = 0; i < T; i++)
        {
            fscanf(input, "%c%c%c%c\n", &board[0][0], &board[0][1], &board[0][2], &board[0][3]);
            fscanf(input, "%c%c%c%c\n", &board[1][0], &board[1][1], &board[1][2], &board[1][3]);
            fscanf(input, "%c%c%c%c\n", &board[2][0], &board[2][1], &board[2][2], &board[2][3]);
            fscanf(input, "%c%c%c%c\n", &board[3][0], &board[3][1], &board[3][2], &board[3][3]);
            printf("Case #%d: %s\n", i + 1, showStatus(board));
            fscanf(input, "\n");
        }
        fclose(input);
    }
    else
    {
        printf("Unable to read input file\n");
        exit(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

/*
 * Returns the winner
 */
char *winner(int X1, int X2, int O1, int O2, int T1, int T2)
{
    if(X1 + T1 >= 4 || X2 + T2 >=4)
    {
        return "X won";
    }
    if(O1 + T1 >= 4 || O2+ T2 >=4)
    {
        return "O won";
    }

    return NULL;
}

/*
 * Returns Game Status
 */
char *showStatus(char board[4][4])
{
    int i, j, X1, X2, O1, O2, T1, T2,dotCount;
    char *result;
    dotCount = 0;
    X1 = 0;
    X2 = 0;
    O1 = 0;
    O2 = 0;
    T1=0;
    T2=0;

    // Inspect board diagonally
    for(i = 0; i < 4; i++)
    {
        if(board[i][i] == 'X')
        {
            X1++;
        }
        else if(board[i][i] == 'O')
        {
            O1++;
        }
        else if (board[i][i] == 'T')
        {
            T1++;
        }

        if(board[i][3 - i] == 'X')
        {
            X2++;
        }
        else if(board[i][3 - i] == 'O')
        {
            O2++;
        }
        else if(board[i][3 - i] == 'T')
        {
            T2++;
        }
    }

    result = winner(X1,X2,O1,O2,T1,T2);
    if(result != NULL)
    {
        return result;
    }

    // Inspect board horizontally and vertically
    for(i = 0; i < 4; i++)
    {
        X1 = 0; X2 = 0; O1 = 0; O2 = 0; T1=0; T2=0;

        for(j = 0; j < 4; j++)
        {
            //Horizontal Counters
            if(board[i][j] == 'X')
            {
                X1++;
            }
            else if(board[i][j] == 'O')
            {
                O1++;
            }
            else if(board[i][j] == 'T')
            {
                T1++;
            }
            else if(board[i][j] == '.')
            {
                dotCount++;
            }
            //Vertical Counters
            if(board[j][i] == 'X')
            {
                X2++;
            }
            else if(board[j][i] == 'O')
            {
                O2++;
            }
            else if(board[j][i] == 'T')
            {
                T2++;
            }
        }

        result = winner(X1,X2,O1,O2,T1,T2);
        if(result != NULL)
        {
            return result;
        }
    }

    // Uncompleted Game
    if(dotCount > 0)
    {
        return "Game has not completed";
    }

    return "Draw";
}
