#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _MEMBER{

    int age;
    char name[102];

} MEMBER;


void MergeSort(MEMBER m[], int l, int r);
void Merge(MEMBER m[], int L, int l, int R, int r);


int main(){

    int N;
    scanf("%d", &N);

    MEMBER* m = malloc(sizeof(MEMBER)*N);

    for (int i = 0; i < N; i++){

        scanf("%d %s", &m[i].age, m[i].name);
    }

    MergeSort(m, 0, N-1);
   
    for (int i = 0; i < N; i++){
        
        printf("%d %s\n", m[i].age, m[i].name);
    }

    free(m);

}


void MergeSort(MEMBER m[], int l, int r){
 
    if( l < r ){      // 무한루프 제한 기준

        MergeSort(m, l, (l+r)/2);       // n값 잘못 설정해줘서 무한루프
        MergeSort(m, (l+r)/2+1, r);
        Merge(m, l, (l+r)/2+1, (l+r)/2, r);
        
    }

    
}

void Merge(MEMBER m[], int L, int l, int R, int r){

    int i, j, k;
    i = L;
    j = l;
    k = L;
    MEMBER* B = (MEMBER*)malloc(sizeof(MEMBER) * (r+1));     // 임시 배열 사용


    while( i < (R+1) && j < (r+1) ){

        if (m[i].age <= m[j].age){

            B[k].age = m[i].age;
            strcpy(B[k].name, m[i].name);
            i = i+1;
        }
        else{

            B[k].age = m[j].age;
            strcpy(B[k].name, m[j].name);
            j = j+1;
        }
        
        k++;

    }

    if (j == r+1){
        
        for (int I = i; I <= R; I++){
            
            B[k].age = m[I].age;
            strcpy(B[k].name, m[I].name);
            k++;
        } 
    }
    else if (i == R+1){
        
        for (int I = j; I <= r; I++){

            B[k].age = m[I].age;
            strcpy(B[k].name, m[I].name);
            k++;
        } 
    }

    for (int I = L; I <= r; I++){

        m[I].age = B[I].age;
        strcpy(m[I].name, B[I].name);

    }


    free(B);
 

}
