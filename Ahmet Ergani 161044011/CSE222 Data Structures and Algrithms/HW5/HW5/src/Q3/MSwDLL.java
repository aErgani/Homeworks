package Q3;

public class MSwDLL<E extends Comparable<E>>
{
    /**
     * beginning of linked list
     */
    private Node<E> head;
    /**
     * end of linked list
     */
    private Node<E> tail;

    /**
     * getter
     * @return head
     */
    public Node<E> getHead() {return head;}

    /**
     * basic doubly linked list node implementation
     * @param <E> data type
     */
    static class Node<E extends Comparable<E>>
    {
        /**
         * value that is being held
         */
        E data;
        /**
         * Next node
         */
        Node<E> Next = null;
        /**
         * previous node
         */
        Node<E> Before = null;

        /**
         * Constructs the node
         * @param item value that is to be held
         */
        Node(E item)
        {
            data = item;
        }
    }

    /**
     * creates a node then links it to the tail
     * @param item value of the node that will be created
     */
    public void add(E item)
    {
        Node temp = head;
        if(head == null)
        {
            head = new Node<>(item);
            tail = head;
        }
        else
        {
            temp = tail;
            tail.Next = new Node<>(item);
            tail = tail.Next;
            tail.Before = temp;
        }
    }

    /**
     * Sorts the given linked list and assigns the beginning of the result to head
     * @param node head of the linked list that will be sort
     * @return the head of sorted linked list
     */
    public Node<E> mergeSort(Node<E> node)
    {
        if (node == null || node.Next == null)
            return node;
        Node<E> newNode = split(node);
        node = mergeSort(node);
        newNode = mergeSort(newNode);
        return head = merge(node, newNode);
    }

    /**
     * Splits the given linked list to 2 linked lists
     * @param node head of the linked list that will be splitted
     * @return head of second linked list
     */
    private Node<E> split(Node<E> node)
    {
        Node<E> finish = node;
        Node<E> half = node;
        while (finish.Next != null && finish.Next.Next != null)
        {
            finish = finish.Next.Next;
            half = half.Next;
        }
        Node<E> result = half.Next;
        half.Next = null;
        return result;
    }

    /**
     * Merges the two linked list into a linked list
     * @param first first linked list
     * @param second second linked list
     * @return resulting linked ist
     */
    private Node<E> merge(Node<E> first, Node<E> second)
    {
        if(first == null)
            return second;
        if(second == null)
            return first;
        if(first.data.compareTo(second.data) < 0)
        {
            first.Next = merge(first.Next, second);
            first.Next.Before = first;
            first.Before = null;
            return first;
        }
        else
        {
            second.Next = merge(first, second.Next);
            second.Next.Before = second;
            second.Before = null;
            return second;
        }
    }

    /**
     * Prints the linked list
     */
    public void display()
    {
        Node<E> temp = head;
        while(true)
        {
            System.out.println(temp.data);
            if(temp.Next == null)
                break;
            temp = temp.Next;
        }
    }
}
