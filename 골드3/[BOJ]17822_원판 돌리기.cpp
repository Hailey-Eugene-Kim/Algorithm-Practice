#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
#define MAXN 50

int N, M, T;
deque <int> circle[MAXN + 10];
struct INFO {
	int x, d, k;
};
queue <INFO> Rotate;
struct ERASE {
	int n, m;
};
queue <ERASE> Erase;
int visited[MAXN + 10][MAXN + 10];
int dn[] = {0, 0, -1, 1}; //좌우상하
int dm[] = {-1, 1, 0, 0};

void CircleRotate(int x, int d, int k) {

	for (int n = 1; n <= N; n++) {
		if ((n >= x) && (n % x == 0)) {

			for (int i = 1; i <= k; i++) { //k회 회전

				if (d == 0) { //시계방향 회전
					int tmp = circle[n].back(); circle[n].pop_back();
					circle[n].push_front(tmp);
				}

				else if (d == 1) { //반시계방향 회전
					int tmp = circle[n].front(); circle[n].pop_front();
					circle[n].push_back(tmp);
				}
			}
		}
	}
}

void CheckNum(void) {

	int same = 0;
	int sum = 0;
	int cnt = 0;
	memset(visited, 0, sizeof(visited));
	Erase = {};

	for (int i = 1; i <= N; i++) { //1베이스
		for (int j = 0; j < M; j++) { //0베이스

			if (circle[i][j] == 0) continue;

			sum += circle[i][j];
			cnt++;

			visited[i][j] = 1;

			//인접 4개 수
			int flag = 0;
			for (int l = 0; l < 4; l++) { //좌우상하
				int nn = i + dn[l];
				int nm = j + dm[l];

				if ((nn < 1) || (nn > N)) continue; //1 베이스
				if (nm < 0) nm += M; //0 베이스
				if (nm >= M) nm -= M;

				if (circle[nn][nm] == circle[i][j]) {
					flag++; //중복 체크 위치 변경 (이미 방문 했더라도 i, j는 Erase에 안 들어갔을 수 있음)

					if (visited[nn][nm] == 1) continue;

					visited[nn][nm] = 1;
					same++;
					Erase.push({ nn, nm });
				}
			}
			if (flag > 0) Erase.push({ i, j });
		}
	}

	if (same == 0) {
		//int avg = sum / cnt;
		double avg = (double)sum / (double)cnt;

		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++) {

				if (circle[i][j] == 0) continue;
				if (circle[i][j] > avg) circle[i][j] -= 1;
				else if (circle[i][j] < avg) circle[i][j] += 1; //else 빼먹음
			}
		}
	}

	else {
		while (!Erase.empty()) {
			ERASE cur = Erase.front(); Erase.pop();
			circle[cur.n][cur.m] = 0;
		}
	}
}

int Solve(void) {

	while (!Rotate.empty()) {
		INFO cur = Rotate.front(); Rotate.pop();
		CircleRotate(cur.x, cur.d, cur.k);
		CheckNum();
	}

	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) { //0베이스
			sum += circle[i][j];
		}
	}
	return sum;
}

void Input(void) {

	scanf("%d %d %d", &N, &M, &T);

	int c;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &c);
			circle[i].push_back(c);
		}
	}

	int rx, rd, rk;
	for (int t = 1; t <= T; t++) {
		scanf("%d %d %d", &rx, &rd, &rk);
		Rotate.push({ rx, rd, rk });
	}
}

int main(void) {
	
	Input();
	int ans = Solve();
	printf("%d", ans);
	
	return 0;
}