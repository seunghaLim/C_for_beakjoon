#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(){

    int N;
    scanf("%d", &N);

    int *minHeap = malloc(sizeof(int) * N);
    memset(minHeap, 0, sizeof(int) * N);   
    int cap = 0;

    while (N > 0){
    
    int X;
    scanf("%d", &X);

    if (X > 0){
        
        minHeap[cap] = X;
        
        int index = cap;

        // 자녀 > 부모일 때까지 반복
        while(minHeap[index] < minHeap[(index-1) / 2]){
        
            int temp;
            temp = minHeap[index];
            minHeap[index] =  minHeap[(index-1) / 2];
            minHeap[(index-1) / 2] = temp;

            index = (index-1) / 2;

            
        }


        ++cap;
    }
    else if (X == 0){

        if (cap == 0){
            printf("0\n");
        }
        else {
        
        printf("%d\n", minHeap[0]);

        --cap;
        minHeap[0] = minHeap[cap];      
        minHeap[cap] = 0; 

        int index = 0;
        int left = 1;
        int right = 2;

        //flag를 0으로 뒀는데 맥스힙의 경우 큰 문제가 없지만 민힙의 경우 비교할 때 이미 빈 배열인데도 그걸 0값으로 인식할 수 있음 그걸 걸러주는 장치가 필요함
        while ( (minHeap[index] > minHeap[left] && minHeap[left] != 0) || (minHeap[index] > minHeap[right] && minHeap[right] != 0)){
        
            if (minHeap[right] <= minHeap[left]){

                int temp;
                temp = minHeap[index];
                minHeap[index] =  minHeap[right];
                minHeap[right] = temp;

                index = right;

                left = index*2 + 1;
                right = index*2 + 2;

            }
            else if (minHeap[right] > minHeap[left]){

                int temp;
                temp = minHeap[index];
                minHeap[index] =  minHeap[left];
                minHeap[left] = temp;

                index = left;
                left = index*2 + 1;
                right = index*2 + 2;
            }
        
        }
        }

    }


    --N;

    }


    free(minHeap);
    return 0;

} 

