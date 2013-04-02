// Project 6
//
// Assumes that directed edges in both directions (x,y) and (y,x) are present in the input file.
//

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"
#include <queue>
#include <vector>

using namespace std;

int const NONE = -1;  // Used to represent a node that does not exist

bool isCyclic(graph &g,int nodeNumber)
// Returns true if the graph g contains a cycle.  Otherwise, returns false.
{
   if (g.isVisited(nodeNumber))
   {
      return true;
   }
   //Visit the node
   g.visit(nodeNumber);
   for (int i=0;i<g.numNodes();i++)
   {
      if (g.isEdge(nodeNumber,i))
      {
         return isCyclic(g,i);
      }
   }

   return false;
}

void findSpanningForest(graph &g, graph &sf)
// Create a graph sf that contains a spanning forest on the graph g.  
{
   g.clearMark();
   g.clearVisit();
   g.numComponents=0;
   queue<int> currentMoves;
   for (int n=0;n<g.numNodes();n++)
   {
      if (!g.isVisited(n))
      {  
         g.numComponents++;
         int nodeNumber=n;
         g.visit(nodeNumber);
         currentMoves.push(nodeNumber);
         while(currentMoves.size() > 0)
         {
            int currentNode = currentMoves.front();
            currentMoves.pop();
   
            //Populate a list of nodes that can be visited
            for (int i=0;i<g.numNodes();i++)
            {
               if (g.isEdge(currentNode,i) && !g.isVisited(i))
               {
                  g.mark(currentNode,i);
                  sf.addEdge(currentNode,i);
                  cout << i <<" ";
                  g.visit(i);
                  currentMoves.push(i);
               }
            }
         }
      }
   }
   cout << "\nThere are "<<g.numComponents<<" components or spanning trees.\nThe Original Graph: \n"<<g<<"\n";
}


bool isConnected(graph &g)
// Returns true if the graph g is connected.  Otherwise returns false.
{
   g.clearMark();
   g.clearVisit();
   g.numComponents=0;
   queue<int> currentMoves;
   for (int n=0;n<g.numNodes();n++)
   {
      if (!g.isVisited(n))
      {  
         g.numComponents++;
         int nodeNumber=n;
         g.visit(nodeNumber);
         currentMoves.push(nodeNumber);
         while(currentMoves.size() > 0)
         {
            int currentNode = currentMoves.front();
            currentMoves.pop();
            //Populate a list of nodes that can be visited
            for (int i=0;i<g.numNodes();i++)
            {
               if (g.isEdge(currentNode,i) && !g.isVisited(i))
               {
                  g.mark(currentNode,i);
                  g.visit(i);
                  currentMoves.push(i);
               }
            }
         }
      }
   }

   if (g.numComponents>1)
      return false;
   else
      return true;
   
}
int main()
{
   char x;
   ifstream fin;
   stack <int> moves;
   string fileName;
   
   // Read the name of the graph from the keyboard or
   // hard code it here for testing.
   
   fileName = "graph1.txt";

   //   cout << "Enter filename" << endl;
   //   cin >> fileName;
   
   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try

   {
      cout << "Reading graph" << endl;
      graph g(fin);

      //cout << g;
	    
      bool connected;
      bool cyclic;

      connected = isConnected(g);
      cyclic = isCyclic(g,0);

      if (connected)
	 cout << "Graph is connected" << endl;
      else
	 cout << "Graph is not connected" << endl;

      if (cyclic)
	 cout << "Graph contains a cycle" << endl;
      else
	 cout << "Graph does not contain a cycle" << endl;

      cout << endl;
     
      cout << "Finding spanning forest" << endl;

      // Initialize an empty graph to contain the spanning forest
      graph sf(g.numNodes());
      findSpanningForest(g,sf);

      cout << endl;

      cout << sf;

      cout << "Spanning forest weight: " << sf.getTotalEdgeWeight()/2 << endl;

      //Can't do this in is Cyclic because that's recursive.
         connected = isConnected(sf);
         sf.clearMark();
         sf.clearVisit();
         cyclic = isCyclic(sf,0);
         
      
      if (connected)
	 cout << "Graph is connected" << endl;
      else
	 cout << "Graph is not connected" << endl;

      if (cyclic)
	 cout << "Graph contains a cycle" << endl;
      else
	 cout << "Graph does not contain a cycle" << endl;

      cout << endl;
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

