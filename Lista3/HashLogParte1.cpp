#include <iostream>
#include <string>

using namespace std;

struct DATA {
    int T;
    long long int C;
};

int binarySearch(DATA A[], int l, int r, int T) {
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (A[mid].T == T)
            return mid;

        if (A[mid].T < T)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return -1;
}

int hoarepartition(DATA A[], int l, int r) {
    int p = A[l].T;
    int i = l, j = r + 1;
    DATA temp;

    do {
        do { i++; } while (i <= r && A[i].T < p);
        do { j--; } while (A[j].T > p);
        if (i < j) {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    } while (i < j);

    temp = A[l];
    A[l] = A[j];
    A[j] = temp;

    return j;
}

void quicksort(DATA A[], int l, int r) {
    if (l < r) {
        int s = hoarepartition(A, l, r);
        quicksort(A, l, s - 1);
        quicksort(A, s + 1, r);
    }
}

int main() {
    string str;
    int T;
    int i = 0;
    DATA* dados = new DATA[1000000];

    while (cin >> str) {
        if (str == "NEW") {
            cin >> dados[i].T >> dados[i].C;
            i++;
        }
        else if (str == "QRY") {
            cin >> T;
            quicksort(dados, 0, i - 1);
            int idx = binarySearch(dados, 0, i - 1, T);
            if (idx != -1) {
                cout << dados[idx].C << " " << idx << endl;
            }
            else {
                cout << "-1 -1" << endl;
            }
        }
        else if (str == "END") {
            break;
        }
    }

    delete[] dados;
    return 0;
}
