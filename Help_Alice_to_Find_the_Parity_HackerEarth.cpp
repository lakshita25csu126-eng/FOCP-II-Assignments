#include <iostream>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long L, R;
    cin >> L >> R;

    long long odd_count = (R + 1) / 2 - L / 2;

    if (odd_count % 2)
        cout << "odd";
    else
        cout << "even";

    return 0;
}
