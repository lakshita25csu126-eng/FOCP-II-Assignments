#include <iostream>
using namespace std;

const int MAXN = 10000000;

int cnt[MAXN + 1]; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 2; i <= MAXN; i++) {
        if (cnt[i] == 0) {
            for (int j = i; j <= MAXN; j += i) {
                cnt[j]++;
            }
        }
    }

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        cout << (1 << cnt[n]) << '\n'; 
    }

    return 0;
}
