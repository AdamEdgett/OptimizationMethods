#include <fstream>
#include <istream>
#include <iostream>
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

wordlist::wordlist():wlist(NULL) {
	std::cout <<"Reading\n";
	fname="wordlist";
	readFile();
}
wordlist::wordlist(string fn):wlist(NULL) {
	fname=fn;
	readFile();
}

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
	std::cout << "The word count is "<<wordCount<<" and the vector size is "<<wlist.size()<<"\n";
	std::cout << "The first word is "<<wlist.front()<<"\n";
	std::cout << "The last word is "<<wlist.back()<<"\n";
}

bool wordlist::isWord(string word) {
    int size=getList()->size();
	for(int i=0; i < size; i++) {
		//Get the string from the list at this index.
		string testString=(*(getList()))[i];
		if (word == testString) {
		    return true; //Once a word is found, return true, so it doesn't look for more words starting with that letter.
		}
	}
    return false;
}
