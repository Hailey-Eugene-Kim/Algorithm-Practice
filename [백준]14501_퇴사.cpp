#include <stdio.h>
#define MAXN (15)

int N;
int T[MAXN + 10];
int P[MAXN + 10];
int sol;

void DFS(int d, int m) { //날짜 , 금액

	if (d > N) {
		//N회차 넘었으면 상담 안 하고 이전비용 리턴
		//해당 회차 상담이 N 넘어가면 리턴 

		if (d > N + 1) return;
		if (sol < m) sol = m; // 이전비용 m 리턴
		return;
	}

	//다음 날짜 , 이번 비용 
	DFS(d + 1, m); //상담 안 하고 넘기기
	DFS(d + T[d], m + P[d]); //상담 하기
}

int Solve(void) {
	sol = 0;
	DFS(1, 0);
	return sol;
}

void InputData(void) {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &T[i], &P[i]);
	}
}

int main(void) {

	InputData();
	int ans = Solve();

	printf("%d", ans);

	return 0;
}
