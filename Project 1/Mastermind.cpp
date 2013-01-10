#include <iostream>
#include <vector>
using namespace std;

class code {
   public:
       code(int n, int m);
       void print() const;
       int checkCorrect() const;
    private:
        vector<int> data;
        int n, m;
};

code::code(int newN, int newM) {
    n = newN;
    m = newM;
    srand (time(NULL));
    data = vector<int>(n);
    for(int i = 0; i < n; i++) {
        data[i] = rand() % m;
    }
}
int code::checkCorrect(vector<int> guess) const {
    return 0;
}

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
    Mastermind master (n, m);
    master.print();
}