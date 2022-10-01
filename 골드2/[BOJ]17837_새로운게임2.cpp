#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
using namespace std;
#define MAXN (12)

int N, K;
int map[MAXN + 10][MAXN + 10]; //0흰 1빨 2파
struct HORSE {
	int num, dir;
};
deque <HORSE> pos[MAXN + 10][MAXN + 10];
deque <HORSE> newhorse; //이동하는 말
struct INFO {
	int r, c, dir;
};
vector <INFO> horse;
int turn;
int numcheck = 0; //4개 이상 체크
int dr[] = { 0, 0, 0, -1, 1 }; //오 왼 위 아 //1베이스
int dc[] = { 0, 1, -1, 0, 0 };

void CheckChess(int hnum, int cr, int cc, int cdir, int nr, int nc) {

	if ((map[nr][nc] == 2) || ((nr < 1) || (nr > N) || (nc < 1) || (nc > N))) { //파 //범위 밖 //이 조건 먼저
		//ndir - nnr, nnc 구하기
		//if 파 or 범위 밖 -> 그대로, 방향 반대로 갱신 return
		//else CheckChess 보내기

		int ndir;
		if (cdir == 1) ndir = 2;
		if (cdir == 2) ndir = 1;
		if (cdir == 3) ndir = 4;
		if (cdir == 4) ndir = 3;

		int nnr = cr + dr[ndir];
		int nnc = cc + dc[ndir];

		int I = pos[cr][cc].size();
		for (int i = 0; i < I; i++) {
			if (pos[cr][cc][i].num == hnum) { //hnum말만 변경, 위에 있는 말은 x
				pos[cr][cc][i].dir = ndir; 
				horse[pos[cr][cc][i].num].dir = ndir;
				break;
			}
		}

		if ((map[nnr][nnc] == 2) || ((nnr < 1) || (nnr > N) || (nnc < 1) || (nnc > N))) return;

		CheckChess(hnum, cr, cc, ndir, nnr, nnc);
	}

	else if (map[nr][nc] == 0) { //흰

		//newhorse에 이동하는 말 저장
		//pos[cr][cc] 이동하는 말 삭제
		//pos[nr][nc] 이동하는 말 입력
		//horse 값 갱신

		int flag = 0;
		newhorse.clear();
		int I = pos[cr][cc].size();
		for (int i = 0; i < I; i++) {
			if (pos[cr][cc][i].num == hnum) flag++;
			if (flag > 0) newhorse.push_back(pos[cr][cc][i]); //이동하는 말 저장 //순서대로
		}

		int flag2 = 0;
		for (int i = I - 1; i >= 0; i--) { //뒤부터 삭제
			if (pos[cr][cc][i].num == hnum) flag2++;
			pos[cr][cc].pop_back();
			if (flag2 > 0) break;
		}

		int J = newhorse.size();
		for (int j = 0; j < J; j++) {
			pos[nr][nc].push_back(newhorse[j]);
			//horse[newhorse[j].num] = { nr, nc, cdir };
			horse[newhorse[j].num].r = nr;
			horse[newhorse[j].num].c = nc;
		}
		if (pos[nr][nc].size() >= 4) numcheck++;
	}

	else if (map[nr][nc] == 1) { //빨
		int flag = 0;
		newhorse.clear();
		int I = pos[cr][cc].size();
		for (int i = 0; i < I; i++) {
			if (pos[cr][cc][i].num == hnum) flag++;
			if (flag > 0) newhorse.push_front(pos[cr][cc][i]); //이동하는 말 저장 //역순대로
		}

		int flag2 = 0;
		for (int i = I - 1; i >= 0; i--) { //뒤부터 삭제
			if (pos[cr][cc][i].num == hnum) flag2++;
			pos[cr][cc].pop_back();
			if (flag2 > 0) break;
		}

		int J = newhorse.size();
		for (int j = 0; j < J; j++) {
			pos[nr][nc].push_back(newhorse[j]);
			//horse[newhorse[j].num] = { nr, nc, cdir };
			horse[newhorse[j].num].r = nr;
			horse[newhorse[j].num].c = nc;
		}

		if (pos[nr][nc].size() >= 4) numcheck++;
	}
}

int Solve(void) {
	turn = 0;

	for (;;) {
		turn++;
		if (turn > 1000) return -1;

		int h;
		int H = horse.size();
		for (h = 0; h < H; h++) { //각 말 이동, pos에 쌓기, 기존 pos 삭제
			int cr = horse[h].r;
			int cc = horse[h].c;
			int cdir = horse[h].dir;

			int nr = cr + dr[cdir];
			int nc = cc + dc[cdir];

			CheckChess(h, cr, cc, cdir, nr, nc);
			if (numcheck > 0) return turn; //4개 이상
		}
	}

}

void InputData(void) {
	scanf("%d %d", &N, &K);

	for (int i = 1; i <= N; i++) { //지도 1 베이스
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	int hr, hc, hdir;
	for (int k = 0; k < K; k++) { //말 0 베이스
		scanf("%d %d %d", &hr, &hc, &hdir);
		horse.push_back({ hr, hc, hdir });
		pos[hr][hc].push_back({ k, hdir }); //말 번호, 방향
	}
}

int main(void) {

	InputData();
	int ans = Solve();
	printf("%d", ans);

	return 0;
}