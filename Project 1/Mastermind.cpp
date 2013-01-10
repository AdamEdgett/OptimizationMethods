#include <iostream>
#include <vector>
using namespace std;

class code {
   public:
       code(int n = 4, int m = 4);
       void print() const;
       int checkCorrect(vector<int> guess) const;
    private:
        vector<int> data;
        int n, m;
};

// Constructor
// Initializes a new code with n digits in length and 0-m as possible digits
code::code(int newN, int newM) {
    n = newN;
    m = newM;
    srand (time(NULL));
    data = vector<int>(n);
    for(int i = 0; i < n; i++) {
        data[i] = rand() % m;
    }
}
// Checks the user's guess and returns the number of spots that are correct
int code::checkCorrect(vector<int> guess) const {
    int numCorrect = 0;
    for(int i = 0; i < n; i++) {
        if(data[i] == guess[i]) {
            numCorrect++;
        }
    }
    return numCorrect;
}
// Prints the code
void code::print() const {
    cout << "data:" << endl;
    for(unsigned int i = 0; i < data.size(); i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

int main () {
    int n, m;
    cout << "Enter the number of digits to use:" << endl;
    cin >> n;
    cout << "Enter the range of digits (<=10)" << endl;
    cin >> m;
    code master (n, m);
    master.print();
    //prompt user for guesses
    for(int i = 0; i < 4; i++) {
        vector<int> guess(n);
        cout << "Enter a guess" << endl;
        for(int i = 0; i < n; i++) {
            cin >> guess[i];
        }
        int result = master.checkCorrect(guess);
        if(result == n) {
            cout << "Correct!" << endl;
            return 0;
        } else {
            cout << "You got " << result << " correct" << endl;
        }
    }
}