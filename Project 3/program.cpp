#include <string>
#include <vector>
#include "wordlist.h"
#include "grid.h"


using namespace std;

void findMatches(wordlist w, grid g)
{
	for (int i=0; i<g.crossword.cols();i++) {
		for (int j=0; j<g.crossword.rows(); j++){
			cout<< " Value= "<< g.crossword[i][j]<<"\n";
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
	wordlist test;
	grid g("input15");
	findMatches(test,g);
}