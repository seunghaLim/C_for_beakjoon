#include <stdio.h>
#include <string.h>

#define MAX 1001
int matrix[MAX][MAX];
int flag[MAX][MAX] = { 0, };
int break_the_wall(int r, int c, int N, int M, int paths[]);
int find_shortest(int n, int path[]);


int main(){

    int N, M;
    int count;
    int paths[MAX];
    int smallest_path;
  
    scanf("%d %d", &N, &M);
    //rewind(stdin);                              // scanf 개행문자.... 정말 알다가도 모르겠는 친구네요ㅎ

    for (int i = 0; i < N; i++){

        for (int j = 0; j < M; j++){
           
            scanf("%1d", &matrix[i][j]);
        }
        //rewind(stdin);
    }
  
    count = break_the_wall(0, 0, N, M, paths);

    if (count == 0){
        printf("-1\n");
    }
    else {
        smallest_path = find_shortest(count, paths);
        printf("\n%d\n", smallest_path);
    }
    

}

int break_the_wall(int r, int c, int N, int M, int paths[]){

    static int path = 0;
    static int check = 0;
    static int count = 0;
    
    int y1 = r; int x1 = c-1; 
    int y2 = r; int x2 = c+1; 
    int y3 = r-1; int x3 = c; 
    int y4 = r+1; int x4 = c; 

    ++path;
    flag[r][c] = 1;

    if (r == N-1 && c == M-1 ){     // 종료조건

        paths[count] = path;
        ++count;
        
        return count;
    }

    // 왼쪽으로 가는 경우
    if (y1 >= 0 && y1 <= 5 && x1 >= 0 && x1 <= 3 && flag[y1][x1] == 0){

        if ( matrix[y1][x1] == 0){

            break_the_wall(y1, x1, N, M, paths);
            --path;
            flag[y1][x1] = 0;

        }
        else if (matrix[y1][x1] == 1 && check == 0){

            check = 1;
            break_the_wall(y1, x1, N, M, paths);
            --path;
            check = 0;
            flag[y1][x1] = 0;
        }
    }

    // 오른쪽
    if (y2 >= 0 && y2 <= 5 && x2 >= 0 && x2 <= 3 && flag[y2][x2] == 0){

        if ( matrix[y2][x2] == 0){

            break_the_wall(y2, x2, N, M, paths);
            --path;
            flag[y2][x2] = 0;

        }
        else if (matrix[y2][x2] == 1 && check == 0){

            check = 1;
            break_the_wall(y2, x2, N, M, paths);
            --path;
            check = 0;
            flag[y2][x2] = 0;
        }
    }

    // 위쪽
    if (y3 >= 0 && y3 <= 5 && x3 >= 0 && x3 <= 3 && flag[y3][x3] == 0){

        if ( matrix[y3][x3] == 0){

            break_the_wall(y3, x3, N, M, paths);
            --path;
            flag[y3][x3] = 0;

        }
        else if (matrix[y3][x3] == 1 && check == 0){

            check = 1;
            break_the_wall(y3, x3, N, M, paths);
            --path;
            check = 0;
            flag[y3][x3] = 0;
        }
    }
        
    // 아래쪽

    if (y4 >= 0 && y4 <= 5 && x4 >= 0 && x4 <= 3 && flag[y4][x4] == 0){

        if ( matrix[y4][x4] == 0){

            break_the_wall(y4, x4, N, M, paths);
            --path;
            flag[y4][x4] = 0;

        }
        else if (matrix[y4][x4] == 1 && check == 0){

            check = 1;
            break_the_wall(y4, x4, N, M, paths);
            --path;
            check = 0;
            flag[y4][x4] = 0;
        }
    }

    //if ( matrix[y1][x1] != 0 && matrix[y2][x2] != 0 && matrix[y3][x3] != 0 && matrix[y4][x4] == 0 && check != 0)    //데드 엔드인 경우를 이렇게 설정해줬는데 걍 count=0인 게 데드엔드같음
        //return -1;
    

    return count;

}

int find_shortest(int c, int path[]){

    int smallest = 0;
    for (int i = 1; i < c; i++){
        
        if (path[i] < path[smallest]){
            smallest = i;
        } 
    }
    
    return path[smallest];

}