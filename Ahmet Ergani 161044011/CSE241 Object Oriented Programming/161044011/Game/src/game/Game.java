/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package game;
import java.awt.GridLayout; 
import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame; 
import javax.swing.JPanel;
import java.awt.BorderLayout;
import java.awt.Color;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import java.security.InvalidParameterException;
import javax.swing.JScrollPane;
/**
 * Creates a JFrame and fills it according to a ConnecetFour game
 * @author Ahmet Ergani
 */

public class Game extends ConnectFour
{
    /**
     * This field is our JFrame, It has 2 JPanels
     */
    private JFrame gameFrame = new JFrame("GAME");
    /**
     * Represents a Cell with value 'X'
     */
    private final ImageIcon p1 = new ImageIcon("1.png");
    /**
     * Represents a Cell with value 'O'
     */
    private final ImageIcon p2 = new ImageIcon("2.png");
    /**
     * Represents a Cell with value 'x'
     */
    private final ImageIcon p1win = new ImageIcon("1win.png");
    /**
     * Represents a Cell with value 'o'
     */
    private final ImageIcon p2win = new ImageIcon("2win.png");
    /**
     * Represents an empty Cell
     */
    private final ImageIcon empty = new ImageIcon("empty.png");
    /**
     * This JPanel holds an array of JButtons
     */
    private final JPanel buttonPanel = new JPanel();
    /**
     * This JPanel holds a two-dimensional array of JLabels
     */
    private final JPanel boardPanel = new JPanel();
    /**
     * Scroll for vertical direction
     */
    private JScrollPane gameScroll;
    /**
     * This field will be assigned to JPanel buttonPanel
     */
    private final JButton[] gameButtons = new JButton[20];
    /**
     * This field will be assigned to JPanel boardPanel
     */
    private final JLabel[][] grid= new JLabel[20][20];
    /**
     * Fills the JPanel according to board array of ConnectFour Game
     */
    private void initBoardPanel()
    {
        for(int i = 0;i < size;i++)
            for(int j = 0;j<size;j++)
            {
                switch (board[size - i - 1][j].value) 
                {
                    case '.':
                        grid[i][j] = new JLabel(empty);
                        break;
                    case 'X':
                        grid[i][j] = new JLabel(p1);
                        break;
                    case 'O':
                        grid[i][j] = new JLabel(p2);
                        break;
                    case 'x':
                        grid[i][j] = new JLabel(p1win);
                        break;
                    case 'o':
                        grid[i][j] = new JLabel(p2win);
                        break;
                    default:
                        break;
                }
                boardPanel.add(grid[i][j]);
            }
        gameFrame.add(boardPanel,BorderLayout.SOUTH);
        gameScroll = new JScrollPane(boardPanel);
        gameScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        gameFrame.add(gameScroll,BorderLayout.CENTER);
    }
    /**
     * Creates the JFrame, initializes the JPanels and fills them
     * @param size Size of Board
     * @param choice PvP or PvAI
     */
    Game(int size,int choice)
    {
        super(size);
        if(size > 20)
            throw new InvalidParameterException("SIZE VALUE YOU ENTERED IS TOO BIG");
        playType = choice;
        ButtonHandler handler = new ButtonHandler();
        char A = 'A';
        String col = "A";
        buttonPanel.setLayout(new GridLayout(1,size));
        boardPanel.setLayout(new GridLayout(size,size));
        for(int i = 0;i < size; i++)
        {
            gameButtons[i] = new JButton(col);
            gameButtons[i].addActionListener(handler); 
            col = col.replace(A, ++A);
        }    
        for(int i = 0;i < size; i++)
            buttonPanel.add(gameButtons[i]); 
        gameFrame.add(buttonPanel, BorderLayout.NORTH);
        initBoardPanel();
        printBoard();
    }
    /**
     * recreates the JFrame if user choose change the settings after a GAME_END
     */
    private void restartNew()
    {
        buttonPanel.removeAll();
        if(size > 18)
            throw new InvalidParameterException("SIZE VALUE YOU ENTERED IS TOO BIG");
        ButtonHandler handler = new ButtonHandler();
        char A = 'A';
        String col = "A";
        buttonPanel.setLayout(new GridLayout(1,size));
        boardPanel.setLayout(new GridLayout(size,size));
        for(int i = 0;i < size; i++)
        {
            gameButtons[i] = new JButton(col);
            gameButtons[i].addActionListener(handler); 
            col = col.replace(A, ++A);
        }    
        for(int i = 0;i < size; i++)
            buttonPanel.add(gameButtons[i]); 
        gameFrame.add(buttonPanel, BorderLayout.NORTH); // add panel to JFrame
        initBoardPanel();
        printBoard();
    }
    /**
     * Synchronizes the JFrame's boardPanel with the board of ConnectFour game
     */
    private void syncBoard()
    {
        gameFrame.dispose();
        boardPanel.removeAll();
        gameFrame = new JFrame("GAME");
        gameFrame.setBackground(Color.yellow);
        gameFrame.add(buttonPanel, BorderLayout.NORTH); // add panel to JFrame
        gameFrame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        gameFrame.setSize(size*110, size*120); 
        gameFrame.setVisible( true );  
        initBoardPanel();
    }
    /**
     * Switches between X and O
     */
    private void changeXorO()
    {
        if(XorO == 'X')
            XorO = 'O';
        else
            XorO = 'X';
    }
    /**
     * Class that helps us declare what to do after JButton interactions
     */
    private class ButtonHandler implements ActionListener
    {
        /**
         * Tells runtime what to do after each JButton interaction
         * This method is the method that lets the user play the game
         * @param move is the JButton user pressed
         */
        @Override
        public void actionPerformed(ActionEvent move)
        {
            int P_no = 1;
            if(XorO == 'O')
                P_no = 2;
            boolean isLegal;
            column = move.getActionCommand().charAt(0);
            isLegal = play();
            if(!isLegal)
                JOptionPane.showMessageDialog(null,"that column is full");
            else if(playType != 0)
            {
                if(winCheck())
                {
                    lowerCase();
                    printBoard();
                    syncBoard();
                    JOptionPane.showMessageDialog(null,"YOU WIN PLAYER " + P_no);
                    if(JOptionPane.showConfirmDialog(null,"DO YOU WANT THE SAME SETTINGS FOR THE NEXT GAME?") != 0)
                    {
                        String strSize = JOptionPane.showInputDialog( "Enter the size of the board (from 5 to 18)" );
                        size = Integer.parseInt(strSize);
                        if(JOptionPane.showConfirmDialog( null,"SELECT 'YES' IF YOU WANT TO PLAY AGAINST MR OMNIPOTENT,\"SELECT 'NO' IF YOU WANT TO PLAY PVP" ) == 0)
                            playType = 0;
                        else
                            playType = 1;
                        initBoard();
                        restartNew();
                    }
                    else
                    {
                        initBoard();
                        syncBoard();
                    }
                }
                else if(livingCell == size*size)
                    JOptionPane.showMessageDialog(null,"DRAW");
                changeXorO();
                syncBoard();
            }
            else
            {
                if(winCheck())
                {
                    lowerCase();
                    printBoard();
                    syncBoard();
                    JOptionPane.showMessageDialog(null,"YOU WIN PLAYER " + P_no);
                    if(JOptionPane.showConfirmDialog(null,"DO YOU WANT THE SAME SETTINGS FOR THE NEXT GAME?") != 0)
                    {
                        String strSize = JOptionPane.showInputDialog( "Enter the size of the board (from 5 to 18)" );
                        size = Integer.parseInt(strSize);
                        if(JOptionPane.showConfirmDialog( null,"SELECT 'YES' IF YOU WANT TO PLAY AGAINST MR OMNIPOTENT,\"SELECT 'NO' IF YOU WANT TO PLAY PVP" ) == 0)
                            playType = 0;
                        else
                            playType = 1;
                        initBoard();
                        restartNew();
                    }
                    else
                    {
                        initBoard();
                        syncBoard();
                    }
                }
                else if(livingCell == size*size)
                    JOptionPane.showMessageDialog(null,"DRAW");
                mrOmniPotent();
                if(winCheck())
                {
                    lowerCase();
                    printBoard();
                    syncBoard();
                    JOptionPane.showMessageDialog(null,"MR OMNIPOTENT HAS WON AS EXPECTED");
                    if(JOptionPane.showConfirmDialog(null,"DO YOU WANT THE SAME SETTINGS FOR THE NEXT GAME?") != 0)
                    {
                        String strSize = JOptionPane.showInputDialog( "Enter the size of the board (from 5 to 18)" );
                        size = Integer.parseInt(strSize);
                        if(JOptionPane.showConfirmDialog( null,"SELECT 'YES' IF YOU WANT TO PLAY AGAINST MR OMNIPOTENT,\"SELECT 'NO' IF YOU WANT TO PLAY PVP" ) == 0)
                            playType = 0;
                        else
                            playType = 1;
                        initBoard();
                        restartNew();
                    }
                    else
                    {
                        initBoard();
                        syncBoard();
                    }
                }
                else if(livingCell == size*size)
                    JOptionPane.showMessageDialog(null,"DRAW");
                XorO = 'X';
                syncBoard();
            }    
            printBoard();
            
        } 
    } 
    /**
     * Creates a Game object. gets inputs
     * @param args the command line arguments
    */
    public static void main(String[] args) 
    {
        String strSize = JOptionPane.showInputDialog( "Enter the size of the board (from 5 to 18)" );
        int size = Integer.parseInt(strSize);
        int choice = JOptionPane.showConfirmDialog( null,"SELECT 'YES' IF YOU WANT TO PLAY AGAINST MR OMNIPOTENT,\"SELECT 'NO' IF YOU WANT TO PLAY PVP" );
        Game HW8;
        System.out.println("your choice is " + choice);
        if(choice == 0)
            HW8 = new Game(size,0);
        else
            HW8 = new Game(size,1);
        HW8.gameFrame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        HW8.gameFrame.setSize(size*110, size*120); 
        HW8.gameFrame.setVisible( true ); 
    }
}
