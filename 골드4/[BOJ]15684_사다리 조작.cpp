#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAX (30)
#define INF ((int)2e9)

int N, M, H;
int sol;
int map[MAX + 10][MAX + 10];
struct LAD {
	int r, c;
};
deque <LAD> ladder;
int EmptyNum;

bool CheckResult(void) {

	int value;
	for (int i = 1; i <= N; i++) {
		value = i;
		for (int j = 1; j <= H; j++) {
			value += map[j][value];
		}
		if (value != i) return false; //불가능
	}
	return true; //가능
}

void DFS(int idx, int cnt) {

	if (cnt > 3) return; //3보다 큰 경우 제외
	if (cnt > 0) {

		if (CheckResult()) {
			if (sol > cnt) sol = cnt;
			return;
		}
	}

	for (int i = idx; i < EmptyNum; i++) {
		//제외 조건

		//이미 있는 경우
		//양쪽 있는 경우
		//범위 : 오른쪽에 놓는 경우만 => N - 1열 까지만 //이미 걸러짐
		if (map[ladder[i].r][ladder[i].c] == 1) continue;
		if (map[ladder[i].r][ladder[i].c + 1] == 1) continue;
		if (map[ladder[i].r][ladder[i].c - 1] == 1) continue;

		map[ladder[i].r][ladder[i].c] = 1;
		map[ladder[i].r][ladder[i].c + 1] = -1;

		DFS(i + 1, cnt + 1);

		map[ladder[i].r][ladder[i].c] = 0;
		map[ladder[i].r][ladder[i].c + 1] = 0;
	}
}

int Solve(void) { //추가 사다리 최소값
	sol = INF;

	int result = CheckResult(); //처음부터 가능한 경우
	if (result == 1) return 0;

	DFS(0, 0);

	if (sol == INF) return -1; //불가능한 경우

	return sol;
}

void InputData(void) {
	scanf("%d %d %d", &N, &M, &H);

	memset(map, 0, sizeof(map));
	int a, b;
	for (int m = 1; m <= M; m++) {
		scanf("%d %d", &a, &b);
		map[a][b] = 1;
		map[a][b + 1] = -1;
	}

	//이미 있는 경우
		//양쪽 있는 경우
		//범위 : 오른쪽에 놓는 경우만 => N - 1열 까지만

	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N - 1; j++) { //사다리 놓을 수 있는 곳만 저장

			if (map[i][j] == 1) continue;
			if (map[i][j + 1] == 1) continue;
			if (map[i][j - 1] == 1) continue;

			ladder.push_back({ i, j });
		}
	}

	EmptyNum = ladder.size();
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin.tie(nullptr);

	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}