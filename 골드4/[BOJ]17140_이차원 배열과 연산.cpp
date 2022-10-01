	//(수, 수의 등장) => 벡터 N
		//등장횟수 오름차순 //수의 크기 오름차순
	//vector size 최대 * 2 => C값 갱신
	//vector 값 A 배열에 복사 
		//해당 열 C보다 작으면 나머지 0 채우기

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 100

int r, c, k;
int A[MAXN + 10][MAXN + 10];
int R, C; //행 크기 , 열 크기
struct NUM {
	int num, cnt;
};
vector <NUM> N[MAXN + 10];
bool cmp(NUM a, NUM b) { //cnt 기준 오름차순 //cnt 같으면 num 기준 오름차순
	if (a.cnt == b.cnt) return a.num < b.num;
	return a.cnt < b.cnt;
}

void CalR(void) {
	//벡터 초기화
	for (int i = 1; i <= R; i++) {
		N[i].clear();
	}

	int MaxSize = -1;
	for (int i = 1; i <= R; i++) { //추가: 0 나올 때 처리
		for (int j = 1; j <= C; j++) {
			if (A[i][j] == 0) continue;
			if (j == 1) N[i].push_back({ A[i][j], 1 }); //초기값

			else { //중복값 cnt++ 
				int flag = 0;
				int P = N[i].size();
				for (int p = 0; p < P; p++) {
					if (A[i][j] == N[i][p].num) {
						N[i][p].cnt++;
						flag++;
					}
				}

				if (flag == 0) {
					N[i].push_back({ A[i][j], 1 }); //중복값 없으면 num 저장 
				}
			}
		}
		int size = N[i].size();
		if (MaxSize < size) MaxSize = size;

		sort(N[i].begin(), N[i].end(), cmp); //Q 철도잇기에서는 cmp & 빼면 오류
	}

	C = 2 * MaxSize; //C값 갱신
}

void CalC(void) {
	//벡터 초기화
	for (int i = 1; i <= C; i++) {
		N[i].clear();
	}

	int MaxSize = -1;
	for (int i = 1; i <= C; i++) { //추가: 0 나올 때 처리
		for (int j = 1; j <= R; j++) {
			if (A[j][i] == 0) continue;
			if (j == 1) N[i].push_back({ A[j][i], 1 }); //초기값

			else { //중복값 cnt++ 
				int flag = 0;
				int P = N[i].size();
				for (int p = 0; p < P; p++) {
					if (A[j][i] == N[i][p].num) {
						N[i][p].cnt++;
						flag++;
					}
				}

				if (flag == 0) {
					N[i].push_back({ A[j][i], 1 }); //중복값 없으면 num 저장 
				}
			}
		}
		int size = N[i].size();
		if (MaxSize < size) MaxSize = size;

		sort(N[i].begin(), N[i].end(), cmp); //Q 철도잇기에서는 cmp & 빼면 오류
	}

	R = 2 * MaxSize; //R값 갱신
}

void CopyArrayR(void) { 

	memset(A, 0, sizeof(A));
	for (int i = 1; i <= R; i++) {
		int J = N[i].size();
		for (int j = 0; j < J; j++) {
			A[i][2 * (j + 1) - 1] = N[i][j].num;
			A[i][2 * (j + 1)] = N[i][j].cnt;
		}
	}
}

void CopyArrayC(void) {

	memset(A, 0, sizeof(A));
	for (int i = 1; i <= C; i++) {
		int J = N[i].size();
		for (int j = 0; j < J; j++) {
			A[2 * (j + 1) - 1][i] = N[i][j].num;
			A[2 * (j + 1)][i] = N[i][j].cnt;
		}
	}
}

int Solve(void) {
	int sol = -1;

	for (int t = 0; t <= 100; t++) {
		if (A[r][c] == k) {
			sol = t;
			break;
		}
		if (R >= C) {
			CalR();
			CopyArrayR();
		}
		else if (R < C) {
			CalC();
			CopyArrayC();
		}
	}

	return sol;
}

void InputData(void) {
	scanf("%d %d %d", &r, &c, &k);

	memset(A, 0, sizeof(A));
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	R = 3; C = 3;
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}