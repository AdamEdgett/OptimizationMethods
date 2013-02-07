#include <fstream>
#include <istream>
#include <iostream>
#include "d_matrix.h"
using std::vector;
using std::string;



class grid{
	public:
		grid(string fname);
		void readFile(string fname);
	// private:
		matrix<char> crossword;
};
	
grid::grid(string fname)
{
	readFile(fname);
}

void grid::readFile(string fname)
{
	std::cout <<"Reading in '"<<fname<<"'. \n";
	std::fstream file;
	
	file.open(fname.c_str(),std::ios::in);
	if (!file) {
		std::cout << "Can't open, Bro.\n";
	}
	// char dimChar[50];
	// file.getline(dimChar,50);
	// string dimString=dimChar;
	// std::cout << dimString << "\n\n";
	int width,height;
	file >> width >> height;
	crossword.resize(width,height);
	char x;
	int i(0),j(0);
	while (	file >> x) {
		if (i==width) {
			j++;
			i=0;
		}
		crossword[i][j]=x;
		i++;
	//	std::cout << x <<"\n";
	}
	std::cout <<" The value at 5,4 is "<< crossword[5][4] <<"\n";


}