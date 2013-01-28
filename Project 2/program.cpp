#include <cstdlib>
#include "deck.h"
#include "d_except.h"
using namespace std;

int main() {
    try {
        deck d;
        cout << d << "\n";
    } catch (rangeError e) {
        cout << "There was an error when running the game:\n";
        cout << e.what() << "\n";
        exit(0);
    }
}
