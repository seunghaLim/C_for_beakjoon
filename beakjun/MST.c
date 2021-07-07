#include <stdio.h>
#include <malloc.h>

#define MAX 10000

int matrix[MAX][MAX] = {0, };
int flag[MAX] = {0, };

typedef struct _NODE{
    int weight;
    int next;
}Node;

typedef struct _MINHEAP{

    Node *heap;
    int cap;
    int num;

}MinHeap;


int print_MST_weight(int v, int e, int start, MinHeap* minheap);
void push(Node node, MinHeap* minheap);
Node pop(MinHeap* minheap);


int main(){

    int v, e, sum;

    scanf("%d %d", &v, &e);

    for (int i = 0; i < e; i++){

        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        matrix[a][b] = c;
        matrix[b][a] = c;
    } 

    MinHeap *minheap = malloc(sizeof(minheap));
    minheap->cap = 1;
    minheap->num = 0;
    minheap->heap = (Node*)malloc(minheap->cap*sizeof(Node));

    sum = print_MST_weight(v, e, 1, minheap);
    printf("%d\n", sum);

}


int print_MST_weight(int v, int e, int start, MinHeap* minheap){
   
    static int weight = 0; 
    static int count = 0;
    
    flag[start] = 1;

    if (count == v-1){         // 저장한 가중치가 v-1개가 되면 멈춤
        
        return weight;                 // 리턴
    }  

    for (int c = 1; c <= v; c++){
    
        if (matrix[start][c] != 0 && flag[c] == 0){

            if (minheap->num == minheap->cap){

                ++minheap->cap;
                minheap->heap = (Node *)realloc( minheap->heap, minheap->cap*sizeof(Node));

            }

            minheap->heap[minheap->num].next = c;
            minheap->heap[minheap->num].weight = matrix[start][c];

            push(minheap->heap[minheap->num], minheap); // minheap에 넣음
    
        }
    }

    Node ret = pop(minheap);    // minheap에서 하나 빼고, 가중치 값 저장
    weight += ret.weight; 
    count++;
    

    print_MST_weight(v, e, ret.next, minheap); // minheap에서 뺀 걸로 다시 반복

    // for문으로 free해줌
}
       
    

 
void push(Node node, MinHeap* minheap){
            
    int index = minheap->num;
    
    // 자녀 < 부모일 때까지 반복
    while(minheap->heap[index].weight < minheap->heap[(index-1) / 2].weight){
            
        Node node;
        node = minheap->heap[index];
        minheap->heap[index] =  minheap->heap[(index-1) / 2];
        minheap->heap[(index-1) / 2] = node;

        index = (index-1) / 2;

    }

    ++minheap->num;

}

Node pop(MinHeap* minheap){

    Node ret; 
            
        ret = minheap->heap[0];
        --minheap->num;
        minheap->heap[0] = minheap->heap[minheap->num];      
        minheap->heap[minheap->num].weight = 0; 
        // next는 초기화 안해주나?

        int index = 0;
        int left = 1;
        int right = 2;

        //flag를 0으로 뒀는데 맥스힙의 경우 큰 문제가 없지만 민힙의 경우 비교할 때 이미 빈 배열인데도 그걸 0값으로 인식할 수 있음 그걸 걸러주는 장치가 필요함
        while ( (minheap->heap[index].weight > minheap->heap[left].weight && minheap->heap[left].weight != 0) || 
                (minheap->heap[index].weight > minheap->heap[right].weight && minheap->heap[right].weight != 0)){
                
            Node smallest;
            int smallest_idx;

            if (minheap->heap[right].weight == 0){

                smallest = minheap->heap[left];
                smallest_idx = left;
            }
            else {

                if (minheap->heap[left].weight < minheap->heap[right].weight){

                    smallest = minheap->heap[left];
                    smallest_idx = left;    

                }
                else if (minheap->heap[left].weight >= minheap->heap[right].weight){
                            
                    smallest = minheap->heap[right];
                    smallest_idx = right;

                }

            }

            Node temp;
            temp = minheap->heap[index];
            minheap->heap[index] =  minheap->heap[smallest_idx];
            minheap->heap[smallest_idx] = temp;

            index = smallest_idx;

            left = index*2 + 1;
            right = index*2 + 2;
                
        }
    

    return ret;

} 


