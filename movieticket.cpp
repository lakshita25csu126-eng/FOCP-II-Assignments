#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

const int MAX_USERS = 100005;
const int MAX_MOVIES = 10005;

bool booked[MAX_USERS][MAX_MOVIES];
int seats[MAX_MOVIES];

int main() {
    int Q;
    cin >> Q;

    // Initialize all movies with 100 seats
    for (int i = 0; i < MAX_MOVIES; i++) {
        seats[i] = 100;
    }

    while (Q--) {
        string type;
        cin >> type;

        if (type == "BOOK") {
            int x, y;
            cin >> x >> y;

            if (booked[x][y] || seats[y] == 0) {
                cout << "false\n";
            } else {
                booked[x][y] = true;
                seats[y]--;
                cout << "true\n";
            }
        }
        else if (type == "CANCEL") {
            int x, y;
            cin >> x >> y;

            if (!booked[x][y]) {
                cout << "false\n";
            } else {
                booked[x][y] = false;
                seats[y]++;
                cout << "true\n";
            }
        }
        else if (type == "IS_BOOKED") {
            int x, y;
            cin >> x >> y;

            cout << (booked[x][y] ? "true\n" : "false\n");
        }
        else if (type == "AVAILABLE_TICKETS") {
            int y;
            cin >> y;

            cout << seats[y] << "\n";
        }
    }

    ret
