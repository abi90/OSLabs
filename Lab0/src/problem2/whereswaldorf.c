/*
 * File:   whereswaldorf.c
 * Author: Abisai Ramos
 *
 * Created on August 27, 2016, 3:44 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void findWordsHorizontally(char **board, char *word, int M, int W);
void printOccurrence(const char *word, const char *line, int i);
int firsOccurrence(const char *word, const char *line);
char *reverse(const char *word);
char *toUpper(const char *string);
int read_line(FILE *in, char *buffer, size_t max);


/*
 * Verifies the given input file and outputs the words results as line and index
 */
int main(int argc, char** argv)
{
    FILE *input;

    int T,M,N,W,i,j,k;

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
            fscanf(input, "%d %d\n", &M,&N);
            char board[M][N];
            for(j=0;j<M;j++)
            {
                for(k=0;k<N;k++)
                    fscanf(input,"%c", &board[j][k]);
                fscanf(input, "\n");
            }
            fscanf(input, "%d\n", &W);
            char word[W][M*N];
            for(j=0;j<W;j++)
            {
                char temp[N];
                read_line(input,temp, sizeof temp);
                strcpy(word[j],temp);
            }

            printf("Test Case %d:\n",i+1);
            int l,m,n;
            for(l=0;l<M;l++)
            {
                char line[N];
                for(n=0;n<N;n++)
                    line[n]=toupper(board[l][n]);
                //printf("%s\n",line);
                for (m = 0; m < W; m++)
                {
                    char *temp1,*temp2;
                    temp1=toUpper(word[m]);
                    printOccurrence(temp1, line, l+1);
                    //printf("temp1:%s\nline:%s\nl:%d\n",temp1,line,l);
                    temp2 = reverse(temp1);
                    printOccurrence(temp2, line, l+1);
                }
            }
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


void printOccurrence(const char *word, const char *line, int i)
{
    int index = firsOccurrence(word,line);
    if(index>=0)
    {
        printf("%d %d\n", i, index+1);
    }
}

int firsOccurrence(const char *word, const char *line)
{
    int index =-1;
    char *temp = strstr(line,word);
    if(temp!=NULL)
        index=temp-line;
    return index;
}

char *reverse(const char *word)
{
    int i,len;
    len = strlen(word);
    char result[len];
    for(i=0;i<len;i++)
    {
        result[i] = word[len-(i+1)];
    }
    return result;
}

char *toUpper(const char *string)
{
    int len,i;
    char temp[strlen(string)];
    len= strlen(string);
    if(len>0)
    {
        for(i=0;i<len;i++)
            if(string[i] != '\n')
                temp[i]=toupper(string[i]);
            else temp[i]='\0';
    }
    return temp;
}

int read_line(FILE *in, char *buffer, size_t max)
{
    return fgets(buffer, max, in) == buffer;
}