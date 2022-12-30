#include <bits/stdc++.h>
using namespace std;
const size_t LIM = 10000 + 10;
list<int> L[LIM];
string command;
void addNewNum(size_t id, int num) { L[id].push_back(num); }
void mergeUp(size_t id1, size_t id2) { L[id1].merge(L[id2]); }
void uniqueUp(size_t id) {
    L[id].sort();
    L[id].unique();
}
void outputL(size_t id) {
    if (!L[id].empty()) {
        L[id].sort();
        for (list<int>::iterator iter = L[id].begin(); iter != L[id].end();
             iter++)
            cout << *iter << ' ';
    }
    cout << endl;
}
int main() {
    int n;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    while (n--) {
        size_t item1, item2;
        cin >> command >> item1;
        switch (command[0]) {
            case 'n': break;
            case 'a':
                cin >> item2;
                addNewNum(item1, item2);
                break;
            case 'm':
                cin >> item2;
                mergeUp(item1, item2);
                break;
            case 'u': uniqueUp(item1); break;
            case 'o': outputL(item1); break;
        }
    }

    return 0;
}