//
//  main.c
//  mergesort-threads
//
//  Created by karim fathy on 11/20/18.
//  Copyright © 2018 Fetouh. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
int arraySize;
typedef struct{
    int *array;
    int start, end;
}argo ;



void input_array(int array[100])
{
    FILE *fp;
    //input array from file
    fp = fopen("/Users/fetouh/Desktop/matrixthread/input.txt", "r");
    fscanf(fp, "%d", &arraySize);
    if(arraySize>100)
    { printf("maximum 100 elements");
        return;}
    int i=0;
    while(i<arraySize && !feof(fp))
    {
        
        
        fscanf (fp, "%d", &array[i]);
        
        i++;
    }
    fclose(fp);
}





void mergehalves(int array[],int start, int end, int middle)
{
    int i, j, k;
    
    int n1 = middle - start + 1;
    int n2 =  end - middle;
    
    
    int left[n1], right[n2]; //temp arrays
    
    
    for (i = 0; i < n1; i++) //fill arrays
        left[i] = array[start + i];
    for (j = 0; j < n2; j++)
        right[j] = array[middle + 1+ j];
    
    
    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            array[k] = left[i];
            i++;
        }
        else
        {
            array[k] = right[j];
            j++;
            //rest of  elements
        }
        k++;
    }
    
    
    while (i < n1)
    {
        array[k] = left[i];
        i++;
        k++;
    }
    
    
    while (j < n2)
    {
        array[k] = right[j];
        j++;
        k++;
    }
}
void* mergeS(void *data)
{
    argo* x=   (argo*)data;
    
    int start= x->start;
    int end=x->end;
    argo x1,x2;
    x1.array=x->array; // left part
    x2.array=x->array; // right part
    
    if(start<end)
    {
        
        int middle= (start+end)/2;
        
        pthread_t threads[2];
        x1.start=start;
        x1.end=middle;
        pthread_create(&threads[0], NULL, mergeS, (void *)&x1);
        x2.end=end;
        x2.start=middle+1;
        pthread_create(&threads[1], NULL, mergeS, (void *)&x2);
        
        for (int i = 0; i < 2; i++)
            pthread_join(threads[i], NULL);
   
        mergehalves(x->array,start,end,middle);
        
        
        
    }
    pthread_exit(NULL);
    
    
}
int main(int argc, const char * argv[]) {
    argo x;
    int array[100];
    input_array(array);
    int i=0;
    x.array=array;
    x.start=0;
    x.end=arraySize-1;
    pthread_t threads[1];
    pthread_create(&threads[0], NULL, mergeS, (void *)&x);
    pthread_join(threads[0], NULL);
    
    
    
    
    
    while(i<arraySize-1)
    {printf("%d ",x.array[i]);
        i++;
    }
    
    
    
    
    return 0;
    
}
