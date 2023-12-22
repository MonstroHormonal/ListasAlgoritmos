#include <stdio.h>

void merge(long long int A[], long long int temp[], long long int l, long long int r);
void mergesort(long long int A[], long long int temp[], long long int l, long long int r);

 int main(){

     long long int n, m, i;

    scanf("%lld", &n);

       long long int A[n], temp[n], tot = 0;
    for(i = 0; i < n; i++){
        scanf("%lld ", &A[i]);
        tot += A[i];
    }

    scanf("%lld", &m);

       long long int q[m];
    for(i = 0; i < m; i++){
        scanf("%lld", &q[i]);
    }

    mergesort(A, temp, 0, n - 1);

    for(i = 0; i < m; i++){
         printf("%lld\n", tot - A[n - q[i]]);
    }

    return 0;
}

void merge(long long int A[], long long int temp[], long long l, long long r){

     long long int i;

     for(i = l; i <= r; i++){
         temp[i] = A[i];
     }

     long long int m = (l + r)/2;
     long long int i1 = l;
     long long int i2 = m + 1;

     long long int curr;

     for(curr = l; curr <= r; curr++){

         if(i1 == m + 1){
             A[curr] = temp[i2++];
         }

         else if(i2 > r){
             A[curr] = temp[i1++];
         }

         else if(temp[i1] <= temp[i2]){
             A[curr] = temp[i1++];
         }

         else{
             A[curr] = temp[i2++];
         }
     }

 }

void mergesort(long long int A[], long long int temp[], long long int l, long long int r){

     long long int m;

     if(l < r){
         m = (l + r)/2;
         mergesort(A, temp, l, m);
         mergesort(A, temp, m + 1, r);
         merge(A, temp, l, r);
     }
 }