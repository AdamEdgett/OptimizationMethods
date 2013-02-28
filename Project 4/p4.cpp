// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = 0;  // Indicates that a cell is blank
 
const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

//This is just a case check that returns the square number for a set of indexes as
int getSquareNumber(int x,int y)
{
    if (x<=3 && y <=3)
        return 1;
    else if (x<=3 && y>3 &&y<=6)
        return 2;
    else if (x<=3 && y>6)
        return 3;
    else if (x>3 && x<7 && y<=3)
        return 4;
    else if (x>3 && x<7 && y>3 && y<7)
        return 5;
    else if (x>3 && x<7 && y>6)
        return 6;
    else if (x>6 && y<=3)
        return 7;
    else if (x>6 && y>3 &&y<7)
        return 8;
    else
        return 9;
}


class board
// Stores the entire Sudoku board
{
    public:
        board(int);
        void clear();
        void clearCell(int,int);
        void initialize(ifstream &fin);
        void print();
        bool isBlank(int, int);
        ValueType getCell(int, int);
        void setCell(int, int, ValueType);
        
        bool checkValue(int, int, ValueType);
        void addValue(int x,int y,ValueType input);
        void printConflicts();
        void printItemConflicts(int, string);
        void updateConflicts();
        bool solved();
        
        vector< vector<bool>  > columns;
        vector< vector<bool>  > rows;
        vector< vector<bool>  > squares;
    private:

        // The following matrices go from 1 to BoardSize in each
        // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)

        matrix<ValueType> value;
};

board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1)
// Board constructor
{
    int size(value.rows());
    columns.resize(size);
    rows.resize(size);
    squares.resize(size);
    for (int i=1;i<size;i++)
    {  
        columns[i].resize(size);
        rows[i].resize(size);    
        squares[i].resize(size);
    }
}

void board::clear()
{
    for (int i=1;i<value.rows();i++)
        for (int j=1;j<value.rows();j++)
            setCell(i,j,Blank);

}
void board::printConflicts()
{

    for (int i=1;i<value.rows();i++)
    {
        print();
        printItemConflicts(i,"row");
        printItemConflicts(i,"column");
        printItemConflicts(i,"square");
    }
}

void board::printItemConflicts(int itemNumber, string item)
{
    if (item=="square")
    {
        cout << "Square " << itemNumber << " conflicts vector: \n";
        for (int i=1;i<10;i++)
            cout << i << " ";
        cout <<"\n";
        for (int i=1;i<10;i++)
            cout <<"--";
        cout <<"\n";
        for (int i=1;i<10;i++)
            cout << squares[itemNumber][i] << " ";
    }
    else if (item=="row")
    {
        
        cout << "Row " << itemNumber << " conflicts vector: \n";
        for (int i=1;i<10;i++)
            cout << i << " ";
        cout <<"\n";
        for (int i=1;i<10;i++)
            cout <<"--";
        cout <<"\n";
        for (int i=1;i<10;i++)
            cout << rows[itemNumber][i] << " ";
    }
    else if (item=="column")
    {
        cout << "Column " << itemNumber << " conflicts vector: \n";
        for (int i=1;i<10;i++)
            cout <<i<<"|"<< columns[itemNumber][i] <<"\n";
    }
    else
    {
        cout << "Not a valid item type.";
    }
    cout <<"\n\n";
    return;
}

//This function adds a value to the board and updates the conflicts
void board::addValue(int x,int y,ValueType input)
{
    if(checkValue(x,y,input))
    {
        setCell(x,y,input);
        updateConflicts();
        printConflicts();
    }
    else 
        cout << "Did not set because doing so would cause a conflict.\n";
}

//This looks at a space, and checks if a conflict will be created.
bool board::checkValue(int x,int y,ValueType input)
{
    if (rows[x][input] == false || columns[y][input] == false || squares[getSquareNumber(x,y)][input] == false)
    {
        cout << input << " will cause a conflict if it is placed at "<<x<<","<<y<<".\n";
        return false;
    }
    else
    {
        cout << input << " can be placed at without causing conflict "<<x<<","<<y<<".\n";
        return true;
    }
}
//This builds the conflict vectors for the board. 9 Rows, 9 Columns, and 9 Squares.
//The vectors are bool vectors with false at the values that cannot go into the row/col/square
void board::updateConflicts()
{   
    //Holds the Indices for the start of each box (Could also do with mod)
    int boxY[]={0,1,1,1,4,4,4,7,7,7};
    int boxX[]={0,1,4,7,1,4,7,1,4,7};
    for (int i=1;i<value.rows();i++)
    {
        //This sets all value possiblities equal to true, and a value will be marked false if it exists in the row
        for (int m=1;m<value.rows();m++)
        {
            squares[i][m]=true;
            rows[i][m]=true;
            columns[i][m]=true;
        }

        for (int k=0;k<3;k++) //Iterate through the three values in the row
            for (int l=0;l<3;l++) //Move down one and repeat
                squares[i][getCell(boxY[i]+k,boxX[i]+l)]=false;

        for (int j=1;j<value.rows();j++)
        {
            if (getCell(i,j))
                rows[i][getCell(i,j)]=false;
            if (getCell(j,i))
                columns[i][getCell(j,i)]=false;
        }
    }
}

void board::setCell(int i, int j, ValueType cellVal)
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    else
        value[i][j] = cellVal;
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
    char ch;

    clear();
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
        {
            fin >> ch;

            // If the read char is not Blank
            if (ch != '.')
            {
                setCell(i,j,ch-'0');   // Convert char to int
            }
        }
    updateConflicts();
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
    // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
    // coordinates of the square that i,j is in.  

    return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
    for (unsigned int i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    ostr << endl;
    return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
        return value[i][j];
    else
        throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    else
        return getCell(i,j) == Blank;
}

void board::print()
// Prints the current board.
{
    for (int i = 1; i <= BoardSize; i++)
    {
        if ((i-1) % SquareSize == 0)
        {
            cout << " -";
            for (int j = 1; j <= BoardSize; j++)
                cout << "---";
            cout << "-";
            cout << endl;
        }
        for (int j = 1; j <= BoardSize; j++)
        {
            if ((j-1) % SquareSize == 0)
                cout << "|";
            if (!isBlank(i,j))
                cout << " " << getCell(i,j) << " ";
            else
                cout << "   ";
        }
        cout << "|";
        cout << endl;
    }

    cout << " -";
    for (int j = 1; j <= BoardSize; j++)
        cout << "---";
    cout << "-";
    cout << endl;
}
//clears a cell
void board::clearCell(int x, int y)
{
    setCell(x,y,Blank);
    updateConflicts();
    printConflicts();
}
//Checks if the puzzle is solved
bool board::solved()
{ 
    //iterate through the matrix
    for (int x=1;x<value.cols();x++)
        for (int y=1;y<value.cols();y++)
        {
            //if a value is blank it's not solved
            if (isBlank(x,y))
                return false;
            
            //iterate through the row to find duplicates
            for (int i=1;i<value.rows();i++) //This checks the row
            {  
                if (x!=i && getCell(i,y))//If we're not comparing the same index value and there is a value
                    if(getCell(i,y) == getCell(x,y))//and if the values are equal
                    {
                        return false; //it's not solved and something has been done wrong
                    }
            }
            //Same deal, but for columns
            for (int i=1;i<value.cols();i++)//This checks the columns
                if (y!=i && getCell(x,i))
                    if(getCell(x,i) == getCell(x,y))
                    {
                        return false;
                    }

            //And again for squares
            int startX=x-((x-1)%3);
            int startY=y-((y-1)%3);
            for (int i=0;i<3;i++) //This checks the box
            {   
                int temp(startY);
                for (int j=0;j<3;j++)
                {
                    if (y!=temp && x!=startY && getCell(startX,temp))
                        if(getCell(startX,temp) == getCell(x,y))
                            return false;
                    temp++;
                }
                startX++;
            }
        }
        return true;
}
int main()
{
    ifstream fin;
   
    // Read the sample grid from the file.
    string fileName = "sudoku1.txt";

    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try
    {
        board b1(SquareSize);
        while (fin && fin.peek() != 'Z')
        {
            b1.initialize(fin);
            b1.print();

            //We first print the conflicts which have been updated upon board initilization:
            cout << "\nBoard Initilized\n\n\n\n Printing Conflicts...\n";
            b1.printConflicts();
            //Then we check to see if we could put a value of 5 at 1, 2 (We Can)
            cout << "\n\n\n\n\n\n\n\n\n\n\n\nBoarding Value of 5 at 1,2\n\n";
            b1.checkValue(1,2,5);
            //Now one we know we cannot put there.
            cout << "\n\n\n\n\n\n\n\n\n\n\n\nChecking Value of 3 at 1,2\n\n";
            b1.checkValue(1,2,3);
            //Now we add the five at 1,2
            cout << "\n\n\n\n\n\n\n\n\n\n\n\nAdding Value of 5 at 1,2\n";
            b1.addValue(1,2,5);
            //Now we go ahead and clear it
            cout << "\n\n\n\n\n\n\n\n\n\n\n\nClearing Value of 5 at 1,2\n";
            b1.clearCell(1,2);
            cout << "\n\n\nIs it solved?\n";
            if (b1.solved()==false)
                cout << "This puzzle is not solved\n";
            else
                cout << "This puzzle is solved\n";
        }
    }   
    catch  (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }

}

