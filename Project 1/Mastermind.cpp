#include <iostream>
#include <vector>
using namespace std;

class Mastermind {
   public:
       Mastermind(int n, int m);
       void print() const;
       int checkCorrect() const;
    private:
        vector<int> code;
        int n, m;
};

Mastermind::Mastermind(int newN, int newM) {
    n = newN;
    m = newM;
    srand (time(NULL));
    code = vector<int>(n);
    for(int i = 0; i < n; i++) {
        code[i] = rand() % m;
    }
}
int Mastermind::checkCorrect(vector<int> guess) const {
    return 0;
}

void Mastermind::print() const {
    cout << "code:" << endl;
    for(unsigned int i = 0; i < code.size(); i++) {
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