
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define MAXN (20)

int n, m, k, c; //격자의 크기 n, 박멸이 진행되는 년 수 m, 제초제의 확산 범위 k, 제초제가 남아있는 년 수 c
int map[MAXN + 10][MAXN + 10]; //빈 칸 0, 벽 -1
int growtree[MAXN + 10][MAXN + 10]; 
int spread[MAXN + 10][MAXN + 10]; 
int deletetree[MAXN + 10][MAXN + 10]; 
int selectpos[MAXN + 10][MAXN + 10]; 

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

int ddr[] = { -1, -1, 1, 1}; 
int ddc[] = { -1, 1, -1, 1}; 

int maxR, maxC;
int sol;

void InputData(void) { //OK
	scanf("%d %d %d %d", &n, &m, &k, &c);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}

void Growth(void) {
	memset(growtree, 0, sizeof(growtree));

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			
			if (map[r][c] <= 0) continue; //나무일 경우만

			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nr = r + dr[k];
				int nc = c + dc[k];

				if ((nr < 1) || (nr > n) || (nc < 1) || (nc > n)) continue;
				if (map[nr][nc] > 0) cnt++;
			}

			growtree[r][c] += cnt;
		}
	}

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			map[r][c] += growtree[r][c];
		}
	}
}

void Spread(void) {
	memset(spread, 0, sizeof(spread));

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			
			if (map[r][c] <= 0) continue;

			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nr = r + dr[k];
				int nc = c + dc[k];

				if ((nr < 1) || (nr > n) || (nc < 1) || (nc > n)) continue; //범위 밖
				if (map[nr][nc] == -1) continue; //벽
				if (map[nr][nc] > 0) continue; //다른 나무
				if (deletetree[nr][nc] > 0) continue; //제초제

				cnt++;
			}

			if (cnt == 0) continue;

			int spreadvalue = map[r][c] / cnt;
			for (int k = 0; k < 4; k++) {
				int nr = r + dr[k];
				int nc = c + dc[k];

				if ((nr < 1) || (nr > n) || (nc < 1) || (nc > n)) continue; //범위 밖
				if (map[nr][nc] == -1) continue; //벽
				if (map[nr][nc] > 0) continue; //다른 나무
				if (deletetree[nr][nc] > 0) continue; //제초제

				spread[nr][nc] += spreadvalue;
			}
		}
	}

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			map[r][c] += spread[r][c];
		}
	}
}

void Select(void) 
	
	memset(selectpos, 0, sizeof(selectpos));
	int max = -1;

	for (int r = n; r >= 1; r--) {
		for (int c = n; c >= 1; c--) {

			int deletevalue = 0;

			//자기 자신
			if (map[r][c] > 0) { //나무일 때 대각선 확산

				deletevalue = map[r][c];

				for (int i = 0; i < 4; i++) { //대각선
					for (int j = 1; j <= k; j++) { //k길이만큼
						int nr = r + j * ddr[i];
						int nc = c + j * ddc[i];

						if ((nr < 1) || (nr > n) || (nc < 1) || (nc > n)) break; //범위 밖
						if (map[nr][nc] == -1) break; //벽일 경우 중단
						if (map[nr][nc] == 0) break; //0일 경우 중단
						if (map[nr][nc] > 0) deletevalue += map[nr][nc]; //나무일 경우
					}
				}
			}

			selectpos[r][c] = deletevalue;

			if (max <= deletevalue) { //최대 삭제, 행 낮, 열 낮
				max = deletevalue;
				maxR = r;
				maxC = c;
			}
		}
	}

	sol += max;
}

void Delete(void) {

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			if (deletetree[r][c] > 0) deletetree[r][c]--;
		}
	}

	//maxR, maxC

	map[maxR][maxC] = 0;
	deletetree[maxR][maxC] += c;


	for (int i = 0; i < 4; i++) { //대각선
		for (int j = 1; j <= k; j++) { //k길이만큼
			int nr = maxR + j * ddr[i];
			int nc = maxC + j * ddc[i];

			if ((nr < 1) || (nr > n) || (nc < 1) || (nc > n)) break; //범위 밖
			if (map[nr][nc] == -1) break; //벽일 경우 중단
			
			deletetree[nr][nc] = c;

			if (map[nr][nc] == 0)  break;
		}
	}

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			
			if (deletetree[r][c] > 0) map[r][c] = 0;
		}
	}
}


int Solve(void) { //m년 동안 총 박멸한 나무의 그루 수
	sol = 0;
	memset(deletetree, 0, sizeof(deletetree));

	for (int i = 1; i <= m; i++) {
		//나무의 성장
		Growth()

		//나무의 번식
		Spread();
	
		//제초제를 뿌릴 위치 선정
		Select();

		//제초제를 뿌리는 작업 진행
		Delete();
	}

	return sol;
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}