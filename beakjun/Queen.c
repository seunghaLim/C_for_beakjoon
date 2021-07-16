#include <stdio.h>

int m[14][14];

int main(){

    int n;

    scanf("%d", &n);

    m[0][0] = 1;

    move_queen(n, 0, 0);


}

int move_queen(int n, int r, int l){

    m[r][l] = 1;

    if (m[r+1][l-1] == 0 && r+1 < n && r+1 > 0 && l-1 < n && l-1 > 0){

        move_queen(n, r, l);
        m[r+1][l-1] = 0;

    }


}