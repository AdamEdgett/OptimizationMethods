#include <string>
#include <vector>
#include "wordlist.h"
#include "grid.h"
#include <cmath>

using namespace std;

/*
class wordNode
{
	public:
		wordNode();
		wordNode(char v){
			value=v;
		}
		char value;
		wordNode * next;
		wordNode * prev;
};

class wordLoop {
	public:
		wordLoop(const grid& g, int x, int y):first(g.crossword[x][y])
		{
			wordNode * iter =
			for (int i=1;i<x+1;i++){
				first.next=new wordNode(g.crossword[x+i][y]);		
				first.next->prev=&first;
			}
		}
		wordNode  first;
};
*/
int mod(int number, int modulus)
{
     int result = number % modulus;

     if (result < 0) result += modulus;

     return result;
}

void getAllWords(const grid * g,const wordlist * w,int x_pos,int  y_pos){
	int length=g->crossword.cols();
	for (int i=-1;i<2;i++)
	{
		for (int j=-1;j<2;j++)
		{	
			if (i==-1 && j==-1)
			{
				cout << "\nNorth West: \n";
			}
			if (i==-1 && j==0)
			{
				cout << "\nWest: \n";
			}
			if (i==-1 && j==1)
			{
				cout << "\nSouth West: \n";
			}
			if (i==0 && j==-1)
			{
				cout << "\nNorth: \n";
			}
			if (i==0 && j==1)
			{
				cout << "\nSouth: \n";
			}
			if (i==1 && j==-1)
			{
				cout << "\nNorth East: \n";
			}
			if (i==1 && j==0)
			{
				cout << "\nEast: \n";
			}
			if (i==1 && j==1)
			{
				cout << "\nSouth East: \n";
			}
			
			for (int k=0;k<length;k++) 
			{
				
				if (i!=0 || j!=0)
				{
					cout << g->crossword[mod((x_pos+(k*i)),length)][mod(y_pos+(k*j),length)] << " ";	
				}
			}
		}
	}
	cout << "\n";
}

void findMatches(const wordlist * w,const grid *g){
	for (int i=0; i<g->crossword.cols();i++) {
		for (int j=0; j<g->crossword.rows(); j++) {
			cout<< "\nLetter = "<< g->crossword[j][i]<<" at point "<<j<<","<<i<<"\n";
			getAllWords(g,w,j,i);
		}
	}
}

const char* stringToChar(string s){
	const char* c=s.c_str();
	return c;
}

int main(void)
{
	const char* c = stringToChar("Dog");
	
	cout <<c[0]<<"\n";
	wordlist * w=new wordlist;
	grid * g=new grid("input15");
	findMatches(w,g);
}