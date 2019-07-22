#include <stdio.h>

int recursive(char line[100],int * index,int * branch)  /*this function gets the line we read and 2 pointers: "index" lets us move to the next char of the string */
{                                                       /*and "branch" lets us know how many '-' we will have to print when we encounter a letter*/
    int i;
    if(line[*index] == '.')             /*if we encounter a dot it means the line ended so we can terminate this recursive function*/
        return 0;
    else if(line[*index] == '(')        /*if we encounter a '(' it means we need to increase the value of branch*/
        *branch = *branch + 1;
    else if(line[*index] == ')')        /*if we encounter a ')' it means we need to decrease the value of branch*/
        *branch = *branch - 1;
    else if(line[*index] != ',')        /*this "else" means we encountered a letter.(we ignore commas)*/
    {
        for(i = 0;i < *branch;i++)      /*we print '-' by the necessary amount (we hold that amount in the address of branch)*/
            printf("-");
        printf("%c\n",line[*index]);    /*then we print our letter*/
    }
    *index = *index + 1;                /*if we did not encounter a dot,we increase the value of index by 1 and call our function again*/
    recursive(line,index,branch);
}

int main()                              /*in main function we just open our file and create the string that holds the line*/
{
    FILE * fptr;                        /*declaring and assigning necessary variables*/
    int count = 0,index = 0,branch = 0;
    char c,line[100];
    fptr = fopen("input.txt","r");      /*opening the file*/
    while(!feof(fptr))                  /*while checking if the file ended or not, we read the characters to our string*/
    {
        c = getc(fptr);
        line[count] = c;
        count++;
    }
    line[count-1] = '.';                /*because our read algorithm, after we exit the loop our count will be "character count + 1" so we decrease it by 1 to assign a dot at the end*/
    recursive(line,&index,&branch);     /*then we call our recursive function*/
    return 0;
}
