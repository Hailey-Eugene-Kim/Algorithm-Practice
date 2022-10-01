#include <iostream>
#include <cstring>
#include <queue>
#define MAXN 100
using namespace std;

int N, L, R;
int map[MAXN + 10][MAXN + 10];
int visited[MAXN + 10][MAXN + 10];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

struct QUE {
	int r, c;
};
queue <QUE> que;
queue <QUE> unite;
int flag;

//for루프 인구이동 탐색 //연합 BFS //visited배열로 이미 방문했으면 패스 
//전체 for루프 돌 때마다 +1일
//인구이동 없는 경우 이전 일수 리턴

void FloodFill (int r, int c) { //(r,c)의 연합 

	//초기값
	que = {};
	unite = {};

	que.push({ r, c });
	unite.push({ r, c });
	visited[r][c] = 1;
	int sum = map[r][c];

	//큐

	QUE cur = {};
	while (!que.empty()) { //연합 확산

		cur = que.front(); que.pop();

		for (int k = 0; k < 4; k++) {
			int nr = cur.r + dr[k];
			int nc = cur.c + dc[k];

			if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue; //범위 밖
			if (visited[nr][nc] == 1) continue; //이미 방문

			int tmp = abs(map[cur.r][cur.c] - map[nr][nc]);
			if ((L <= tmp) && (tmp <= R)) { //상하좌우 중 연합 있는 경우 연합 따지기

				que.push({ nr, nc });
				unite.push({ nr, nc });
				visited[nr][nc] = 1;
				sum += map[nr][nc];
				flag++;
			}
		}
	}

	//연합 값 갱신
	int num = unite.size();
	if (num >= 2) {
		int value = sum / num;
		for (int i = 0; i < num; i++) {
			QUE tmp = unite.front(); unite.pop();
			map[tmp.r][tmp.c] = value;
		}
	}

	//연합 해체
	unite = {};
	sum = 0;
	num = 0;

}

int Solve(void) {

	int day = 0;

	for (;;) {
		day++;
		//int flag = 0;
		flag = 0;
		memset(visited, 0, sizeof(visited));

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (visited[i][j] == 1) continue; //이미 따진 연합
				FloodFill(i, j);
			}
		}
		if (flag == 0) return day - 1; //더 이상 연합 없으면 이전 일수 반환
	}

}

void InputData(void) {
	scanf("%d %d %d", &N, &L, &R);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}