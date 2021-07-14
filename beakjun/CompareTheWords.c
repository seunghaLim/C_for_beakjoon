#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void QuickSort(int l, int r, char** arr);
int Quick(int l, int r, char** arr);
void swap (char* A, char* B);

//char* arr[20002];

int main(){

    int N;

    scanf("%d\n", &N);

    char** arr = malloc(sizeof(char*)*N);

    for (int i = 0; i < N; i++){

        arr[i] = malloc(sizeof(char)*50);       // char* 배열에 문자열 쓰는거 주의 -> char* 선언하고 메모리 할당해야지 쓸 수 있음
        scanf("%s", arr[i]);
    }

    QuickSort(0, N-1, arr);

    printf("\n");

    for (int i = 0; i < N-1; i++){
        
        if ( strcmp(arr[i], arr[i+1]) != 0 ){
            printf("%s\n", arr[i]);
        }
    }
    printf("%s\n", arr[N-1]);
    

    for (int i = 0; i < N; i++){

        free(arr[i]);
    }

    free(arr);

    return 0;

}

void QuickSort(int l, int r, char** arr){

    if (l < r){
        
        int s = Quick(l, r, arr);
        QuickSort(l, s-1, arr);
        QuickSort(s+1, r, arr);
    }
}

int Quick(int l, int r, char** arr){

    int i = l+1;
    int j = r;
    int p = l;

    do{

        while( strlen(arr[i]) <= strlen(arr[p]) && i != r){

            if( strlen(arr[i]) == strlen(arr[p]) && strcmp(arr[i], arr[p]) > 0 ){     //strcpy는 비교 함수.............
                break;
            }
            else {
                i++;
            }

        }

        while( strlen(arr[j]) >= strlen(arr[p]) && j != l ){        // j부분 조건문 주의
             
            if( strlen(arr[j]) == strlen(arr[p]) && strcmp(arr[j], arr[p]) < 0 ){
                break;
            }
            else {
                j--;
            }
        }

        swap(arr[i], arr[j]);

    }while( i < j);

    swap(arr[i], arr[j]);
    swap(arr[p], arr[j]);
    
    return j;
}

void swap (char* A, char* B){
    
    char* temp = malloc(sizeof(char)*50);

    strcpy(temp, A);        // 문자열 옮기는 건 =이 아니라 strcpy 함수로
    strcpy(A, B);
    strcpy(B, temp);

    //free(temp);
    

}