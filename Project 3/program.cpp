#include <string>
#include <vector>
#include "wordlist.h"
#include "grid.h"
#include <cmath>

using namespace std;

int min_length=5;
int max_size;
vector<string> words;


int mod(int number, int modulus)
{
     int result = number % modulus;

     if (result < 0) result += modulus;

     return result;
}

string testSearch()
{
	string filename;
	cout << "Please enter your file's name.\n";
	cin >> filename;
	if (filename=="")
	{
		filename="input15";
	}
	return filename;

}

bool is_word(string s1, wordlist * w)
{
	int size=w->get_list()->size();
	for(int i=0; i < size; i++)
	{
		//Get the string from the list at this index.
		string s2=(*(w->get_list()))[i];
		// cout <<"\nComparing '"<<s1<<"' with '"<<s2<<"'\n";
		if (s2==s1)
		{
		cout<<"Match! " << s1 << " = "<<s2<<"\n";
		words.push_back(s1); //add to words vector.
		return true; //Once a word is found, return true, so it doesn't look for more words starting with that letter.
		}
	}
}

void getAllWords(grid * g,wordlist * w,int x_pos,int  y_pos){
	int length=g->get_matrix()->cols();
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
			
			string s; //String we'll be using to compare with the other strings.
			for (int k=min_length-1;k<length;k++)  //From 4 to 14
			{
				if (i!=0 || j!=0) //Ignore case where the iterator doesn't move in either direction
				{
					//letter is what we'll be adding.
					char * letter=&((*(g->get_matrix()))[mod((x_pos+(k*i)),length)][mod(y_pos+(k*j),length)]);
					if (k==min_length-1) //If we're at the starting point
					{	
						//We want to build the string up to the minimum length
						for (int l=0;l<min_length;l++)
						{
						s+=((*(g->get_matrix()))[mod((x_pos+(l*i)),length)][mod(y_pos+(l*j),length)]);
						}
					}
					else //Now we keep adding the next letter into the string
					{
						s+=*letter;
					}
					// cout << "The char is "<<*letter << " and the string is "<<s<<"\n";
					
					if (is_word(s,w)==true) //is_word compares the string with all strings in the word list
					{
						k=max_size;
					}				}
			}
		}
	}
	cout << "\n\n";
}

void findMatches(wordlist * w,  grid *g){
	for (int i=0; i<g->get_matrix()->cols();i++) {
		for (int j=0; j<g->get_matrix()->rows(); j++) {
			cout<< "\nLetter = "<< (*(g->get_matrix()))[j][i]<<" at point "<<j<<","<<i<<"\n";
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
	wordlist * w=new wordlist;
	grid * g=new grid(testSearch());

	max_size=g->get_matrix()->rows();
	

	findMatches(w,g);
	

	cout << "There are "<<words.size() << " words. \nThey are:\n";
	for (int i=0;i<words.size();i++)
	{
		cout << words[i] <<"\n";
	}
}