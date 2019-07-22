package Q1;

public class Main
{
    public static void main(String[] args)
    {
        RedBlackTree<Integer> tree1 = new RedBlackTree();
        RedBlackTree<Integer> tree2 = new RedBlackTree();
        System.out.println("**********TEST CASE 1**********");
        for(int i = 1; i < 24; i++)
            tree1.add(i);
        System.out.println(tree1);
        System.out.println("**********TEST CASE 2**********");
        for(int i = 1; i < 24; i++)
            tree2.add(3 * i);
        System.out.println(tree2);
    }
}
