#include <string> 
#include <iostream> 
#include "d_except.h"
const std::string suits[4] = {"club", "diamond", "heart", "spade"};
const std::string values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "ace"};

class card {
    public:
        card(int value = 0, int suit = 0);
        card(const card& c);
        int getValue();
        void setValue(int value);
        int getSuit();
        void setSuit(int suit);
        card& operator=(const card& c);
        friend std::ostream& operator<<(std::ostream &out, card c);
    private:
        int value;
        int suit;
};

// Constructor
// Initializes a new card with a value and a suit
card::card(int newValue, int newSuit) {
    setValue(newValue);
    setSuit(newSuit);
}
// Copy constructor
card::card(const card& c) {
    setValue(c.value);
    setSuit(c.suit);
}

// Geters and seters
int card::getValue() {
    return value;
}

void card::setValue(int newValue) {
    if(newValue < 0 || newValue > 12) {
        throw rangeError("Invalid card value");
    } else {
        value = newValue;
    }
}

int card::getSuit() {
    return suit;
}

void card::setSuit(int newSuit) {
    if(newSuit < 0 || newSuit > 3) {
        throw rangeError("Invalid card suit");
    } else {        
        suit = newSuit;
    }
}

// Assignment operator
card& card::operator=(const card& c) {
    setValue(c.value);
    setSuit(c.suit);
    return *this;
}

// Outstream operator
std::ostream& operator<<(std::ostream &out, const card c) {
    out << values[c.value] << " of " << suits[c.suit];
    return out;
}
