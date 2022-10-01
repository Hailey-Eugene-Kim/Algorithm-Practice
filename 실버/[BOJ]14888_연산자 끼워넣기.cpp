#include <iostream>
#include <cstring>
#define MAXN (11)
#define INF ((int)2e9)

int N;
int A[MAXN + 10];
int B[4 + 10];
int used[4 + 10];
int sol1, sol2; //최대 , 최소

int Cal(int x, int i, int n) { //이전 값 , 현재 i

	if (i == 1) return x + A[n];
	if (i == 2) return x - A[n];
	if (i == 3) return x * A[n];
	if (i == 4) return x / A[n];
}

void DFS(int d, int cnt) { //순열 //계산 값, 회차

	//최소값 가지치기 //X 두 값 다 구해야 하니까,,
	if (cnt == N) {
		if (sol1 < d) sol1 = d; //최대
		if (sol2 > d) sol2 = d; //최소

		return;
	}


	for (int i = 1; i <= 4; i++) {
		if (used[i] == B[i]) continue;
		
		used[i]++;
		DFS(Cal(d, i, cnt + 1), cnt + 1);
		used[i]--;
	}
}

void Solve(void) {
	//sol1 = 0; //최대
	sol1 = -INF; //최대
	sol2 = INF; //최소
	memset(used, 0, sizeof(used));

	DFS(A[1], 1);
}

void InputData(void) {
	scanf("%d", &N);

	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));

	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
	}
	
	for (int i = 1; i <= 4; i++) {
		scanf("%d", &B[i]);
	}
}

int main(void) {

	InputData();
	Solve();
	printf("%d\n", sol1);
	printf("%d", sol2);
	return 0;
}
