#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXVERTICES 1001                    // define 뒤에 세미콜론 안붙이나봐;;;;; 당황
int graph[MAXVERTICES][MAXVERTICES] = { 0, };
int vertices_flag[MAXVERTICES] = { 0, };    // 모든 flag를 0으로 초기화
int cap = 0;

void BFS(int N, int V);
void push (int x, int minHeap[], int cap);
int pop (int minHeap[], int cap); 

int main(){

    int N, M, V;

    scanf("%d %d %d", &N, &M, &V);

    for (int i = 1; i <= M; i++){

        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][y] = 1;
        graph[y][x] = 1;

    }
    
    BFS(N, V); // BFS 함수 구현


}

void BFS(int N, int V){

    int queue[100000];     // 큐 만듦 (minheap)  QUEUE *queue = CreateQueue(N); 
    int queue_cap, front, rear;
    queue_cap = 0;
    front = 0;
    rear = 0;               

    for (int x = V; x <= N; x++){              //모든 그래프 정점 순환
        
        if (vertices_flag[V] == 0){             // 그래프 flag가 0이라면
            
            queue[rear] = V;  ++rear;  ++queue_cap;                    // 큐에다가 넣고 flag 1로 바꿈     
            vertices_flag[V] = 1;

            while(queue_cap != 0) {                         // queue가 0이 아닐 때까지 순환

                int temp = queue[front];  front++;              //  q에서 하나 빼옴
                --queue_cap;
                printf("%d ", temp);                              // 프린트하고 처리함
                vertices_flag[temp] = 2;
               
                for (int y = 1; y <= N; y++){                                // q에서 빼온 정점과 인접한 정점 모두 순환
                
                    if ( graph[temp][y] == 1 && vertices_flag[y] == 0 ){     //  인접한 정점의 flag가 0이라면
                        
                        queue[rear] = y;  ++rear;  ++queue_cap;                         // q에 넣음
                        vertices_flag[y] = 1;                               // flag를 1로 표시 야!!!!!!!!!!!! 미쳤냐??????? 야!!!!!!!!!!!! 미쳤냐??????? 야!!!!!!!!!!!! 미쳤냐??????? 야!!!!!!!!!!!! 미쳤냐??????? 
                    }
                }
            }
        }
    }

}