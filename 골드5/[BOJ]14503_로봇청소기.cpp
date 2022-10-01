#include <iostream>
#include <cstring>
#include <stdlib.h>
#define MAXN (50)
int N, M;
int rr, rc, rd;
int map[MAXN + 10][MAXN + 10];
int visited[MAXN + 10][MAXN + 10];

int dr[] = {-1, 0, 1, 0}; //북 동 남 서 //위 오 아 왼 (시계)
int dc[] = {0, 1, 0, -1};
int sol;
int flag;

void FloodFill(int r, int c, int d) {
	
	if (flag == 1) return;
	if (map[r][c] == 1) return;
	if ((map[r][c] == 0)&& (visited[r][c] != 2)) { //1번 위치가 청소 안 한 칸일 경우
		visited[r][c] = 2;
		sol++;
	}

	//왼쪽 이동 : nd = (d + 3) % 4
	// if (map[nr][nc] != 0) continue; //왼쪽 한 번 더 이동 
	//연속 네번 후진 : nr = r + dr[(d + 2) % 4]

	int cnt = 0;
	for(int i = 1; i <= 4; i++) {
		int nd = (d + 3 * i) % 4; //반시계 방향 회전
		int nr = r + dr[nd];
		int nc = c + dc[nd];

		if ((map[nr][nc] == 1) || (visited[nr][nc] == 2)) { //이동 안 하고 회전
			cnt++;
			continue;
		}
		FloodFill(nr, nc, nd);
		visited[nr][nc] = 2;
		sol++;
	}

	if (cnt == 4) {
			int nnd = (d + 2) % 4;
			int nnr = r + dr[nnd];
			int nnc = c + dc[nnd];

		if (map[nnr][nnc] == 1) {
			printf("%d", sol);
			exit(0);
		}
		else FloodFill(nnr, nnc, d); 
	}
}

int Solve(void) {
	sol = 0;
	flag = 0;
	FloodFill(rr, rc, rd);
	return sol;
}

void InputData(void) {
	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &rr, &rc, &rd);
	
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			scanf("%d", &map[r][c]);
		}
	}
}

int main(void){
	InputData();
	int ans = Solve();
	//printf("%d", ans);
	
	return 0;
}