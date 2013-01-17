// Adam Edgett & Dan Nordness
// Project 1
// program.cpp
#include <iostream>
#include <vector>
#include "code.h"
using namespace std;

int main () {
    // Setup for game
    int n, m;
    cout << "Enter the number of digits to use:" << endl;
    cin >> n;
    cout << "Enter the range of digits (<=10)" << endl;
    cin >> m;
    code master (n, m);
    cout << "Answer: " << master << endl;
    
    // Prompt user for guesses
    for(int i = 0; i < 4; i++) {
        vector<int> guess(n);
        cout << "Enter a guess" << endl;
        for(int i = 0; i < n; i++) {
            cin >> guess[i];
        }
        // Check this guess
        int result = master.checkCorrect(guess);
        if(result == n) {
            cout << "Correct!" << endl;
            return 0;
        } else {
            cout << "You got " << result << " correct" << endl;
            int misplaced = master.checkIncorrect(guess);
            cout << "You got " << misplaced;
            cout << " correct in the incorrect places" << endl;
        }
    }
}