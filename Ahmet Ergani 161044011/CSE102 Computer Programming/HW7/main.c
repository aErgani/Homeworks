/*created by Ahmet Ergani 161044011*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct gate{        /*this is our struct,it also holds inputs too*/
    int value;              /*value will be assigned after evaluation*/
    int type;               /*types are --> 0 : INPUT / 1 : AND / 2 : OR / 3 : NOT / 4 : FLIPFLOP*/
    struct gate * input1;
    struct gate * input2;
};

int evaluate(struct gate * GATE,int * former)   /*this funciton evaluates a GATE's value according to it's type, using it's input(s)*/
{
    switch(GATE->type)      /*there is a case for each type*/
    {
    case 0: break;
    case 1: if(GATE->input1->value == 1 && GATE->input2->value == 1) GATE->value = 1;  else GATE->value = 0; break;
    case 2: if(GATE->input1->value == 1 || GATE->input2->value == 1) GATE->value = 1;  else GATE->value = 0; break;
    case 3: if(GATE->input1->value == 1) GATE->value = 0;  else GATE->value = 1; GATE->input2 = NULL; break;
    case 4: if(GATE->input1->value == *former ) {GATE->value = 0;*former = 0;} else {GATE->value = 1;*former = 1;}; GATE->input2 = NULL; break;
    }
    return GATE->value;
}

int indexVariable(char var[10],char varArr[20][10],int varCount)    /*this function searches for our variable, checks all the variables and returns the matching variable's index*/
{
    int i;
    for(i = 0; i < varCount-1; i++)
        if(strcmp(var,varArr[i]) == 0)
           return i;
    return 0;
}

void circuit(struct gate * sptrArr[20],int inputArr[10],int * former,int inputCount,int VarCount)   /*this is the function version of our whole circuit*/
{
    int result,i;
    for(i = 0; i < inputCount; i++)         /*first we assign the inputs*/
        sptrArr[i]->value = inputArr[i];
    for(i = inputCount; i < VarCount; i++)  /*then we evaluate each GATE by order*/
    {
        evaluate(sptrArr[i],former);
    }
    result = sptrArr[VarCount - 1]->value;  /*the last GATE's value is our result so we assign it and print it*/
    printf("%d\n",result);

}

int main()          /*in main we read oth files and assign the GATEs and INPUTs but we don't evaluate them*/
{
    struct gate * sptr;
    struct gate * sptrArr[20];      /*this array is to hold all the inputs and GATEs, we allocate when we read a new one*/
    FILE * fptr;
    char str[10],tempC,varArr[20][10],var1[10],var2[10];    /*str is for temporary situations, varArr holds all the identifiers,var1 and var 2 holds input variables*/
    int i,letterCount = 0,varCount = 0,flag = 0,type = 0,former = 0,inputCount = 0,inputArr[10];
    fptr = fopen("circuit.txt","r");    /*opening the file */
    tempC = getc(fptr);
    while(1)                                /*this loop reads all the inputs char by char and assign it to the varArr*/
    {
        while(tempC != ' ' && tempC != '\n')
        {
            str[letterCount] = tempC;
            letterCount++;
            tempC = getc(fptr);
            if(tempC == '\n')
                break;
        }
        str[letterCount] = '\0';
        letterCount = 0;
        if(!(strcmp("INPUT",str) == 0))
        {
            strcpy(varArr[varCount],str);
            sptrArr[varCount] = malloc(sizeof(struct gate));    /*allocating a struct for each input*/
            sptrArr[varCount]->type = 0;
            sptrArr[varCount]->value = 1;
            sptrArr[varCount]->input1 = NULL;
            sptrArr[varCount]->input2 = NULL;
            varCount++;
            letterCount = 0;
        }
        if(tempC == '\n')
            break;
        for(i= 0; i < 10;i++) str[i] = '\0';        /*we empty the temp string after each use to prevent errors*/
    tempC = getc(fptr);
    }
    inputCount = varCount;                  /*after that loop we got ourselves our inputCount*/
    for(i= 0; i < 10;i++) str[i] = '\0';
    letterCount = 0;
    tempC = getc(fptr);
    while(1)
    {
        while(tempC != ' ' && !feof(fptr))                /*reading the GATETYPE here*/
        {
            str[letterCount] = tempC;
            letterCount++;
            tempC = getc(fptr);
            if(tempC == '\n')
                break;
        }
        str[letterCount] = '\0';
        if(strcmp("AND",str) == 0 || strcmp("OR",str) == 0 || strcmp("NOT",str) == 0 || strcmp("FLIPFLOP",str) == 0)    /*we assign the GATEs' type here*/
        {
            sptrArr[varCount] = malloc(sizeof(struct gate));
            if(strcmp("AND",str) == 0)
                { type = 1; sptrArr[varCount]->type = 1; }
            if(strcmp("OR",str) == 0)
                { type = 2; sptrArr[varCount]->type = 2; }
            if(strcmp("NOT",str) == 0)
                { type = 3; sptrArr[varCount]->type = 3; sptrArr[varCount]->input2 = NULL; }
            if(strcmp("FLIPFLOP",str) == 0)
                { type = 4; sptrArr[varCount]->type = 4; sptrArr[varCount]->input2 = malloc(sizeof(struct gate)); }
            letterCount = 0;
            tempC = getc(fptr);
            for(i= 0; i < 10;i++) str[i] = '\0';
            while(tempC != ' ')             /*these loop reads the identifier of the GATE*/
            {
                str[letterCount] = tempC;
                letterCount++;
                tempC = getc(fptr);
                if(tempC == '\n')
                    break;
            }
            strcpy(varArr[varCount],str);
            varCount++;
            letterCount = 0;
            for(i= 0; i < 10;i++) str[i] = '\0';
            sptrArr[varCount - 1]->type = type;
            sptrArr[varCount - 1]->input1 = sptrArr[indexVariable(str,varArr,varCount)];
            for(i= 0; i < 10;i++) str[i] = '\0';
            tempC = getc(fptr);
            while(tempC != '\n' && !feof(fptr))     /*after that we read our input1*/
            {
                str[letterCount] = tempC;
                letterCount++;
                tempC = getc(fptr);
                if(tempC == '\n')
                    break;
            }
            if(type == 1 || type == 2)              /*if our GATE is AND or OR we read the second input too and assign tehm to our GATE*/
            {
                sscanf(str,"%s %s",var1,var2);
                sptrArr[varCount - 1]->input1 = sptrArr[indexVariable(var1,varArr,varCount)];
                sptrArr[varCount - 1]->input2 = sptrArr[indexVariable(var2,varArr,varCount)];
            }
            if(type == 3 || type == 4)              /*else (NOT or FLIPFLOP) we only assign the input1*/
            {
                sscanf(str,"%s",var1);
                sptrArr[varCount - 1]->input1 = sptrArr[indexVariable(var1,varArr,varCount)];
            }
        }
        if(feof(fptr))
            break;
        for(i= 0; i < 10;i++) str[i] = '\0';
        letterCount = 0;
        tempC = getc(fptr);
    }
    fclose(fptr);                       /*we close the circuit.txt and open the input.txt*/
    fptr = fopen("input.txt","r");
    for(i= 0; i < 10;i++) str[i] = '\0';
    letterCount = 0;
    tempC = getc(fptr);
    while(!feof(fptr))                  /*we read the input lines in this loop*/
    {
        while(tempC != '\n' && !feof(fptr))
            {
                str[letterCount] = tempC;
                letterCount++;
                tempC = getc(fptr);
                if(tempC == '\n')
                    break;
            }
        for(i = 0; i < inputCount; i++) /*after each line we assign the inputs to our input array*/
            inputArr[i] = str[2 * i] - '0';
        for(i= 0; i < 10;i++) str[i] = '\0';
        letterCount = 0;
        tempC = getc(fptr);
        circuit(sptrArr,inputArr,&former,inputCount,varCount); /*the inputArr is ready so we call circuit function.it will evaluate the result and print it after each line we read*/
    }
    fclose(fptr);   /*closing the input.txt*/
    return 0;
}
