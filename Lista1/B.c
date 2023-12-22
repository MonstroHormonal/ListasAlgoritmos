B.c

#include <stdio.h>

int hoarepartition(int A[], int l, int r);
void quicksort(int A[], int l, int r);
int binarysearch(int A[], int l, int r, int K);

int main(){

    int n, k, i = 0, numK = 0, pos;

    scanf("%d %d", &n, &k);

    int A[n];

    for(i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }

    quicksort(A, 0, n - 1);

    for(i = 0; i < n; i++){
         pos = binarysearch(A, 0, n, A[i] + k);
         if(pos != -1 && pos != i){
            numK++;
         }
    }

    printf("%d", numK);


    return 0;
}

int hoarepartition(int A[], int l, int r){
    int p, i, j, temp;
    p = A[l];
    i = l;
    j = r + 1;
    do{
        do{
            i = i + 1;
        }while(!(A[i] >= p || i >= r));
        do{
            j = j - 1;
        }while(!(A[j] <= p));
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }while(!(i >= j));

    temp = A[i];
    A[i] = A[j];
    A[j] = temp;

    temp = A[l];
    A[l] = A[j];
    A[j] = temp;
    return j;
}

void quicksort(int A[], int l, int r){
    int s;
    if(l < r){
        s = hoarepartition(A, l, r);
        quicksort(A, l, s - 1);
        quicksort(A, s + 1, r);

    }
}

int binarysearch(int A[], int l, int r, int K){

    int m;
    if(r >= l){
        m = (l + r)/2;
        if(K == A[m]) return m;
        else if(K < A[m]) return binarysearch(A, l, m - 1, K);
        else return binarysearch(A, m + 1, r, K);
    }
    else return -1;
}