#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>

void merge(int **A, int *B, int *C);
void mergesort(int *A);


int main()
{
    int num;
    scanf("%d", &num); 

    int* A = (int *)malloc(sizeof(int) * num);

    for (int i = 0; i < num; i++)
    {
        scanf("%d", &A[i]);
    }

    mergesort(A);

    for (int i = 0; i < num; i++)
    {
        printf("%d\n", A[i]);
    }

    free(A);

}

void mergesort(int *A){
    
    int num = _msize(A) / sizeof(int);


    if (num > 1){    
        int* B = (int *)malloc(sizeof(int) * floor(num/2));
        int* C = (int *)malloc(sizeof(int) * ceil(num/2)); // 홀수일 때 생각

        for (int i = 0; i < floor(num/2) ; i++)
        {
            B[i] = A[i];  
        }

        for (int i = floor(num/2); i < num ; i++)
        {
            int I = i - floor(num/2);
            C[I] = A[i]; 
        }

        mergesort(B);
        mergesort(C);

        merge(&A, B, C);
    }
    // free 언제해줌? 
}



void merge(int **A, int *B, int *C){
    int i = 0;  // 배열 b
    int j = 0;  // 배열 c
    int k = 0;  // 배열 a

    int p = sizeof(B) / sizeof(int);  // 배열 b의 개수
    int q = sizeof(A) / sizeof(int);  // 배열 c의 개수

    while (i < p && j < q){

        if (B[i] <= C[j]){
            *A[k] = B[i];
            i++;
        }
        else {
            *A[k] = C[j];
            j++;
        }

        k++;
    }

    if (i = p){ // 배열 b가 다 찼을 경우
        for(int J = j; J < q; J++){
            *A[k] = C[j];  // 여기 맞는지 확인
            k++;
        }
    }
    else if (j = q){ // 배열 c가 다 찼을 경우
        for(int I = i; I < p; I++){
            *A[k] = B[i];
            k++; 
        }
    }
}