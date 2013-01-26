#include <string> 
#include <iostream> 
const std::string suits[4] = {"club", "diamond", "heart", "spade"};
const std::string values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "ace"};
class card {
    public:
        card(int value = 0, int suit = 0);
        int getValue();
        void setValue(int value);
        int getSuit();
        void setSuit(int suit);
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

// Geters and seters

int card::getValue() {
    return value;
}

void card::setValue(int newValue) {
    value = newValue;
}

int card::getSuit() {
    return suit;
}

void card::setSuit(int newSuit) {
    suit = newSuit;
}

// Outstream operator
std::ostream& operator<<(std::ostream &out, const card c) {
    out << values[c.value] << " of " << suits[c.suit];
    return out;
}
