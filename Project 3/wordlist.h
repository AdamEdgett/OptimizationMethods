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
		vector<string> * get_list();
		string fname;
	private:
		vector<string> wlist;	
};
vector<string>* wordlist::get_list()
{
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


