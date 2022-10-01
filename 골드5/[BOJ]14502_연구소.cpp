#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN (8)

int map[MAXN + 2][MAXN + 2];
int visited[MAXN + 2][MAXN + 2];
int N, M;
int sol = 0;
int virus = 3;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

//벽 세우기 : 조합 DFS
//안전영역 FloodFill 최대값

void FloodFill(int r, int c) { //바이러스 확산

	if ((r < 1) || (r > N) || (c < 1) || (c > M)) return;
	if ((visited[r][c] == 1) || (visited[r][c] == virus)) return; //새 벽 or 이번에 확산
	if (map[r][c] == 1) return; //원래 벽

	visited[r][c] = virus;

	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		FloodFill(nr, nc);
	}
}

int CalSafe(void) { //FloddFill //visited 1 새 벽 3개 //map 1 원래 벽 

	//visited 초기화 어떻게?? => virus 값을 유니크 값으로 
	//바이러스 확산
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] == 2) FloodFill(i, j);
		}
	}

	//안전영역 계산
	int SafeCnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if ((map[i][j] == 0) && (visited[i][j] != virus) && (visited[i][j] != 1)) SafeCnt++;
		}
	}
	return SafeCnt;
}

void DFS(int cnt) {  //벽 3개 조합

	if (cnt == 3) {
		//벽 3개 - FloodFill 안전영역크기
		int ret = CalSafe();
		if (sol < ret) sol = ret;

		virus++; //유니크값 변경
		return;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {

			if (visited[i][j] == 1) continue;
			if (map[i][j] != 0) continue; //원래 벽, 바이러스

			visited[i][j] = 1;
			DFS(cnt + 1);
			visited[i][j] = 0;
		}
	}
}

int Solve(void) {

	DFS(0);

	return sol;
}

void InputData(void) {
	scanf("%d %d", &N, &M);

	memset(map, 0, sizeof(map));
	memset(visited, 0, sizeof(visited));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) visited[i][j] = 1;
			if (map[i][j] == 2) visited[i][j] = 2;
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);

}