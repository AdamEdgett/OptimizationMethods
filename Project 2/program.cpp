#include <cstdlib>
#include "deck.h"
#include "d_except.h"
using namespace std;

int calculatePoints(card dealtCard, int points) {
    // Check points by card value
    if(dealtCard.getValue() >= 12) {
        points += 10;
    } else if(dealtCard.getValue() >= 9) {
        points += 5;
    } else if(dealtCard.getValue() >= 6) {
        points += 0;
    } else if(dealtCard.getValue() >= 5) {
        points /= 2;
    } else if(dealtCard.getValue() >= 0) {
        points = 0;
    }
    // Check if card is a heart
    if(dealtCard.getSuit() == 2) {
        points += 1;
    }
    return points;
}

int playFlip() {
    // Initialize game
    deck d;
    cout << d << "\n\n";
    int points = 0;
    // d.shuffle();
    
    // Start dealing
    card dealtCard = d.deal();
    cout << "First card: " << dealtCard << "\n";
    cout << "Current score: " << points << "\n";
    cout << "Would you like to continue? (y/n) ";
    string response;
    cin >> response;
    while(true)  {
        // Verify input
        while(response != "y" && response != "n") {
            cout << "Invalid input. y or n are acceptable inputs\n";
            cout << "Continue? (y/n) ";
            cin >> response;
        }
        // Continue game
        if(response == "y") {
            dealtCard = d.deal();
            points = calculatePoints(dealtCard, points);
            cout << "Dealt card: " << dealtCard << "\n";
            cout << "Current score: " << points << "\n";
            cout << "Continue? (y/n) ";
            cin >> response;
        // End game
        } else if(response == "n") {
            cout << "Final score: " << points << "\n";
            return 0;
        }
    }
}

int main() {
    try {
        playFlip();
    } catch (rangeError e) {
        cout << "There was an error when running the game:\n";
        cout << e.what() << "\n";
        exit(0);
    }
}