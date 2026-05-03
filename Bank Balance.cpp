#include <iostream>
#include <map>
using namespace std;

int main() {
    int Q;
    cin >> Q;

    map<int, long long> balance;

    while (Q--) {
        string type;
        cin >> type;

        if (type == "CREATE") {
            int x;
            long long y;
            cin >> x >> y;

            if (balance.count(x) == 0) {
                balance[x] = y;
                cout << "true\n";
            } else {
                balance[x] += y;
                cout << "false\n";
            }
        }

        else if (type == "DEBIT") {
            int x;
            long long y;
            cin >> x >> y;

            if (balance.count(x) == 0 || balance[x] < y) {
                cout << "false\n";
            } else {
                balance[x] -= y;
                cout << "true\n";
            }
        }

        else if (type == "CREDIT") {
            int x;
            long long y;
            cin >> x >> y;

            if (balance.count(x) == 0) {
                cout << "false\n";
            } else {
                balance[x] += y;
                cout << "true\n";
            }
        }

        else if (type == "BALANCE") {
            int x;
            cin >> x;

            if (balance.count(x) == 0) {
                cout << -1 << endl;
            } else {
                cout << balance[x] << endl;
            }
        }
    }

    return 0;
}
