using namespace std;
#include "d_node.h";
#include "card.h";

class deck {
    public:
        deck();
        node<card>* getFirst();
        void setFirst(node<card>* newFirst);
        friend ostream& operator<<(ostream& out, deck d);
    private:
        node<card>* first;
};

// Constructor
deck::deck() {
    // Initialize deck of 52 cards
    // For each number value
    node<card>* prevNode;
    for(unsigned int i = 0; i < sizeof(values)/sizeof(string); i++) {
        // For each suit value
        for(unsigned int j = 0; j < sizeof(suits)/sizeof(string); j++) {
            // Create a new card and add it to the deck
            card currentCard(i, j);
            node<card>* currentNode = new node<card>(currentCard);
            if(i == 0 && j == 0) {
                first = currentNode; // set as first
            } else {
                prevNode->next = currentNode;
            }
            prevNode = currentNode;
        }
    }


            
}

// Getters and setters for private variables
node<card>* deck::getFirst() {
    return first;
}

void deck::setFirst(node<card>* newFirst) {
    first = newFirst;
}

// Outstream operator
ostream& operator<<(ostream &out, const deck d) {
    node<card>* currentNode = d.first;
    while(currentNode != NULL) {
        out << currentNode->nodeValue << endl;
        currentNode = currentNode->next;
    }
    return out;
}