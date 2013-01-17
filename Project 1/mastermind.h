// Adam Edgett & Dan Nordness
// Project 1
// mastermind.h
#include "code.h"
using namespace std;

class mastermind {
    public:
        mastermind();
        mastermind(int n, int m);
        void play();
    private:
        code answer;
};

mastermind::mastermind() {
    // Take keyboard input
    // Setup for game
    int n, m;
    cout << "Enter the number of digits to use:" << endl;
    cin >> n;
    cout << "Enter the range of digits (<=10)" << endl;
    cin >> m;
    code answer (n, m);
    cout << "Answer: " << answer << endl;
}

mastermind::mastermind(int n, int m) {
    answer = code(n, m);
    cout << "Answer: " << answer << endl;
}

void mastermind::play() {
    // Prompt user for guesses
    for(int i = 0; i < 4; i++) {
        vector<int> guess(answer.size());
        cout << "Enter a guess" << endl;
        for(unsigned int i = 0; i < guess.size(); i++) {
            cin >> guess[i];
        }
        // Check this guess
        int result = answer.checkCorrect(guess);
        if(result == answer.size()) {
            cout << "Correct!" << endl;
            return;
        } else {
            cout << "You got " << result << " correct" << endl;
            int misplaced = answer.checkIncorrect(guess);
            cout << "You got " << misplaced;
            cout << " correct in the incorrect places" << endl;
        }
    }
}