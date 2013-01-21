// Adam Edgett & Dan Nordness
// Project 1
// mastermind.h
#include "code.h"
#include "d_except.h"
using namespace std;

class mastermind {
    public:
        mastermind();
        mastermind(int n = 4, int m = 4);
        void play() const;
    private:
        code answer;
};

// Constructor
// Creates a new code and prints the answer
mastermind::mastermind(int n, int m)
    : answer(n, m) {
    cout << "Answer: " << answer << endl;
}

// Plays mastermind
// Asks for guesses and checks them against the answer
void mastermind::play() const {
    // Prompt user for guesses
    for(int i = 0; i < 4; i++) {
        vector<int> guess(answer.size());
        cout << "Enter a guess" << endl;
        for(unsigned int i = 0; i < guess.size(); i++) {
            cin >> guess[i];
            if(cin.fail()) { // Verify input was cast and stored correctly
                throw baseException("Invalid input: non-digit");
            }
        }
        int correct = answer.checkCorrect(guess);
        // Check this guess
        if(correct == answer.size()) {
            cout << "Correct!" << endl;
            return;
        } else {
            cout << "You got " << correct << " correct" << endl;
            int misplaced = answer.checkIncorrect(guess);
            cout << "You got " << misplaced;
            cout << " correct in the incorrect places" << endl;
        }
    }
}