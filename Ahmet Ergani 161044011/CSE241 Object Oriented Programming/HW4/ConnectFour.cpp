//
// Created by ahmet on 05-Nov-17.
//

#include "ConnectFour.h"
#include <fstream>

int ConnectFour::livingCell = 0;

int ConnectFour::initBoard()
{
    string line;
    ifstream file;
    int a = 0;
    if (boardType)							//this part is for creating a board without reading a file,which has no use in this homework.same algorithm as the HW3
    {
        board = new Cell *[height];
        for (int i = 0; i < height; ++i)
            board[i] = new Cell[width];

        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
            {
                board[i][j].setRow(i);
                board[i][j].setColumn(j);
            }
	boardType = false;
    } else									//and this part is for creating a board according to a file
    {
		cout << "filename = " << filename << endl;	//we just assign our member variables at the first opening
        file.open(filename);
        getline(file, line);
        width = line.size();
        while (true)
        {
            a++;
            if (file.eof())
                break;
            getline(file, line);
        }
        file.close();						//after we calculated our height and width we close the file
        height = a - 1;
        board = new Cell *[height];			//we allocate our board
        for (int i = 0; i < width; ++i)
            board[i] = new Cell[width];
        file.open(filename);				//then open the file again
        a = height - 1;
        while (true)						//and this time we read the values to our allocated board
        {
            getline(file, line);
            if (file.eof())
                break;
            for (int j = 0; j < width; j++)
            {
                board[a][j].setRow(a);
                board[a][j].setColumn(j);
                board[a][j].setValue(line[j]);
                if (board[a][j].getValue() == '*')
                {
                    totalDot++;
                    board[a][j].setValue('.');
                }
            }
            a--;

        }
    }

}

int ConnectFour::printBoard()
{
    auto A = 'A';
    if(!boardType)								//this is for the index line (A B C D E F ...)
    {
        for (int i = width; i > 0; --i)
        {
            cout << A << " ";
            A++;
        }
        cout << endl;
        for (int i = height - 1; i >= 0; --i)	//and this is the double loop that prints our board
        {
            for (int j = 0; j < width; ++j)
                cout << board[i][j].getValue() << " ";
            cout << endl;
        }
    }
}

int ConnectFour::play()
{
    int a = column - 'A';						//a will be our X coordinate
    for (int i = 0; i < height; ++i)			//starting from the bottom we search for a '.'
        if(board[i][a].getValue() == '.')
        {
            increaseLivingCell();				//we make the arrangements if we found one and return 1
            board[i][a].setValue(XorO);
            currentX = a;
            currentY = i;
            return 1;							//if there is none we return 0.that means the column is full
        }
    return 0;									
}

int ConnectFour::undoPlay()
{
    int a = column - 'A';
    for (int i = height - 1; i >= 0 ; --i)
        if(board[i][a].getValue() == 'X' || board[i][a].getValue() == 'O')
        {
            board[i][a].setValue('.');
            decreaseLivingCell();
            return 1;
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
				if(board[i][j].getValue() == ' ')
					save << 'E' << endl;
				else
                	save << board[i][j].getValue() << endl;
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
    for (int i = 1; i < height; ++i)
        delete [] board[i];
    //delete [] board;
    load >> hw;                                        //reading height, width
    height = hw;
    load >> hw;
    width = hw;
    boardType = true;
    initBoard();                                        //initializing the new vector
    if (load.is_open())
    {
        for (int i = 0; i < height; i++)                //reading and rearranging the board
        {
            for (int j = 0; j < width; j++)
            {
                load >> val;
				if(val == 'E')
	                board[i][j].setValue(' ');
				else
					board[i][j].setValue(val);
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

int ConnectFour::horizontal()                                       //this function counts the same neigbours in horizontal direction
{
    int horizontal = 0;                                             //this is our count
    for(int i = 1;i < 4;i++)
    {
        if(XorO == board[currentY][currentX + i].getValue())    // checking right neighbour(s)
            horizontal++;
        else
            break;                                                  //breaks if not same
    }
    for(int i = 1;i < 4;i++)
    {
        if(currentX - i < 0)                                        //checking if the location is in the boundaries or not
            break;
        if(XorO == board[currentY][currentX - i].getValue())    //checking left neighbours
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
        if(XorO == board[currentY + i][currentX].getValue())    //checking up neighbours
            vertical++;
        else
            break;
    }
    for(int i = 1;i < 4;i++)
    {
        if(currentY - i < 0)                                        //checking if the location is in the boundaries or not
            break;
        if(XorO == board[currentY - i][currentX].getValue())    //checking down neighbours
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
        if(XorO == board[currentY + i][currentX + i].getValue())//checking the up right neighbours
            fab++;
        else
            break;
    }
    for(int i = 1;i < 4;i++)
    {
        if(currentY - i < 0 || currentX - i < 0)                    //checking if the location is in the boundaries or not
            break;
        if(XorO == board[currentY - i][currentX - i].getValue())//checking the down left neighbours
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
            if(XorO == board[currentY + i][currentX - i].getValue())//checking the up left neighbours
                sab++;
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentY - i < 0)                                        //checking if the location is in the boundaries or not
                break;
            if(XorO == board[currentY - i][currentX + i].getValue())//checking the down right neighbours
                sab++;
            else
                break;
        }
        return sab;
    }
}

int ConnectFour::lowerCase()                                            //this function takes gets the winning cell and assigns it and it's neighbours the lowercase version of the XorO
{
    char lower = 'a' -
                 'A';                                             //this char will allow us to accomplish this operation
    board[currentY][currentX].setValue(XorO + lower);               //converting the case of the winning cell
    if (winDirection ==
        'h')                                         //according to  which direction the player won,we will enter one of those 4 if statements and scan the neighbours like the functions above[horizontal() vertical() firstAngleBisector() secondAngleBisector()]
    {                                                                   //horizontal() direction
        for (int i = 1; i < 4; i++)
        {
            if (XorO == board[currentY][currentX + i].getValue())
                board[currentY][currentX + i].setValue(XorO + lower);
            else
                break;
        }
        for (int i = 1; i < 4; i++)
        {
            if (currentX - i < 0)
                break;
            if (XorO == board[currentY][currentX - i].getValue())
                board[currentY][currentX - i].setValue(XorO + lower);
            else
                break;
        }
    }
    if (winDirection == 'v')
    {                                                                   //vertical() direction
        for (int i = 1; i < 4; i++)
        {
            if (XorO == board[currentY + i][currentX].getValue())
                board[currentY + i][currentX].setValue(XorO + lower);
            else
                break;
        }
        for (int i = 1; i < 4; i++)
        {
            if (currentY - i < 0)
                break;
            if (XorO == board[currentY - i][currentX].getValue())
                board[currentY - i][currentX].setValue(XorO + lower);
            else
                break;
        }
    }
    if (winDirection == 'f')
    {                                                                   //firstAngleBisector() direction
        for (int i = 1; i < 4; i++)
        {
            if (XorO == board[currentY + i][currentX + i].getValue())
                board[currentY + i][currentX + i].setValue(XorO + lower);
            else
                break;
        }
        for (int i = 1; i < 4; i++)
        {
            if (currentY - i < 0 || currentX - i < 0)
                break;
            if (XorO == board[currentY - i][currentX - i].getValue())
                board[currentY - i][currentX - i].setValue(XorO + lower);
            else
                break;
        }
    }
    if (winDirection == 's')
    {                                                                   //secondAngleBisector() direction
        for (int i = 1; i < 4; i++)
        {
            if (currentX - i < 0)
                break;
            if (XorO == board[currentY + i][currentX - i].getValue())
                board[currentY + i][currentX - i].setValue(XorO + lower);
            else
                break;
        }
        for (int i = 1; i < 4; i++)
        {
            if (currentY - i < 0)
            {
                break;
            }
            if (XorO == board[currentY - i][currentX + i].getValue())
                board[currentY - i][currentX + i].setValue(XorO + lower);
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
        winDirection = 'h';                   //in this situation funciton sets winDirection and returns 1
        return 1;
    }
    if(vertic >= 3)
    {
        winDirection = 'v';
        return 1;
    }if(fab >= 3)
    {
        winDirection = 'f';
        return 1;
    }if(sab >= 3)
    {
        winDirection = 's';
        return 1;
    }
    return 0;                                   //returns 0 if the player hasn't won yet
}

int ConnectFour::MrOmnipotent()                 //this function is our AI
{
    int random = rand();                        //this random int will help us move randomly
    XorO = 'O';
    for(int i = 0; i < width ; i++)             //first Mr Omnipotent checks every column to see if he has a chance to win
    {
        column = 'A' + i;                     //it simultaneously calls the functions play() and undoPlay()
        if(play())
        {
            if (winCheck())
                return 1;                           //it simply returns 1 if he can win since he already played
            undoPlay();
        }
    }
    XorO = 'X';                               //if  he canot win he will check if you are gonna win and if you are, he will prevent you
    for(int i = 0; i < width ; i++)
    {
        column = 'A' + i;                     //similar algorithm with the loop above only
        if (play())
        {
            if (winCheck())
            {
                undoPlay();                         //he calls undoPlay() sets XorO to his value then call play() again
                XorO = 'O';
                play();
                return 2;
            }
        undoPlay();
        }
    }
    XorO = 'O';                               //if no one is going to win, he plays randomly
    random = random % width;
    column = 'A' + random;
    play();
    return 0;
}

bool ConnectFour::Cell::operator==(const Cell& other) {return other.value == value;}	//we simply compare the values of both cell

bool ConnectFour::Cell::operator!=(const Cell& other) {return other.value != value;}

ConnectFour::Cell& ConnectFour::Cell::operator++()		//this overload is err... here yes,Don't know what it is for but here it is
{
    if(value == 'X')
        value = 'O';
    if(value == 'O')
        value = '.';
    if(value == '.')
        value = 'X';
}

ConnectFour::Cell& ConnectFour::Cell::operator--()
{
    if(value == 'X')
        value = '.';
    if(value == 'O')
        value = 'X';
    if(value == '.')
        value = 'O';
}


int ConnectFour::playGame()
{
    char inputPlayType;                             //playType is meant to hold the values 'c' 'C' 'p' and 'P'
    if(dontPlay != 2 )
    {
        printBoard();                               //printing the first initial empty board
        cout << "Here is your Board" << endl;
        cout << "Type 'P' if you want to play PvP. Type 'C' if you want to play against Mr. Omnipotent "
             << endl;                               //asking for playType
        cin >> inputPlayType;
        while (1)                                   //checking if the input is valid or not
        {
            if (inputPlayType != 'P' && inputPlayType != 'p' && inputPlayType != 'C' && inputPlayType != 'c')
            {
                cerr << "invalid input try something else" << endl;
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
        gameFinish = 0;
        return 0;
    }
    if (playType == 'P' || playType == 'p')
    {
        while (1)
        {
            XorO = 'X';
            cout << "Select a column player 1 , You may also LOAD or SAVE" << endl;
            cin >> command;
            while (1)                                                                    //This whole loop is for the move of player 1
            {
                while (1)                                                                //checking if the input is valid or not
                {
                    if (command != "LOAD" && command != "SAVE" && command.length() > 1)
                    {
                        cerr << "invalid input try something else player 1" << endl;
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
                    cin >> command;                                                     //since saving or loading is not a "move" we need to ask for a column this time
                }else if (command == "LOAD")                                             //same algorithm as SAVE
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
                        cerr << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                column = command[0];                                                    //this will be the column where wthe player will accomplish his MOVE
                if (play() == 1)
                {
                    break;                                                              //breaks after a succesfull play()
                } else if (play() == 0)                                                   //Checking if that column is full or empty
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
                gameFinish = 1;
                if(dontPlay != 2)
                {
                    return 1;
                }
                else
                {
                    decreaseLivingCell();
                    decreaseLivingCell();
                    break;
                }
            }else
            {
                printBoard();	
                if(totalDot == getLivingCell())										  //If there is no "win" situation we check for "draw" situation					
                {
                    cout << "DRAW" << endl;
                    return 1;
                }
            }

            XorO = 'O';                                                               //getting ready for player 2, setting XorO
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
                }else if (command == "LOAD")                                   //LOAD section
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
                        cerr << "invalid input try something else player 2" << endl;
                        cin >> command;
                    } else
                        break;
                }
                column = command[0];                                          //play() part
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
                gameFinish = 1;
                if(dontPlay != 2)
                    return 1;
                else
                {
                    decreaseLivingCell();
                    decreaseLivingCell();
                    break;
                }
            }else
            {
                printBoard();
                if(totalDot == getLivingCell())								//If there is no "win" situation we check for "draw" situation
                {
                    cout << "DRAW" << endl;
                    return 1;
                }
                if(dontPlay == 2)
                {
                    decreaseLivingCell();
                    decreaseLivingCell();
                    break;
                }
            }
        }
    }
    if(playType == 'C' || playType == 'c')                                               //This if statement is for the brave ones who challenge Mr Omnipotent
        while(1)
        {
            XorO = 'X';
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
                column = command[0];
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
                gameFinish = 1;
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
            {
                printBoard();
                if(totalDot == getLivingCell())								//If there is no "win" situation we check for "draw" situation
                {
                    cout << "DRAW" << endl;
                    return 1;
                }
            }
            MrOmnipotent();                                                     //after the player make his move calling the function MrOmnipotent()
            if (winCheck())                                                     //After his glorious victory,this part informs the user that he couldn't escaped the inevitable
            {
                lowerCase();
                printBoard();
                cout << "MR OMNIPOTENT WON AS EXPECTED" << endl;
                gameFinish = 1;
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
            {
                printBoard();
                if(totalDot == getLivingCell())									//If there is no "win" situation we check for "draw" situation
                {
                    cout << "DRAW" << endl;
                    return 1;
                }
            }
            if(dontPlay == 2)
            {
                decreaseLivingCell();
                decreaseLivingCell();
                break;
            }
        }
    return 0;
}
ConnectFour::~ConnectFour()
{
    for (int i = 1; i < height; i++)
        delete[] board[i];	
    //delete[] board;
}
ConnectFour::ConnectFour(const ConnectFour& other){*this = other;}

ConnectFour& ConnectFour::operator=(const ConnectFour& other)
{
    for (int i = 1; i < height; ++i)					//first we delete the board
        delete [] board[i];
    //delete [] board;
    height = other.height;								//then assign this object's variables with the other object's variables
    width = other.width;
    boardType = other.boardType;
    initBoard();										//then initialize the board again
    for (int i = 0; i < height; i++)					//copying the other object's board
        for (int j = 0; j < width; ++j)
        {
            board[i][j] = other.board[i][j];
        }
    column = other.column;
    return *this;										//returning the last state of the object
}

bool ConnectFour::operator==(const ConnectFour& other) const
{
    if(height != other.height)							//we first check if the heights and widths are the same
        return false;
    if(width != other.width)
        return false;
    for (int i = 0; i < height; ++i)					//if they are,we check every cell of the board
        for (int j = 0; j < width; ++j)
            if(board[i][j] != other.board[i][j])
                return false;
    return true;										//return true if all of those are same
}
bool ConnectFour::operator!=(const ConnectFour& other) const {return !(*this == other);}

istream& operator>>(istream& console ,ConnectFour::Cell& other)
{
    int r;												//we assign temporary values 
    char c,v;
    console >> r;										//get them and assign them to the necessary member variables
    other.row = r;
    console >> c;
    other.column = c;
    console >> v;
    other.value = v;
    return console;
}
ostream& operator<<(ostream& console ,const ConnectFour::Cell& other)
{
    console << other.value;								//we just extract the value of the cell
    return console;
}

void multiplayer(string file)
{
    int objectNo;									//we get filename for each object ,declare and init afterwards
	cout << "enter filename" << endl;
    cin >> file;
    ConnectFour GAME1(file);
	GAME1.setDontPlay(1);
	GAME1.playGame();
    cout << "Object 1 initialized" << endl;
    GAME1.setDontPlay(2);							//after each initialization we assign dontPlay 2.when dontPlay is 2 playGame() function allows both player to accomplish one move
    cout << "enter filename" << endl;
    cin >> file;
    ConnectFour GAME2(file);
	GAME2.setDontPlay(1);
    GAME2.playGame();
    cout << "Object 2 initialized" << endl;
    GAME2.setDontPlay(2);
    cout << "enter filename" << endl;
    cin >> file;
    ConnectFour GAME3(file);
	GAME3.setDontPlay(1);
    GAME3.playGame();
    cout << "Object 3 initialized" << endl;
    GAME3.setDontPlay(2);
    cout << "enter filename" << endl;
    cin >> file;
    ConnectFour GAME4(file);
	GAME4.setDontPlay(1);
    GAME4.playGame();
    cout << "Object 4 initialized" << endl;
    GAME4.setDontPlay(2);
    cout << "enter filename" << endl;
    cin >> file;
	ConnectFour GAME5(file);
	GAME5.setDontPlay(1);
    GAME5.playGame();
    cout << "Object 5 initialized" << endl;
    GAME5.setDontPlay(2);

	while(GAME1.getGameFinish() != 1 ||             //this loop breaks when all the games are finished
          GAME2.getGameFinish() != 1 ||
          GAME3.getGameFinish() != 1 ||
          GAME4.getGameFinish() != 1 ||
          GAME5.getGameFinish() != 1)
    {
        cout << "select object" << endl;
        cin >> objectNo;
        while(objectNo < 1 || objectNo > 5)
        {
            cout << "invalid input" << endl;
            cin >> objectNo;
        }
        switch(objectNo)                            //this switch lets us play the object we desire
        {
            case 1:
                if(GAME1.getGameFinish() == 1)
                {
                    cout << "this object is a finished game select another object" << endl;
                    break;
                }
                GAME1.playGame();
                break;
            case 2:
                if(GAME2.getGameFinish() == 1)
                {
                    cout << "this object is a finished game select another object" << endl;
                    break;
                }
                GAME2.playGame();
                break;
            case 3:
                if(GAME3.getGameFinish() == 1)
                {
                    cout << "this object is a finished game select another object" << endl;
                    break;
                }
                GAME3.playGame();
                break;
            case 4:
                if(GAME4.getGameFinish() == 1)
                {
                    cout << "this object is a finished game select another object" << endl;
                    break;
                }
                GAME4.playGame();
                break;
            case 5:
                if(GAME5.getGameFinish() == 1)
                {
                    cout << "this object is a finished game select another object" << endl;
                    break;
                }
                GAME5.playGame();
                break;
            default:
                break;
        }
    }

}

ConnectFour::ConnectFour(const string &a)
{
	cout << "a = " << a << endl;
	height = 0;
	width = 0;
	boardType = false;
	filename = a;
	initBoard();
}

ConnectFour::ConnectFour(int w,int h)
{
	boardType = true;
	height = h;
	width = w;
	initBoard();
}

ConnectFour::ConnectFour()
{
	boardType = true;
	width = 5;
	height = 5;
	initBoard();
}

