#include <stdio.h>

#define MAX 1000000

int arr[MAX];

void QuickSort (int A[], int l, int r);
int Partiton_H(int A[], int L, int R);
void swap(int *A, int *B);


int main(){

    int N, l, r;
    scanf("%d",&N);
    

    for (int i = 0; i < N; i++){

        scanf("%d", &arr[i]);
        
    }

    l = 0;
    r = N-1;    //  4
    
    QuickSort (arr, l, r);
    

    for (int i = 0; i < N; i++){
        printf("%d\n", arr[i]);
    }

    
}

void QuickSort (int A[], int l, int r){

    //if문 - array 인덱스에서 벗어나는지 검사하는 역할 
    if (l < r){
        
        int s = Partiton_H(A, l, r);
        QuickSort(A, l, s-1);
        QuickSort(A, s+1, r);

    } 
}

int Partiton_H(int A[], int L, int R){

    int p = L;
    int i = L+1;
    int j = R;

    do {
        
        // A[i]가 피봇값보다 크거나 같으면 멈춤
        // i < R -> 인덱스 변수 i가 인덱스 범위를 벗어나지 않게 막아줌
        while (A[i] < A[p] && i < R){
            
            i = i+1;
        }
        // A[j]가 피봇값보다 작거나 같으면 멈춤
        while (A[j] > A[p]){
            
            j = j-1;
        }
        
        swap(&A[i], &A[j]);
        
    } while (i < j);

    swap(&A[i], &A[j]);
    swap(&A[j], &A[p]);

    return j;  

}

void swap(int *A, int *B){

    int temp;
    temp = *A;
    *A = *B; 
    *B = temp;
}



