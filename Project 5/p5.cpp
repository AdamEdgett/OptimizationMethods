   // Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"

using namespace std;

class maze
{
   public:
      maze(ifstream &fin);

      int numRows(){return rows;};
      int numCols(){return cols;};

      void print(int,int,int,int);
      bool isLegal(int i, int j);

      void setMap(int i, int j, int n);
      int getMap(int i, int j) const;
      int getReverseMapI(int n) const;
      int getReverseMapJ(int n) const;

      void mapMazeToGraph(graph &g);
      int nodeNumberFromCoordinates(int, int);
      void coordinatesFromNodeNumber(int,int *);
      matrix<int> nodeNumbers;
      void findPathRecursive(graph &g,int);
      void findPathNonRecursive(graph &g,int);
      string getDirection(int i, int j);
      bool solved;
      void printDirections();
      void checkDirections();
      void reset(graph &g);
   private:
      vector<string> correctMoves;
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze
      matrix<bool> value;
};

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n. 
{
}

int maze ::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
}

int maze ::getReverseMapI(int n) const
// Return reverse mapping of node n to it's maze i value.
{
}

int maze ::getReverseMapJ(int n) const
// Return reverse mapping of node n to it's maze j value.
{
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;
   
   char x;
   value.resize(rows,cols);
   nodeNumbers.resize(rows,cols);
   int numberNodes=0;
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
      	 fin >> x;
      	 if (x == 'O')
         {
            value[i][j] = true;
            nodeNumbers[i][j]=numberNodes;
            numberNodes++;
         }
      	else
         {
            value[i][j] = false;
            nodeNumbers[i][j]=-1;
         }
	   
      }
   //map.resize(rows,cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to occupy cell (i,j).
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
   //matrix<int> nodeNumbers(numRows(),numCols(),0); //This will be how we look up a node number from coordinates
 
   int iNew;
   int jNew;
   //This loop adds the nodes, and 
   for (int i=0;i<numRows();i++)
      for (int j=0;j<numCols();j++)
         if(isLegal(i,j))
            g.addNode();

   //This loop adds the edges 
   for (int i=0;i<numRows();i++)
      for (int j=0;j<numCols();j++)
         if(isLegal(i,j))
         {
            int iAdd[]={0,0,-1,1};
            int jAdd[]={-1,1,0,0};
            for (int k=0;k<4;k++)
               {
                  iNew=i+iAdd[k];
                  jNew=j+jAdd[k];
                  if (iNew > -1 && jNew > -1 && iNew < numRows() && jNew < numCols() && isLegal(iNew,jNew))
                  //If the surrounding index is within the bounds of the matrix and there is a legal move
                  {
                     g.addEdge(nodeNumberFromCoordinates(i,j),nodeNumberFromCoordinates(iNew,jNew));
                  }
               }
         }
   g.printNodes();
   g.printEdges();

}
int maze::nodeNumberFromCoordinates(int i, int j)
//Gets a node's number from it's cell coordinates
//Might want to add some error catching here
{
   if(nodeNumbers[i][j]!=-1)
   {
      return nodeNumbers[i][j];   
   }
   else
   {
      cout << "\nThere is not a valid position at that cell.\n";
      return -1;
   }
   
}
void maze::coordinatesFromNodeNumber(int number,int * x)
//Gets the coordinates of a particular node and puts them in the array passed in
{
   for (int i=0;i<numRows();i++)
      for (int j=0;j<numCols();j++)
         if (nodeNumbers[i][j]==number)
         {
            x[0]=i;
            x[1]=j;
         }
}
string maze::getDirection(int i, int j)
{
   int x[2];
   int y[2];
   coordinatesFromNodeNumber(i,x);
   coordinatesFromNodeNumber(j,y);
   if (y[0]-x[0]==1)
      return "Down";
   if (y[0]-x[0]==-1)
      return "Up";
   if (y[1]-x[1]==1)
      return "Right";
   if (y[1]-x[1]==-1)
      return "Left";


}

void maze::findPathRecursive(graph &g,int nodeNumber)
{
   solved=0;
   g.visit(nodeNumber);
   vector<int> nodesCanVisit;
   int x[2];
   coordinatesFromNodeNumber(nodeNumber,x);
   print(x[0],x[1],rows-1,cols-1);

   //If it's the goal node, we're done.
   if (x[0]==rows-1 && x[1]==cols-1)
   {
      cout << "Solved!\n";
      solved=1;
      checkDirections();
      printDirections();
      print(x[0],x[1],rows-1,cols-1);
   }   

   //Populate a list of nodes that can be visited
   for (int i=0;i<g.numNodes();i++)
       if (g.isEdge(nodeNumber,i) && !g.isVisited(i))
         nodesCanVisit.push_back(i);
   
   //If we can visit any nodes that aren't already visited. Return
   if (nodesCanVisit.size()==0)
   {
      g.unVisit(nodeNumber);
      return;
   }

   for (int i=0;i<nodesCanVisit.size();i++)
   {
      cout << nodesCanVisit[i] <<" ";
      correctMoves.push_back(getDirection(nodeNumber,nodesCanVisit[i]));
      findPathRecursive(g,nodesCanVisit[i]);
       //Once a solution is found, stop searching for more.
       if (solved)
          return;
       correctMoves.pop_back();
   } 
}

void maze::findPathNonRecursive(graph &g,int nodeNumber)
{
   vector<int> directions;
   vector<int> nodes;
   
   nodes.push_back(nodeNumber);
   directions.push_back(0);
   int x[2];
   int node;
   solved=0;
   while (!nodes.empty() && !solved)
   {
      //Print Stack for Debugging
      for (int i=nodes.size()-1;i>-1;i--)
         cout << "\nNode: " <<nodes[i] << " Directions: "<<directions[i];
      
      //Get the new node
      node=nodes.back();
      //Resizing Correct Moves Vector to store Correct Path
      string temp;
      bool fix=directions.back() + 1 != correctMoves.size();

      if(!correctMoves.empty())
      {
         temp=correctMoves.back();
         correctMoves.resize(directions.back() + 1);
      }   
      
      if (!correctMoves.empty() && fix)
         correctMoves.back()=temp;

      //Visit the new node
      g.visit(node);
      
      //Pop the new node off the stack
      nodes.pop_back();
      directions.pop_back();
      
      //Check if solved
      coordinatesFromNodeNumber(node,x);

      if (x[0]==rows-1 && x[1]==cols-1)
      {
         cout << "\nSolved!\n\n";
         solved=1;
         checkDirections();
         printDirections();
         return;
      }   

      
      //Push next node options into stack
      for (int i=0;i<g.numNodes();i++)
         if (g.isEdge(node,i) && !g.isVisited(i))
            {
               nodes.push_back(i);
               directions.push_back(correctMoves.size());
            }
      
      //Push move into correct moves
      correctMoves.push_back(getDirection(node,nodes.back()));
      print(x[0],x[1],rows-1,cols-1);
   }
   
   if (!solved)
      cout << "No Solution Found Using Non-Recursive Model";
}

void maze::printDirections()
{
   for (int i=0;i<correctMoves.size();i++)
      cout << correctMoves[i] <<"\n";
}

void maze::checkDirections()
{
   int i=0; 
   int j=0;
   for (int k=0;k<correctMoves.size();k++)
   {
      if (correctMoves[k]=="Down")
         i++;
      else if (correctMoves[k]=="Up")
         i--;
      else if (correctMoves[k]=="Right")
         j++;
      else if (correctMoves[k]=="Left")
         j--;
      //cout << "i=" <<i<<" j="<<j<<"\n";
      //print(i,j,rows-1,cols-1);
   }
   
   if (i==rows-1 && j==cols-1)
      cout << "Direction List is a verfied solution.\n";
   else
      cout << "Direction list is not a solution.\n";
}

void maze::reset(graph &g)
{
   correctMoves.clear();
   solved=0;
   g.clearVisit();

}

int main()
{
   char x;
   ifstream fin;
   
   // Read the maze from the file.
   string fileName = "maze1.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      graph g;
      while (fin && fin.peek() != 'Z')
      {
         maze m(fin);
         m.mapMazeToGraph(g);
         m.findPathRecursive(g,0);
         if (!m.solved)
            cout << "No Solution Found Using Recursive Algorithm\n";
         m.reset(g);
         m.findPathNonRecursive(g,0);
        
      }
   } 
   catch (indexRangeError &ex) 
   { 
      cout << ex.what() << endl; exit(1);
   }
   catch (rangeError &ex)
   {
      cout << ex.what() << endl; exit(1);
   }
}
