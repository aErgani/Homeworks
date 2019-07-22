package Q3;

import java.util.Random;

public class Main3
{
    public static void main(String args[])
    {
        System.out.println("****CREATING AN INTEGER LINKED LIST AND ADDING 20 RANDOM ELEMENTS****");
        MSwDLL<Integer> list = new MSwDLL<>();
        list.add(234);
        list.add(143);
        list.add(252);
        list.add(142);
        list.add(63);
        list.add(1515);
        list.add(12);
        list.add(1);
        list.add(5);
        list.add(25);
        list.add(32);
        list.add(2363262);
        list.add(12);
        list.add(23532);
        list.add(235);
        list.add(2352);
        list.add(325);
        list.add(258);
        list.add(7654);
        list.add(345);
        list.display();
        System.out.println("****SORTING LIST****");
        list.mergeSort(list.getHead());
        list.display();
        Random rand;
        MSwDLL<Integer> tempList;
        System.out.println("****100 ELEMENT LIST****");
        rand = new Random();
        tempList = new MSwDLL<>();
        for(int k = 0; k < 100; k++)
            tempList.add(rand.nextInt());
        long start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        double process = (System.nanoTime() - start) / 100000000.0;
        System.out.println(process + " * 10^(-4) seconds passed during process");
        System.out.println("****200 ELEMENT LIST****");
        rand = new Random();
        tempList = new MSwDLL<>();
        for(int k = 0; k < 200; k++)
            tempList.add(rand.nextInt());
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 100000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        System.out.println("****300 ELEMENT LIST****");
        rand = new Random();
        tempList = new MSwDLL<>();
        for(int k = 0; k < 300; k++)
            tempList.add(rand.nextInt());
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 100000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        System.out.println("****400 ELEMENT LIST****");
        rand = new Random();
        tempList = new MSwDLL<>();
        for(int k = 0; k < 400; k++)
            tempList.add(rand.nextInt());
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 100000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        System.out.println("****500 ELEMENT LIST****");
        rand = new Random();
        tempList = new MSwDLL<>();
        for(int k = 0; k < 500; k++)
            tempList.add(rand.nextInt());
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 100000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        System.out.println("****600 ELEMENT LIST****");
        rand = new Random();
        tempList = new MSwDLL<>();
        for(int k = 0; k < 600; k++)
            tempList.add(rand.nextInt());
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 100000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        System.out.println("****700 ELEMENT LIST****");
        rand = new Random();
        tempList = new MSwDLL<>();
        for(int k = 0; k < 700; k++)
            tempList.add(rand.nextInt());
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 100000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        System.out.println("****800 ELEMENT LIST****");
        rand = new Random();
        tempList = new MSwDLL<>();
        for(int k = 0; k < 800; k++)
            tempList.add(rand.nextInt());
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 100000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        System.out.println("****900 ELEMENT LIST****");
        rand = new Random();
        tempList = new MSwDLL<>();
        for(int k = 0; k < 900; k++)
            tempList.add(rand.nextInt());
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 100000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        System.out.println("****1000 ELEMENT LIST****");
        rand = new Random();
        tempList = new MSwDLL<>();
        for(int k = 0; k < 1000; k++)
            tempList.add(rand.nextInt());
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 100000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        System.out.println("Worst cases");
        /* ****************WORST CASE**************** */
        tempList = new MSwDLL<>();
        for(int i = 0; i < 500; i++)
        {
            tempList.add(i);
            i+=2;
        }
        for(int i = 1; i < 500; i++)
        {
            tempList.add(i);
            i+=2;
        }
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 1000000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        /* ****************WORST CASE**************** */
        tempList = new MSwDLL<>();
        for(int i = 0; i < 1000; i++)
        {
            tempList.add(i);
            i+=2;
        }
        for(int i = 1; i < 1000; i++)
        {
            tempList.add(i);
            i+=2;
        }
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 1000000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        /* ****************WORST CASE**************** */
        tempList = new MSwDLL<>();
        for(int i = 0; i < 1500; i+=2)
        {
            tempList.add(i);
        }
        for(int i = 1; i < 1500; i+=2)
        {
            tempList.add(i);
        }
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 1000000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
        /* ****************WORST CASE**************** */
        tempList = new MSwDLL<>();
        for(int i = 0; i < 2000; i++)
        {
            tempList.add(i);
            i+=2;
        }
        for(int i = 1; i < 2000; i++)
        {
            tempList.add(i);
            i+=2;
        }
        start = System.nanoTime();
        tempList.mergeSort(tempList.getHead());
        process = (System.nanoTime() - start) / 1000000000.0;
        System.out.println(process + " * 10^(-1) seconds passed during process");
    }
}
