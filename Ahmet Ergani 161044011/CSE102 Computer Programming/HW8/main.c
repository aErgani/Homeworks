#include <stdio.h>


//THERE ARE MINOR ERRORS IN COLUMN ROTATING


void initCube(int n,int ** arr[6])
{
    int i,j,k;
    for(j = 0;j < 6; j++)
    {
        arr[j] = (int **)malloc((n) * sizeof(int *));
        for (i=0; i<n; i++)
        {
            arr[j][i] = (int *)malloc(n * sizeof(int));
        }
        for(i=0; i<n; i++)
            for(k = 0;k<n;k++)
                arr[j][i][k] = j;
    }
}

void flip(int * line1,int * line2,int * line3,int * line4,int rot,int n)
{
    int temp[n],i,j;
    if(rot)
    {
        for(i = 0; i < n;i++)
            temp[i] = line1[i];
        for(i = 0; i < n;i++)
            line1[i] = line4[i];
        for(i = 0; i < n;i++)
            line4[i] = line3[i];
        for(i = 0; i < n;i++)
            line3[i] = line2[i];
        for(i = 0; i < n;i++)
            line2[i] = temp[i];
    }
    else
    {
        for(i = 0; i < n;i++)
            temp[i] = line1[i];
        for(i = 0; i < n;i++)
            line1[i] = line2[i];
        for(i = 0; i < n;i++)
            line2[i] = line3[i];
        for(i = 0; i < n;i++)
            line3[i] = line4[i];
        for(i = 0; i < n;i++)
            line4[i] = temp[i];
    }
}

int main()
{
    FILE * fptr;
    int n,faceNo,lineNo,i,j,k,space = 0;
    int ** FACES[6];
    int * line1;
    int * line2;
    int * line3;
    int * line4;
    char tempC,lineType[10],direction[6],rotate[10],readLine[30];
    fptr = fopen("commands.txt","r");
    fscanf(fptr,"%d",&n);
    initCube(n,FACES);
    line1 = (int*)malloc(n*sizeof(int));
    for(i = 0; i < n; i++)
        line1[i] = 9;
    line2 = (int*)malloc(n*sizeof(int));
    for(i = 0; i < n; i++)
        line2[i] = 9;
    line3 = (int*)malloc(n*sizeof(int));
    for(i = 0; i < n; i++)
        line3[i] = 9;
    line4 = (int*)malloc(n*sizeof(int));
    for(i = 0; i < n; i++)
        line4[i] = 9;
    while(1)
    {
    fscanf(fptr,"%s",rotate);
    fscanf(fptr,"%d",&faceNo);
    fscanf(fptr,"%s",lineType);
    fscanf(fptr,"%d",&lineNo);
    fscanf(fptr,"%s",direction);
    if(faceNo == 0)             /*MY swap algorithm is I find all 4 of the effected lines in that rotation and swap them 1 by 1*/
    {
        if(strcmp(lineType,"row") == 0)
        {
            for(i = 0;i < n;i++)        /*I hold those 4 lines in line1 line2 line3 line4*/
                line1[i] = FACES[0][lineNo][i];
            for(i = 0;i < n;i++)
                line2[i] = FACES[1][lineNo][i];
            for(i = 0;i < n;i++)
                line3[i] = FACES[2][lineNo][i];
            for(i = 0;i < n;i++)
                line4[i] = FACES[3][lineNo][i];
            if(strcmp(direction,"right") == 0)
                flip(line1,line2,line3,line4,1,n);      /*flip function can assign eacch one of them to next one or the previous one*/
            else
                flip(line1,line2,line3,line4,0,n);

            for(i = 0; i < n;i++)
                FACES[0][lineNo][i] = line1[i];         /*after that I assign them back (sometimes mirrored if necessary)*/
            for(i = 0; i < n;i++)
                FACES[1][lineNo][i] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][lineNo][i] = line3[i];
            for(i = 0; i < n;i++)
                FACES[3][lineNo][i] = line4[i];
        }
        else if(strcmp(lineType,"column") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[0][i][lineNo];
            for(i = 0;i < n;i++)
                line2[i] = FACES[5][i][lineNo];
            for(i = 0;i < n;i++)
                line3[i] = FACES[2][i][n - 1 - lineNo];
            for(i = 0;i < n;i++)
                line4[i] = FACES[4][i][lineNo];
            if(strcmp(direction,"down") == 0)
            {
                flip(line1,line2,line3,line4,1,n);
            for(i = 0; i < n;i++)
                FACES[0][i][lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][i][lineNo] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][n-1-i][lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][n-1-i][lineNo] = line4[i];
            }
            else
            {
                flip(line1,line2,line3,line4,0,n);
            for(i = 0; i < n;i++)
                FACES[0][i][lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][n-1-i][lineNo] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][n-1-i][lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][i][lineNo] = line4[i];
            }
        }
    }
    if(faceNo == 1)
    {
        if(strcmp(lineType,"row") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[0][lineNo][i];
            for(i = 0;i < n;i++)
                line2[i] = FACES[1][lineNo][i];
            for(i = 0;i < n;i++)
                line3[i] = FACES[2][lineNo][i];
            for(i = 0;i < n;i++)
                line4[i] = FACES[3][lineNo][i];

            if(strcmp(direction,"right") == 0)
                flip(line1,line2,line3,line4,1,n);
            else
                flip(line1,line2,line3,line4,0,n);

            for(i = 0; i < n;i++)
                FACES[0][lineNo][i] = line1[i];
            for(i = 0; i < n;i++)
                FACES[1][lineNo][i] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][lineNo][i] = line3[i];
            for(i = 0; i < n;i++)
                FACES[3][lineNo][i] = line4[i];
        }
        if(strcmp(lineType,"column") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[1][i][lineNo];
            for(i = 0;i < n;i++)
                line2[i] = FACES[5][lineNo][i];
            for(i = 0;i < n;i++)
                line3[i] = FACES[3][i][n - 1 - lineNo];
            for(i = 0;i < n;i++)
                line4[i] = FACES[4][n - 1 - lineNo][i];

            if(strcmp(direction,"down") == 0)
                flip(line1,line2,line3,line4,1,n);
            else
                flip(line1,line2,line3,line4,0,n);

            for(i = 0; i < n;i++)
                FACES[1][i][lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][lineNo][i] = line2[i];
            for(i = 0; i < n;i++)
                FACES[3][i][n - 1 - lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][n - 1 - lineNo][i] = line4[i];
        }
    }
    if(faceNo == 2)
    {
        if(strcmp(lineType,"row") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[0][lineNo][i];
            for(i = 0;i < n;i++)
                line2[i] = FACES[1][lineNo][i];
            for(i = 0;i < n;i++)
                line3[i] = FACES[2][lineNo][i];
            for(i = 0;i < n;i++)
                line4[i] = FACES[3][lineNo][i];
            if(strcmp(direction,"right") == 0)
                flip(line1,line2,line3,line4,1,n);
            else
                flip(line1,line2,line3,line4,0,n);

            for(i = 0; i < n;i++)
                FACES[0][lineNo][i] = line1[i];
            for(i = 0; i < n;i++)
                FACES[1][lineNo][i] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][lineNo][i] = line3[i];
            for(i = 0; i < n;i++)
                FACES[3][lineNo][i] = line4[i];
        }
        else if(strcmp(lineType,"column") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[0][i][n-1-lineNo];
            for(i = 0;i < n;i++)
                line2[i] = FACES[5][i][n-1 - lineNo];
            for(i = 0;i < n;i++)
                line3[i] = FACES[2][i][lineNo];
            for(i = 0;i < n;i++)
                line4[i] = FACES[4][i][n-1-lineNo];
            if(strcmp(direction,"down") == 0)
            {
                flip(line1,line2,line3,line4,1,n);
            for(i = 0; i < n;i++)
                FACES[0][i][lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][i][lineNo] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][n-1-i][lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][n-1-i][lineNo] = line4[i];
            }
            else
            {
                flip(line1,line2,line3,line4,0,n);
            for(i = 0; i < n;i++)
                FACES[0][i][lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][n-1-i][lineNo] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][n-1-i][lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][i][lineNo] = line4[i];
            }
        }
    }
    if(faceNo == 3)
    {
        if(strcmp(lineType,"row") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[0][lineNo][i];
            for(i = 0;i < n;i++)
                line2[i] = FACES[1][lineNo][i];
            for(i = 0;i < n;i++)
                line3[i] = FACES[2][lineNo][i];
            for(i = 0;i < n;i++)
                line4[i] = FACES[3][lineNo][i];
            if(strcmp(direction,"right") == 0)
                flip(line1,line2,line3,line4,1,n);
            else
                flip(line1,line2,line3,line4,0,n);

            for(i = 0; i < n;i++)
                FACES[0][lineNo][i] = line1[i];
            for(i = 0; i < n;i++)
                FACES[1][lineNo][i] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][lineNo][i] = line3[i];
            for(i = 0; i < n;i++)
                FACES[3][lineNo][i] = line4[i];
        }
        if(strcmp(lineType,"column") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[1][i][n - 1 - lineNo];
            for(i = 0;i < n;i++)
                line2[i] = FACES[5][n - 1 - lineNo][i];
            for(i = 0;i < n;i++)
                line3[i] = FACES[3][i][lineNo];
            for(i = 0;i < n;i++)
                line4[i] = FACES[4][lineNo][i];

            if(strcmp(direction,"up") == 0)
                flip(line1,line2,line3,line4,1,n);
            else
                flip(line1,line2,line3,line4,0,n);

            for(i = 0; i < n;i++)
                FACES[1][i][n - 1 - lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][n - 1 - lineNo][n - 1 - i] = line2[i];
            for(i = 0; i < n;i++)
                FACES[3][i][lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][lineNo][n - 1 - i] = line4[i];
        }
    }
    if(faceNo == 4)
    {
        if(strcmp(lineType,"row") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[1][i][n - 1 - lineNo];
            for(i = 0;i < n;i++)
                line2[i] = FACES[5][n - 1 - lineNo][i];
            for(i = 0;i < n;i++)
                line3[i] = FACES[3][i][lineNo];
            for(i = 0;i < n;i++)
                line4[i] = FACES[4][lineNo][i];

            if(strcmp(direction,"right") == 0)
                flip(line1,line2,line3,line4,1,n);
            else
                flip(line1,line2,line3,line4,0,n);

            for(i = 0; i < n;i++)
                FACES[1][i][n - 1 - lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][n - 1 - lineNo][i] = line2[i];
            for(i = 0; i < n;i++)
                FACES[3][i][lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][lineNo][i] = line4[i];
        }
        if(strcmp(lineType,"column") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[0][i][lineNo];
            for(i = 0;i < n;i++)
                line2[i] = FACES[5][i][lineNo];
            for(i = 0;i < n;i++)
                line3[i] = FACES[2][i][n - 1 - lineNo];
            for(i = 0;i < n;i++)
                line4[i] = FACES[4][i][lineNo];
            if(strcmp(direction,"down") == 0)
            {
                flip(line1,line2,line3,line4,1,n);
            for(i = 0; i < n;i++)
                FACES[0][i][lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][i][lineNo] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][n-1-i][lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][n-1-i][lineNo] = line4[i];
            }
            else
            {
                flip(line1,line2,line3,line4,0,n);
            for(i = 0; i < n;i++)
                FACES[0][i][lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][n-1-i][lineNo] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][n-1-i][lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][i][lineNo] = line4[i];
            }
        }

    }
    if(faceNo == 5)
    {
        if(strcmp(lineType,"row") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[1][i][lineNo];
            for(i = 0;i < n;i++)
                line2[i] = FACES[5][lineNo][i];
            for(i = 0;i < n;i++)
                line3[i] = FACES[3][i][n - 1 - lineNo];
            for(i = 0;i < n;i++)
                line4[i] = FACES[4][n - 1 - lineNo][i];

            if(strcmp(direction,"left") == 0)
                flip(line1,line2,line3,line4,1,n);
            else
                flip(line1,line2,line3,line4,0,n);

            for(i = 0; i < n;i++)
                FACES[1][i][lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][lineNo][n - i -1] = line2[i];
            for(i = 0; i < n;i++)
                FACES[3][i][n - 1 - lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][n - 1 - lineNo][n - i -1] = line4[i];
        }
        if(strcmp(lineType,"column") == 0)
        {
            for(i = 0;i < n;i++)
                line1[i] = FACES[0][i][lineNo];
            for(i = 0;i < n;i++)
                line2[i] = FACES[5][i][lineNo];
            for(i = 0;i < n;i++)
                line3[i] = FACES[2][i][n - 1 - lineNo];
            for(i = 0;i < n;i++)
                line4[i] = FACES[4][i][lineNo];
            if(strcmp(direction,"down") == 0)
            {
                flip(line1,line2,line3,line4,1,n);
            for(i = 0; i < n;i++)
                FACES[0][i][lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][i][lineNo] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][n-1-i][lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][n-1-i][lineNo] = line4[i];
            }
            else
            {
                flip(line1,line2,line3,line4,0,n);
            for(i = 0; i < n;i++)
                FACES[0][i][lineNo] = line1[i];
            for(i = 0; i < n;i++)
                FACES[5][n-1-i][lineNo] = line2[i];
            for(i = 0; i < n;i++)
                FACES[2][n-1-i][lineNo] = line3[i];
            for(i = 0; i < n;i++)
                FACES[4][i][lineNo] = line4[i];
            }
        }
    }
    if(feof(fptr))
        break;
    }
    fclose(fptr);
    fptr = fopen("result.txt","w");
    for(k = 0;k < 6;k++)
    {
        for(i = 0;i < n;i++)
        {
            for(j = 0;j < n;j++)
            {
                fprintf(fptr,"%d",FACES[k][i][j]);
            }
        fprintf(fptr,"\n");
        }
    fprintf(fptr,"\n");
    }
    return 0;
}
