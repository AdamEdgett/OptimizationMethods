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
		matrix<char> * getMatrix();
	 private:
		matrix<char> crossword;
};

matrix<char> * grid::getMatrix() {
	return &crossword;
}	


grid::grid(string fname) {
	readFile(fname);
}

void grid::readFile(string fname) {
	std::cout <<"Reading in '"<<fname<<"'. \n";
	std::fstream file;
	
	file.open(fname.c_str(),std::ios::in);
	if (!file) {
		std::cout << "Can't open, Bro.\n";
	}
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
	}
}