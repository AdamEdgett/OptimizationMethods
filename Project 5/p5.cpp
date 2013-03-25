// Project 5

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include "d_except.h"
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
      bool findShortestPath1(graph &g, int);
      bool findShortestPath2(graph &g, int);
      string getDirection(int i, int j);
      bool solved;
      void printDirections();
      void checkDirections();
      void reset(graph &g);
   private:
      vector<string> correctMoves;
      vector<string> shortestPath;
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
                  if (iNew > -1 && jNew > -1 
                     && iNew < numRows() && jNew < numCols() && isLegal(iNew,jNew))
                  //If the surrounding index is within the bounds of the matrix and there is a legal move
                  {
                     g.addEdge(nodeNumberFromCoordinates(i,j),
                        nodeNumberFromCoordinates(iNew,jNew));
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
      cout << "Solved in " << correctMoves.size() << "\n";
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
      cout << "Nodes can visit: " << nodesCanVisit[i] <<" ";
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
   //Stores the Iterator Stack
   vector<int> nodes;

   //Stores the nodes visited, will be resized if a path is found to be a dead end
   //this will contain the solution to the maze in the end
   vector<int> nodesVisited;

   //Stack in paralell with the nodes stack that holds the size of the nodesVisited vector at a node
   //When we encounter a dead end, we pop back to the start of the dead end path
   //and resize our nodesVisited thus removing all the dead end nodes from the nodesVisited stack
   vector<int> sizes;
   
   //Push our starting values
   nodes.push_back(nodeNumber);
   sizes.push_back(0);
   
   //Used to capture coordinates from node
   int x[2];
   int node;
   solved=0;
   //While the nodes stack isn't empty and the maze isn't solved
   while (!nodes.empty() && !solved)
   {  
      //Resize nodesVisited to remove any bad nodes (dead ends)
      nodesVisited.resize(sizes.back());

      //get next node to try from stack and visit it and put it into nodes visited
      node=nodes.back();
      g.visit(node);
      nodesVisited.push_back(node);
      
      //Pop the size and node off the stacks since they've now been visited
      nodes.pop_back();
      sizes.pop_back();
      
      //Check solved
      coordinatesFromNodeNumber(node,x);
      
      if (x[0]==rows-1 && x[1]==cols-1)
      {
         solved=1;
         int i=0;
         do
         {
            //Print Path
            coordinatesFromNodeNumber(nodesVisited[i],x);
            print(x[0],x[1],rows-1,cols-1);
            //Fill in moves
            correctMoves.push_back(getDirection(nodesVisited[i],nodesVisited[i+1]));
            i++;
         }
         while (i+1!=nodesVisited.size());
         checkDirections();
         printDirections();
         cout << "\nSolved!\n\n";
         return;
      }   

      //Push next node options into stack
      for (int i=0;i<g.numNodes();i++)
         if (g.isEdge(node,i) && !g.isVisited(i))
            {
               nodes.push_back(i);
               sizes.push_back(nodesVisited.size());
            }
   }
   
   if (!solved)
      cout << "No Solution Found Using Non-Recursive Model";
}

// finds the shortest solution using depth first search
bool maze::findShortestPath1(graph& g, int nodeNumber)
{
   g.visit(nodeNumber);
   int x[2];
   coordinatesFromNodeNumber(nodeNumber,x);
   print(x[0],x[1],rows-1,cols-1);

   //If it's the goal node, we're done.
   if (x[0]==rows-1 && x[1]==cols-1)
   {
      cout << "Solved in " << correctMoves.size() << " moves\n";
      solved = true;
      if(shortestPath.size() == 0 || correctMoves.size() < shortestPath.size())
      {
         cout << "Found new shortest solution" << "\n";
         shortestPath = correctMoves;
      }
      checkDirections();
      printDirections();
      print(x[0],x[1],rows-1,cols-1);
   }   

   //Populate a list of nodes that can be visited
   for (int i=0;i<g.numNodes();i++)
   {
      if (g.isEdge(nodeNumber,i) && !g.isVisited(i))
      {
         cout << i << " ";
         correctMoves.push_back(getDirection(nodeNumber,i));
         findShortestPath1(g,i);
         correctMoves.pop_back();
      }
   }

   g.unVisit(nodeNumber);
   return solved;
}

// finds the shortest solution using breadth first search
bool maze::findShortestPath2(graph& g, int nodeNumber)   
{
   queue<int> currentMoves;
   g.visit(nodeNumber);
   currentMoves.push(nodeNumber);
   while(currentMoves.size() > 0)
   {
      int currentNode = currentMoves.front();
      currentMoves.pop();
      int x[2];
      coordinatesFromNodeNumber(currentNode,x);
      print(x[0],x[1],rows-1,cols-1);

      //If it's the goal node, we're done.
      if (x[0]==rows-1 && x[1]==cols-1)
      {
         solved = true;
         return true;
      }
      //Populate a list of nodes that can be visited
      for (int i=0;i<g.numNodes();i++)
      {
         if (g.isEdge(currentNode,i) && !g.isVisited(i))
         {
            cout << i <<" ";
            g.visit(i);
            currentMoves.push(i);
         }
      }
   }
   return false;
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
   shortestPath.clear();
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
      bool recursiveSolved=false;
      bool nonRecursiveSolved=false;
      graph g;
      while (fin && fin.peek() != 'Z')
      {
         maze m(fin);
         m.mapMazeToGraph(g);
         cout << "\n\n";
         cout << "Finding solution using Depth-First Search\n";
         m.findShortestPath1(g,0);
         if (!m.solved)
            cout << "No Solution Found Using Depth-First Search\n";
         m.reset(g);
         cout << "\n\n";
         cout << "Finding solution using Breadth-First Search\n";
         m.findShortestPath2(g,0);
         if (!m.solved)
            cout << "No Solution Found Using Breadth-First Search\n";
         m.reset(g);

         // if (recursiveSolved && nonRecursiveSolved)
         //    cout <<"\nFound solutions using both recursive and non-recursive algorithms.";
         // else if (!recursiveSolved && nonRecursiveSolved)
         //    cout <<"\nFound solutions using non-recursive algorithm but not with recursive algorithm.";
         // else if (recursiveSolved && !nonRecursiveSolved)
         //    cout <<"\nFound solutions using recursive algorithm but not with non-recursive algorithm.";
         // else
         //    cout << "\nNo solutions found with either algorithm.";
         
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
