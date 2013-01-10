#include <iostream>
using namespace std;

class Mastermind {
   public:
       Mastermind(int n, int m);
       void print() const;
       int checkCorrect() const;
    private:
        int* code;
        int n, m;
};

Mastermind::Mastermind(int newN, int newM) {
    n = newN;
    m = newM;
    srand (time(NULL));
    code = new int[n];
    for(int i = 0; i < n; i++) {
        code[i] = rand() % m;
    }
}
int Mastermind::checkCorrect() const {
    return 0;
}

void Mastermind::print() const {
    cout << "code:" << endl;
    for(int i = 0; i < n; i++) {
        cout << code[i] << " ";
    }
    cout << endl;
}

int main () {
    int n, m;
    cout << "Enter the number of digits to use:" << endl;
    cin >> n;
    cout << "Enter the range of digits (<=10)" << endl;
    cin >> m;
    Mastermind master (n, m);
    master.print();
}