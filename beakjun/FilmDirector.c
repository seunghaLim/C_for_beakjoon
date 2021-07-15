#include <stdio.h>
#include <math.h>

int arr[10000];

int main(){

    int n;
    scanf("%d", &n);    //n번째 영화의 이름 찾기

    int name = 666; 
    int count = 0;


    while(count < n){

        // 자릿수 구하기 
        int name_temp= name;
        int num = 0;
        while(name_temp != 0)
        {
            name_temp = name_temp/10;
            ++num;
        }

        // 각 자릿수 분리해서 배열에 넣음
        int temp = name;
        for(double i = num-1; i > 0; i--){

            double p = pow(10.0, i);        // pow함수는 리턴값도 아규먼트도 둘 다 double형
                
            if (i == 1){
                arr[(int)i+1] = temp / p;
                arr[1] = temp % (int)p;     // % 연산자는 나누는 수가 정수여야 되나봄
            }
            else {
                arr[(int)i+1] = temp / p;
                temp =  temp % (int)p;
            }
        }

        // 루프문 돌려서 연속으로 666 나오는지 확인
        int check = 0;
        int i = 1;
        while(check < num-2){

            if ( arr[i] == 6 && arr[i+1] == 6 && arr[i+2] == 6 && arr[i+3] != 6){           //&& arr[i+3] != 6 조건 필요한 이유
                count += 1;
            }
            
            if (count == n){
                printf("%d\n", name);
                return 0;
            }
            else {
                i = i+1;
                check++;
            }
        }

        name += 1;
        
    }
}

