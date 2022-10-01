#include <iostream>
#include <cstring>
using namespace std;
#define MAXN (50)

int R, C, T;
int map[MAXN + 10][MAXN + 10];
int spread[MAXN + 10][MAXN + 10];
int dr[] = { -1, 1, 0, 0 }; //위 아 왼 오
int dc[] = { 0, 0, -1, 1 };

void printmap(void) {
	printf("\n");
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			printf("%d ", map[r][c]);
		}
		printf("\n");
	}
}

void Move_Air(void) { //왜 안 될까....
	int flag = 0;
	for (int r = 1; r <= R; r++) {

		if ((map[r][1] == -1) && (flag == 0)) { //공기청정기1 반시계방향 
			
			for (int a = r - 1; a > 1; a--) {
				map[a][1] = map[a - 1][1]; //한 칸씩 이동
			}
			
			for (int b = 1; b < C; b++) {
				map[1][b] = map[1][b + 1];
			}

			for (int c = 1; c < r; c++) {
				map[c][C] = map[c + 1][C];
			}

			for (int d = C; d > 2; d--) { //이것만 됨
				map[r][d] = map[r][d - 1];
			}

			flag++; //공기청정기1 완료 표시
			map[r][1] = -1; //공기청정기 
			map[r][2] = 0; //마지막값 갱신
		}

		else if ((map[r][1] == -1) && (flag == 1)) { //공기청정기2 시계방향

			for (int a = r + 1; a < R; a++) {
				map[a][1] = map[a + 1][1]; //한 칸씩 이동
			}

			for (int b = 1; b < C; b++) { //이것만 됨
				map[R][b] = map[R][b + 1];
			}

			for (int c = R; c > r; c--) {
				map[c][C] = map[c - 1][C];
			}

			for (int d = C; d > 2; d--) { 
				map[r][d] = map[r][d - 1];
			}

			map[r][1] = -1; //공기청정기 
			map[r][2] = 0; //마지막값 갱신
		}
	}
}

void Spread_Dust(void) { //OK

	//확산값 spread 배열 구하기, map값 빼주기
	memset(spread, 0, sizeof(spread));
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {

			int cnt = 0;
			if (map[r][c] > 0) {
				for (int i = 0; i < 4; i++) {
					int nr = r + dr[i];
					int nc = c + dc[i];

					if ((nr < 1) || (nr > R) || (nc < 1) || (nc > C)) continue;
					if (map[nr][nc] == -1) continue;
					spread[nr][nc] += map[r][c] / 5;
					cnt++;
				}
				map[r][c] -= cnt * (map[r][c] / 5);
			}
		}
	}

	//spread값 map에 합산
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			map[r][c] += spread[r][c];
		}
	}
}

int Solve(void) {

	for (int t = 1; t <= T; t++) {
		Spread_Dust(); //T회 확산 & 순환
		Move_Air();
	}

	int sol = 0;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (map[i][j] != -1) sol += map[i][j];
		}
	}
	return sol;
}

void InputData(void) {
	scanf("%d %d %d", &R, &C, &T);

	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			scanf("%d", &map[r][c]);
		}
	}
}

int main(void) {
	
	InputData();
	int ans = Solve();
	printf("%d", ans);
	
	return 0;
}
