#include <stdlib.h> // atoi, rand, qsort, malloc
#include <stdio.h>
#include <assert.h> // assert
#include <time.h> //time
#include <math.h> // fabs 함수

#define RANGE 10000

typedef struct  // 점 구조체
{
	int x;
	int y;
} t_point;

typedef struct  // 선 구조체
{
	t_point from;
	t_point to;
} t_line;

t_line *upper_hull( t_point *points, int num_point, t_point p1, t_point pn, t_line *lines, int *num_line, int *capacity);
float distance( float a, float b, float c, t_point p);
void separate_points( t_point *points, int num_point, t_point from, t_point to, t_point *s1, t_point *s2, int *n1, int *n2);



////////////////////////////////////////////////////////////////////////////////
// function declaration
// 점들의 집합(points; 점의 수 num_point)에서 점 p1과 점 pn을 잇는 직선의 upper hull을 구하는 함수 (재귀호출)
// [output] lines: convex hull을 이루는 선들의 집합 - upper hall이 만들어지면 lines에 넣어줌
// [output] num_line: 선의 수 - 기존에 저장된 라인 수를 갱신  
// [output] capacity: lines에 할당된 메모리의 용량 (할당 가능한 선의 수) - t_line의 용량. 용량을 수정하고 메모리를 재할당하고 라인들을 추가해줌
// return value: 선들의 집합(lines)에 대한 포인터
//  p1과 pn을 연결해서 나오는 직선의 양 극단을 계속 lines에 추가
t_line *upper_hull( t_point *points, int num_point, t_point p1, t_point pn, t_line *lines, int *num_line, int *capacity)
{
	if (num_point == 0){
        int index = 0;
        *num_line++;
        index = *num_line - 1;

		if (num_line > capacity){
			*capacity += 10;
			lines = (t_line *) realloc(lines, sizeof(t_line) * 10);
		}
		// 인덱스 설정 어떻게 할지 고민해보셈
		lines[index].from.x = p1.x;
        lines[index].from.y = p1.y;
        lines[index].to.x = pn.x;
        lines[index].to.y = pn.y;
	
        return lines;
	}
	else{
		float a = pn.y - p1.y;
		float b = p1.x - pn.x;
		float c = p1.x * pn.y - p1.y * pn.x;
		int max_index = 0;
		float max_dist = distance(a, b, c, points[0]);
		
		for (int i = 1; i < num_point; i++){
			int dist = distance(a, b, c, points[i]);
			if (dist < max_dist){
				max_index = i;
				max_dist = dist;
				}
		}

	    t_point *s3 = (t_point *)malloc(sizeof(t_point) * num_point);
	    assert( s3 != NULL);

	    t_point *s4 = (t_point *)malloc(sizeof(t_point) * num_point);
	    assert( s4 != NULL);

        t_point *s5 = (t_point *)malloc(sizeof(t_point) * num_point);
	    assert( s5 != NULL);

	    t_point *s6 = (t_point *)malloc(sizeof(t_point) * num_point);
	    assert( s6 != NULL);

	    int n3, n4, n5, n6; 

        separate_points(points, num_point, p1, points[max_index], s3, s4, &n3, &n4);
        separate_points(points, num_point, points[max_index], pn, s5, s6, &n5, &n6);

        lines = upper_hull( s3, n3, p1, points[max_index], lines, num_line, capacity);
        lines = upper_hull( s5, n5, points[max_index], pn, lines, num_line, capacity);

        free(s3);
        free(s4);
        free(s5);
        free(s6);
	}

}


// base csae: if 위에 있는 점(s1, points)가 없으면, 즉 num point가 0이면 그 직선의 두 점이 convex hall임. line 구조체에 그 두 저을 넣어줌
// else 있으면 점들의 집합 s1 중 직선과 가장 멀리 떨어져 있는 점을 구함 - 직선과 모든 점 사이의 거리를 구할 때 distance 함수 호출 
// 그 점을 구한 뒤 다시 upper_hull 호출 


// 직선(ax+by-c=0)과 주어진 점 p(x1, y1) 간의 거리
// distance = |ax1+by1-c| / sqrt(a^2 + b^2)
// 실제로는 sqrt는 계산하지 않음
// return value: 직선과 점 사이의 거리 (분모 제외)
float distance( float a, float b, float c, t_point p){
    float dist = 0;
    dist = fabs(a * p.x + b * p.y - c);
    return dist;
}




// 두 점(from, to)을 연결하는 직선(ax + by - c = 0)으로 n개의 점들의 집합 s(점의 수 num_point)를 s1(점의 수 n1)과 s2(점의 수 n2)로 분리하는 함수
// [output] s1 : 직선의 upper(left)에 속한 점들의 집합 (ax+by-c < 0)
// [output] s2 : lower(right)에 속한 점들의 집합 (ax+by-c > 0)
// [output] n1 : s1 집합에 속한 점의 수
// [output] n2 : s2 집합에 속한 점의 수
// from과 to가 s1과 s2에 속하지 않도록 만들어 주어야 함 

void separate_points( t_point *points, int num_point, t_point from, t_point to, t_point *s1, t_point *s2, int *n1, int *n2){
    float a = to.y - from.y;
    float b = from.x - to.x;
    float c = from.x * to.y - from.y * to.x;

    for (int i = 1; i < num_point -1; i++){
        if (a * points[i].x + b * points[i].y - c < 0){
            s1[i - 1].x = points[i].x;
            s1[i - 1].y = points[i].y;
            *n1++;
        }
        else if (a * points[i].x + b * points[i].y - c > 0){
            s1[i - 1].x = points[i].x;
            s1[i - 1].y = points[i].y;
            *n2++;
        }
    }
}



 
////////////////////////////////////////////////////////////////////////////////
void print_header(char *filename)
{
	printf( "#! /usr/bin/env Rscript\n");
	printf( "png(\"%s\", width=700, height=700)\n", filename);
	
	printf( "plot(1:%d, 1:%d, type=\"n\")\n", RANGE, RANGE);
}

////////////////////////////////////////////////////////////////////////////////
void print_footer(void)
{
	printf( "dev.off()\n");
}

////////////////////////////////////////////////////////////////////////////////
// qsort를 위한 비교 함수 - 점 정렬을 위한 함수
int cmp_x( const void *p1, const void *p2)
{
	t_point *p = (t_point *)p1;
	t_point *q = (t_point *)p2;
	
	float diff = p->x - q->x;
	
    return ((diff >= 0.0) ? ((diff > 0.0) ? +1 : 0) : -1);
}

////////////////////////////////////////////////////////////////////////////////
void print_points( t_point *points, int num_point)
{
	int i;
	printf( "\n#points\n");
	
	for (i = 0; i < num_point; i++)
		printf( "points(%d,%d)\n", points[i].x, points[i].y);
}

////////////////////////////////////////////////////////////////////////////////
void print_line_segments( t_line *lines, int num_line)
{
	int i;

	printf( "\n#line segments\n");
	
	for (i = 0; i < num_line; i++)
		printf( "segments(%d,%d,%d,%d)\n", lines[i].from.x, lines[i].from.y, lines[i].to.x, lines[i].to.y);
}

////////////////////////////////////////////////////////////////////////////////
// [input] points : set of points
// [input] num_point : number of points
// [output] num_line : number of lines
// return value : pointer of set of line segments that forms the convex hull
t_line *convex_hull( t_point *points, int num_point, int *num_line)
{
	int capacity = 10;  // 일단 line을 10개만 저장할 수 있음

	t_line *lines = (t_line *) malloc( capacity * sizeof(t_line));
	*num_line = 0;

	// s1: set of points
	t_point *s1 = (t_point *)malloc(sizeof(t_point) * num_point);
	assert( s1 != NULL);

	// s2: set of points
	t_point *s2 = (t_point *)malloc(sizeof(t_point) * num_point);
	assert( s2 != NULL);

	int n1, n2; // number of points in s1, s2, respectively

	// x 좌표에 따라 정렬된 점들의 집합이 입력된 경우
	// points[0] : leftmost point (p1)
	// points[num_point-1] : rightmost point (pn)
	
	// 점들을 s1, s2으로 분리
	separate_points( points, num_point, points[0], points[num_point-1], s1, s2, &n1, &n2);

	// upper hull을 구한다.
	//  points[0], points[num_point-1]를 연결해서 나오는 직선의 양 극단을 계속 lines에 추가
	lines = upper_hull( s1, n1, points[0], points[num_point-1], lines, num_line, &capacity);
	lines = upper_hull( s2, n2, points[num_point-1], points[0], lines, num_line, &capacity);
	
	free( s1);
	free( s2);

	return lines;
}

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	float x, y;
	int num_point; // number of points
	
	if (argc != 2)
	{
		printf( "%s number_of_points\n", argv[0]);
		return 0;
	}

	num_point = atoi( argv[1]);
	if (num_point <= 0)
	{
		printf( "The number of points should be a positive integer!\n");
		return 0;
	}

	t_point *points;
	points = (t_point *)malloc( sizeof(t_point) * num_point);
	assert( points != NULL);
	
	// making points
	srand( time(NULL));
	for (int i = 0; i < num_point; i++)
	{
		x = rand() % RANGE + 1; // 1 ~ RANGE random number
		y = rand() % RANGE + 1;
	
		points[i].x = x;
		points[i].y = y;
 	}

	fprintf( stderr, "%d points created!\n", num_point);
	
	// sort the points by their x coordinate
	qsort( points, num_point, sizeof(t_point), cmp_x);

	print_header( "convex.png");
	
	print_points( points, num_point);
	
	// convex hull algorithm
	int num_line;
	t_line *lines = convex_hull( points, num_point, &num_line);
	
	fprintf( stderr, "%d lines created!\n", num_line);

	print_line_segments( lines, num_line);
	
	print_footer();
	
	free( points);
	free( lines);
	
	return 0;
}
