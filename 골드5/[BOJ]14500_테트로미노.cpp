#include <iostream>
#include <cstring>

#define MAXN (500)

int N, M;
int map[MAXN + 10][MAXN + 10];
int visited[MAXN + 10][MAXN + 10];
int sol = 0;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void DFS(int r, int c, int cnt, int sum) {

	if (cnt == 4) {
		if (sol < sum) sol = sum;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if ((nr < 0) || (nr >= N) || (nc < 0) || (nc >= M)) continue;
		if (visited[nr][nc] == 1) continue;

		if (cnt == 2) { //2번째일 경우 현재 위치에서 탐색 한 번 더 => F shape
			visited[nr][nc] = 1;
			DFS(r, c, cnt + 1, sum + map[nr][nc]);
			visited[nr][nc] = 0;
		}

		visited[nr][nc] = 1;
		DFS(nr, nc, cnt + 1, sum + map[nr][nc]);
		visited[nr][nc] = 0;
	}
}

int Solve(void) {
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = 1;
			DFS(i, j, 1, map[i][j]);
			visited[i][j] = 0;
		}
	}
	return sol;
}

void InputData(void) {
	scanf("%d %d", &N, &M);

	memset(map, 0, sizeof(map));
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
}