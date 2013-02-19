#include <fstream>
#include <istream>
#include <iostream>
#include "sorts.cpp"
using std::vector;
using std::string;

class wordlist {
	public:
		wordlist();
		wordlist(string fn);
		void readFile();
		vector<string> * getList();
        bool isWord(string word);
		string fname;
	private:
		vector<string> wlist;	
};
vector<string>* wordlist::getList() {
	return & wlist;
}
//Default constructor with no filename;
wordlist::wordlist():wlist(NULL) {
	fname="wordlist";
	readFile();
}
//With filename
wordlist::wordlist(string fn):wlist(NULL) {
	fname=fn;
	readFile();
}
//Reads in the wordlist
void wordlist::readFile() {
	std::cout <<"Reading in '"<<fname<<"'. \n";
	std::fstream file;
	
	file.open(fname.c_str(),std::ios::in);
	if (!file) {
		std::cout << "Can't open, Bro.\n";
	}

	char wordChar[50];
	string wordString;
	int wordCount=0;
	while(!file.eof()) {	
		file.getline(wordChar,50);
		wordString=wordChar;
		if (wordString!="") {
			wlist.push_back(wordString);
			wordCount++;
		}
	}
    quicksort(wlist, 0, wlist.size() - 1);
    //mergesort(wlist);
	std::cout << "The word count is "<<wordCount<<" and the vector size is "<<wlist.size()<<"\n";
	std::cout << "The first word is "<<wlist.front()<<"\n";
	std::cout << "The last word is "<<wlist.back()<<"\n";
}

// Checks for the word using binary search
bool wordlist::isWord(string word) {
    int size=getList()->size();
    int beg = 0, end = size - 1;
    while(beg <= end) {
        int middle = int((beg + end)/2);
        if(word.compare(wlist[middle]) < 0) {
            end = middle - 1; // Contiue checking first half of list
        } else if(word.compare(wlist[middle]) > 0) {
            beg = middle + 1; // Continue checking second half of list
        } else if(word.compare(wlist[middle]) == 0) {
            return true; // Found the word
        }
    }
    return false; // Word was not found
}
