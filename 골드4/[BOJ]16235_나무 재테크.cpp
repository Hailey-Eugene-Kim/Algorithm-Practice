#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAXN (10)
#define MAXK (1000)
int N, M, K; //땅크기, 나무 개수, 몇년후
int A[MAXN + 10][MAXN + 10]; // 추가되는 양분
int map[MAXN + 10][MAXN + 10]; // 현재 땅의 양분 

int dr[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 }; //8방향, 1 베이스
int dc[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

struct TREE {
	int r, c, n; //나무 행, 열, 나이
};

//배열 말고 deque로 동적
//살아있는 나무 / 죽은 나무 분리
//TREE T[MAXN * MAXN * MAXK + 10];
deque <int> T[MAXN + 10][MAXN + 10];
deque <TREE> dead;

void Seasons(void) {
	//봄
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int K = T[i][j].size();
			for (int k = 0; k < K; k++) {
				int cur = T[i][j].front(); T[i][j].pop_front();
				if (cur > map[i][j]) { //이번에 죽음
					dead.push_back({ i , j, cur });
				}
				else {
					map[i][j] -= cur;
					T[i][j].push_back(cur + 1);
				}
			}
		}
	}

	//여름
	while (!dead.empty()) {
		TREE temp = dead.front(); dead.pop_front();
		map[temp.r][temp.c] += temp.n / 2;
	}

	//가을
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {

			int K = T[i][j].size();
			for (int k = 0; k < K; k++) { //Q 배열처럼 활용 가능???

				int cur = T[i][j].front(); T[i][j].pop_front();
				if ((cur >= 5)&& (cur % 5 == 0)) { //재생산
					
					for (int l = 1; l <= 8; l++) {
						int nr = i + dr[l];
						int nc = j + dc[l];
						if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue;
						T[nr][nc].push_front(1);
					}
				}
				T[i][j].push_back(cur);
			}
		}
	}

	//겨울
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] += A[i][j];
		}
	}
}

int Solve(void) {
	int sol = 0;

	for (int k = 1; k <= K; k++) {
		Seasons(); //K년 반복
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sol += T[i][j].size();
		}
	}

	return sol;
}

void InputData(void) {
	memset(A, 0, sizeof(A));
	memset(map, 0, sizeof(map));

	scanf("%d %d %d", &N, &M, &K);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
		}
	}

	//나무
	int x, y, z;
	for (int m = 0; m < M; m++) { //sort 써야하므로 0 베이스
		scanf("%d %d %d", &x, &y, &z); //Q 여러개 받을 때 배열로 안 받아도 상관 X?
		T[x][y].push_back(z);
	}

	//map 초기화 5
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] = 5;
			sort(T[i][j].begin(), T[i][j].end()); //오름차순 정렬
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d\n", ans);

	return 0;
}