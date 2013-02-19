#include <string>
#include <vector>
#include "wordlist.h"
#include "grid.h"
#include <cmath>

using namespace std;

int min_length=5;
int max_size;
vector<string> words;

//A mod function that actually works the way math should using negative numbers
int mod(int number, int modulus) {
     int result = number % modulus;
     
     if (result < 0) result += modulus;
     
     return result;
}
//Allows the user to select the grid to use
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
//Iterates through all directions at the point given.
void getAllWords(grid * g,wordlist * w,int x_pos,int  y_pos){
	int length=g->getMatrix()->cols();
	for (int i=-1;i<2;i++) {
        for (int j=-1;j<2;j++) {
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
					if (w->isWord(s)) {//is_word compares the string with all strings in the word list
            		    words.push_back(s); //add to words vector.
					}
				}
			}
		}
	}
}
//Iterates through the grid.
void findMatches(wordlist * w,  grid *g){
	for (int i=0; i<g->getMatrix()->cols();i++) {
		for (int j=0; j<g->getMatrix()->rows(); j++) {
			getAllWords(g,w,j,i);
		}
	}
}

int main(void) {
    wordlist * w=new wordlist;
    grid * g=new grid(testSearch());
    
    max_size=g->getMatrix()->rows();
 
    
    findMatches(w,g);
    
    cout << "\n";
    cout << "There are "<<words.size() << " words. \nThey are:\n";
    for (unsigned int i=0;i<words.size();i++) {
        cout << words[i] <<"\n";
    }
}