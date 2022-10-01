//DFS, 큐 //DFS 조합도 큐로 돌리는 방법
#if 0
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
#define MAXN 50
#define INF ((int)2e9)

int N, M;
int map[MAXN + 10][MAXN + 10];
int visited[MAXN + 10][MAXN + 10];
int chicken = 0;
int sol;

struct QUE {
	int r, c;
};
deque <QUE> C;
deque <QUE> SC;
deque <QUE> H;

int CalDistance(void) {
	int DistSum = 0;

	int L = H.size();
	for (int l = 0; l < L; l++) {
		int dist = 0;
		int MinDist = INF;
		int K = SC.size();
		for(int k = 0; k < K; k++) {
			dist = abs(H[l].r - SC[k].r) + abs(H[l].c - SC[k].c);
			if (MinDist > dist) MinDist = dist;
		}
		DistSum += MinDist;
	}
	
	return DistSum;
}

void DFS(int cnt, int idx) { //고른 치킨집만 visited 배열

	if (cnt == M) {
		int ret = CalDistance();
		if (sol > ret) sol = ret; //최소값 갱신

		return;
	}

	int K = C.size(); //visited 배열을 이용하는데 일렬로 하는 방법도 있음
	for (int k = idx; k < K; k++) {

		SC.push_back({ C[k].r, C[k].c });
		DFS(cnt + 1, k + 1);
		SC.pop_back();
	}
}

int Solve(void) {
	sol = INF;
	DFS(0, 0);
	return sol;
}

void InputData(void) {
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%1d", &map[i][j]);
			if (map[i][j] == 2) {
				chicken++;
				C.push_back({ i, j });
			}
			if (map[i][j] == 1) {
				H.push_back({ i, j });
			}
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}
#endif