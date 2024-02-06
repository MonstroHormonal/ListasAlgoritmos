#include <iostream>

using namespace std;

void Heapify(int * H, int n, int i){

        int k = i;
        int v = H[i];
        bool heap = false;
        while(!heap && 2 * k <= n){ 
            int j = 2 * k;
            if(j < n){
                if(H[j] > H[j + 1]) j = j + 1;
            }
            if(v <= H[j]) heap = true;
            else{
                H[k] = H[j];
                k = j;
            }
        }
        H[k] = v;

}

void HeapBottomUp(int * H, int n){

    int i;
    for(i = n/2; i > 0; i--){
        Heapify(H, n, i);
    } 
}

int pop(int * H, int &n){

    int bruno = H[1];
    H[1] = H[n];
    n--;
    Heapify(H, n, 1);
    return bruno;

}

int main(){

    int n;
    int i;
    int tot = 0;
    int popped;

    cin >> n;

    while(n != 0){

        int array[n + 1];
        for(i = 1; i <= n; i++){
            cin >> array[i];
        }
        HeapBottomUp(array, n);
        while(n > 1){
            popped = pop(array, n);
            array[1] += popped;
            tot += array[1]; 
            Heapify(array, n, 1);
        }

        cout << tot << '\n';
        cin >> n;
        tot = 0;
    }
    

    return 0;
}
