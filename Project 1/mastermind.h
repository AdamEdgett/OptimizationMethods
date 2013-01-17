#include "code.h"
using namespace std;

class mastermind {
    public:
        mastermind();
        mastermind(int n, int m);
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
}
mastermind::mastermind(int n, int m) {
    answer = code(n, m);
}