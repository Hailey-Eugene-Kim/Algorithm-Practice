#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
#define MAXN (50)

int N, M;
int A[MAXN + 10][MAXN + 10];
int C[MAXN + 10][MAXN + 10];
int cd, cs;

struct QUE {
	int d, s;
};
struct DIR {
	int r, c;
};
deque <QUE> que; //이동정보
deque <DIR> cld; //구름위치
deque <DIR> increase; 

int dr[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };  //짝수 대각선
int dc[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

void CloudMove(void) { //OK
	
	QUE cur = que.front(); que.pop_front();
	int pr = cur.s * dr[cur.d] % N;
	int pc = cur.s * dc[cur.d] % N;

	int I = cld.size();

	for (int i = 0; i < I; i++) {
		cld[i].r = (cld[i].r + pr + N) % N;
		cld[i].c = (cld[i].c + pc + N) % N;
		if (cld[i].r == 0) cld[i].r = N;
		if (cld[i].c == 0) cld[i].c = N;
		
	}
}

void RainPour(void) {
	increase = {};
	int I = cld.size();

	for (int i = 0; i < I; i++) {
		A[cld[i].r][cld[i].c] += 1;
		C[cld[i].r][cld[i].c] = 1;
		increase.push_back({ cld[i].r, cld[i].c });
	}

	//구름 사라짐
	cld = {};
}

void WaterCopy(void) {
	int I = increase.size();

	for (int i = 0; i < I; i++) {

		for (int j = 1; j <= 4; j++) {
			int nr = increase[i].r + dr[2 * j];
			int nc = increase[i].c + dc[2 * j];

			if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue;

			if (A[nr][nc] >= 1) A[increase[i].r][increase[i].c]++;
		}
	}
}

void CloudCreate(void) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if ((A[i][j] >= 2)&&(C[i][j] != 1)) {
				cld.push_back({ i, j });
				A[i][j] -= 2;
			}
		}
	}
	memset(C, 0, sizeof(C));
}

int Solve(void) {
	int sol = 0;

	memset(C, 0, sizeof(C));

	cld.push_back({ N - 1, 1 });
	cld.push_back({ N - 1, 2 });
	cld.push_back({ N, 1 });
	cld.push_back({ N, 2 });

	for (int i = 0; i < M; i++) {
		CloudMove();
		RainPour();
		WaterCopy();
		CloudCreate();
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sol += A[i][j];
		}
	}

	return sol;
}

void InputData(void) {
	scanf("%d %d", &N, &M);

	memset(A, 0, sizeof(A));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
		}
	}

	que = {};
	for (int k = 1; k <= M; k++) {
		scanf("%d %d", &cd, &cs);
		que.push_back({ cd, cs });
	}
}

int main(void) {

	InputData();
	int ans = Solve();
	printf("%d", ans);

	return 0;
}