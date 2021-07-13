#include <stdio.h>
#include <string.h>

char* arr[20002];

int main(){

    int N;

    scanf("%d\n", &N);

    for (int i = 0; i < N; i++){

        scanf("%s", &arr[i]);
    }

    QuickSort(0, N-1);

    for (int i = 0; i < N-1; i++){

        if(arr[i] != arr[i+1]){
            printf("%s\n", &arr[i]);
        }
    }
    printf("%s\n", &arr[N-1]);

    return 0;

}

void QuickSort(int l, int r){

    if (l < r){
        
        int s = Quick(l, r);
        QuickSort(l, s-1);
        QuickSort(s+1, r);
    }
}

int Quick(int l, int r){

    int i = l+1;
    int j = r;
    int p = l;

    do{

        while( strlen(arr[i]) <= strlen(arr[p]) && i != r){

            if( strlen(arr[i]) == strlen(arr[p]) && strcpy(arr[i], arr[p]) > 0 ){
                break;
            }
            else {
                i++;
            }

        }

        while( strlen(arr[j]) >= strlen(arr[p]) ){
            
            if( strlen(arr[j]) == strlen(arr[p]) && strcpy(arr[j], arr[p]) < 0 ){
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
    
    char* temp;
    temp = *A;
    *A = *B;
    *B = temp;

}