package Q2;

public class Main
{
    public static void main(String[] args)
    {
        BTree<Integer> tree1 = new BTree<>(5);
        BTree<Integer> tree2 = new BTree<>(4);
        for(int i = 1; i < 21; i++)
            tree1.add(2 * i);
        System.out.println("**********TEST CASE 1**********");
        System.out.println(tree1);
        for(int i = 20; i > 10; i--)
            tree2.add(i);
        tree2.add(1);
        tree2.add(3);
        tree2.add(5);
        tree2.add(25);
        tree2.add(45);
        tree2.add(6);
        tree2.add(46);
        tree2.add(7);
        tree2.add(9);
        System.out.println("**********TEST CASE 2**********");
        System.out.println(tree2);
    }
}
