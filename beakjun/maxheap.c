#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(){

    int N;
    scanf("%d", &N);

    int *maxHeap = malloc(sizeof(int) * N);
    memset(maxHeap, 0, sizeof(int) * N);  // memset함수 쓸 때 주의. 그냥 귀찮다고 sizeof(maxHeap)하니까 안됨 
    int cap = 0;

    while (N > 0){
    
    int X;
    scanf("%d", &X);

    if (X > 0){
        
        maxHeap[cap] = X;
        
        int index = cap;

        // 자녀 > 부모일 때까지 반복
        while(maxHeap[index] > maxHeap[(index-1) / 2]){
        
            int temp;
            temp = maxHeap[index];
            maxHeap[index] =  maxHeap[(index-1) / 2];
            maxHeap[(index-1) / 2] = temp;

            index = (index-1) / 2;

            
        }


        ++cap;
    }
    else if (X == 0){

        if (cap == 0){
            printf("0\n");
        }
        else {
        
        printf("%d\n", maxHeap[0]);

        --cap;
        maxHeap[0] = maxHeap[cap];      //cap변수 주의 그냥 maxHeap[--cap] 이렇게 쓰면 이 배열 안에서만 cap이 1 감소된 것 같은데 아님
        maxHeap[cap] = 0; 

        int index = 0;
        int left = 1;
        int right = 2;

        while ( maxHeap[index] < maxHeap[left] || maxHeap[index] < maxHeap[right]){
        
            if (maxHeap[right] >= maxHeap[left]){

                int temp;
                temp = maxHeap[index];
                maxHeap[index] =  maxHeap[right];
                maxHeap[right] = temp;

                index = right;
                left = index*2 + 1;
                right = index*2 + 2;

            }
            else{

                int temp;
                temp = maxHeap[index];
                maxHeap[index] =  maxHeap[left];
                maxHeap[left] = temp;

                index = left;
                left = index*2 + 1;
                right = index*2 + 2;
            }
        
        }
        }

    }


    --N;

    }


    free(maxHeap);
    return 0;

} 

