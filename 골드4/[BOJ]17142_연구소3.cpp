//바이러스 M개 선택 => DFS
	//vector에 바이러스 저장해서 M개 조합
	//확산 => BFS
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
#define MAXN (50)
#define INF ((int)2e9)

int N, M;
int map[MAXN + 10][MAXN + 10];
int visited[MAXN + 10][MAXN + 10]; //M개 바이러스 = -1 //나중에 필요 없으면 아웃
int time[MAXN + 10][MAXN + 10];
int checkact[MAXN + 10][MAXN + 10];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
int uniq = 0;
struct DIR {
	int r, c;
};
vector <DIR> virus;
vector <DIR> selected;
vector <DIR> act;
//int time; 
int sol;
int vacant;
int all, impossible;

struct QUE {
	int r, c, t;
};
queue <QUE> que;

int BFS(void) { //가중치 BFS //시간 리턴 

	//초기화
	que = {};
	memset(visited, 0, sizeof(visited));
	memset(time, 0, sizeof(time));
	int maxtime = 0;
	int cnt = 0;

	//처음값
	for (auto e : selected) {
		que.push({ e.r, e.c, 0 });
		visited[e.r][e.c] = 1;
		time[e.r][e.c] = 0;
	}

	//반복
	while (!que.empty()) {
		QUE cur = que.front(); que.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i]; //실수

			if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue;
			if (visited[nr][nc] == 1) continue;
			if (map[nr][nc] == 1) continue;

			que.push({ nr, nc, cur.t + 1 });
			visited[nr][nc] = 1;
			time[nr][nc] = cur.t + 1;
			if (map[nr][nc] == 0) cnt++;

			if (cnt == vacant) {

				for (int i = 1; i <= N; i++) {
					for (int j = 1; j <= N; j++) {
						if (maxtime < time[i][j]) maxtime = time[i][j];
					}
				}
				return maxtime;
			}
		}
	}

	return maxtime;
}

void DFS(int idx, int cnt) {

	if (cnt == M) {
		int ret = BFS();

		all++;
		if (ret == 0) impossible++;
		else if (sol > ret) sol = ret; //최소 값으로 갱신
		return;
	}

	for (int i = idx; i < virus.size(); i++) { //vector은 미만으로

		if (checkact[virus[i].r][virus[i].c] == 1) continue; //이미 선택

		checkact[virus[i].r][virus[i].c] = 1; //고른 바이러스 표시 
		selected.push_back({ virus[i].r, virus[i].c });
		DFS(i, cnt + 1);
		checkact[virus[i].r][virus[i].c] = 0;
		selected.pop_back();
	}

}

int Solve(void) {
	sol = INF;
	all = 0;
	impossible = 0;

	if (vacant == 0) return 0;

	DFS(0, 0); //바이러스 M개 조합
	if (impossible == all) return -1;

	return sol;
}

void InputData(void) {
	memset(map, 0, sizeof(map));
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) virus.push_back({ i, j });
			if (map[i][j] == 0) vacant++;
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}
