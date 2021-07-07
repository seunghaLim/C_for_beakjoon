#include <stdio.h>
#define MAX 1000 

int matrix[MAX][MAX] = {0, };
int flag[MAX] = {0, };



void printSpanningTree(int n, int m);


int main(){

    int T, N, M, ret;

    scanf("%d", &T);

    for (int i = 0; i < T; i++){

        scanf("%d %d", &N, &M);

        for (int i = 0; i < M; i++){

            int a, b;
            scanf("%d %d", &a, &b);
            matrix[a][b] = 1;
            matrix[b][a] = 1;
        } 

        printSpanningTree(N, M);

    }


}


void printSpanningTree(int n, int m){

    int queue[MAX];
    int front, rear, cap;
    cap = 0;
    front = 0;
    rear = 0;

    static int check = 0;

    for (int r = 1; r <= n; r++ ){
        
        if (flag[r] == 0){
            queue[rear] = r;
            ++rear; ++cap;
            flag[r] = 1;
            
        }

        while(cap != 0){

            int temp = queue[front];
            ++front; --cap;
            flag[temp] = 2;
            ++check;


            for (int c = 1; c <= n; c++){
                
                if (matrix[temp][c] == 1 && flag[c] == 0){

                    queue[rear] = c;
                    ++rear; ++cap;
                    flag[c] = 1;

                }
            }
        }
    }


    printf("%d\n", check-1 );




}