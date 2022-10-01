#include <iostream>
#include <cstring>
using namespace std;
#define MAXN (20)
#define INF ((int)2e9)

int N;
int S[MAXN + 10][MAXN + 10]; // 능력치
int Team[MAXN + 10]; // 1: Start , 0: Link
int sol;

void DFS(int cnt, int num) { //조합

	if (cnt == N / 2) { //팀 인원 완료
		int SScore = 0;
		int LScore = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if ((Team[i] == 1) && (Team[j] == 1)) SScore += S[i][j];
				else if ((Team[i] == 0) && (Team[j] == 0)) LScore += S[i][j];
			}
		}
		int gap = abs(SScore - LScore);
		if (sol > gap) sol = gap;
		return;
	}

	for (int i = num; i < N; i++) {
		if (!Team[i]) {
			Team[i] = 1;
			//DFS(cnt + 1, num + 1); //QQQQ //현재값의 다음 값부터 DFS 돌려줘야 하니까 i
			DFS(cnt + 1, i + 1);
			Team[i] = 0;
		}
	}
}

int Solve(void) {
	memset(Team, 0, sizeof(Team));
	sol = INF;
	DFS(0, 0);
	return sol;
}

void InputData(void) {
	scanf("%d", &N);

	memset(S, 0, sizeof(S));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &S[i][j]);
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}