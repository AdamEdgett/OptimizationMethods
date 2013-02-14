#include <string>
#include <vector>
#include "wordlist.h"
#include "grid.h"
#include "sorts.cpp"
#include <cmath>

using namespace std;

int min_length=5;
int max_size;
vector<string> words;


int mod(int number, int modulus) {
     int result = number % modulus;
     
     if (result < 0) result += modulus;
     
     return result;
}

string testSearch() {
	string filename;
	cout << "Please enter your file's name.\n";
	cin >> filename;
	if (filename=="") {
		filename="input15";
		cout << "You didn't enter a name so we chose input15 for you. \n";
	}
	return filename;
}

void getAllWords(grid * g,wordlist * w,int x_pos,int  y_pos){
	int length=g->getMatrix()->cols();
	for (int i=-1;i<2;i++) {
		for (int j=-1;j<2;j++) {	
			// if (i==-1 && j==-1)
			// 	{
			// 		cout << "\nNorth West: \n";
			// 	}
			// 	if (i==-1 && j==0)
			// 	{
			// 		cout << "\nWest: \n";
			// 	}
			// 	if (i==-1 && j==1)
			// 	{
			// 		cout << "\nSouth West: \n";
			// 	}
			// 	if (i==0 && j==-1)
			// 	{
			// 		cout << "\nNorth: \n";
			// 	}
			// 	if (i==0 && j==1)
			// 	{
			// 		cout << "\nSouth: \n";
			// 	}
			// 	if (i==1 && j==-1)
			// 	{
			// 		cout << "\nNorth East: \n";
			// 	}
			// 	if (i==1 && j==0)
			// 	{
			// 		cout << "\nEast: \n";
			// 	}
			// 	if (i==1 && j==1)
			// 	{
			// 		cout << "\nSouth East: \n";
			// 	}
			
			string s; //String we'll be using to compare with the other strings.
			for (int k=min_length-1;k<length;k++)  {//From 4 to 14
				if (i!=0 || j!=0) {//Ignore case where the iterator doesn't move in either direction
					//letter is what we'll be adding.
					char * letter=&((*(g->getMatrix()))[mod((x_pos+(k*i)),length)][mod(y_pos+(k*j),length)]);
					if (k==min_length-1) {//If we're at the starting point
						//We want to build the string up to the minimum length
						for (int l=0;l<min_length;l++) {
						    s+=((*(g->getMatrix()))[mod((x_pos+(l*i)),length)][mod(y_pos+(l*j),length)]);
						}
					}
					else {//Now we keep adding the next letter into the string
						s+=*letter;
					}
					// cout << "The char is "<<*letter << " and the string is "<<s<<"\n";
					
					if (w->isWord(s)) {//is_word compares the string with all strings in the word list
					    cout<<"Match! " << s <<"\n";
            		    words.push_back(s); //add to words vector.
						k=max_size;
					}
				}
			}
		}
	}
}

void findMatches(wordlist * w,  grid *g){
	for (int i=0; i<g->getMatrix()->cols();i++) {
		for (int j=0; j<g->getMatrix()->rows(); j++) {
			cout<< "\nLetter = "<< (*(g->getMatrix()))[j][i]<<" at point "<<j<<","<<i<<"\n";
			getAllWords(g,w,j,i);
		}
	}
}

const char* stringToChar(string s) {
	const char* c=s.c_str();
	return c;
}

int main(void) {
    wordlist * w=new wordlist;
    grid * g=new grid(testSearch());
    
    max_size=g->getMatrix()->rows();
 
    
    findMatches(w,g);
    
    cout << "There are "<<words.size() << " words. \nThey are:\n";
    for (unsigned int i=0;i<words.size();i++) {
        cout << words[i] <<"\n";
    }
    
    cout << "\n\nPLEASE NOTE\nWe did not count words that included words already discovered. For example, Northeastern appears in our word search but once the program discovers North it will not count northeast northeaster or northeastern as words. This was our concious choice, because we though it best in tune with how a crossword is done it can be easily ammended to include all words by changing the return of is_word to always be false.\n";
}