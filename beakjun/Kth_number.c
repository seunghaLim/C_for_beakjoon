#include <stdio.h>
#include <stdlib.h>


int QuickSelect(int A[], int l, int r, int k);
int Partition_L(int A[], int l, int r);
void swap(int *A, int *B);


int main(){

    int N,n,K;

    scanf("%d", &N);
        
    n = N*N;
    int *arr = malloc(sizeof(int) * n);

    // 2차원 배열을 1차원 배열처럼 활용
    for (int i = 0; i < N; i++){
        
        for (int j = 0; j < N; j++){

            arr[i*N + j] = (i+1)*(j+1);
        } 
    }

    scanf("%d", &K);

    printf("%d\n", QuickSelect(arr, 0, n-1, K));
    

    free(arr);
    
    
}


int QuickSelect(int A[], int l, int r, int k){

    int s = Partition_L(A, l, r);

    if (s == k-1){
        
        return A[s];
    }
    else if (s > l + (k-1)){            // l(제일 왼쪽 인덱스)이 0이라면 그냥 s > k-1 이렇게 해줘도 되는데  
                                        // 0이 아닐지도 모르니 l+k-1 이렇게 해줘야 한다
        QuickSelect(A, l, s-1, k);
    }
    else{        
        
        QuickSelect(A, s+1, r, k);

    }

}

int Partition_L(int A[], int l, int r){

    int s, p;
    s = l;
    p = l;

    for (int i = l+1; i <= r; i++){

        if (A[i] < A[p]){
            
            s += 1;
            swap(&A[s], &A[i]);
        }
    }

    swap(&A[s], &A[p]);

    return s;

}


void swap(int *A, int *B){

    int temp;
    temp = *A;
    *A = *B; 
    *B = temp;
}
