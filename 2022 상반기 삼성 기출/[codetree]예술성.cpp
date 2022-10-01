#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAXN (29)

int n;
int map[MAXN + 10][MAXN + 10];
int visited[MAXN + 10][MAXN + 10];
int map_cpy[MAXN + 10][MAXN + 10];
struct VALUE {
	int color, r, c;
};
vector <VALUE> groupblock;
struct INFO {
	int gidx, color, cnt;
};
vector <INFO> groupinfo;
int relation[MAXN * MAXN + 10][MAXN * MAXN + 10];
int gidx;

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void PrintMap(void) {
	printf("Map\n");
	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			printf("%d ", map[r][c]);
		}
		printf("\n");
	}

	printf("MapCpy\n");
	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			printf("%d ", map_cpy[r][c]);
		}
		printf("\n");
	}
}

void FloodFill(int r, int c, int gidx, int color) {

	if ((r < 1) || (r > n) || (c < 1) || (c > n)) return;
	if (visited[r][c] > 0) return; //이미 방문 
	if (map[r][c] != color) return; // 해당 컬러만

	visited[r][c] = gidx;
	groupblock.push_back({ map[r][c], r, c });

	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		FloodFill(nr, nc, gidx, color);
	}
}

void MakeGroup(void) {
	gidx = 0;
	groupinfo.clear();
	groupinfo.push_back({ 0, 0, 0 });

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {

			if (visited[r][c] > 0) continue;

			gidx++;
			groupblock.clear();

			FloodFill(r, c, gidx, map[r][c]);

			int gcnt = groupblock.size();
			groupinfo.push_back({ gidx, map[r][c], gcnt });
		}
	}
}

int CalScore(void) {
	int score = 0;
	memset(relation, 0, sizeof(relation));

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			for (int k = 0; k < 4; k++) {
				int nr = r + dr[k];
				int nc = c + dc[k];

				if ((nr < 1) || (nr > n) || (nc < 1) || (nc > n)) continue;

				if (visited[r][c] != visited[nr][nc]) relation[visited[r][c]][visited[nr][nc]]++;
			}
		}
	}

	int I = groupinfo.size();
	for (int i = 1; i <= I; i++) {
		for (int j = i + 1; j <= I; j++) {
			if (relation[i][j] > 0) {
				int gscore = (groupinfo[i].cnt + groupinfo[j].cnt) * groupinfo[i].color * groupinfo[j].color * relation[i][j];
				score += gscore;
			}
		}
	}

	return score;
}

void Rotate(void) {
	int center = n / 2 + 1;
	memset(map_cpy, 0, sizeof(map_cpy));

	//십자
	for (int c = 1; c <= n; c++) { //r = center
		map_cpy[n - (c - 1)][center] = map[center][c];
	}
	for (int r = 1; r <= n; r++) { //c = center
		map_cpy[n - (center - 1)][r] = map[r][center];
	}

	//PrintMap();

	//나머지
	for (int r = 1; r <= n / 2; r++) {
		for (int c = 1; c <= n / 2; c++) {
			map_cpy[c][center - r] = map[r][c];
		}
	}
	

	for (int r = 1; r <= n / 2; r++) {
		for (int c = center + 1; c <= n; c++) {
			map_cpy[c - center][n - (r - 1)] = map[r][c];
		}
	}
	
	for (int r = center + 1; r <= n; r++) {
		for (int c = 1; c <= n / 2; c++) {
			map_cpy[center + c][center - (r - center)] = map[r][c];
		}
	}
	
	for (int r = center + 1; r <= n; r++) {
		for (int c = center + 1; c <= n; c++) {
			map_cpy[c][n - (r - center - 1)] = map[r][c];
		}
	}

	//map에 적용
	memcpy(map, map_cpy, sizeof(map_cpy));
	//PrintMap();
}



int Solve(void) {
	int sol = 0;

	MakeGroup();
	sol += CalScore();

	for (int m = 1; m <= 3; m++) {
		Rotate();
		memset(visited, 0, sizeof(visited));
		MakeGroup();
		sol += CalScore();
	}

	return sol;
}

void InputData(void) {
	scanf("%d", &n);

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
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
