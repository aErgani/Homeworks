package Q4;

import java.util.Random;

public class Main4
{

    public static void main(String args[])
    {
        Random rand = new Random();
        int size = 100000;
        Integer[] arr = new Integer[size];
        double start = 0;
        double totalTime = 0;
        for(int i = 0; i < size ; i++)
            arr[i] = rand.nextInt();
        HeapSort heapSort = new HeapSort();
        start = System.nanoTime();
        heapSort.sort(arr);
        totalTime = (System.nanoTime() - start) / 100000000.0;
        System.out.println(totalTime + " seconds passed. element count " + size);
        for(int i = 0; i < size ; i++)
            arr[i] = rand.nextInt();
        MergeSort mergeSort = new MergeSort();
        start = System.nanoTime();
        mergeSort.sort(arr);
        totalTime = (System.nanoTime() - start) / 100000000.0;
        System.out.println(totalTime + " seconds passed. element count " + size);
        int[] arr2 = new int[size];
        for(int i = 0; i < size ; i++)
            arr2[i] = rand.nextInt();
        QuickSort quickSort = new QuickSort();
        start = System.nanoTime();
        quickSort.sort(arr2,0,size-1);
        totalTime = (System.nanoTime() - start) / 100000000.0;
        System.out.println(totalTime + " seconds passed. element count " + size);
        for(int i = 0; i < size ; i++)
            arr[i] = rand.nextInt();
        InsertionSort insertionSort = new InsertionSort();
        start = System.nanoTime();
        insertionSort.sort(arr);
        totalTime = (System.nanoTime() - start) / 100000000.0;
        System.out.println(totalTime + " seconds passed. element count " + size);
    }
}
