#include <stdio.h>
#include <malloc.h>


int Combination(int M, int n, int r, int c, int *arr, int *Copy, int *sum);
int compute_Comb(int count, int *Copy);
int findBlackJack(int M, int count, int *sum, int *sub);


int main(){

    int N; // 카드 개수
    int M;
    scanf("%d %d", &N, &M); 

    int *cards = malloc(sizeof(int) * N);       // 카드 저장

    int sum[1000];         // 카드들의 조합 합 저장 
    int Copy[3];        // 조합 계산할 때 필요한 임시 배열
    int sub[1000];         // M - 카드 조합 계산할 때 필요한 배열
    int Blackjack;      // 최종 결과
    int count; 

    for (int i = 0; i < N; i++)
        scanf("%d", &cards[i]);

    count = Combination(M, N, 3, 3, cards, Copy, sum); 
    Blackjack = findBlackJack(M, count, sum, sub);  // 인수에 카드의 개수 N이 아니라 카드 조합 경우의 수를 넣어주어야 함

    printf("%d\n", Blackjack);

    free(cards);


}


int compute_Comb(int c, int *Copy){ 
    
    int sum = 0;

    for(int i = 0; i < c; i++){ 

        sum += Copy[i];          // 더하고 배열에 값 저장 
                                
    }  
    
    return sum;
} 

int Combination(int M, int n, int r, int c, int *arr, int *Copy, int *sum){ //재귀함수     
    
    static int count = 0;

    if (r==0){ 

        int ret = compute_Comb(c, Copy); //  배열 안에 있는 거 더하는 함수 호출
        
        if  (ret <= M ){
            
            sum[count] = ret;
            count++;
            return count;   // count 조심
        }
        else
            return count; 
 
    }

    if (n<r){ 

        return count; 
    } 
    else { 
        Copy[r-1] = arr[n-1]; 
        Combination(M, n-1,r-1,c, arr, Copy, sum); 
        Combination(M, n-1,r,c, arr, Copy, sum); 
    } 

    return count;
} 

int findBlackJack(int M, int count, int *sum, int *sub){

    for (int i = 0; i < count; i++){

        sub[i] = M - sum[i];

    }

    int blackjack = 0;

    for (int i = 0; i < count-1; i++){

        if ( sub[i+1] < sub[blackjack]){           // michinnoma 정신차려

            blackjack = i+1;

        }

    }

    return sum[blackjack];

}

