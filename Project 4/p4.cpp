// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank
 
const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

class board
// Stores the entire Sudoku board
{
    public:
        board(int);
        void clear();
        void initialize(ifstream &fin);
        void print();
        bool isBlank(int, int);
        ValueType getCell(int, int);
        void setCell(int, int, ValueType);
        void printConflicts();
        void printCellConflicts(int, int);
        void updateConflicts();
        void updateCellConflicts(int x, int y);
    private:

        // The following matrices go from 1 to BoardSize in each
        // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)

        matrix<ValueType> value;
};

board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1)
// Board constructor
{
}
void board::printConflicts()
{

}

void board::printCellConflicts(int x, int y)
{
}

//This looks at a cell and determines if there are any conflicts with it in the row, column, or box
void board::updateCellConflicts(int x, int y)
{   //x is the h.index of the cell you're checking and y is the v.index
    for (int i=1;i<value.rows();i++) //This checks the row
        if (x!=i && getCell(i,y))
            if(getCell(i,y) == getCell(x,y))
            {
                cout << "\nCol Conflict with "<<getCell(x,y)<<" (location: "<<x<<","<<y<<") with a "<<getCell(i,y)<<" at x="<<i<<" y="<<y<<".\n"; 
            }
    for (int i=1;i<value.cols();i++)//This checks the columns
        if (y!=i && getCell(x,i))
            if(getCell(x,i) == getCell(x,y))
            {
                cout << "\nRow Conflict with "<<getCell(x,y)<<" (location: "<<x<<","<<y<<") with a "<<getCell(x,i)<<" at x="<<x<<" y="<<i<<".\n"; 
            }
    int startX=x-((x-1)%3);
    int startY=y-((y-1)%3);
    cout <<"\n"<< getCell(startX,startY)<<"\n";
    for (int i=0;i<3;i++) //This checks the box
    {   int temp(startY);
        for (int j=0;j<3;j++)
        {
            cout << getCell(startX,temp) << " ";
            if (y!=temp && x!=startY && getCell(startX,temp))
                if(getCell(startX,temp) == getCell(x,y))
                {
                    cout << "\nBox Conflict with "<<getCell(x,y)<<" (location: "<<x<<","<<y<<") with a "<<getCell(startX,temp)<<" at x="<<startX<<" y="<<temp<<".\n"; 
                }
            temp++;
        }
        cout <<"\n";
        
        startX++;
    }
}

void board::updateConflicts()
{
    for (int i=1;i<value.rows();i++)
        for (int j=1;j<value.rows();j++)
        {
            if (getCell(i,j))
            {
                updateCellConflicts(i,j);
            }
        }
}
void board::clear()
{
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
        return !getCell(i,j);
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

int main()
{
    ifstream fin;
   
    // Read the sample grid from the file.
    string fileName = "sudoku2.txt";

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
            //b1.printConflicts();
        }
        b1.updateConflicts();
    }
    catch  (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }

}

