package Q5;

import Q4.HeapSort;
import Q4.InsertionSort;
import Q4.MergeSort;
import Q4.QuickSort;

public class Main5
{
    public static void main(String args[])
    {
        HeapSort heapSort = new HeapSort();
        QuickSort quickSort = new QuickSort();
        InsertionSort insertionSort = new InsertionSort();
        MergeSort mergeSort = new MergeSort();
        int size = 2000;

        Integer[] mergeArr = new Integer[size];
        int k = 0;
        for(int i = 0; i < size / 2; i++)
        {
            mergeArr[i] = k;
            k += 2;
        }
        k = 1;
        for(int i = size/2; i < size; i++)
        {
            mergeArr[i] = k;
            k += 2;
        }
        double start = System.nanoTime();
        mergeSort.sort(mergeArr);
        double process = (System.nanoTime() - start) / 1000000000.0;
        System.out.println("process time is " + process);

        Integer[] heapArr = new Integer[size];
        k = size;
        for(int i = 0; i < size; i++)
        {
            heapArr[i] = k;
            k--;
        }
        start = System.nanoTime();
        heapSort.sort(heapArr);
        process = (System.nanoTime() - start) / 1000000000.0;
        System.out.println("process time is " + process);

        int[] quickArr = new int[size];
        k = size;
        for(int i = 0; i < size; i++)
        {
            quickArr[i] = k;
            k--;
        }
        start = System.nanoTime();
        quickSort.sort(quickArr,0,size-1);
        process = (System.nanoTime() - start) / 1000000000.0;
        System.out.println("process time is " + process);

        Integer[] insertionArr = new Integer[size];
        k = size;
        for(int i = 0; i < size; i++)
        {
            insertionArr[i] = k;
            k--;
        }
        start = System.nanoTime();
        insertionSort.sort(insertionArr);
        process = (System.nanoTime() - start) / 1000000000.0;
        System.out.println("process time is " + process);
    }
}
