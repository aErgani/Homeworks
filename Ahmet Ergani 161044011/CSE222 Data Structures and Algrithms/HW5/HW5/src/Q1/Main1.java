package Q1;

/**
 * Tests the Double Hashing Map Methods
 */
public class Main1
{
    public static void main(String args[])
    {
        DHMap<Integer,String> hashMap = new DHMap<>();
        if(hashMap.isEmpty())
            System.out.println("Table is empty");
        else
            System.out.println("Table is not empty");
        System.out.println("****ADDING 9 ENTRIES****");
        hashMap.put(1,"Ahmet");
        hashMap.put(2,"Onur");
        hashMap.put(3,"Enes");
        hashMap.put(4,"Alihan");
        hashMap.put(13,"Yasir");
        hashMap.put(34,"Yusuf");
        hashMap.put(17,"Akif");
        hashMap.put(8,"Mustafa");
        hashMap.put(7,"Elif");
        if(hashMap.isEmpty())
            System.out.println("Table is empty");
        else
            System.out.println("Table is not empty");
        hashMap.display();
        if(hashMap.containsKey(3))
            System.out.println("Table contains 3");
        else
            System.out.println("Table does not contain 3");
        if(hashMap.containsKey(12))
            System.out.println("Table contains 12");
        else
            System.out.println("Table does not contain 12");
        if(hashMap.containsValue("Alihan"))
            System.out.println("Table contains Alihan");
        else
            System.out.println("Table does not contain Alihan");
        if(hashMap.containsValue("Saruman"))
            System.out.println("Table contains Saruman");
        else
            System.out.println("Table does not contain Saruman");
        System.out.println("****ADDING 2 MORE ENTRIES TO EXCEED CAPACITY****");
        hashMap.put(128,"Levent");
        hashMap.put(427,"Musab");
        hashMap.display();
        System.out.println("****CREATING THE SECOND HASHMAP****");
        DHMap<Integer,String> hashMap2 = new DHMap<>();
        hashMap2.put(12,"celalettin");
        hashMap2.put(23,"selahattin");
        hashMap2.put(35,"nurettin");
        hashMap2.put(10,"nizamettin");
        hashMap2.put(16,"ziyaattin");
        hashMap2.display();
        System.out.println("****CLEAR THE FIRST HASHMAP AND COPY THE SECOND TO IT USING putAll() METHOD****");
        hashMap.clear();
        hashMap.putAll(hashMap2);
        hashMap.display();
    }
}
