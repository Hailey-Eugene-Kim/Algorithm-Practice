#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
#define MAXN (100)

int R, C, M;
int map[MAXN + 10][MAXN + 10];
int mapmove[MAXN + 10][MAXN + 10];
struct SHARK {
	int r, c, s, d, z;
};
vector <SHARK> shark;
int KC;
int score;
int dr[] = { 0, -1, 1, 0, 0 }; //위 아 오 왼
int dc[] = { 0, 0, 0, 1, -1 }; //위 아 오 왼

int Scnt;

void CatchShark(int KC) {
	for (int i = 1; i <= R; i++) {
		if (map[i][KC] != -1) {
			int Snum = map[i][KC]; //상어 번호
			score += shark[Snum].z; //score + 상어 크기

			map[i][KC] = -1;//상어 삭제
			shark[Snum].r = 0; //실수 : shark에서 안 지움
			shark[Snum].c = 0;

			Scnt--;

			break;
		}
	}
}

int OutRangeFirst(int np, int m) { //1 미만 //위 왼 //방향 바꾸고, 한 칸 이동 //nr 리턴

	if (shark[m].d == 1) shark[m].d = 2;
	else if (shark[m].d == 4) shark[m].d = 3;

	return np + 2;
}

int OutRangeSecond(int np, int m) { // 범위 초과 //아 오

	if (shark[m].d == 2) shark[m].d = 1;
	else if (shark[m].d == 3) shark[m].d = 4;

	return np - 2;
}

void SharkMove(void) { //기존 벡터 //이동한 후 벡터 구분 필요
	memset(mapmove, -1, sizeof(mapmove));

	for (int m = 0; m < M; m++) {

		if (shark[m].r == 0) continue; //실수 : 삭제 상어 반영 안 함

		int sr = shark[m].r;
		int sc = shark[m].c;
		int ss = shark[m].s;
		int sd = shark[m].d;
		int sz = shark[m].z;

		map[sr][sc] = -1; //실수 : 기존 위치 삭제 누락 
		//mapmove[sr][sc].clear(); //실수 : 초기화 위치 => 이렇게 되면 새로운 위치값 삭제될 수 있음

		int nr = sr;
		int nc = sc;
		int ns;

//시간초과 해결: 속력 처리
		if ((sd == 1) || (sd == 2)) ns = ss % (2 * (R - 1)); //제자리로 돌아오는 경우 전부 제거
		else if ((sd == 3) || (sd == 4)) ns = ss % (2 * (C - 1));

		for (int i = 1; i <= ns; i++) {
			nr = nr + dr[shark[m].d];
			nc = nc + dc[shark[m].d];

			if (nr < 1) nr = OutRangeFirst(nr, m); //방향 바꾸고, 한 칸 이동
			if (nr > R) nr = OutRangeSecond(nr, m);
			if (nc < 1) nc = OutRangeFirst(nc, m);
			if (nc > C) nc = OutRangeSecond(nc, m);
		}

		if (mapmove[nr][nc] != -1) { //두 마리 이상
			if (shark[mapmove[nr][nc]].z < sz) { //맵에 있던 상어가 먹힘
				shark[mapmove[nr][nc]].r = 0;
				shark[mapmove[nr][nc]].c = 0;

				mapmove[nr][nc] = m;

				shark[m].r = nr;
				shark[m].c = nc;
			}
			else { //m 상어가 먹힘
				shark[m].r = 0;
				shark[m].c = 0;
			}
		}

		else { //한 마리
			mapmove[nr][nc] = m;
			shark[m].r = nr;
			shark[m].c = nc;
		}
	}

	//벡터 복사 //시간초과
	/*for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			map[r][c] = mapmove[r][c];
			mapmove[r][c].clear();
		}
	}*/

	//for (int m = 0; m < M; m++) { //이것도 시간초과 => 없애는 방법 : 배열로 바꿔서 memcpy사용 or index 사용해서 안 섞이게
	//	if (shark[m].r == 0) continue;
	//	map[shark[m].r][shark[m].c].push_back(m);
	//	mapmove[shark[m].r][shark[m].c].clear();
	//}

	memcpy(map, mapmove, sizeof(mapmove));
}

int Solve(void) {
	score = 0;
	KC = 0;
	Scnt = M;

	for (;;) {
		KC++; //열 이동
		if (KC == C + 1) break;
		CatchShark(KC);
		if (Scnt == 0) break;
		SharkMove();
	}

	return score;
}

void InputData(void) {
	scanf("%d %d %d", &R, &C, &M);

	memset(map, -1, sizeof(map));
	int a, b, c, d, e;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
		shark.push_back({ a, b, c, d, e }); //상어 0 베이스
		map[a][b] = i; //0번 상어가 있으므로 빈 부분 : -1
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}