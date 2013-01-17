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
    int numMisplaced = 0;
    vector<int> dataCopy = data;
    for(int i = 0; i < n; i++) {
        if(dataCopy[i] == guess[i]) {
            dataCopy[i] = -1;
        }
        for(int j = 0; j < n; j++) {
            if(i != j && dataCopy[i] == guess[j]) {
                numMisplaced++;
                dataCopy[i] = -1;
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