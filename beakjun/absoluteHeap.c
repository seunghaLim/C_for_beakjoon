#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(){

    int N;
    scanf("%d", &N);

    int *Heap = malloc(sizeof(int) * N);
    memset(Heap, 0, sizeof(int) * N);   
    int cap = 0;

    while (N > 0){
    
    int X;
    scanf("%d", &X);


    // X가 음수가 될 수 있으니 if(X > 0)은 안됨
    if (X != 0){
        
        Heap[cap] = X;
        
        int index = cap;

        // 자녀절대 < 부모절대일 때까지 반복
        // 반복문 주의. 자녀절대 = 부모절대이지만 자녀 절대가 부모 절대보다 더 커서 바꿀 필요가 없을 때 break 해줘야 함   
        while(abs(Heap[index]) <= abs(Heap[(index-1) / 2]) && index != 0 ){
        
            if ( abs(Heap[index]) == abs(Heap[(index-1) / 2]) && (Heap[index] < Heap[(index-1) / 2]) ){

                int temp;
                temp = Heap[index];
                Heap[index] =  Heap[(index-1) / 2];
                Heap[(index-1) / 2] = temp;

                index = (index-1) / 2;

            }
            else if(abs(Heap[index]) < abs(Heap[(index-1) / 2])) {
                
                int temp;
                temp = Heap[index];
                Heap[index] =  Heap[(index-1) / 2];
                Heap[(index-1) / 2] = temp;

                index = (index-1) / 2;

            }
            else
                break;

        }

        


        ++cap;
    }
    else if (X == 0){

        if (cap == 0){
            printf("0\n");
        }
        else {
        
            printf("%d\n", Heap[0]);

            --cap;
            Heap[0] = Heap[cap];      
            Heap[cap] = 0; 

            int index = 0;
            int left = 1;
            int right = 2;

            //flag를 0으로 뒀는데 맥스힙의 경우 큰 문제가 없지만 민힙의 경우 비교할 때 이미 빈 배열인데도 그걸 0값으로 인식할 수 있음 그걸 걸러주는 장치가 필요함
            // 음... flag를 0으로 준 것 자체가 잘못된 것 같음ㅅㅂ 코드가 너무 더러워짐
            while ( (abs(Heap[index]) >= abs(Heap[left]) && Heap[left] != 0) || (abs(Heap[index]) >= abs(Heap[right]) && Heap[right] != 0)){

                int smallest;
                int smallest_idx;

                if (Heap[right] == 0){

                    smallest = Heap[left];
                    smallest_idx = left;
                }
                else {

                    if (abs(Heap[right]) < abs(Heap[left])){

                        smallest = Heap[right];
                        smallest_idx = right;    

                    }
                    else if (abs(Heap[right]) > abs(Heap[left])){
                        
                        smallest = Heap[left];
                        smallest_idx = left;

                    }
                    else{

                        if (Heap[right] <= Heap[left]){
                        
                            smallest = Heap[right];
                            smallest_idx = right;  

                        }
                        else{

                            smallest = Heap[left];
                            smallest_idx = left;

                        }
                    }
                }


                int temp;
                temp = Heap[index];
                Heap[index] =  Heap[smallest_idx];
                Heap[smallest_idx] = temp;

                index = smallest_idx;

                left = index*2 + 1;
                right = index*2 + 2;
                
            
            }
        }

    }


    --N;

    }


    free(Heap);
    return 0;

} 

