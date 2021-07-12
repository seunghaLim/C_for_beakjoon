#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 1000000

int arr[MAX];

void MergeSort(int A[], int l, int r, int n);
void Merge(int A[], int L, int l, int R, int r);

int main(){
        
    int N, l, r;
    scanf("%d",&N);
    

    for (int i = 0; i < N; i++){

        scanf("%d", &arr[i]);
        
    }

    l = 0;
    r = N-1;    //  4
    
    MergeSort(arr, l, r, N);
    
    printf("\n");

    for (int i = 0; i < N; i++){
        printf("%d\n", arr[i]);
    }
    
}

void MergeSort(int A[], int l, int r, int n){
 
    if(n > 1){

        MergeSort(A, l, (l+r)/2, floor(n/2));       // n값 잘못 설정해줘서 무한루프
        MergeSort(A, (l+r)/2+1, r, ceil(n/2));
        Merge(A, l, (l+r)/2+1, (l+r)/2, r);
        
    }

    
}

void Merge(int A[], int L, int l, int R, int r){

    int i, j, k;
    i = L;
    j = l;
    k = L;
    int* B = malloc(sizeof(int) * r+1);     // 임시 배열 사용


    while( i < (R+1) && j < (r+1) ){

        if (A[i] <= A[j]){
            B[k] = A[i];
            i = i+1;
        }
        else{
            B[k] = A[j];
            j = j+1;
        }
        
        k++;

    }

    if (j == r+1){
        
        for (int I = i; I <= R; I++){
            B[k] = A[I]; 
            k++;
        } 
    }
    else if (i == R+1){
        
        for (int I = j; I <= r; I++){
            B[k] = A[I]; 
            k++;
        } 
    }

    for (int I = L; I <= r; I++){

        A[I] = B[I];

    }


    free(B);
 

}

