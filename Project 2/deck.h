#include "d_node.h"
#include "card.h"
#include <cstdlib>
#include <string> 
#include <iostream> 


class deck {
    public:
        deck();
        ~deck();
        node<card>* getFirst();
        void setFirst(node<card>* newFirst);
        friend std::ostream& operator<<(std::ostream& out, deck& d);
        card deal();
        void replace(card c);
        void shuffle();
    private:
        node<card>* first;
};

// Constructor
deck::deck() {
    // Initialize deck of 52 cards
    // For each number value
    node<card>* prevNode;
    for(unsigned int i = 0; i < sizeof(values)/sizeof(std::string); i++) {
        // For each suit value
        for(unsigned int j = 0; j < sizeof(suits)/sizeof(std::string); j++) {
            // Create a new card and add it to the deck
            card currentCard(i, j);
            node<card>* currentNode = new node<card>(currentCard);
            if(i == 0 && j == 0) {
                // set as first card of the deck
                first = currentNode;
            } else {
                // set as the next card of the previous card
                prevNode->next = currentNode;
            }
            prevNode = currentNode;
        }
    }
}

// Destructor
deck::~deck() {
    node<card>* currentNode = first;
    while(currentNode) {
        node<card>* prevNode = currentNode;
        currentNode = currentNode->next;
        delete prevNode;
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
std::ostream& operator<<(std::ostream &out, deck& d) {
    node<card>* currentNode = d.first;
    while(currentNode != NULL) {
        out << currentNode->nodeValue << "\n";
        currentNode = currentNode->next;
    }
    return out;
}

// Returns (deals) the first card of the deck
card deck::deal() {
    if(first == NULL) {
        throw rangeError("No more cards left to deal");
    }
    card topCard = first->nodeValue;
    setFirst(first->next);
    return topCard;
}

// Replaces the given card at the bottom of the deck
void deck::replace(card c) {
    node<card>* newNode = new node<card>(c);
    node<card>* currentNode = first;
    while(currentNode->next) { // get to the last node
        currentNode = currentNode->next;
    }
    currentNode->next = newNode; // insert the card at the end
}

// Puts the card in a random order
void deck::shuffle() {
    // Seed a new random generator
    srand (time(NULL));
    
    // Iterate through all the cards
    node<card>* currentNode = first;
    int currentIndex = 0;
    while(currentNode) {
        // Find a different card at a random index
        node<card>* switchNode = currentNode;
        int switchIndex = rand() % (52 - currentIndex);
        for(int i = 0; i < switchIndex; i++) {
            switchNode = switchNode->next;
        }
        // Switch the current card with the random card
        card switchCard = switchNode->nodeValue;
        switchNode->nodeValue = currentNode->nodeValue;
        currentNode->nodeValue = switchCard;
        
        // Continue iterating
        currentNode = currentNode->next;
        currentIndex++;
    }
}