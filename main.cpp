#include<bits/stdc++.h>
using namespace std;

#define MAXSIDE 30
#define MAXBAR 16
#define MAXMINES 99

int SIDE ; // side length of the board
int BAR ; // bar length of the board
int MINES ;// number of mines on the board

int Last_x[30];
int Last_y[30];
int Counter = 0;
int UndoMoves = 0;
char realBoard[MAXBAR][MAXSIDE], myBoard[MAXBAR][MAXSIDE];

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not
bool isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < BAR) &&
           (col >= 0) && (col < SIDE);
}

// A Function to print the current gameplay board
void printBoard(char MyBoard[MAXBAR][MAXSIDE])
{
    int i, j;

    printf (" ");

    for (i=0; i<SIDE; i++)
        printf ("%d ", i);

    printf ("\n\n");

    for (i=0; i<BAR; i++)
    {
        printf ("%d ", i);

        for (j=0; j<SIDE; j++)
            printf ("%c ", MyBoard[i][j]);
        printf ("\n");
    }
}


// A Utility Function to check whether given cell (row, col)
// has a mine or not.
bool isMine (int row, int col, char board[MAXBAR][MAXSIDE])
{
    if (board[row][col] == '*')
        return (true);
    else
        return (false);
}

// A Function to undo
void undoMove(int *x, int *y, char myboard[MAXBAR][MAXSIDE]) {
    if (UndoMoves > 0) {
        UndoMoves--;
        *x = Last_x[UndoMoves - 1];
        *y = Last_y[UndoMoves - 1];
        myBoard[Last_x[UndoMoves]][Last_y[UndoMoves]] = '-';
        printBoard(myboard);
        Counter -- ;
    } else {
        cout << "No more moves to undo!" << endl;
        *x = -1;
        *y = -1;
    }
}

// A Function to get the user's move
void makeMove(int *x, int *y,char pString[MAXBAR][MAXSIDE])
{
    // Take the input move
    printf("Enter your move, (row, column) or undo(-1, -1)-> ");
    scanf("%i %i", x, y);
    if (*x >= 0 && *y >= 0)
    {
        Last_y[Counter] = *y;
        Last_x[Counter] = *x;
        Counter++;
        UndoMoves++;
    }
    else
    {
        undoMove(x, y, pString);
    }

}

// A Function to count the number of
// mines in the adjacent cells
int countAdjacentMines(int row, int col,char Realboard[MAXBAR][MAXSIDE])
{
    int count = 0;

    /*
        Count all the mines in the 8 adjacent
        cells

            N.W N N.E
            \ | /
            \ | /
            W----Cell----E
                / | \
            / | \
            S.W S S.E

        Cell-->Current Cell (row, col)
        N --> North	 (row-1, col)
        S --> South	 (row+1, col)
        E --> East		 (row, col+1)
        W --> West		 (row, col-1)
        N.E--> North-East (row-1, col+1)
        N.W--> North-West (row-1, col-1)
        S.E--> South-East (row+1, col+1)
        S.W--> South-West (row+1, col-1)
    */

    //----------- 1st Neighbour (North) ------------

    // Only process this cell if this is a valid one
    if (isValid(row - 1, col))
    {
        if (isMine(row - 1, col, Realboard))
            count++;
    }

    //----------- 2nd Neighbour (South) ------------

    // Only process this cell if this is a valid one
    if (isValid(row + 1, col))
    {
        if (isMine(row + 1, col, Realboard))
            count++;
    }

    //----------- 3rd Neighbour (East) ------------

    // Only process this cell if this is a valid one
    if (isValid(row, col + 1))
    {
        if (isMine(row, col + 1, Realboard))
            count++;
    }

    //----------- 4th Neighbour (West) ------------

    // Only process this cell if this is a valid one
    if (isValid(row, col - 1))
    {
        if (isMine(row, col - 1, Realboard))
            count++;
    }

    //----------- 5th Neighbour (North-East) ------------

    // Only process this cell if this is a valid one
    if (isValid(row - 1, col + 1))
    {
        if (isMine(row - 1, col + 1, Realboard))
            count++;
    }

    //----------- 6th Neighbour (North-West) ------------

    // Only process this cell if this is a valid one
    if (isValid(row - 1, col - 1))
    {
        if (isMine(row - 1, col - 1, Realboard))
            count++;
    }

    //----------- 7th Neighbour (South-East) ------------

    // Only process this cell if this is a valid one
    if (isValid(row + 1, col + 1))
    {
        if (isMine(row + 1, col + 1, Realboard))
            count++;
    }

    //----------- 8th Neighbour (South-West) ------------

    // Only process this cell if this is a valid one
    if (isValid(row + 1, col - 1))
    {
        if (isMine(row + 1, col - 1, Realboard))
            count++;
    }

    return (count);
}

// A Recursive Function to play the Minesweeper Game
bool playMinesweeperUtil(int mines[][2], int row, int col, int *movesLeft)
{

    if (myBoard[row][col] != '-')
        return (false);

    int i;

    if (realBoard[row][col] == '*')
    {
        myBoard[row][col]='*';

        for (i=0; i<MINES; i++)
            myBoard[mines[i][0]][mines[i][1]]='*';

        printBoard (myBoard);
        printf ("\nYou lost!\n");
        return (true) ;
    }

    else
    {
        // Calculate the number of adjacent mines and put it
        // on the board
        int count = countAdjacentMines(row, col, realBoard);
        (*movesLeft)--;

        myBoard[row][col] = count + '0';
        if (!count)
        {
            /*
            Recur for all 8 adjacent cells

                N.W N N.E
                \ | /
                    \ | /
                W----Cell----E
                    / | \
                / | \
                S.W S S.E

            Cell-->Current Cell (row, col)
            N --> North	 (row-1, col)
            S --> South	 (row+1, col)
            E --> East		 (row, col+1)
            W --> West		 (row, col-1)
            N.E--> North-East (row-1, col+1)
            N.W--> North-West (row-1, col-1)
            S.E--> South-East (row+1, col+1)
            S.W--> South-West (row+1, col-1)
            */

            if (isValid(row - 1, col))
            {
                if (!isMine(row - 1, col, realBoard))
                    playMinesweeperUtil(mines, row-1, col, movesLeft);
            }
            if (isValid(row + 1, col))
            {
                if (!isMine(row + 1, col, realBoard))
                    playMinesweeperUtil(mines, row+1, col, movesLeft);
            }
            if (isValid(row, col + 1))
            {
                if (!isMine(row, col + 1, realBoard))
                    playMinesweeperUtil(mines, row, col+1, movesLeft);
            }
            if (isValid(row, col - 1))
            {
                if (!isMine(row, col - 1, realBoard))
                    playMinesweeperUtil(mines, row, col-1, movesLeft);
            }
            if (isValid(row - 1, col + 1))
            {
                if (!isMine(row - 1, col + 1, realBoard))
                    playMinesweeperUtil(mines, row-1, col+1, movesLeft);
            }
            if (isValid(row - 1, col - 1))
            {
                if (!isMine(row - 1, col - 1, realBoard))
                    playMinesweeperUtil(mines, row-1, col-1, movesLeft);
            }
            if (isValid(row + 1, col + 1))
            {
                if (!isMine(row + 1, col + 1, realBoard))
                    playMinesweeperUtil(mines, row+1, col+1, movesLeft);
            }
            if (isValid(row + 1, col - 1))
            {
                if (!isMine(row + 1, col - 1, realBoard))
                    playMinesweeperUtil(mines, row+1, col-1, movesLeft);
            }
        }

        return (false);
    }
}

// A Function to place the mines randomly
// on the board
void placeMines(int mines[][2])
{
    bool mark[MAXBAR][MAXSIDE];

    memset (mark, false, sizeof (mark));

    // Continue until all random mines have been created.
    for (int i=0; i<MINES; )
    {
        //int random = rand() % (BAR*SIDE);
        int x = rand() % BAR;
        int y = rand() % SIDE;

        // Add the mine if no mine is placed at this
        // position on the board
        if (!mark[x][y])
        {
            // Row Index of the Mine
            mines[i][0]= x;
            // Column Index of the Mine
            mines[i][1] = y;

            // Place the mine
            realBoard[mines[i][0]][mines[i][1]] = '*';
            mark[x][y] = true;
            i++;
        }
    }
}

// A Function to initialise the game
void initialise()
{

    // Assign all the cells as mine-free
    for (int i=0; i<BAR; i++)
    {
        for (int j=0; j<SIDE; j++)
        {
            myBoard[i][j] = realBoard[i][j] = '-';
        }
    }
}

// A function to replace the mine from (row, col) and put
// it to a vacant space
void replaceMine (int row, int col, char board[][MAXSIDE])
{
    for (int i=0; i<BAR; i++)
    {
        for (int j=0; j<SIDE; j++)
        {
            // Find the first location in the board
            // which is not having a mine and put a mine
            // there.
            if (board[i][j] != '*')
            {
                board[i][j] = '*';
                board[row][col] = '-';
                return;
            }
        }
    }
}

// A Function to play Minesweeper game
void playMinesweeper ()
{
    // Initially the game is not over
    bool gameOver = false;

    int movesLeft = BAR * SIDE - MINES, x, y;
    int mines[MAXMINES][2]; // stores (x,y) coordinates of all mines.

    initialise ();

    // Place the Mines randomly
    placeMines (mines);

    int currentMoveIndex = 0;
    while (!gameOver)
    {
        cout << "Moves: "<< Counter << endl;
        printf ("Current Status of Board : \n");
        printBoard (myBoard);
        makeMove (&x, &y, myBoard);

        // This is to guarantee that the first move is
        // always safe
        // If it is the first move of the game
        if (currentMoveIndex == 0)
        {
            // If the first move itself is a mine
            // then we remove the mine from that location
            if (isMine(x, y, realBoard))
                replaceMine (x, y, realBoard);
        }

        currentMoveIndex ++;

        if (x >= 0 && y >= 0)
        {
            gameOver = playMinesweeperUtil (mines, x, y, &movesLeft);
        }
        if (!gameOver && (movesLeft == 0))
        {
            printf ("\nYou won !\n");
            gameOver = true;
        }
    }
}
// A Function to set up the size of the board
void gamesetup ()
{
        SIDE = 30;
        BAR = 16;
        MINES = 99;
}

int main()
{
    gamesetup();

    playMinesweeper ();

    return (0);
}

