#include <cstdlib>
#include "deck.h"
#include "d_except.h"
using namespace std;



int main() {
    try {
     deck d;
     cout << d << "\n";
    }
    catch (rangeError e) {
    cout << "There was an error with the selected value or suit, perhaps out of range. \n";
    cout << e.what() << "\n";
    return(0);
    }
}
