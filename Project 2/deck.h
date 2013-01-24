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
        out << currentNode << " : " << currentNode->nodeValue << endl;
        currentNode = currentNode->next;
    }
    return out;
}