// Adam Edgett & Dan Nordness
// Project 1
// code.h
#include <iostream>
#include <vector>
using namespace std;

class code {
   public:
       code(int n = 4, int m = 4);
       int checkCorrect(vector<int> guess) const;
       int checkIncorrect(vector<int> guess) const;
       friend ostream& operator<<(ostream &out, code c);
    private:
        vector<int> data;
        int n, m;
};

// Constructor
// Initializes a new code with n digits in length and 0-m as possible digits
code::code(int newN, int newM) {
    n = newN;
    m = newM;
    srand (time(NULL));
    data = vector<int>(n);
    for(int i = 0; i < n; i++) {
        data[i] = rand() % m;
    }
}

// Checks the user's guess and returns the number of spots that are correct
int code::checkCorrect(vector<int> guess) const {
    int numCorrect = 0;
    for(int i = 0; i < n; i++) {
        if(data[i] == guess[i]) {
            numCorrect++;
        }
    }
    return numCorrect;
}

//Check for correct digits in the incorrect place
int code::checkIncorrect(vector<int> guess) const {
    int numMisplaced = 0; //Start at zero
    vector<int> dataCopy = data; //Make copy of the secret code (because we'll be changing the data inside the vector and therefore can't use original)
	vector<int> guessCopy = guess;
    for(int i = 0; i < n; i++) 
	{ //Go through the top number and see if they are the same index with same value AKA number corrent
	  	if(dataCopy[i] == guessCopy[i]) 
		{ //If they are
            dataCopy[i] = -1; //Change the code value at i to -1 so that it won't be considered in the number misplaced counter
			guessCopy[i]	= -1; //Change the guess value at i to -1 for the same reason
	    }
	}
	for (int i = 0; i < n; i++) //Go through dataCopy, and stop to look for a misplaced value at all indices whose values !=-1
	{
		if (dataCopy[i]!=-1)
		{
	  	 	for(int j = 0; j < n; j++) //Iterate through guess and see if there are misplaced values
			{
	           if(dataCopy[i] == guessCopy[j]) //If there is one misplaced
				{
	               	numMisplaced++; //add one
					dataCopy[i] = -1; //flag both so they're not longer considered
					guessCopy[i] 	= -1;
		        }
			}
		}
  	}
    return numMisplaced;
}

// Prints the code
ostream& operator<<(ostream &out, code c){
    out << c.data;
    return out;
}

template <class T>;
ostream& operator<<(ostream &out, vector<T> v) {
    for unsigned int i = 0; i < v.size(); i++){
        out << v[i] << " ";
    }
    return out;
}