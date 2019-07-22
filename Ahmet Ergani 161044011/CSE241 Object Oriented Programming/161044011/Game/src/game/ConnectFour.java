/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package game;
import java.util.Random;
/**
 *This class is the java version of our console game ConnectFour
 * @author Ahmet Ergani
 */
public class ConnectFour 
{
    /**
     * This field holds the value hthat helps us determine which column we will add our Cell to 
     */
    protected char column;
    /**
     * This field holds 'X' or 'O'. It is for the cell type
     */
    protected char XorO = 'X';
    /**
     * This field holds which direction has at least 4 same Cells
     */
    protected char winDirection;
    /**
     * This field holds the size of an edge of our square sahped board
     */
    protected int size;
    /**
     * This field holds 0 if user is playing against AI, holds 1 or -1 otherwise
     */
    protected int playType;
    /**
     * This field holds our 2 dimensional square shaped array
     */
    protected Cell board[][];
    /**
     * This field is holds the count of non-empty Cells
     */
    protected static int livingCell = 0;
    /**
     * This field holds the current axis value
     */
    protected int currentX;
    /**
     * This field holds the current ordinate value
     */
    protected int currentY;
    /**
     * This constructor initializes the board using initBoard() method
     * @param s The size of board 
     */
    ConnectFour(int s)
    {
        size = s;
        initBoard();
    }
    /**
     * Our board contains this inner class's objects
     */
    protected class Cell
    {
        /**
         * Holds the axis of the Cell
         */
        private int col;
        /**
         * Holds the ordinate of the Cell
         */
        private int row;
        /**
         * Holds the value of the Cell ('X' or 'O')
         */
        public char value;
        void setCol(int c){col = c;}
        void setRow(int r){row = r;}
        /**
         * sets coordinates to zero and sets the value to 'X'
         */
        public Cell()
        {
            row = 0;
            col = 0;
            value = 'X';
        }
    }
    /**
     * Increases LivingCell amount by 1
     */
    void increaseLivingCell(){livingCell++;}
    /**
     * Decreases LivingCell amount by 1
     */
    void decreaseLivingCell(){livingCell--;}
    /**
     * This is the primary method of our class
     * Changes the value of the first empty cell (started from the bottom) with XorO
     * @return true if successful , false if the column is full
     */
    boolean play()
    {
        int a = column - 'A';                       
    for(int i = 0; i < size; i++)                   
    {
        if(board[i][a].value == '.')                
        {
            board[i][a].value = XorO;
            currentX = a;
            currentY = i;
            increaseLivingCell();                   
            return true;                               
        }
    }
    return false;                                       
    }
    /**
     * Allocates the board
     */
    void initBoard()
    {
        board = new Cell[size][size];
        for(int i = 0; i < size; i++)               
        {    
            for (int j = 0; j < size; j++)
            {
                board[i][j] = new Cell();
                board[i][j].value = '.';            
                board[i][j].setCol(j + 1);
                board[i][j].setRow(i + 1);
            }
        }
    }
    /**
     * prints the board to console
     */
    protected void printBoard()
    {
        char A = 'A';
        for(int i = 0; i < size; i++ )                 
            {
                System.out.print(A + " ");
                A++;
            }
        System.out.println("");
        for(int i = size - 1 ; i >= 0; i--)               
        {
            for (int j = 0; j < size; j++)
                System.out.print(board[i][j].value + " ");
            System.out.println("");
        }
    }
    /**
     * Empties the Cell that is at the top of current column
     * @return 1 if successful, 0 if not 
     */
    protected int undoPlay()
    {
        int a = column - 'A';
        for (int i = size - 1; i >= 0; i--)
        {
            if(board[i][a].value == 'X' || board[i][a].value == 'O' )
            {
                board[i][a].value = '.';
                decreaseLivingCell();
                return 1;
            }
        }
        return 0;
    }
    /**
     * Counts the neighbors at the horizontal direciton
     * @return neighbor count
     */
    protected int horizontal()                                       
    {
        int horizontal = 0;                                             
        for(int i = 1;i < 4;i++)
        {
            if(currentX+i <= size-1 && XorO == board[currentY][currentX + i].value)    
                horizontal++;
            else
                break;                                                  
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentX - i < 0)                                        
                    break;
            if(XorO == board[currentY][currentX - i].value)    
                horizontal++;
            else
                break;
        }
        return horizontal;                                              
    }
    /**
     * Counts the neighbors at the vertical direciton
     * @return neighbor count
     */
    protected int vertical()                                         
    {
        int vertical = 0;
        for(int i = 1;i < 4;i++)
        {
            if(currentY == size - 1)                                  
                break;
            if(XorO == board[currentY + i][currentX].value)    
                vertical++;
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentY - i < 0)                                        
                break;
            if(XorO == board[currentY - i][currentX].value)    
                vertical++;
            else
                break;
        }
        return vertical;
    }
    /**
     * Counts the neighbors at the diagonal direction
     * that is parallel to the first angle bisector
     * @return neighbor count
     */
    private int firstAngleBisector()                               
    {
        int fab = 0;
        for(int i = 1;i < 4;i++)
        {
            if(currentY == size - 1)                                  
                break;
            if(currentX+i <= size-1 && currentY+i <= size-1 && XorO == board[currentY + i][currentX + i].value)
                fab++;
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentY - i < 0 || currentX - i < 0)                    
                break;
            if(XorO == board[currentY - i][currentX - i].value)
                fab++;
            else
                break;
        }
        return fab;
    }
    /**
     * Counts the neighbors at the diagonal direction
     * that is parallel to the second angle bisector
     * @return neighbor count
     */
    private int secondAngleBisector()                                  
    {
        {
            int sab = 0;
            for(int i = 1;i < 4;i++)
            {
                if(currentX - i < 0 || currentY + i > size - 1)              
                    break;
                if(XorO == board[currentY + i][currentX - i].value)
                    sab++;
                else
                    break;
            }
            for(int i = 1;i < 4;i++)
            {
                if(currentY - i < 0)                                        
                    break;
                if(currentX+i <= size-1 && currentY-i >= 0 && XorO == board[currentY - i][currentX + i].value)
                    sab++;
                else
                    break;
            }
            return sab;
        }
    }
    /**
     * Lowers the case of characters of neighbours at the winning direction
     */
    protected void lowerCase()                                            
    {
        char lower = 'a' - 'A';                                             //this char will allow us to accomplish this operation
        board[currentY][currentX].value = (char) (XorO + lower);               //converting the case of the winning cell
        if(winDirection == 'h')                                         //according to  which direction the player won,we will enter one of those 4 if statements and scan the neighbours like the functions above[horizontal() vertical() firstAngleBisector() secondAngleBisector()]
        {                                                                   //horizontal() direction
            for(int i = 1;i < 4;i++)
            {
                if(currentX + i < size && XorO == board[currentY][currentX + i].value)
                    board[currentY][currentX + i].value = (char) (XorO + lower);
                else
                    break;
            }
            for(int i = 1;i < 4;i++)
            {
                if(currentX - i < 0)
                    break;
                if(currentX - i > 0 && XorO == board[currentY][currentX - i].value)
                    board[currentY][currentX - i].value = (char) (XorO + lower);
                else
                    break;
            }
        }
        if(winDirection == 'v')
        {                                                                   //vertical() direction
            for(int i = 1;i < 4;i++)
            {
                if(currentY + i < size && XorO == board[currentY + i][currentX].value)
                    board[currentY + i][currentX].value = (char) (XorO + lower);
                else
                    break;
            }
            for(int i = 1;i < 4;i++)
            {
                if(currentY - i < 0)
                    break;
                if(XorO == board[currentY - i][currentX].value)
                    board[currentY - i][currentX].value = (char) (XorO + lower);
                else
                    break;
            }
        }
        if(winDirection == 'f')
        {                                                                   //firstAngleBisector() direction
            for(int i = 1;i < 4;i++)
            {
                if(currentY + i < size && currentX + i < size && XorO == board[currentY + i][currentX + i].value)
                    board[currentY + i][currentX + i].value = (char) (XorO + lower);
                else
                    break;
            }
            for(int i = 1;i < 4;i++)
            {
                if(currentY - i < 0 || currentX - i < 0)
                    break;
                if(XorO == board[currentY - i][currentX - i].value)
                    board[currentY - i][currentX - i].value = (char) (XorO + lower);
                else
                    break;
            }
        }
        if(winDirection == 's')
        {                                                                   //secondAngleBisector() direction
            for(int i = 1;i < 4;i++)
            {
                if(currentX - i < 0 || currentY + i > size)
                    break;
                if(XorO == board[currentY + i][currentX - i].value)
                    board[currentY + i][currentX - i].value = (char) (XorO + lower);
                else
                    break;
            }
            for(int i = 1;i < 4;i++)
            {
                if(currentY - i < 0)
                    break;
                if(XorO == board[currentY - i][currentX + i].value)
                    board[currentY - i][currentX + i].value = (char) (XorO + lower);
                else
                    break;
            }
        }
    }
    /**
     * This method call the 4 neighbor counting methods and checks if any direction has 3 same neighbor
     * @return true if somebody has won, false if nobodys has won the game yet
     */
    protected boolean winCheck()                         
    {
        int horiz = 0, vertic = 0, fab = 0,sab = 0;
        horiz = horizontal();                       //how? by checking the return values of these 4 function
        vertic = vertical();
        fab = firstAngleBisector();
        sab = secondAngleBisector();
        if(horiz >= 3)                              //if one of these direction have the same 3 neighbours it means "WIN"
        {
            winDirection = 'h';                     //in this situation funciton sets winDirection and returns 1
            return true;
        }
        if(vertic >= 3)
        {
            winDirection = 'v';
            return true;
        }
        if(fab >= 3)
        {
            winDirection = 'f';
            return true;
        }
        if(sab >= 3)
        {
            winDirection = 's';
            return true;
        }
        return false;                                   //returns 0 if the player hasn't won yet
    }
    protected void mrOmniPotent()
    {
        XorO = 'O';
        char moveCol = 'A';
        for(int i = 0; i < size;i++)
        {
            column = (char) (moveCol + i);
            if(play())
            {
                if(winCheck())
                    return;
                else
                    undoPlay();
           }
        }
        XorO = 'X';
        for(int i = 0; i < size;i++)
        {
            column = (char) (moveCol + i);
            if(play())
            {
                if(winCheck())
                {
                    undoPlay();
                    XorO = 'O';
                    play();
                    return;
                }
                else
                    undoPlay();
           }
        }
        while(true)
        {
            Random random = new Random();
            int moveRandom = random.nextInt(size) + 0;
            XorO = 'O';
            column = (char) (moveCol + moveRandom);
            if(play())
                break;
        }
        XorO = 'X';
    }
}
