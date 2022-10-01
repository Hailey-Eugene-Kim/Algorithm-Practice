#include <iostream>
#include <cstring>
using namespace std;
#define MAXN (100)

int N, K;
int A[2 * MAXN + 10];
int R[2 * MAXN + 10];
int cnt = 0;

void Rotate(void) {
	int tmp1 = A[2 * N];
	int tmp2 = R[2 * N];
	for (int i = 2 * N; i >= 2; i--) {
		A[i] = A[i - 1];
		R[i] = R[i - 1]; 
	}
	A[1] = tmp1;
	R[1] = tmp2;

	if (R[N] == 1) R[N] = 0;
}

void RobotMove(void) { 
	for (int i = N - 1; i >= 1; i--) {
		if (R[i] != 1) continue; //로봇 있을 때만
		if ((R[i + 1] == 0) && (A[i + 1] >= 1)) { //이동

			R[i] = 0;
			R[i + 1] = 1;
			A[i + 1]--;
		}
	}

	if (R[N] == 1) R[N] = 0;
}

void RobotPut(void) {
	if ((A[1] >= 1) && (R[1] == 0)) {
		R[1] = 1;
		A[1]--;
	}
}

int ZeroCount(void) {
	int z = 0;
	for (int i = 1; i <= 2 * N; i++) {
		if (A[i] == 0) z++;
	}
	return z;
}

int Solve(void) {
	int sol = 0; //단계
	memset(R, 0, sizeof(R));
	for (;;) {
		sol++;
		Rotate();
		RobotMove();
		RobotPut();

		int cnt = ZeroCount();
		if (cnt >= K) break;
	}

	return sol;
}

void InputData(void) {
	scanf("%d %d", &N, &K);

	memset(A, 0, sizeof(A));
	for (int i = 1; i <= 2 * N; i++) {
		scanf("%d", &A[i]);
		if (A[i] == 0) cnt++;
	}
}

int main(void) {

	InputData();
	int ans = Solve();
	printf("%d", ans);

	return 0;
}