#include <stdio.h>
#include <string.h>

double evaluate(char polinom[1000],double value)        /*this functions analyzes the polinom and calculates the result for the given value*/
{
    double coeffs[100],coef = 1,resultTemp = 1,result = 0;          /*declaring our variables and assigning the necessary ones*/
    char temp[10];
    int powers[100],l = 0,k = 0,order = -1,negative = 0,i,j;
    if(polinom[0] == '-')                                           /*checking if the polynomial's first digit is '-' or not to prevent an expected error*/
        negative = 1;
    while(polinom[k] != '\0')                                       /*this function checks the polynomial digit by digit*/
    {
        if(polinom[k] == '-')                                       /*if we encounter a '-' we set negative 1,this will help us make the coefficiant negative later*/
        {
            negative = 1;
        }
        if(polinom[k] != 'x' && polinom[k] != '+' && polinom[k] != '-') /*we store every number value in the string temp[] till we find our 'x'*/
        {
            temp[l] = polinom[k];
            l++;
        }
        if(polinom[k] == 'x')                               /*after we do*/
        {
            order++;                                        /*we increase our index*/
            sscanf(temp,"%lf",&coef);                       /*convert the temp to a double*/
            if(negative)                                    /*if it's negative do what is necessary*/
                coef = -coef;
            negative = 0;
            coeffs[order] = coef;                           /*and assign it to the coefficiants array*/
            l = 0;
            strcpy(temp,"1");                               /*after that we empty the temp array by assiging it '1'*/
            if(polinom[k + 1] == '^')                       /*if there is a '^' after x we get it by checking the next digit*/
            {
                powers[order] = polinom[k + 2] - '0';       /*and assign it to the powers[] array*/
                k+=2;                                       /*loop counter increase*/
            }
            else
                powers[order] = 1;                          /*if there is no '^' after x, we assign 1*/
        }
        k++;                                                /*loop counter increase*/
    }
    if(!(strcmp(temp,"1")))                                 /*this part is for if there is a "x^0" part at the end exists*/
    {
        order++;
        sscanf(temp,"%lf",&coef);
        if(negative)
            coef = -coef;
        negative = 0;
        coeffs[order] = coef;
        powers[order] = 0;
    }
    for(i = 0;i<order;i++)                      /*and this is the evaluation part*/
    {
        if(powers[i] == 0)                      /*resultTemp is one because we are going to do the multiply operation with it*/
            resultTemp *= coeffs[i];            /*if we are dealing with a "x^0" we just multiply the resultTemp with the coefficiant*/
        else
        {
            for(j = 0;j<powers[i];j++)          /*but if we are not dealing with that kind of 'x' we multiply resultTemp with the value then the coefficiant*/
                resultTemp *= value;
            resultTemp *= coeffs[i];
        }
        result += resultTemp;                   /*result is 0 because we will just add the resultTemp to it in every step of this loop*/
        resultTemp = 1;                         /*after that we assign resultTemp with '1' again*/
    }
    return result;                              /*after the loop we should have the value ve need to return*/
}

int main()
{
    char polinom[1000];                         /*declaring variables and assigning the necessary ones*/
    FILE *fp;
    int count = 0,i = 0;
    double values[100],results[100];
    if(fp = fopen("values.txt","r"))            /*this part is for reading the alues from the file*/
    {
        printf("File successfully opened\n");
        for (i = 0; !feof(fp) ; i++)            /*while reading we also hold the count of the doubles at the variable 'count'*/
        {
            fscanf(fp,"%lf",&values[i]);
            count++;
        }
    }
    fclose(fp);                                 /*closing the values file*/
    if(fp = fopen("polynomial.txt","r"))        /*This part is for reading the polinom*/
    {
        printf("File successfully opened\n");
        fscanf(fp,"%s",polinom);                /*we read it with the placeholder %s to get the whole line */
    }
    fclose(fp);                                 /*closing the polynomial file*/
    for(i = 0; i < count ; i++)                     /*after reading both we call our evaluation file for each double we read*/
    {
        results[i] = evaluate(polinom,values[i]);   /*and assign it to the results[] array*/
    }
    if(fp = fopen("evaluations.txt","w"))           /*we got our results,this part is for printing the results*/
        printf("File successfully opened\n");
    for(i = 0; i < count; i++)                      /*we know how many results we have so we simply print them with a single for loop*/
        fprintf(fp,"%.2lf\n",results[i]);
    return 0;
}
