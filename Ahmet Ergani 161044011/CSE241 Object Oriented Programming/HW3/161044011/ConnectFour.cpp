//
// Created by ahmte on 17-Oct-17.
//

#include "ConnectFour.h"
#include <fstream>

using namespace std;

int ConnectFour::livingCell = 0;
int ConnectFour::play()                         //this function accomplishes move
{
    int a = column - 'A';                       //a will be our x coordinate
    for(int i = 0; i < height; i++)             //this loop slowly ascends X or O till "dot encounter", i will be our coordinate Y
    {
        if(gameCells[i][a].getValue() == '.')   //assigning the necessary variables when a "dot" is detected
        {
            gameCells[i][a].setValue(XorO);
            currentX = a;
            currentY = i;
            increaseLivingCell();               //increasing livingCell after each succesfull play
            return 1;                           //1 means a succesfull move
        }
    }
    return 0;                                   //0 means that column is full
}
int ConnectFour::undoPlay()                     //this function descends from top unlike play() and it assigns dot to the last played cells. NOTE: this function is for Mr. Omnipotent
{
        int a = column - 'A';
        for (int i = height - 1; i >= 0; i--)
        {
            if(gameCells[i][a].getValue() == 'X' || gameCells[i][a].getValue() == 'O')
            {
                gameCells[i][a].setValue('.');
                break;
            }
        }
}
int ConnectFour::save()
{
    ofstream save;                                      //"save" is our ofstream
    save.open(filename);                                //opening the file
    save << height << endl;                             //height, width and livingcell are at the top of the savefile
    save << width << endl;
    if (save.is_open())                                 //checking if it's opened or not just in case of an error
    {
        for (int i = 0; i < height; i++)                //writing the board to the file
        {
            for (int j = 0; j < width; j++)
            {
                save << gameCells[i][j].getValue() << endl;
            }
        }
    }
    else cerr << "FILE OPEN ERROR";                     //if program fails to open the file
    save.close();                                       //closing the file
    return 1;
}
int ConnectFour::load()
{
    int hw = 0;                                        //hwl temporarily holds height and width
    char val;                                           //value temporarily hold value
    ifstream load;                                      //load is our ifstream
    load.open(filename);                                //opening the file
    while(getLivingCell() > 0)                          //making our livingCell 0
        decreaseLivingCell();
    gameCells.clear();                                  //clearing our vector
    load >> hw;                                        //reading height, width
    setHeight(hw);
    load >> hw;
    setWidth(hw);
    initBoard();                                        //initializing the new vector
    if (load.is_open())
    {
        for (int i = 0; i < height; i++)                //reading and rearranging the board
        {
            for (int j = 0; j < width; j++)
            {
                load >> val;
                gameCells[i][j].setValue(val);
                if(val == 'X' || val == 'O')
                    increaseLivingCell();
            }
        }
    }
    else cerr << "FILE OPEN ERROR";                     //if program fails to open the file
    load.close();                                       //closing the file
    printBoard();
    return 1;
}
int ConnectFour::initBoard()                            //this function initializes the board
{
    for(int i = 0; i < height; i++)                     //this double loop creates and fills the cells
    {
        gameCells.push_back(vector<Cell> (width));
        for (int j = 0; j < width; j++)
        {
            gameCells[i][j].setValue('.');              //setting necessary variables
            gameCells[i][j].setColumn(j + 1);
            gameCells[i][j].setRow(i + 1);
        }
    }
    return 1;
}
int ConnectFour::printBoard()                           //this function prints the board
{
    auto A = 'A';
    for(int i = 0; i < width; i++ )                     //printing the index line. for example if our width is 5 this line will be "A B C D E"
    {
        cout << A << " ";
        A++;
    }
    cout<<endl;
    for(int i = height - 1 ; i >= 0; i--)               //a double loop that similar to the one in initBoard(),it prints the value of  each cell and a " "
    {
        for (int j = 0; j < width; j++)
            cout << gameCells[i][j].getValue()<<" ";
        cout << endl;
    }
    return 1;
}
int ConnectFour::horizontal()                                       //this function counts the same neigbours in horizontal direction
{
    int horizontal = 0;                                             //this is our count
    for(int i = 1;i < 4;i++)
    {
        if(XorO == gameCells[currentY][currentX + i].getValue())    // checking right neighbour(s)
            horizontal++;
        else
            break;                                                  //breaks if not same
    }
    for(int i = 1;i < 4;i++)
    {
        if(currentX - i < 0)                                        //checking if the location is in the boundaries or not
                break;
        if(XorO == gameCells[currentY][currentX - i].getValue())    //checking left neighbours
            horizontal++;
        else
            break;
    }
    return horizontal;                                              //return the count
}
int ConnectFour::vertical()                                         //this function counts the same neigbours in vertical direction. uses an algorithm that nearly same with horizontal()
{
    int vertical = 0;
    for(int i = 1;i < 4;i++)
    {
        if(currentY == height - 1)                                  //checking if the location is in the boundaries or not
            break;
        if(XorO == gameCells[currentY + i][currentX].getValue())    //checking up neighbours
            vertical++;
        else
            break;
    }
    for(int i = 1;i < 4;i++)
    {
        if(currentY - i < 0)                                        //checking if the location is in the boundaries or not
            break;
        if(XorO == gameCells[currentY - i][currentX].getValue())    //checking down neighbours
            vertical++;
        else
            break;
    }
    return vertical;
}
int ConnectFour::firstAngleBisector()                               //this function counts the same neighbours in a direction which is parallel to FIRST ANGLE BISECTOR. uses an algorithm that nearly same with horizontal()
{
    int fab = 0;
    for(int i = 1;i < 4;i++)
    {
        if(currentY == height - 1)                                  //checking if the location is in the boundaries or not
            break;
        if(XorO == gameCells[currentY + i][currentX + i].getValue())//checking the up right neighbours
            fab++;
        else
            break;
    }
    for(int i = 1;i < 4;i++)
    {
        if(currentY - i < 0 || currentX - i < 0)                    //checking if the location is in the boundaries or not
            break;
        if(XorO == gameCells[currentY - i][currentX - i].getValue())//checking the down left neighbours
            fab++;
        else
            break;
    }
    return fab;
}
int ConnectFour::secondAngleBisector()                                  //this function counts the same neighbours in a direction which is parallel to SECOND ANGLE BISECTOR. uses an algorithm that nearly same with horizontal()
{
    {
        int sab = 0;
        for(int i = 1;i < 4;i++)
        {
            if(currentX - i < 0 || currentY == height - 1)              //checking if the location is in the boundaries or not
                break;
            if(XorO == gameCells[currentY + i][currentX - i].getValue())//checking the up left neighbours
                sab++;
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentY - i < 0)                                        //checking if the location is in the boundaries or not
                break;
            if(XorO == gameCells[currentY - i][currentX + i].getValue())//checking the down right neighbours
                sab++;
            else
                break;
        }
        return sab;
    }
}
int ConnectFour::lowerCase()                                            //this function takes gets the winning cell and assigns it and it's neighbours the lowercase version of the XorO
{
    char lower = 'a' - 'A';                                             //this char will allow us to accomplish this operation
    gameCells[currentY][currentX].setValue(XorO + lower);               //converting the case of the winning cell
    if(getWinDirecton() == 'h')                                         //according to  which direction the player won,we will enter one of those 4 if statements and scan the neighbours like the functions above[horizontal() vertical() firstAngleBisector() secondAngleBisector()]
    {                                                                   //horizontal() direction
        for(int i = 1;i < 4;i++)
        {
            if(XorO == gameCells[currentY][currentX + i].getValue())
                gameCells[currentY][currentX + i].setValue(XorO + lower);
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentX - i < 0)
                break;
            if(XorO == gameCells[currentY][currentX - i].getValue())
                gameCells[currentY][currentX - i].setValue(XorO + lower);
            else
                break;
        }
    }
    if(getWinDirecton() == 'v')
    {                                                                   //vertical() direction
        for(int i = 1;i < 4;i++)
        {
            if(XorO == gameCells[currentY + i][currentX].getValue())
                gameCells[currentY + i][currentX].setValue(XorO + lower);
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentY - i < 0)
                break;
            if(XorO == gameCells[currentY - i][currentX].getValue())
                gameCells[currentY - i][currentX].setValue(XorO + lower);
            else
                break;
        }
    }
    if(getWinDirecton() == 'f')
    {                                                                   //firstAngleBisector() direction
        for(int i = 1;i < 4;i++)
        {
            if(XorO == gameCells[currentY + i][currentX + i].getValue())
                gameCells[currentY + i][currentX + i].setValue(XorO + lower);
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentY - i < 0 || currentX - i < 0)
                break;
            if(XorO == gameCells[currentY - i][currentX - i].getValue())
                gameCells[currentY - i][currentX - i].setValue(XorO + lower);
            else
                break;
        }
    }
    if(getWinDirecton() == 's')
    {                                                                   //secondAngleBisector() direction
        for(int i = 1;i < 4;i++)
        {
            if(currentX - i < 0)
                break;
            if(XorO == gameCells[currentY + i][currentX - i].getValue())
                gameCells[currentY + i][currentX - i].setValue(XorO + lower);
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentY - i < 0)
            {
                break;
            }
            if(XorO == gameCells[currentY - i][currentX + i].getValue())
                gameCells[currentY - i][currentX + i].setValue(XorO + lower);
            else
                break;
        }
    }
    return 1;
}
int ConnectFour::winCheck()                     //this function checks if the last player who played won or not
{
    int horiz = 0, vertic = 0, fab = 0,sab = 0;
    horiz = horizontal();                       //how? by checking the return values of these 4 function
    vertic = vertical();
    fab = firstAngleBisector();
    sab = secondAngleBisector();
    if(horiz >= 3)                              //if one of these direction have the same 3 neighbours it means "WIN"
    {
        setWinDirection('h');                   //in this situation funciton sets winDirection and returns 1
        return 1;
    }
    if(vertic >= 3)
    {
        setWinDirection('v');
        return 1;
    }if(fab >= 3)
    {
        setWinDirection('f');
        return 1;
    }if(sab >= 3)
    {
        setWinDirection('s');
        return 1;
    }
    return 0;                                   //returns 0 if the player hasn't won yet
}
int ConnectFour::MrOmnipotent()                 //this function is our AI
{
    int random = rand();                        //this random int will help us move randomly
    setXorO('O');
    for(int i = 0; i < width ; i++)             //first Mr Omnipotent checks every column to see if he has a chance to win
    {
        setColumn('A' + i);                     //it simultaneously calls the functions play() and undoPlay()
        play();
        if(winCheck())
            return 1;                           //it simply returns 1 if he can win since he already played
        undoPlay();
    }
    setXorO('X');                               //if  he canot win he will check if you are gonna win and if you are, he will prevent you
    for(int i = 0; i < width ; i++)
    {
        setColumn('A' + i);                     //similar algorithm with the loop above only
        play();
        if(winCheck())
        {
            undoPlay();                         //he calls undoPlay() sets XorO to his value then call play() again
            setXorO('O');
            play();
            return 2;
        }
        undoPlay();
    }
    setXorO('O');                               //if no one is going to win, he plays randomly
    random = random % width;
    setColumn('A' + random);
    play();
    return 0;
}
int ConnectFour::playGame()                         //this is _-*"THE FUNCTION"*-_ :)
{
    char inputPlayType;                             //playType is meant to hold the values 'c' 'C' 'p' and 'P'
    int inputHeight, inputWidth;                    //inputHeight will be used to set height inputWidth will be used to set witdh
    if(dontPlay != 2 )
    {
        cout << "Enter Height" << endl;             //asking the height and width from the user
        cin >> inputHeight;
        cout << "Enter Width" << endl;
        cin >> inputWidth;
        setHeight(inputHeight);                     //setting part
        setWidth(inputWidth);
        cout << "Initializing Board" << endl;
        initBoard();                                //initializing the values
        printBoard();                               //printing the first initial empty board
        cout << "Here is your Board" << endl;
        cout << "Type if you 'P' if you want to play PvP. Type 'C' if you want to play against Mr. Omnipotent "
             << endl;    //asking for playType
        cin >> inputPlayType;
        while (1)       //checking if the input is valid or not
        {
            if (inputPlayType != 'P' && inputPlayType != 'p' && inputPlayType != 'C' && inputPlayType != 'c')
            {
                cout << "invalid input try something else" << endl;
                cin >> inputPlayType;
            } else
            {
                playType = inputPlayType;
                break;
            }
        }
    }
    if(dontPlay == 1)
    {
        setGameFinish(0);
        return 0;
    }
    if (playType == 'P' || playType == 'p')
    {
        while (1)
        {
            cout << "livingCell : " << getLivingCell() << endl;
            setXorO('X');
            cout << "Select a column player 1 , You may also LOAD or SAVE" << endl;
            cin >> command;
            while (1)                                                                    //This whole loop is for the move of player 1
            {
                while (1)                                                                //checking if the input is valid or not
                {
                    if (command != "LOAD" && command != "SAVE" && command.length() > 1)
                    {
                        cout << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                if (command == "SAVE")                                                  //SAVE section
                {
                    cout << "enter file name player 1" << endl;                         //asking for a filename
                    cin >> filename;
                    save();                                                             //calling the save function
                    cout << "select a column player 1" << endl;
                    cin
                            >> command;                                                     //since saving or loading is not a "move" we need to ask for a column this time
                } else if (command == "LOAD")                                             //same algorithm as SAVE
                {
                    cout << "enter file name player 1" << endl;
                    cin >> filename;
                    load();
                    cout << "select a column player 1" << endl;
                    cin >> command;
                }
                while (1)                                                               //checking if the input is valid or not
                {
                    if (command.length() > 1)
                    {
                        cout << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                setColumn(
                        command[0]);                                                  //tthis will be the column where wthe player will accomplish his MOVE
                if (play() == 1)
                {
                    break;                                                              //breaks after a succesfull play()
                } else if (play() ==
                           0)                                                   //Checking if that column is full or empty
                {
                    cerr << "that column is full try something else player 1"
                         << endl;  //asking another column if that one is full
                    cin >> command;
                }
            }
            if (winCheck())                                                             //Checking for WIN after each "move"
            {
                lowerCase();                                                            //calling lowerCase function, printing the board and informing the users after one of them has won
                printBoard();
                cout << "YOU WON PLAYER 1" << endl;
                setGameFinish(1);
                if(dontPlay != 2)
                    return 1;
                else
                {
                    decreaseLivingCell();
                    decreaseLivingCell();
                    break;
                }
            } else
                printBoard();

            setXorO('O');                                                               //getting ready for player 2, setting XorO
            cout << "Select a column player 2 , You may also LOAD or SAVE" << endl;
            cin >> command;
            while (1)                                                                   //everything is same as the while loop above except this time it's player 2
            {
                while (1)       //checking if the input is valid or not
                {
                    if (command != "LOAD" && command != "SAVE" && command.length() > 1)
                    {
                        cout << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                if (command == "SAVE")                                          //SAVE section
                {
                    cout << "enter file name player 2" << endl;
                    cin >> filename;
                    save();
                    cout << "select a column player 2" << endl;
                    cin
                            >> command;
                } else if (command == "LOAD")                                   //LOAD section
                {
                    cout << "enter file name player 2" << endl;
                    cin >> filename;
                    load();
                    cout << "select a column player 2" << endl;
                    cin >> command;
                }
                while (1)       //checking if the input is valid or not         //input validation check
                {
                    if (command.length() > 1)
                    {
                        cout << "invalid input try something else player 2" << endl;
                        cin >> command;
                    } else
                        break;
                }
                setColumn(command[0]);                                          //play() part
                if (play() == 1)
                    break;
                else if (play() == 0)
                {
                    cerr << "that column is full try something else player 2" << endl;
                    cin >> command;
                }
            }
            if (winCheck())                                 //Checking for WIN after each "move"
            {
                lowerCase();
                printBoard();
                cout << "YOU WON PLAYER 2" << endl;
                setGameFinish(1);
                if(dontPlay != 2)
                    return 1;
                else
                {
                    decreaseLivingCell();
                    decreaseLivingCell();
                    break;
                }
            } else
            {
                printBoard();
                if(dontPlay == 2)
                {
                    decreaseLivingCell();
                    decreaseLivingCell();
                    break;
                }
            }
        }
    }
    if(playType == 'C' || playType == 'c')                                               //This if statement is for the brave ones who challenge the Mr Omnipotent
        while(1)
        {
            setXorO('X');
            cout << "Select a column player 1 , You may also LOAD or SAVE" << endl;
            cin >> command;
            while (1)
            {
                while (1)       //checking if the input is valid or not
                {
                    if (command != "LOAD" && command != "SAVE" && command.length() > 1)
                    {
                        cout << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                if (command == "SAVE")                                          //SAVE section
                {
                    cout << "enter file name player 1" << endl;
                    cin >> filename;
                    save();
                    cout << "select a column player 1" << endl;
                    cin
                            >> command;
                } else if (command == "LOAD")                                   //LOAD section
                {
                    cout << "enter file name player 1" << endl;
                    cin >> filename;
                    load();
                    cout << "select a column player 1" << endl;
                    cin >> command;
                }
                while (1)                                                       //checking input validation
                {
                    if (command.length() > 1)
                    {
                        cout << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                setColumn(command[0]);
                if (play() == 1)                                                //play() part
                    break;
                else if (play() == 0)
                {
                    cerr << "that column is full try something else player 1" << endl;
                    cin >> command;
                }
            }
            if (winCheck())                                                     //Checking for WIN after each "move"
            {
                lowerCase();
                printBoard();
                cout << "YOU WON PLAYER 1" << endl;
                setGameFinish(1);
                if(dontPlay != 2)
                    return 1;
                else
                {
                    decreaseLivingCell();
                    decreaseLivingCell();
                    break;
                }
            }
            else
                printBoard();
            MrOmnipotent();                                                     //after the player make his move calling the function MrOmnipotent()
            if (winCheck())                                                     //After his glorious victory,this part informs the user that he couldn't escaped the inevitable
            {
                lowerCase();
                printBoard();
                cout << "MR OMNIPOTENT WON AS EXPECTED" << endl;
                setGameFinish(1);
                if(dontPlay != 2)
                    return 1;
                else
                {
                    decreaseLivingCell();
                    decreaseLivingCell();
                    break;
                }
            }
            else
                printBoard();
            if(dontPlay == 2)
            {
                decreaseLivingCell();
                decreaseLivingCell();
                break;
            }
        }
}

int ConnectFour::getHeight() const                                              //rest of these functions are getters and setters
{
    return height;
}

void ConnectFour::setHeight(int h)
{
    ConnectFour::height = h;
}

int ConnectFour::getWidth() const
{
    return width;
}

void ConnectFour::setWidth(int w)
{
    ConnectFour::width = w;
}
void ConnectFour::setXorO(char XO)
{
    ConnectFour::XorO = XO;
}


void ConnectFour::setColumn(char C)
{
    ConnectFour::column = C;
}

inline char ConnectFour::Cell::getValue() const
{
    return value;
}
inline void ConnectFour::Cell::setValue(char V)
{
    value = V;
}
void ConnectFour::Cell::setColumn(int C)
{
    column = C;
}
void ConnectFour::Cell::setRow(int R)
{
    row = R;
}

char ConnectFour::getWinDirecton() const
{
    return winDirection;
}

void ConnectFour::setWinDirection(char W)
{
    winDirection = W;
}
void ConnectFour::setDontPlay(int d)
{
    dontPlay = d;
}

int ConnectFour::getGameFinish() const
{
    return gameFinish;
}

void ConnectFour::setGameFinish(int g)
{
    gameFinish = g;
}

ConnectFour::Cell::Cell()
{
    setValue('.');
    setRow(0);
    setColumn(0);
}

ConnectFour::ConnectFour()
{
    height = 0;
    width = 0;
    currentX = 0;
    currentY = 0;
    dontPlay = 0;
    gameFinish = 0;
}
ConnectFour::ConnectFour(int a)
{
    height = a;
    width = a;
    currentX = a;
    currentY = a;
    dontPlay = a;
    gameFinish = a;
}