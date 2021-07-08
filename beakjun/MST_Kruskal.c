#include <stdio.h>

#define MAX_V 10001
#define MAX_E 100001

typedef struct _EDGE{
    
    int from, to;
    int weight;

} EDGE;


struct _VERTIX{     // 여기에 typedef 붙이면 안됨 왜....?
    
    int parent;
    int level;

} v[MAX_V];

EDGE e[MAX_E];


void make_set (int a);
int find_set(int a);
void unite (int a, int b );
int MST_kruskal(int v, int e );
void sort_edges( int e);
void max_heapify( int index, int size);
void build_max_heap( int e);


int main(){

    int V, E;

    scanf("%d %d", &V, &E);

    for (int i = 0; i < E; i++){

        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        e[i].from = a;
        e[i].to = b;
        e[i].weight = c;
    }


    printf("%d\n", MST_kruskal(V, E));


}


// vertices 제작. 부모 구조체를 자기 자신으로 초기화
void make_set (int a){

    v[a].parent = a;            
    v[a].level = 0;
    
}

// set에서 자기 자신의 부모가 누구인지 검사하는 함수
int find_set(int a){

    if (v[a].parent != a){          // 자신과 자기 자신의 부모가 다르다면 재귀호출을 통해 다시 자신의 부모를 찾음

        v[a].parent = find_set(v[a].parent);    // ???
    }      
         
    return  v[a].parent;      // 자신과 자신의 부모의 값이 같다면 부모가 없는거임

}

// ??????
void unite (int a, int b ){

    a = find_set(a);
    b = find_set(b);

    if ( v[a].level > v[b].level ){

        v[b].parent = a;
    }
    else{

        v[a].parent = b;

        if ( v[a].level == v[b].level ){

            v[b].level += 1; 
        }
    }
}

int MST_kruskal(int v, int e ){

    int total = 0;
    int i;

    for (i = 1; i <= v; i++){

        make_set(i);
    }

    sort_edges(e);

    for (i = 0 ; i < e; i++){

        if ( find_set ( e[i].from ) != find_set( e[i].to ) ){

            unite( e[i].from, e[i].to );
        
            total += e[i].weight; 
        
        }
    }

    return total;

}


void sort_edge( int e)
{
    EDGE temp;
    int i;

    // 아규먼트가 인덱스로 쓰이기 때문에 -1해줌 -> e배열이 큰 순서대로 나열됨
    build_max_heap( --e);

    for( i = e ; i > 0 ; i --)
    {
        // 배열 e가 작은 순으로 나열되도록 swap
        temp    = e[i];
        e[i]    = e[0];
        e[0]    = temp;

        // 힙 속성 유지시킴 
        max_heapify( 0, i);
    }
}

// 힙 특성(부모지배속성) 유지시키는 함수
void max_heapify( int index, int size)
{
    EDGE temp;
    int left    = index * 2 + 1;
    int right   = index * 2 + 2;
    int largest = index;    // 일단 largest에 부모 인덱스 넣음


    // 왼쪽 노드가 heap 범위 안에 있고 && 왼쪽 노드의 weight이 부모 인덱스보다 더 크다면
    if( left < size && e[left].weight > e[largest].weight )
    {
        largest = left;
    }

    // 오른쪽 노드가 heap 범위 안에 있고 && 오른쪽 노드의 weight이 부모 인덱스보다 더 크다면
    if( right < size && e[right].weight > e[largest].weight )
    {
        largest = right;
    }

    // largest 변수에 부모 인덱스 말고 다른 값이 들어간 상태 = 자식 둘 중에 하나가 부모보다 큰 상태
    if( largest != index)
    {// 둘이 교환
        temp        = e[largest];
        e[largest]  = e[index];
        e[index]    = temp;


        //재귀를 통해 부모지배속성을 만족할 때까지 반복
        max_heapify( largest, size);
    }
}

// 최대힙 만드는 함수 - bottom up 방식으로 제작
void build_max_heap( int e)
{
    // 간선 개수를 /2하는 이유 - 부모 노드만 골라서 힙 속성을 유지시켜 주기 위해
    // 부모 노드 중 가장 밑에 있는 부모 노드에서부터 bottom-up하는 방식
    for (int i = e/2 ; i >= 0 ; i--)
    {
        max_heapify( i, e);
    }
}






