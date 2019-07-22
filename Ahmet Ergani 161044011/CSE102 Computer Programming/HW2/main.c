#include <stdio.h>


int main() {
    FILE *fp;
    float a[1000],b[250][250],averages[250],sum = 0.0,temp = 0.0;                           /*initialize and declaration part*/
    int i = 0,j = 0,count = 0,x = 0,y = 0,orderTemp = 0,order[250],size[250];
    for(i = 0;i < 250; i++)                     /*initializing order[] array*/
        order[i] = i;
    if(fp = fopen("input.txt","r"))             /*opening the file*/
    {
        printf("File successfully opened\n");   /*inform the user if successfull*/
        for (i = 0; !feof(fp) ; i++)            /*scanning the file while checkiing for the end of file*/
        {
            fscanf(fp,"%f",&a[i]);
            count++;
        }
        count--;                                /*prevention of a offby1 error*/
        fclose(fp);                             /*close the file after filling our float array with the inputs*/
        for (i = 0; i < count; ++i)                                 /*this loop scans the float array (a[]) and divides it to chunks and assign the chunks to the 2 dimensional array b[]*/
        {
            b[x][y] = a[i];
            if(a[i +1] == 0.0 && a[i +2] == 0.0 && a[i +3] == 0.0)
            {
                size[x] = y + 1;        /*we also hold every chunk's size in our size[] array*/
                x++;
                i = i + 3;
                y = -1;
            }
            y++;
        }
        size[x] = y;        /*the size of last chunk*/
        i = 0;
        while(1)                        /*this loop calculates each chunk's average and assign it to the averages[] array */
        {
            for(j = 0;j < size[i]; j++)
                sum = sum + b[i][j];
            averages[i] = sum / size[i];
            sum = 0;
            i++;
            if(b[i][0] == 0.0)          /*breaks the loop when it detects the empty cell*/
                break;
        }
        for(i=0 ; i<x ; i++)            /*this double loop is a bubble sort.While it sorts the averages[] array it also sorts our index array (order[])*/
            for(j=0 ; j<x-i ; j++)
            {
                if(averages[j]>averages[j+1])
                {
                    temp = averages[j];
                    averages[j] = averages[j+1];
                    averages[j+1] = temp;
                    orderTemp = order[j];       /*order[] array helps us during file-writing part*/
                    order[j] = order[j + 1];
                    order[j + 1] = orderTemp;
                }
            }
        fopen("output.txt","w");                /*opening the output file to write*/
        for(i = 0; i < 10; i++)
        {
            for(j = 0; j < size[order[i]];j++)          /*after the process we acquired an order[] array. for example if the 3rd chunk has the smallest average => order[0] will be equal to 3*/
            {
                  fprintf(fp,"%f ",b[order[i]][j]);     /*writing the file using the chunk array (b[]) and order array (order[])*/
            }
            fprintf(fp,"\n");
        }
        fclose(fp);         /*closing the file*/
        /*printf("order[0] = %d ",order[0]);
        printf("order[1] = %d ",order[1]);
        printf("order[2] = %d \n",order[2]);
        i = 0;
        while(1)
        {
            printf("averages[%d] = %f\n",i,averages[i]);
            if(averages[i + 1] == 0)
                break;
            i++;
        }
        printf("************************************\n");
        for(i = 0; i < 10; i++)
        {
            for(j = 0; j < size[order[i]];j++)
            {
                  printf("B[%d][%d] = %f\n",order[i],j,b[order[i]][j]);
            }
        }
        printf("************************************\n");
        for (i = 0; i < count; ++i)
        {
            printf("A[%d] = %f \n",i,a[i]);
        }*/
    }
    return 0;
}
