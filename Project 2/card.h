using namespace std;

class card {
    public:
        card(int value = 0, string suit = "");
        int getValue();
        void setValue(int value);
        string getSuit();
        void setSuit(string suit);
        friend ostream& operator<<(ostream &out, card c);
    private:
        int value;
        string suit;
};

// Constructor
// Initializes a new card with a value and a suit
card::card(int newValue, string newSuit) {
    value = newValue;
    suit = newSuit;
}

// Geters and seters

int card::getValue() {
    return value;
}

void card::setValue(int newValue) {
    value = newValue;
}

string card::getSuit() {
    return suit;
}

void card::setSuit(string newSuit) {
    suit = newSuit;
}

// Outstream operator
ostream& operator<<(ostream &out, const card c) {
    out << c.value << " of " << c.suit;
    return out;
}