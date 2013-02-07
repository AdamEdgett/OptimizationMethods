#include <fstream>
#include <istream>
#include <iostream>
using std::vector;
using std::string;



class wordlist
{
public:
	wordlist():wlist(NULL)
		{
			std::cout <<"Reading\n";
			fname="wordlist";
			readfile();
		}
	wordlist(string fn):wlist(NULL)
	{
		fname=fn;
		readfile();
	}
	void readfile();
	string fname;
private:
	vector<string> wlist;	
};

void wordlist::readfile()
{
	std::cout <<"Reading in '"<<fname<<"'. \n";
	std::fstream file;
	
	file.open(fname.c_str(),std::ios::in);
	if (!file)
	{
		std::cout << "Can't open, Bro.\n";
	}

	char wordChar[50];
	string wordString;
	int wordCount=0;
	while(!file.eof())
	{	
		file.getline(wordChar,50);
		wordString=wordChar;
		if (wlist.empty())
		{
			wlist.push_back(wordString);
		}
		else
		{
			wlist.push_back(wordString);
		}
		wordCount++;
//		std::cout << wordString << "\n";
	}
	std::cout << "The word count is "<<wordCount<<"\n";
	std::cout << "The first word is "<<wlist.front()<<"\n";
	std::cout << "The last word is "<<wlist.back()<<"\n";
}


