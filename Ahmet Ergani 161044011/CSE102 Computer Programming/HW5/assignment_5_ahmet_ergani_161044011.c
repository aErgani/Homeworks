#include <stdio.h>

int main()
{
    int bi_grams[27][27],i,j,count = 0;         /* Since we are going to use bi_gram counts of language_x in every comparison we can assign it's array in the main function*/
    char c1,c2;                                 /*these 2 char variable will temporarily hold each character of the bi-gram */
    FILE *fp;                                   /*this is our file pointer*/
    for(i = 0; i < 27;i++)                      /*to prevent junk values we initialize our bi-gram count array*/
        for(j = 0;j < 27;j++)
            bi_grams[i][j] = 0;
    fp = fopen("language_x.txt","r");               /*opening the file and reading the first character*/
    c1 = fgetc(fp);
    while(!feof(fp))                                /*loop that finishes if it detects EOF*/
    {
        c2 = fgetc(fp);                             /*we read the second character we are ready to create a bi-gra*/
        if(c2 == '\n')                              /*if c2 is endline we should treat is as it's a ' '. so we assign it that way*/
            c2 = ' ';
        if(c1 != ' ' || c2 != ' ')                  /*if at least one of them is not ' ' (rule of being a bi-gram) we initiate "bi-gram assignment" process*/
        {
            count++;                                /*first we increase the count as expected*/
            if(c1 == ' ')                           /*then we check all 3 possible bi-gram types : space+letter , letter+space , letter+letter*/
                bi_grams[26][c2 - 'a']++;           /*then we increase the necessary cell of our bi_grams[][] array (we store space at the 26th cell)*/
            else if(c2 == ' ' || feof(fp))
                bi_grams[c1 - 'a'][26]++;
            else
                bi_grams[c1 - 'a'][c2 - 'a']++;
        }
        c1 = c2;                                    /*at the end of each loop we assign c2 to c1 and read the new character to c2, so we don't lose the second member of the latest bi-gram*/
    }
    dissimilarity(bi_grams,count,'1');              /*after we created our bi-gram array for file : "language_X" it's time to call our dissimilarity function*/
    dissimilarity(bi_grams,count,'2');
    dissimilarity(bi_grams,count,'3');
    dissimilarity(bi_grams,count,'4');
    dissimilarity(bi_grams,count,'5');
    return 0;
}

void dissimilarity(int const bi_grams_X[27][27],int count_X,char language_no)           /*this function reads a language file and creates it's array of bi_gram count but also calculates it's*/
{                                                                                       /*dissimilarity, and to do that it takes bi-gram count array and total count of language_x as a parameter*/
    float temp = 0.0,dissimilarity = 0.0,countX = count_X, count = 0.0;                 /*these float variables will help us calculate the dissimilarity*/
    int bi_grams[27][27],i,j;                                                           /*this part is very similar to the "file-read and create bi-gram array part" of the main function*/
    char c1,c2;
    FILE *fp;
    char filename[14] = {'l','a','n','g','u','a','g','e','_','N','.','t','x','t'};      /*this string will be our language file,you must notice we take a char value from 1 to 5*/
    filename[9] = language_no;                                                          /*we assign that numerical value to the 9th cell of our filename string so we have our filename*/
    for(i = 0; i < 27;i++)                      /*initializing the bi-gram array*/
        for(j = 0;j < 27;j++)
            bi_grams[i][j] = 0;
    fp = fopen(filename,"r");                   /*file reading part (same as the part in main function)*/
    c1 = fgetc(fp);
    while(!feof(fp))
    {
        c2 = fgetc(fp);
        if(c2 == '\n')
            c2 = ' ';
        if(c1 != ' ' || c2 != ' ')
        {
            count += 1.0;
            if(c1 == ' ')
                bi_grams[26][c2 - 'a']++;
            else if(c2 == ' ' || feof(fp))
                bi_grams[c1 - 'a'][26]++;
            else
                bi_grams[c1 - 'a'][c2 - 'a']++;
        }
        c1 = c2;
    }                                                                       /*we created bi-gram count array and took the language_X's array as a parameter. we are ready to calculate dissimilarity*/
    for(i = 0;i < 27; i ++)                                                 /*double loop that helps us check every cell of both array*/
        for(j = 0;j < 27; j++)
            {

                temp = (bi_grams_X[i][j]/countX) - (bi_grams[i][j]/count);  /*temp holds frequency difference*/
                if(temp < 0)                                                /*we need the absolute value so if temp's is negative we need to make it positive*/
                    temp = -temp;
                dissimilarity = dissimilarity + temp;                       /*we add temp to the total dissimilarity value each loop*/
            }
    printf("%lf\n",dissimilarity);          /*now we can print the dissimilarity as expected*/
}
