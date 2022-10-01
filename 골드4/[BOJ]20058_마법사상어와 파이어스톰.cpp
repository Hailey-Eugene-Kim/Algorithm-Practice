#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAXN 64

int N, Q;
int n, l;
int level;
int map[MAXN + 10][MAXN + 10];
int rt[MAXN + 10][MAXN + 10];
int visited[MAXN + 10][MAXN + 10];
deque <int> L;
struct DIR {
	int r, c;
};
deque <DIR> Minus;
int Sum, ice, MaxIce;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void FloodFill(int r, int c) { 

	if ((r < 1) || (r > n) || (c < 1) || (c > n)) return;

	visited[r][c] = 1;
	ice++;

	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if ((nr < 1) || (nr > n) || (nc < 1) || (nc > n)) continue; //범위 조건
		if (map[nr][nc] < 1) continue; //얼음 아니면 가지치기
		if (visited[nr][nc] == 1) continue; //이미 확산했으면 가지치기 //조건 빼먹어서 스택오버플로우

		FloodFill(r + dr[i], c + dc[i]);
	}
}

void CalIce(void) {
	memset(visited, 0, sizeof(visited));
	MaxIce = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			Sum += map[i][j]; //얼음 합

			if (visited[i][j] == 1) continue; //이미 확산했으면 가지치기
			if (map[i][j] < 1) continue; //얼음 아니면 가지치기
			ice = 0;
			FloodFill(i, j);
			if (MaxIce < ice) MaxIce = ice;
		}
	}
}

void IceMinus(void) {

	Minus = {};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nr = i + dr[k];
				int nc = j + dc[k];

				if ((nr < 1)||(nr > n)||(nc < 1)||(nc > n)) continue;
				if (map[nr][nc] >= 1) cnt++; //인접 얼음 + 1
			}
			if ((cnt < 3) && (map[i][j] >= 1)) Minus.push_back({i, j}); //인접칸 얼음 3 미만이면 해당칸 얼음 -1
		}
	}

	int J = Minus.size();
	for (int j = 0; j < J; j++) {
		map[Minus[j].r][Minus[j].c]--;
	}
}

void Rotate(int r, int c, int size) {
	for (int i = r; i < r + size; i++) {
		for (int j = c; j < c + size; j++) {
			rt[r + (j - c)][(c + size - 1) - (i - r)] = map[i][j]; //rt에 90도 복사
		}
	}
}

void Solve(void) {
	memset(rt, 0, sizeof(rt));
	while (!L.empty()) { //파이어스톰 Q회 시전
		
		int cur = L.front(); L.pop_front(); //pop_back() 실수
		int I = n / cur;
		for (int i = 0; i < I; i++) { //모든 격자 90도 회전
			for (int j = 0; j < I; j++) {
				Rotate(1 + i * cur, 1 + j * cur, cur); 
			}
		}
		memcpy(map, rt, sizeof(rt)); //전체 회전 map에 반영

		IceMinus();
	}

	CalIce();
}

int CalNum(int x) { //2의 x승 계산
	int num = 1;
	for (int i = 1; i <= x; i++) {
		num *= 2;
	}
	return num;
}

void InputData(void) {
	scanf("%d %d", &N, &Q);
	
	n = CalNum(N); //2의 x승 계산
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	for (int k = 1; k <= Q; k++) {
		scanf("%d", &level); //입력에서 막힘
		l = CalNum(level); //2의 x승 계산해서 단계 큐에 입력
		L.push_back(l);
	}
}

void OutputData(void) {
	printf("%d\n", Sum);
	printf("%d", MaxIce);
}

int main(void) {
	InputData();
	Solve();
	OutputData();
	return 0;
}