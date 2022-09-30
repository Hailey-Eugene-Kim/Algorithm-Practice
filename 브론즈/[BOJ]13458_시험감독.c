#include <stdio.h>
#define MAXN ((int)1e6)

int N, B, C;
int A[MAXN + 10];

int CNT(int n) {
	if (A[n] <= B) return 1;
	
	int cnt = (A[n] - B + (C - 1)) / C;
	return cnt + 1;
}

long long int Solve(void) {
	long long int sol = 0;

	for (int i = 0; i < N; i++) {
		sol += CNT(i);
	}

	return sol;
}

void InputData(void) {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
	}

	scanf("%d %d", &B, &C);
}

int main(void) {

	InputData();
	long long int ans = Solve();

	printf("%lld", ans);

	return 0;
}