// Adam Edgett & Dan Nordness
// Project 1
// program.cpp
#include <cstdlib>
#include "mastermind.h"
#include "d_except.h"
using namespace std;

int main () {
    // Setup for game
    try {
        int n, m;
        cout << "Enter the number of digits to use:" << endl;
        cin >> n;
        if(cin.fail()) { // Verify input was cast and stored correctly
            throw baseException("Invalid input: non-digit");
        }
        cout << "Enter the range of digits (<=10)" << endl;
        cin >> m;
        if(cin.fail()) { // Verify input was cast and stored correctly
            throw baseException("Invalid input: non-digit");
        }
        
        mastermind game(n, m);
        game.play();
    } catch(rangeError e) {
        cout << "There was an error when running the game:" << endl;
        cout << e.what() << endl;
        exit(0);
    } catch(baseException e) {
        cout << "Invalid input was received:" << endl;
        cout << e.what() << endl;
        exit(0);
    }
}
