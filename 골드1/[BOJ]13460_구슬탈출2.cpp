#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAX (10)
#define INF ((int)2e9)

int N, M;
char map[MAX + 10][MAX + 10];

int dr[] = { 0, 0, -1, 1 }; //왼 오 위 아
int dc[] = { -1, 1, 0, 0 };
int rr, rc, br, bc;
int sol;

int RedMove(int k) { //0: 벽 1: 구멍 2: 다른 구슬 3: 움직X

	if (map[rr + dr[k]][rc + dc[k]] == '#') return 3;

	int nrr = rr;
	int nrc = rc;

	for (;;) {
		nrr += dr[k];
		nrc += dc[k];

		if (map[nrr][nrc] == '#') {
			rr = nrr - dr[k];
			rc = nrc - dc[k];
			return 0;
		}

		if (map[nrr][nrc] == 'O') {
			rr = 0;
			rc = 0;
			return 1;
		}

		if (nrr == br && nrc == bc) {
			rr = nrr - dr[k];
			rc = nrc - dc[k];
			return 2;
		}

	}
}

int BlueMove(int k) {

	if (map[br + dr[k]][bc + dc[k]] == '#') return 3;

	int nbr = br;
	int nbc = bc;

	for (;;) {
		nbr += dr[k];
		nbc += dc[k];

		if (map[nbr][nbc] == '#') {
			br = nbr - dr[k];
			bc = nbc - dc[k];
			return 0;
		}

		if (map[nbr][nbc] == 'O') {
			br = 0;
			bc = 0;
			return 1;
		}

		if (nbr == rr && nbc == rc) {
			br = nbr - dr[k];
			bc = nbc - dc[k];
			return 2;
		}

	}
}

void DFS(int cnt) {

	if (cnt > sol) return;
	if (cnt > 10) return;

	int rrt = rr;
	int rct = rc;
	int brt = br;
	int bct = bc;

	for (int k = 0; k < 4; k++) {

		//1: 구멍 2: 다른 구슬 3: 움직X
		int statusR = RedMove(k);
		int statusB = BlueMove(k);

		if (statusB == 1) {
			rr = rrt;
			rc = rct;
			br = brt;
			bc = bct;
			continue;
		}
		if (statusR == 1) {
			rr = rrt;
			rc = rct;
			br = brt;
			bc = bct;
			if (sol > cnt) sol = cnt;
			continue;
		}
		if ((statusB == 3) && (statusR == 3)) continue;
		if (statusR == 2) RedMove(k);

		DFS(cnt + 1);
		rr = rrt;
		rc = rct;
		br = brt;
		bc = bct;

	}

}


int Solve() {
	sol = INF;

	DFS(1);

	if (sol == INF) sol = -1;
	return sol;
}

void InputData() {

	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];

			if (map[i][j] == 'R') {
				rr = i;
				rc = j;
			}
			if (map[i][j] == 'B') {
				br = i;
				bc = j;
			}
		}
	}

}

int main() {

	InputData();
	int ans = Solve();
	cout << ans;

	return 0;
}