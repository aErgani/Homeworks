package Q1;

import java.util.*;

/**
 * Hashed the key of map. Solves collisions with double hashing tactique
 * @param <K> key
 * @param <V> value
 */
public class DHMap<K,V> implements Map<K,V>
{
    /**
     * Holds current member count. Increases after each addition
     */
    private int size = 0;
    /**
     * Doubles itself if it is to be exceeded by size
     */
    private int capacity = 10;
    /**
     * Holds entries in their hash code indexes
     */
    private Entry<K,V>[] table;

    /**
     * Overrided tihs for better utilization
     * @param <K> key
     * @param <V> value
     */
    static class Entry<K,V> implements Map.Entry<K,V>
    {
        /**
         * key (arabic)
         */
        K miftah;
        /**
         * value (latin)
         */
        V valorem;

        /**
         * getter for key
         * @return miftah
         */
        @Override
        public K getKey()
        {
            return miftah;
        }

        /**
         * getter for value
         * @return valorem
         */
        @Override
        public V getValue()
        {
            return valorem;
        }

        /**
         * sets the Entry's value
         * @param value will be assigned to valorem
         * @return given value
         */
        @Override
        public V setValue(V value)
        {
            valorem = value;
            return value;
        }

        /**
         * Constructs the Entry
         * @param key will be assigned to miftah
         * @param value will be assigned to valorem
         */
        public Entry(K key, V value)
        {
            miftah = key;
            valorem = value;
        }
    }

    /**
     * getter for size
     * @return current member count
     */
    @Override
    public int size()
    {
        return size;
    }

    /**
     * checks the table to see if it is empty
     * @return false if size == 0, true if not
     */
    @Override
    public boolean isEmpty()
    {
        return size == 0;
    }

    /**
     * Checks the table's entries to find the given key
     * @param key desired key
     * @return true if it is in table , false if not
     */
    @Override
    public boolean containsKey(Object key)
    {
        for(int i = 0; i < capacity; i++)
            if(table[i] != null && table[i].getKey() == key)
                return true;
        return false;
    }

    /**
     * Checks the table's entries to find the given value
     * @param value desired value
     * @return true if it is in table , false if not
     */
    @Override
    public boolean containsValue(Object value)
    {
        for(int i = 0; i < capacity; i++)
            if(table[i] != null && table[i].getValue() == value)
                return true;
        return false;
    }

    /**
     * Searches the table like it is going to add the key to the table, till it finds the given key
     * @param key desired key
     * @return  the value of the Entry that has the given key
     */
    @Override
    public V get(Object key)
    {
        if(table[key.hashCode() % capacity].getKey() == key)
        {
            return table[key.hashCode() % capacity].getValue();
        }
        else
        {
            int hash2 = (7 - ((key.hashCode() % 7) % capacity));
            int i = 1;
            while(true)
            {
                int hash = ((key.hashCode() % capacity) + i * hash2) % capacity;
                if( table[hash].getKey() == key)
                {
                    return table[hash].getValue();
                }
                i++;
                if(i == size)
                    return null;
            }
        }
    }

    /**
     * Creates an Entry with the given value and key and adds it to table[key.hashCode()]. Uses double hashing if a collision occurs
     * @param key key of Entry
     * @param value value of Entry
     * @return value
     */
    @Override
    public V put(K key, V value)
    {
        if(size == capacity - 1)
        {
            Entry<K,V>[] newTable = table;
            resize(newTable);
        }
        if(table[key.hashCode() % capacity] == null)
        {
            table[key.hashCode() % capacity] = new Entry<>(key,value);
            size++;
            return value;
        }
        else
        {
            int hash2 = (7 - ((key.hashCode() % 7) % capacity));
            int i = 1;
            while(true)
            {
                int hash = ((key.hashCode() % capacity) + i * hash2) % capacity;
                //System.out.println(hash);
                if( table[hash] == null)
                {
                    table[hash] = new Entry<>(key,value);
                    size++;
                    return value;
                }
                i++;
            }
        }
    }

    /**
     * Nullifies the address of the Entry that has the given key, then adds every Entry to table again using put() method
     * @param key key value of soon to be deleted Entry
     * @return the deleted Entry if an Entry with given key exists, null if no Entry exists with the given key
     */
    @Override
    public V remove(Object key)
    {
        for(int i = 0; i < capacity; i++)
            if(table[i].getKey() == key)
            {
                V result = table[i].getValue();
                table[i] = null;
                Entry<K,V>[] newTable = table;
                capacity/=2;
                resize(newTable);
                return result;
            }
        return null;
    }

    /**
     * copies every Entry of an external map to this.table
     * @param m an external DHMap
     */
    @Override
    public void putAll(Map<? extends K, ? extends V> m)
    {
        Set<? extends Map.Entry<? extends K, ? extends V>> copy = m.entrySet();
        for(Map.Entry<? extends K, ? extends V> a : copy)
            this.put(a.getKey(),a.getValue());
    }

    /**
     * clears the table and assigns the size and capacity again
     */
    @Override
    public void clear()
    {
        size = 0;
        capacity = 10;
        table = (Entry<K,V>[]) new Entry[capacity];
    }

    /**
     * Creates a set that holds all the key values of each entry in the table
     * @return the created set
     */
    @Override
    public Set<K> keySet()
    {
        Set<K> keys = new LinkedHashSet<>();
        for(int i = 0; i < capacity; i++)
            if(table[i] != null)
                keys.add(table[i].getKey());
        return keys;
    }
    /**
     * Creates an arrayList that holds all the values of each entry in the table
     * @return the created arrayList
     */
    @Override
    public Collection<V> values()
    {
        ArrayList<V> values = new ArrayList<>();
        for(int i = 0; i < capacity; i++)
            if(table[i] != null)
                values.add(table[i].getValue());
        return values;
    }
    /**
     * Creates a set that holds all the entries in the table
     * @return the created set
     */
    @Override
    public Set<Map.Entry<K, V>> entrySet()
    {
        Set<Map.Entry<K,V>> entries = new LinkedHashSet<>();
        for(int i = 0; i < capacity; i++)
            if(table[i] != null)
                entries.add(table[i]);
        return entries;
    }

    /**
     * default constructor
     */
    public DHMap()
    {
        table = (Entry<K,V>[]) new Entry[capacity];
        for(int i = 0; i < capacity; i++)
            table[i] = null;
    }

    /**
     * doubles the capacity recreates the table
     * @param newTable a copy of table
     */
    private void resize(Entry<K,V>[] newTable)
    {
        System.out.println("    RESIZING");
        capacity*=2;
        size = 0;
        table = (Entry<K,V>[]) new Entry[capacity];
        for(int i = 0; i < capacity/2; i++)
            if(newTable[i] != null)
                put(newTable[i].getKey(),newTable[i].getValue());
    }

    /**
     * Prints the Entries in table with their indexes
     */
    public void display()
    {
        for(int i = 0; i < capacity ; i++)
            if(table[i] == null)
                System.out.println(i);
            else
                System.out.println(i + " " + table[i].getKey() + " " + table[i].getValue());
    }
}
