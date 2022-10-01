#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAX 100

int N, L;
int map[MAX + 10][MAX + 10];
int visited[MAX + 10][MAX + 10];

int dr[] = {0, -1, 1, 0, 0}; //상 하 좌 우 //1 2 3 4 
int dc[] = {0, 0, 0, -1, 1}; //상 하 좌 우 

bool IsPossible(int sr, int sc, int er, int ec, int x) { //행, 열, 길 방향

	/*아래와 같은 경우에는 경사로를 놓을 수 없다.

		경사로를 놓은 곳에 또 경사로를 놓는 경우
		낮은 칸과 높은 칸의 높이 차이가 1이 아닌 경우
		낮은 지점의 칸의 높이가 모두 같지 않거나, L개가 연속되지 않은 경우
		경사로를 놓다가 범위를 벗어나는 경우*/

	if (abs(map[sr][sc] - map[er][ec]) > 1) return false;

	int dir = 0;
	int hr = 0; 
	int hc = 0; 
	int lr = 0; 
	int lc = 0;

	//행 방향
	if (x == 1) { 
		if (map[sr][sc] > map[er][ec]) {
			dir = 4; //우
			lr = er; lc = ec;
			hr = sr; hc = sc;
		}
		else if (map[sr][sc] < map[er][ec]) {
			dir = 3; //좌
			lr = sr; lc = sc;
			hr = er; hc = ec;
		}

		for (int l = 1; l <= L; l++) {
			int nr = hr + l * dr[dir];
			int nc = hc + l * dc[dir];

			if (map[nr][nc] != map[lr][lc]) return false;
			if (visited[nr][nc] == 1) return false;
			if ((nr < 1) || (nr > N) || (nc < 1)|| (nc > N)) return false;
		}

		for (int l = 1; l <= L; l++) {
			int nr = hr + l * dr[dir];
			int nc = hc + l * dc[dir];

			visited[nr][nc] = 1;
		}
		return true;
	}
	
	//열 방향
	if (x == 2) {

		if (map[sr][sc] > map[er][ec]) {
			dir = 2; //하
			lr = er; lc = ec;
			hr = sr; hc = sc;
		}
		else if (map[sr][sc] < map[er][ec]) {
			dir = 1; //상
			lr = sr; lc = sc;
			hr = er; hc = ec;
		}

		for (int l = 1; l <= L; l++) {
			int nr = hr + l * dr[dir];
			int nc = hc + l * dc[dir];

			if (map[nr][nc] != map[lr][lc]) return false;
			if (visited[nr][nc] == 1) return false;
			if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) return false;
		}

		for (int l = 1; l <= L; l++) {
			int nr = hr + l * dr[dir];
			int nc = hc + l * dc[dir];

			visited[nr][nc] = 1;
		}
		return true;
	}
}

int Solve(void) {
	int sol = 0;

	memset(visited, 0, sizeof(visited));
	for (int r = 1; r <= N; r++) { //행 방향
		int cnt = 0;
		for (int c = 1; c <= N - 1; c++) {
			if (map[r][c] == map[r][c + 1]) cnt++;
			else if (IsPossible(r, c , r, c + 1, 1)) cnt++;
			else break;
		}
		if (cnt == N - 1) sol++;
	}

	memset(visited, 0, sizeof(visited));
	for (int c = 1; c <= N; c++) { //열 방향
		int cnt = 0;
		for (int r = 1; r <= N - 1; r++) {
			if (map[r][c] == map[r + 1][c]) cnt++;
			else if (IsPossible(r, c, r + 1, c, 2)) cnt++;
			else break;
		}
		if (cnt == N - 1) sol++;
	}

	return sol;
}

void InputData(void) {
	scanf("%d %d", &N, &L);

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
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