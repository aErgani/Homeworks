#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* fp;                                           /*declaring file pointer and target strings and arrays and variables*/
    char str1[] = "Xanthos";
    char str2[] = "Patara";
    char str3[] = "Myra";
    char str4[] = "Arycanda";
    char str5[] = "Phaselis";
    char HorV[] = "Horizontal";
    char line[250],board[100][250],direction[5];
    int rowAmount,i,j,k,count,a = 0,b,size[250],coordinates[10];
    for(i = 0; i < 250;i++)                             /*to prevent junk values filling size array with zeros*/
        size[i] = 0;

    for(i = 0; i < 100;i++)                             /*to prevent junk values filling board array with null*/
    {
        for(j = 0; j < 250;j++)
        board[i][j] = '\0';
    }
    if(fp = fopen("input.txt","rt"))                    /*opening the file while checking if the opening process is successfull or not*/
    {
        while(fgets(line,sizeof(line),fp))              /*while loop that reads lines*/
        {
            b = 0;
            strcpy(board[a],line);                      /*transferring the line we read to the board array*/
            while(line[b] != '\0')                      /*increasing the size till we finish the line*/
            {
                size[a]++;
                b++;
            }
            a++;
        }
    }
    else
        printf("FILE OPEN ERROR\n");                    /*inform the user if an error has occured while opening the file*/

    fclose(fp);
    rowAmount = a;
    a = 0;
    for(i = 0; i < rowAmount; i++)                              /*horizontal check*/
    {
        for(j = 0;j < size[a]; j++)
        {
            count = 0;                                  /* *ALGORITHM #1* */
            if(board[i][j] == str1[0])                  /*compiler will enter this loop if the letter we checking matches the first letter of the target word*/
                for(k = 0; k < sizeof(str1); k++)       /*this loop checks if the rest of the row matches the given word, increases the count if it matches*/
            {
                if(board[i][j + k] == str1[k])
                {
                    count++;
                }
                else                                    /*breaks the loop if it doesn't match*/
                    break;
            }
                if(count >= sizeof(str1) - 1)           /*checking if the word is found or not*/
                {
                    coordinates[0] = i + 1;             /*if found assign the necessary values to the coordinates array*/
                    coordinates[1] = j + 1;
                    direction[0] = 'h';                 /*assigns 'h' to the direction array since the direction of this word is horizontal*/
                }
            count = 0;                                  /*reset the counter after every check*/
            if(board[i][j] == str2[0])                  /* *ALGORITHM #1* */
                for(k = 0; k < sizeof(str2); k++)
            {
                if(board[i][j + k] == str2[k])
                    count++;
                else
                    break;
            }
                if(count >= sizeof(str2) - 1)
                {
                    coordinates[2] = i + 1;
                    coordinates[3] = j + 1;
                    direction[1] = 'h';
                }
            count = 0;
            if(board[i][j] == str3[0])                  /* *ALGORITHM #1* */
                for(k = 0; k < sizeof(str3); k++)
            {
                if(board[i][j + k] == str3[k])
                    count++;
                else
                    break;
            }
                if(count >= sizeof(str3) - 1)
                {
                    coordinates[4] = i + 1;
                    coordinates[5] = j + 1;
                    direction[2] = 'h';
                }
            count = 0;
            if(board[i][j] == str4[0])                  /* *ALGORITHM #1* */
                for(k = 0; k < sizeof(str4); k++)
            {
                if(board[i][j + k] == str4[k])
                    count++;
                else
                    break;
            }
                if(count >= sizeof(str4) - 1)
                {
                    coordinates[6] = i + 1;
                    coordinates[7] = j + 1;
                    direction[3] = 'h';
                }
            count = 0;
            if(board[i][j] == str5[0])                  /* *ALGORITHM #1* */
                for(k = 0; k < sizeof(str5); k++)
            {
                if(board[i][j + k] == str5[k])
                    count++;
                else
                    break;
            }
                if(count >= sizeof(str5) - 1)
                {
                    coordinates[8] = i + 1;
                    coordinates[9] = j + 1;
                    direction[4] = 'h';
                }
            count = 0;
        }

    }

     /* ***************************************************************************************************************** */

    a = 0;
    for(i = 0; i < rowAmount; i++)                              /*vertical check*/
    {
        for(j = 0;j < size[a]; j++)                         /* *ALGORITHM #2* */
        {
            count = 0;                                      /*nearly same as ALGORITHM #1 but this algorithm check the cell below while other algorithm checks the right */
            if(board[i][j] == str1[0])
                for(k = 0; k < sizeof(str1); k++)
            {
                if(board[i + k][j] == str1[k])
                {
                    count++;
                }
                else
                    break;
            }
                if(count >= sizeof(str1) - 1)
                {
                    coordinates[0] = i + 1;
                    coordinates[1] = j + 1;
                    direction[0] = 'v';                     /*also this algorithm assigns 'v' to the direction array since the direction of this word is vertical*/
                }
            count = 0;
            if(board[i][j] == str2[0])                      /* *ALGORITHM #2* */
                for(k = 0; k < sizeof(str2); k++)
            {
                if(board[i + k][j] == str2[k])
                    count++;
                else
                    break;
            }
                if(count >= sizeof(str2) - 1)
                {
                    coordinates[2] = i + 1;
                    coordinates[3] = j + 1;
                    direction[1] = 'v';
                }
            count = 0;
            if(board[i][j] == str3[0])                      /* *ALGORITHM #2* */
                for(k = 0; k < sizeof(str3); k++)
            {
                if(board[i + k][j] == str3[k])
                    count++;
                else
                    break;
            }
                if(count >= sizeof(str3) - 1)
                {
                    coordinates[4] = i + 1;
                    coordinates[5] = j + 1;
                    direction[2] = 'v';
                }
            count = 0;
            if(board[i][j] == str4[0])                       /* *ALGORITHM #2* */
                for(k = 0; k < sizeof(str4); k++)
            {
                if(board[i + k][j] == str4[k])
                    count++;
                else
                    break;
            }
                if(count >= sizeof(str4) - 1)
                {
                    coordinates[6] = i + 1;
                    coordinates[7] = j + 1;
                    direction[3] = 'v';
                }
            count = 0;
            if(board[i][j] == str5[0])                        /* *ALGORITHM #2* */
                for(k = 0; k < sizeof(str5); k++)
            {
                if(board[i + k][j] == str5[k])
                    count++;
                else
                    break;
            }
                if(count >= sizeof(str5) - 1)
                {
                    coordinates[8] = i + 1;
                    coordinates[9] = j + 1;
                    direction[4] = 'v';
                }
            count = 0;
        }

    }
    if(direction[0] == 'h')                                                     /*we simply check if this word is horizontal or vertical and print it with it's coordinates and direction */
        printf("%s (%d,%d) Horizontal\n",str1,coordinates[0],coordinates[1]);
    if(direction[0] == 'v')
        printf("%s (%d,%d) Vertical\n",str1,coordinates[0],coordinates[1]);

    if(direction[1] == 'h')
        printf("%s (%d,%d) Horizontal\n",str2,coordinates[2],coordinates[3]);
    if(direction[1] == 'v')
        printf("%s (%d,%d) Vertical\n",str2,coordinates[2],coordinates[3]);

    if(direction[2] == 'h')
        printf("%s (%d,%d) Horizontal\n",str3,coordinates[4],coordinates[5]);
    if(direction[2] == 'v')
        printf("%s (%d,%d) Vertical\n",str3,coordinates[4],coordinates[5]);

    if(direction[3] == 'h')
        printf("%s (%d,%d) Horizontal\n",str4,coordinates[6],coordinates[7]);
    if(direction[3] == 'v')
        printf("%s (%d,%d) Vertical\n",str4,coordinates[6],coordinates[7]);

    if(direction[4] == 'h')
        printf("%s (%d,%d) Horizontal\n",str5,coordinates[8],coordinates[9]);
    if(direction[4] == 'v')
        printf("%s (%d,%d) Vertical\n",str5,coordinates[8],coordinates[9]);

    return 0;
}
