//map deque : 같은 칸에 파이어볼 쌓기

//이동
//1, N 연결 
//for 루프 map deque

//하나로 합치기 //4개로 나누기
//for 루프 map deque : size 1 / size 2

#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAXN 50

int N, M, K;
int visited[MAXN + 10][MAXN + 10];
struct FIRE {
	int m, s, d, flag; //행 열 질량 속력 방향 + 삭제 정보
};
//deque <FIRE> fire;
deque <FIRE> map[MAXN + 10][MAXN + 10];
//deque <FIRE> united;
int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void Move(void) {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j].size() == 0) continue; //파이어볼 없으면 패스

			while (!map[i][j].empty()) {
				FIRE cur = map[i][j].front();

				if (cur.flag == 1) break;

				map[i][j].pop_front(); //이전 파이어볼 없애고

				int fr = dr[cur.d] * cur.s % N;
				int fc = dc[cur.d] * cur.s % N;
				int nr = (i + fr + N) % N;
				int nc = (j + fc + N) % N;
				if (nr == 0) nr = N;
				if (nc == 0) nc = N;

				map[nr][nc].push_back({ cur.m, cur.s, cur.d, 1 }); //이동한 거 저장
			}
		}
	}

}

void Unite(void) {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j].size() == 0) continue; //파이어볼 없으면 패스

			if (map[i][j].size() == 1) {
				map[i][j][0].flag = 0;
			}

			else {
				int num = map[i][j].size();
				int nm = 0;
				int ns = 0;
				int odd = 0;

				while (!map[i][j].empty()) {
					FIRE cur = map[i][j].front();
					map[i][j].pop_front(); //이전 파이어볼 없애고

					nm += cur.m; //새 값 갱신
					ns += cur.s;
					if (cur.d % 2 == 1) odd++;
				}
				nm /= 5;
				ns /= num;

				if (nm == 0) continue;

				if ((odd == num) || (odd == 0)) { // 0 2 4 6
					for (int k = 0; k < 4; k++) {
						map[i][j].push_back({ nm, ns, 2 * k, 0 });
					}
				} 
				else { // 1 3 5 7 
					for (int k = 0; k < 4; k++) {
						map[i][j].push_back({ nm, ns, 2 * k + 1, 0 });
					}
				}
			}
		}
	}
}

int Solve(void) {
	int sol = 0;

	for (int k = 1; k <= K; k++) {
		Move();
		Unite();
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			
			int K = map[i][j].size();
			if (K == 0) continue;
			for (int k = 0; k < K; k++) {
				sol += map[i][j][k].m;
			}
		}
	}

	return sol;
}

void InputData(void) {
	scanf("%d %d %d", &N, &M, &K);

	int r, c, m, s, d;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] = {};
		}
	}

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d %d %d", &r, &c, &m, &s, &d);
		map[r][c].push_back({ m, s, d, 0 });
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);

	return 0;
}
