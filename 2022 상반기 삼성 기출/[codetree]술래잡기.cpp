#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAX (99)
#define INF ((int)2e9)

int n, m, h, k;
deque <int> runner[MAX + 10][MAX + 10];
deque <int> runner_move[MAX + 10][MAX + 10];
int tree[MAX + 10][MAX + 10];
struct INFO {
	int r, c, dir;
};
deque <INFO> catcher;
int changedir[MAX + 10][MAX + 10]; //1: 1번 회전 , 2: 반대로 회전
int SR, SC, SD;
int dr[] = { 0, -1, 0, 1, 0 }; //위 오 아 왼
int dc[] = { 0, 0, 1, 0, -1 };
int score;

void RunnerMove(void) {

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			runner_move[r][c].clear();
		}
	}

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {

			if (runner[r][c].size() == 0) continue;
			if (abs(r - SR) + abs(c - SC) > 3) continue;

			while (!runner[r][c].empty()) {
				int cur = runner[r][c].front(); runner[r][c].pop_front();

				int nd = cur;
				int nr = r + dr[nd];
				int nc = c + dc[nd];

				if ((nr < 1) || (nr > n) || (nc < 1) || (nc > n)) {
					nd = (nd + 2) % 4; //방향 반대
					if (nd == 0) nd = 4;

					nr = r + dr[nd];
					nc = c + dc[nd];
				}

				if (nr == SR && nc == SC) {
					nr = r;
					nc = c;
				}

				runner_move[nr][nc].push_back(nd);
			}
			
		}
	}

	for (int r = 1; r <= n; r++) { //****복제가 아니라 추가
		for (int c = 1; c <= n; c++) {

			while (!runner_move[r][c].empty()) {
				int cur = runner_move[r][c].front(); runner_move[r][c].pop_front();
				runner[r][c].push_back(cur);
			}
		}
	}
}

void CatcherMove(int turn) {

	int dec = turn;

	dec %= 2 * (n * n - 1);
	if (dec == 0) dec = 2 * (n * n - 1); //빼먹음

	int nsr = 0;
	int nsc = 0;
	int nsd = 0;
	 
	if (dec < n * n) { //정방향 0 ~ 24

		nsr = catcher[dec].r;
		nsc = catcher[dec].c;
		nsd = catcher[dec].dir;

		if (changedir[nsr][nsc] == 1) nsd = catcher[dec + 1].dir;
		else if (changedir[nsr][nsc] == 2) nsd = 3; //아래
	}
	else { //반대방향 // 25 ~ 48
		
		dec = (n * n - 1) - (dec - (n * n - 1)); //dec 갱신

		nsr = catcher[dec].r;
		nsc = catcher[dec].c;
		nsd = (catcher[dec].dir + 2) % 4; //방향 반대
		if (nsd == 0) nsd = 4;

		if (changedir[nsr][nsc] == 1) {
			nsd = (catcher[dec - 1].dir + 2) % 4;
			if (nsd == 0) nsd = 4;
		}
		
		else if (changedir[nsr][nsc] == 2) nsd = 1; //위
	}

	SR = nsr;
	SC = nsc;
	SD = nsd;

	int cnt = 0;
	for (int i = 0; i < 3; i++) { //3칸 이내 도망자 잡기
		int nsr = SR + i * dr[SD];
		int nsc = SC + i * dc[SD];

		if ((nsr < 1) || (nsr > n) || (nsc < 1) || (nsc > n)) continue;
		if (tree[nsr][nsc] == 1) continue;

		if (runner[nsr][nsc].size() > 0) {
			cnt += runner[nsr][nsc].size(); //잡은 수 추가
			runner[nsr][nsc].clear(); //도망자 제거
		}
	}

	score += turn * cnt;
}

void SetCatcher(void) {

	//memset(catcher, 0, sizeof(catcher));

	SR = (n + 1) / 2;
	SC = (n + 1) / 2;
	SD = 1;

	int nr = SR;
	int nc = SC;
	int nd = SD;
	int idx = 0;

	//초기값
	//catcher[SR][SC] = idx;
	catcher.push_back({ SR, SC, 1 });
	changedir[SR][SC] = 2;

	for (int i = 1; i <= n - 1; i++) { //길이

		for (int j = 1; j <= i; j++) { 
			idx++;
			nr += dr[nd];
			nc += dc[nd];

			//catcher[nr][nc] = idx;
			catcher.push_back({ nr, nc, nd });
		}
		nd++;
		if (nd == 5) nd = 1;
		changedir[nr][nc] = 1;

		for (int j = 1; j <= i; j++) {
			idx++;
			nr += dr[nd];
			nc += dc[nd];

			//catcher[nr][nc] = idx;
			catcher.push_back({ nr, nc, nd });
		}
		nd++;
		if (nd == 5) nd = 1;
		changedir[nr][nc] = 1;

	}

	//마지막 //n - 1 한 번 더
	for (int j = 1; j <= n - 1; j++) {
		idx++;
		nr += dr[nd];
		nc += dc[nd];

		//catcher[nr][nc] = idx;
		catcher.push_back({ nr, nc, nd });
	}
	nd++;
	if (nd == 5) nd = 1;
	changedir[nr][nc] = 2;


}

int Solve(void) {
	score = 0;

	SetCatcher();

	for (int turn = 1; turn <= k; turn++) {
		RunnerMove();
		CatcherMove(turn);
	}

	return score;
}

void InputData(void) {
	scanf("%d %d %d %d", &n, &m, &h, &k);

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			runner[r][c].clear();
		}
	}

	int x, y, d;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &x, &y, &d);
		if (d == 1) runner[x][y].push_back(2);
		else runner[x][y].push_back(3);
	}

	memset(tree, 0, sizeof(tree));
	int tx, ty;
	for (int j = 1; j <= h; j++) {
		scanf("%d %d", &tx, &ty);
		tree[tx][ty] = 1;
	}
}

int main(void) {

	InputData();
	int ans = Solve();
	printf("%d", ans);

	return 0;
}
