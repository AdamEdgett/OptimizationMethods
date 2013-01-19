// Adam Edgett & Dan Nordness
// Project 1
// program.cpp
#include <cstdlib>
#include "mastermind.h"
using namespace std;

int main () {
    // Setup for game
    int n, m;
    cout << "Enter the number of digits to use:" << endl;
    cin >> n;
    cout << "Enter the range of digits (<=10)" << endl;
    cin >> m;
    mastermind game(n, m);
    game.play();
}
