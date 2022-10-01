#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAX 8

int N, M;
int map[MAX + 10][MAX + 10];
int visited[MAX + 10][MAX + 10];
struct CCTV {
	int type, dir, r, c;
};
deque <CCTV> allcase; //종류 별 모든 방향 케이스
deque <deque<CCTV>> cctv; //각 cctv의 allcase
deque <CCTV> Cselect; //DFS에서 선택
int sol;
int cctvNum = 0;
int empNum = 0;
int obsvNum;
int dr[] = {0, -1, 1, 0, 0}; //상 하 좌 우 1 2 3 4
int dc[] = {0, 0, 0, -1, 1}; //상 하 좌 우 1 2 3 4

void Spread(int cR, int cC, int cDir) {
	int nr = cR;
	int nc = cC;
	for (;;) {
		nr += dr[cDir];
		nc += dc[cDir];
		if (map[nr][nc] == -1) break;
		if (map[nr][nc] == 6) break;
		if (visited[nr][nc] == 1) continue;

		if (map[nr][nc] == 0) obsvNum++; //0 일 경우만 감시 구역
		visited[nr][nc] = 1;
	}
}

int CalArea(void) { //select의 사각지대 계산
	memset(visited, 0, sizeof(visited));
	obsvNum = 0;

	for (int i = 0; i < cctvNum; i++) {

		int cType = Cselect[i].type;
		int cDir = Cselect[i].dir;
		int cR = Cselect[i].r;
		int cC = Cselect[i].c;

		if (cType == 1) {
			Spread(cR, cC, cDir);
		}

		else if (cType == 2) {
			if (cDir == 1) { //상하
				Spread(cR, cC, 1);
				Spread(cR, cC, 2);
			}
			else if (cDir == 2) { // 좌우
				Spread(cR, cC, 3);
				Spread(cR, cC, 4);
			}
		}

		else if (cType == 3) {
			if (cDir == 1) { 
				Spread(cR, cC, 1); //상우
				Spread(cR, cC, 4);
			}
			else if (cDir == 2) { //상좌
				Spread(cR, cC, 1);
				Spread(cR, cC, 3);
			}
			else if (cDir == 3) { //하우
				Spread(cR, cC, 2);
				Spread(cR, cC, 4);
			}
			else if (cDir == 4) { //하좌
				Spread(cR, cC, 2);
				Spread(cR, cC, 3);
			}
		}

		else if (cType == 4) {
			for (int k = 1; k <= 4; k++) {
				if (k == cDir) continue;
				Spread(cR, cC, k);
			}
		}

		else if (cType == 5) {

			for (int k = 1; k <= 4; k++) {
				Spread(cR, cC, k);
			}
		}
	}

	return empNum - obsvNum;
}

void DFS(int idx) {

	if (idx == cctvNum) {
		int area = CalArea();
		if (sol > area) sol = area;
		return;
	}

	int P = cctv[idx].size();
	for (int p = 0; p < P; p++) {
		Cselect.push_back({ cctv[idx][p] });
		DFS(idx + 1);
		Cselect.pop_back();
	}
}

int Solve(void) {
	sol = ((int)2e9);
	
	DFS(0);

	return sol;
}

void InputData(void) {
	scanf("%d %d", &N, &M);

	memset(map, -1, sizeof(map));
	cctv.clear();
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			scanf("%d", &map[r][c]);

			if (map[r][c] == 0) empNum++;
			if ((map[r][c] == 0) || (map[r][c] == 6)) continue;
			cctvNum++;

			allcase.clear();
			if (map[r][c] == 1) {
				for (int i = 1; i <= 4; i++) {
					allcase.push_back({ 1, i , r, c});
				}
				cctv.push_back(allcase);
			}
			else if (map[r][c] == 2) {
				for (int i = 1; i <= 2; i++) {
					allcase.push_back({ 2, i, r, c });
				}
				cctv.push_back(allcase);
			}
			else if (map[r][c] == 3) {
				for (int i = 1; i <= 4; i++) {
					allcase.push_back({ 3, i, r, c });
				}
				cctv.push_back(allcase);
			}
			else if (map[r][c] == 4) {
				for (int i = 1; i <= 4; i++) {
					allcase.push_back({ 4, i, r, c });
				}
				cctv.push_back(allcase);
			}
			else if (map[r][c] == 5) {
				allcase.push_back({ 5, 1, r, c });
				cctv.push_back(allcase);
			}
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}