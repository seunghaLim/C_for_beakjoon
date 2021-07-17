#include <stdio.h>

int m[14][14] = {0, };

int move_queen(int n, int r, int c, int *queen);

int main(){

    int n;

    scanf("%d", &n);

    int queen = 0;
    int count = 0;
    //m[0][0] = 1;

    for (int i = 0; i < n; i++){
       count += move_queen(n, 0, i, &queen);
    }

    printf("%d\n %d\n", queen, count);

}

int move_queen(int n, int r, int c, int *queen){

    // 종료조건
    static int count = 0;

   // if (r < n && c < n){ 

        // 같은 열 방향 확인
        int check1 = 0;
        for (int i = 0; i < r; i++){
            
            if (m[i][c] == 1){
                check1 += 1;
            }
                
        }

        // 대각선 방향 확인
        int check2 = 0; int temp_r = r; int temp_c = c;
        /*
        if (r-1 > 0 && r-1 < n && c-1 > 0 && c-1 < n && m[r-1][c-1] == 1){
            check2 += 1;

        }
        if(r-1 > 0 && r-1 < n && c-1 > 0 && c+1 < n && m[r-1][c+1] == 1){
            check2 += 1;
        }
        */

        
        while (temp_r != 0 && temp_c != 0){     // || 아님 &&`임

            if (m[temp_r-1][temp_c-1] == 1){
                check2 += 1;
            }
            temp_r -= 1; 
            temp_c -= 1;
        }
        

        if (check1 == 0 && check2 == 0){

            m[r][c] = 1; ++count;

            if (count == n){
                *queen = *queen + 1; 
                --count;
                return count;
            }

            for (int i = 0; i < n; i++){
                move_queen(n, r+1, i, queen);
            }

            m[r][c] = 0; --count;
        }
        else
            return count;
   // }
    

}