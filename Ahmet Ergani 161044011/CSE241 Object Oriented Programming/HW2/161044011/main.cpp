#include <iostream>
#include <fstream>
using namespace std;

int saveBoard(char board[][20], const int &a, string filename);
int loadBoard(char board[][20], int &a, string filename);
int initBoard(char board[][20],int a);
int printBoard(char board[][20],int a);
int move(char board[][20],char column,int a,int player);
int undoMove(char board[][20],char column,int a);
int horizontal(char board[][20],char XorO,int x,int y);
int vertical(char board[][20],char XorO,int x,int y);
int firstAngleBisector(char board[][20],char XorO,int x,int y);
int secondAngleBisector(char board[][20],char XorO,int x,int y);
int lowerCase(char board[][20],char a,int x,int y,char XorO);
int winCheck(char board[][20],char column,int a,int player);
char mrOmnipotent(char board[][20],int a,char XorO = 'O');          //default

int saveBoard(char board[][20], const int &a, string filename)      //this is our save function it also includes necessary "const parameter which we can call by reference"
{
    ofstream save;                                  //"save" is our ofstream
    save.open(filename);                            //opening the file
    save << a << endl;                              //size is at the top of the savefile
    if (save.is_open())                             //checking if it's opened or not just in case of an error
    {
         for (int i = 0; i < a; i++)                //writing the board to the file
         {
             for (int j = 0; j < a; j++)
             {
                 save << board[i][j] << endl;
             }
         }
    }
    else cerr << "FILE OPEN ERROR";                 //if program fails to open the file
    save.close();                                   //closing the file
    return 1;
}

int loadBoard(char board[][20], int &a, string filename)            //this is our save function it also includes necessary "parameter which we can call by reference"
{
    ifstream load;                          //"load" is our ifstream
    load.open(filename);                    //opening the file
    load >> a;                              //reading the "size" iwhich can be found located at the top of the savefile
    if (load.is_open())
    {
        for (int i = 0; i < a; i++)         //reading and rearranging the board
        {
            for (int j = 0; j < a; j++)
            {
                load >> board[i][j];
            }
        }
    }
    else cerr << "FILE OPEN ERROR";                 //if program fails to open the file
    load.close();                                   //closing the file
    return 1;
}

int initBoard(char board[][20],int a)           //This function initializes the board at the beginning
{
    for (int i = 0; i < a; i++)                 //Simple double loop fills all cells with dots
    {
        for (int j = 0; j < a; ++j)
        {
            board[i][j] = '.';
        }
    }
    return 1;
}

int printBoard(char board[][20],int a)          //This function prints all of the board when necessary
{
    auto A = 'A';                               //A is the first column
    for (int k = 0; k < a; ++k)                 //This loop prints the index line (ABCDEFGH)
    {
        cout << A << " ";
        A++;
    }
    cout << endl;                               //Line end
    for (int i = 0; i < a; i++)                 //This double loop prints our array as board, works similar as the function above
    {
        for (int j = 0; j < a; j++)
        {
            cout << board[a - i - 1][j] << " ";
        }
        cout << endl;                           //Line end
    }
    return 1;
}

int move(char board[][20],char column,int a,int player)            //This function manipulates the array as intended
{

    int b = column - 'A';               //b is our axis
    if(board[a - 1][b] != '.')          //This part checks the column,returns 0 if it's full
        return 0;
    for (int i = 0; i < a; i++)         //Loop starts from the bottom of the column
    {
        if(board[i][b] == '.')          //Dot means we are in the right cell
        {
            if(player == 1)             //Assigning that cell with an 'X' or an 'O' according to which player accomplished this move
            {
                board[i][b] = 'X';
                break;
            }
            if(player == 2)
            {
                board[i][b] = 'O';
                break;
            }
        }
    }
    return 1;                           //A successful move function returns 1
}

int undoMove(char board[][20],char column,int a)            //This function deletes the last added 'X' or 'O'
{
    int b = column - 'A';                                   //b is our axis
    for (int i = a; i >= 0; i--)                            //Loop starts from the top
    {
        if(board[i][b] == 'X' || board[i][b] == 'O')        //An 'X' or an 'O'  means we are at the right cell
        {
            board[i][b] = '.';                              //Assigning a dot to that cell
            break;
        }
    }
}

int horizontal(char board[][20],char XorO,int x,int y)              //This function checks and return how many neighbours are consistently same with the current cell in a horizontal line
{
    decltype(x) horizontal = 0;
    for (int j = 1; j < 4; j++)                             //This loop checks right neighbour cells till "dot encounter"
    {
        if(board[y][x + j] == XorO)
        {
            horizontal++;
        }
        else
            break;
    }
    for (int j = 1; j < 4; j++)                             //This loop checks left neighbour cells till "dot encounter"
    {
        if(board[y][x - j] == XorO)
            horizontal++;
        else
            break;
    }
    return horizontal;
}

int vertical(char board[][20],char XorO,int x,int y)                //This function checks and return how many neighbours are consistently same with the current cell in a vertical line
{
    decltype(x) vertical = 0;
    for (int j = 1; j < 4; j++)                             //This loop checks up neighbour cells till "dot encounter"
    {
        if(board[y + j][x] == XorO)
            vertical++;
        else
            break;
    }
    for (int j = 1; j < 4; j++)                             //This loop checks down neighbour cells till "dot encounter"
    {
        if(board[y - j][x] == XorO)
            vertical++;
        else
            break;
    }
    return vertical;
}

int firstAngleBisector(char board[][20],char XorO,int x,int y)      //This function checks and return how many neighbours are consistently same with the current cell in a line which is parallel to First Angle Bisector
{
    decltype(x) count = 0;
    for (int j = 1; j < 4; j++)
    {
        if(board[y + j][x + j] == XorO)                     //This loop checks up right neighbour cells till "dot encounter"
            count++;
        else
            break;
    }
    for (int j = 1; j < 4; j++)
    {
        if(board[y - j][x - j] == XorO)                     //This loop checks down left neighbour cells till "dot encounter"
            count++;
        else
            break;
    }
    return count;
}

int secondAngleBisector(char board[][20],char XorO,int x,int y)     //This function checks and return how many neighbours are consistently same with the current cell in a a line which is parallel to Second Angle Bisector
{
    decltype(x) count = 0;
    for (int j = 1; j < 4; j++)
    {
        if(board[y + j][x - j] == XorO)                     //This loop checks up left neighbour cells till "dot encounter"
            count++;
        else
            break;
    }
    for (int j = 1; j < 4; j++)
    {
        if(board[y - j][x + j] == XorO)                     //This loop checks down right neigbour cells till "dot encounter"
            count++;
        else
            break;
    }
    return count;
}

int lowerCase(char board[][20],char a,int x,int y,char XorO)        //This function replaces the 'X' or 'O' at the parameter coordinate and it's consistently same neighbours with the lowercase 'X' or 'O'
{
    char lowerCase = 'a' - 'A';
    board[y][x] = board[y][x] + lowerCase;
    switch(a)                                                       //We get winning direction as a parameter (Horizontal or Vertical or First Angle Bisector or Second Angle Bisector
    {                                                               //Following loops checks
        case 'h':
            for (int j = 1; j < 4; j++)                             //right neighbour cells
            {
                if (board[y][x + j] == XorO)
                {
                    board[y][x + j] = XorO + lowerCase;
                } else
                    break;
            }
            for (int j = 1; j < 4; j++)                             //left neighbour cells
            {
                if (board[y][x - j] == XorO)
                    board[y][x - j] = XorO + lowerCase;
                else
                    break;
            }
            break;
        case 'd':
            for (int j = 1; j < 4; j++)                             //up neighbour cells
            {
                if(board[y + j][x] == XorO)
                    board[y + j][x] = XorO + lowerCase;
                else
                    break;
            }
            for (int j = 1; j < 4; j++)                             //down neighbour cells
            {
                if(board[y - j][x] == XorO)
                    board[y - j][x] = XorO + lowerCase;
                else
                    break;
            }
            break;
        case 'f':
            for (int j = 1; j < 4; j++)
            {
                if(board[y + j][x + j] == XorO)                     // up right neighbour cells
                    board[y + j][x + j] = XorO + lowerCase;
                else
                    break;
            }
            for (int j = 1; j < 4; j++)
            {
                if(board[y - j][x - j] == XorO)                     // down left neighbour cells
                    board[y - j][x - j] = XorO + lowerCase;
                else
                    break;
            }
            break;
        case 's':
            for (int j = 1; j < 4; j++)
            {
                if(board[y + j][x - j] == XorO)                     // up left neighbour cells
                    board[y + j][x - j] = XorO + lowerCase;
                else
                    break;
            }
            for (int j = 1; j < 4; j++)
            {
                if(board[y - j][x + j] == XorO)                     // down right neighbour cells
                    board[y - j][x + j] = XorO + lowerCase;
                else
                    break;
            }
        default:
            break;
    }


}
int winCheck(char board[][20],char column,int a,int player)                         //This function checks if player or Mr Omnipotent accomplished winning with last move
{
    char XorO;                                                                      //This char holds either 'X' or 'O' which we get as a parameter
    int horiz = 0, vertic = 0, firstAngleBisec = 0,secondAngleBisec = 0,x = 0,y = 0;  //x and y will be the axis and ordinate of the last move,other integers will be the score,if one of them reaches "3" it means "WIN"
    int b = column - 'A';                                                           //b is our axis
    switch(player)                                                                  //This switch decides if we are working with an 'X' or an 'O' and assign it to the char 'XorO'
    {
        case 1 :
            XorO = 'X' ; break;
        case 2 :
            XorO = 'O'; break;
        default:
            break;
    }
    for (int i = a; i >= 0; i--)                        //loop starts from the top till an encounter with an 'X' or an 'O'
    {
        if(board[i][b] == 'X' || board[i][b] == 'O')
        {
            x = b;                                      //getting our coordinates when that encounter happens
            y = i;
            break;
        }
    }
    horiz = horizontal(board,XorO,x,y);                 //calling the functions and assigning the scores for each direction
    vertic = vertical(board,XorO,x,y);
    firstAngleBisec = firstAngleBisector(board,XorO,x,y);
    secondAngleBisec = secondAngleBisector(board,XorO,x,y);
    if(horiz == 3 || vertic == 3 || firstAngleBisec == 3 || secondAngleBisec == 3)    //Checking if any of them reached 3; if so, also lowercase the winning cells
    {
        if(horiz >= 3)
            lowerCase(board,'h',x,y,XorO);
        if(vertic >= 3)
            lowerCase(board,'d',x,y,XorO);
        if(firstAngleBisec >= 3)
            lowerCase(board,'f',x,y,XorO);
        if(secondAngleBisec >= 3)
            lowerCase(board,'s',x,y,XorO);
        return 1;                                       //win returns 1
    }
    else
        return 0;                                       //else, function returns 0
}

char mrOmnipotent(char board[][20],int a,char XorO)               //This is our AI , Mr Omnipotent (JIGSAW committed suicide after that homework did not get 100 points sadly)
{
    int columnP,columnC;
    int random = rand();                                //This is our random integer
    char fakeBoard[20][20];                             //This omnipotent AI initializes it's own fake board to check all the possible moves
    switch(XorO)
    {
        case 'O':
            columnP = 1;
            columnC = 2;
            break;
        case 'X':
            columnP = 2;
            columnC = 1;
            break;
        default:
            columnP = 1;
            columnC = 2;

    }
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < a; j++)
        {
            fakeBoard[i][j] = board[i][j];
        }
    }
    for (int i = 0; i < a; i++)                 //This part checks if any move can let him win
    {
        move(fakeBoard,'A'+i,a,2);                  //It accomplishes a move on the fake board
        if(winCheck(fakeBoard,'A'+i,a,columnC))           //Then check if it makes him win
        {
            cout << "Mr Omnipotent : I came I saw I won HAHAHAAA" << endl;      //If that move will make him win, it laughs insanely and accomplishes move on the real board
            move(board, 'A' + i, a, columnC);
            return ('A'+i);                         //It returns his last move as char for a fair check in the main function
        }
        undoMove(fakeBoard,'A'+i,a);                //If that move won't make him win it simply undo the move just to check other possibilities
    }
    for (int i = 0; i < a; i++)                 //This part checks if any move can let his opponent win
    {
        move(fakeBoard,'A'+i,a,1);                  //This time he accomplishes moves with 'X', yes like player 1
        if(winCheck(fakeBoard,'A'+i,a,columnP))           //Rest is the same algorithm
        {
            cout << "Mr Omnipotent : HAHAHAAA NOT SO FAST" << endl;             //He informs you too when he prevented you from winning
            move(board, 'A' + i, a, columnC);
            return ('A'+i);
        }
        undoMove(fakeBoard,'A'+i,a);
    }
    random = random % a;                         //If nobody is seeming to win Mr OmniPotent moves randomly using the random integer at the beginning of the function
    move(board,'A' + random,a,columnC);
    return ('A'+random);                         //It always returns his last move as char for a fair check in the main function
}

int main()
{
    int boardSize,player;
    char playType,board[20][20],AIMove;
    string column,filename;
    while(1)                                                                            //This loop gets the boardSize
    {
        cout << "Enter board size (an even number between 4 and 20 )" << endl;
        while(!(cin >> boardSize))                                                      //This loop is for noninteger inputs
        {
            cerr << "Invalid input, try something else" << endl;
            cout << "Enter board size (an even number between 4 and 20 )" << endl;
            cin.clear();
            while(cin.get()!= '\n')
                continue;
        }
        if(boardSize <= 20 && boardSize >= 4 && boardSize % 2 == 0)                     //This part is for integers that are smaller than 4, or bigger than 20, or uneven
            break;
        else
            cerr << "Invalid input, try something else" << endl;
    }
    initBoard(board,boardSize);                                                         //After successfully getting the size of the board we initialize the board
    cout << "type 'P' if you want to play PvP\ntype 'C' if you want to face Mr Omnipotent!" << endl;        //Asking if the game will be PvP or PvAI
    cin >> playType;
    while(playType != 'p' && playType != 'P' && playType != 'c' && playType != 'C')
    {
        cerr << "invalid input try again" << endl;
        cin >> playType;
    }
    printBoard(board,boardSize);                                                                           //Let player see the empty board
    if(playType == 'P' || playType == 'p')                                                                 //This loop is for PvP
    {
        while(1)
        {
            player = 1;                                                                 //player 1 is 'X' and player 2 is 'O'
            cout << "select a column player 1. you may also SAVE or LOAD" << endl;      //player can move or SAVE or LOAD
            cin >> column;
            while(1)                                                                    //This loop checks if the column is both "legal" and "not full" and accomplishes move
            {
                if(column == "SAVE")                                        //SAVE section
                {
                    cout << "enter file name" << endl;                      //asking for a filename
                    cin >> filename;
                    saveBoard(board,boardSize,filename);                    //calling our save function
                    cout << "select a column player 1" << endl;
                    cin >> column;                                          //since saving or loading is not a "move" we need to ask for a column this time
                }
                if(column == "LOAD")                                        //same algorithm as SAVE
                {
                    cout << "enter file name" << endl;
                    cin >> filename;
                    loadBoard(board,boardSize,filename);
                    cout << "select a column player 1" << endl;
                    cin >> column;
                }
                if(column[0] < 'A' || column[0] > 'A' + boardSize - 1 || column.length() > 1)                        //Checking if the input is valid or invalid
                {
                    cerr << "Invalid input. Try something else" << endl;
                    cin >> column;
                }
                else if(move(board, column[0], boardSize, player) == 1)
                    break;
                else if(move(board, column[0], boardSize, player) == 0)                    //Checking if that column is full or empty
                {
                    cerr << "that column is full try something else" << endl;
                    cin >> column;
                }
            }
            if(winCheck(board,column[0],boardSize,player))                                 //Checking for WIN after each "move"
            {
                cout << "YOU WON";                                                      //Inform the player and print for the last time
                printBoard(board,boardSize);
                break;
            }
            printBoard(board,boardSize);                                                //Prints board after each "move"
            player = 2;
            cout << "select a column player 2" << endl;                                 //Rest is the same algorithm, but this is player 2 this time
            cin >> column;
            while(1)
            {
                if(column == "SAVE")
                {
                    cout << "enter file name" << endl;
                    cin >> filename;
                    saveBoard(board,boardSize,filename);
                    cout << "select a column player 1" << endl;
                    cin >> column;
                }
                if(column == "LOAD")
                {
                    cout << "enter file name" << endl;
                    cin >> filename;
                    loadBoard(board,boardSize,filename);
                    cout << "select a column player 2" << endl;
                    cin >> column;
                }
                if(column[0] < 'A' || column[0] > 'A' + boardSize - 1 || column.length() > 1)
                {
                    cerr << "Invalid input. Try something else" << endl;
                    cin >> column;
                }
                else if(move(board, column[0], boardSize, player) == 1)
                    break;
                else if(move(board, column[0], boardSize, player) == 0)
                {
                    cerr << "that column is full try something else" << endl;
                    cin >> column;
                }
            }
            if(winCheck(board,column[0],boardSize,player))
            {
                cout << "YOU WON" << endl;
                printBoard(board,boardSize);
                break;
            }
            printBoard(board,boardSize);
        }
    }
    else if(playType == 'C' || playType == 'c')         //This loop is for PvAI
    {
        while(1)
        {
            player = 1;                                                         //Player 1 part is the same algorithm with PvP part above
            cout << "select a column player 1" << endl;
            cin >> column;
            while (1)
            {
                if(column == "SAVE")
                {
                    cout << "enter file name" << endl;
                    cin >> filename;
                    saveBoard(board,boardSize,filename);
                    cout << "select a column player 1" << endl;
                    cin >> column;
                }
                if(column == "LOAD")
                {
                    cout << "enter file name" << endl;
                    cin >> filename;
                    loadBoard(board,boardSize,filename);
                    cout << "select a column player 1" << endl;
                    cin >> column;
                }
                if (column[0] < 'A' || column[0] > 'A' + boardSize - 1 || column.length() > 1)
                {
                    cerr << "Invalid input. Try something else" << endl;
                    cin >> column;
                } else if (move(board, column[0], boardSize, player) == 1)
                    break;
                else if (move(board, column[0], boardSize, player) == 0)
                {
                    cerr << "that column is full try something else" << endl;
                    cin >> column;
                }
            }
            if (winCheck(board, column[0], boardSize, player))
            {
                cout << "You won" << endl;
                printBoard(board, boardSize);
                break;
            }
            printBoard(board, boardSize);
            player = 2;
            AIMove = mrOmnipotent(board, boardSize);                            //Remember that the AI function returns the move he decided as a char,we assign it to "AIMove"
            if(winCheck(board,AIMove,boardSize,player))                         //We check if Mr Omnipotent has won or not
            {
                cout << "Mr. Omnipotent won" << endl;                           //Informs the player he could not escape the inevitible
                printBoard(board, boardSize);
                break;
            }
            printBoard(board, boardSize);
        }
    }
    return 0;
}