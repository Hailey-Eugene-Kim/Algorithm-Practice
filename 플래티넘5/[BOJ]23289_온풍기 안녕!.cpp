#include <iostream>
#include <cstring>
#include <deque>
#include <queue>
using namespace std;
#define MAX 20
#define INF ((int)2e9)

int R, C, K;
int W;
int map[MAX + 10][MAX + 10]; //온풍기, 조사칸 정보
int temp[MAX + 10][MAX + 10]; //온도 
int moderate[MAX + 10][MAX + 10]; //차이 조정 저장
deque <int> wall[MAX + 10][MAX + 10]; //벽 확인

struct INFO {
	int r, c, dir;
};
deque <INFO> warm; //온풍기 정보
deque <INFO> inspect; //조사해야하는 칸
struct SPD{
	int n, idx; //온도, 온풍기 번호
};
deque <SPD> spread[MAX + 10][MAX + 10];
struct QUE {
	int k, r, c; //온도, 행, 열
};
queue <QUE> que; //확산 BFS용
int dr[] = {0, 0, 0, -1, 1}; //오 왼 위 아 1 2 3 4
int dc[] = {0, 1, -1, 0, 0}; 

void CalSpread2(int w, int wdir, int ck, int cr, int cc, int middir) { //CalSpread에 중간 방향 추가

	int mr = cr + dr[middir]; //중간 좌표
	int mc = cc + dc[middir];

	int nr2 = mr + dr[wdir]; //최종 좌표
	int nc2 = mc + dc[wdir];

	if ((nr2 < 1) || (nr2 > R) || (nc2 < 1) || (nc2 > C)) return; //범위 조건

	int flag = 0;
	for (auto e : wall[cr][cc]) { //벽 조건 1
		if (e == middir) {
			flag++;
			break;
		}
	}
	
	for (auto e : wall[mr][mc]) { //벽 조건 2
		if (e == wdir) {
			flag++;
			break;
		}
	}

	for (auto e : spread[nr2][nc2]) { //같은 온풍기 중복 확인
		if (e.idx == w) {
			flag++;
			break;
		}
	}

	if (!flag) {

		que.push({ ck - 1, nr2, nc2 }); 
		spread[nr2][nc2].push_back({ ck - 1, w });
	}

}

void CalSpread (int w, int wdir, int ck, int cr, int cc) { 
	
	//1. 정방향 확산 

	int nr = cr + dr[wdir];
	int nc = cc + dc[wdir];
	int nr2, nr3, nc2, nc3;

	if ((nr < 1) || (nr > R) || (nc < 1) || (nc > C)) return; //범위 조건

	int flag = 0;
	for (auto e : wall[cr][cc]) { //벽 조건
		if (e == wdir) {
			flag++;
			break;
		}
	}

	for (auto e : spread[nr][nc]) { //중복 조건
		if (e.idx == w) {
			flag++;
			break;
		}
	}
	if (!flag) {
		que.push({ ck - 1, nr, nc });
		spread[nr][nc].push_back({ ck - 1, w });
	}
	

	if ((wdir == 1) || (wdir == 2)) { //2. wdir : 오 왼 -> 위 아 확산

		CalSpread2(w, wdir, ck, cr, cc, 3); //위
		CalSpread2(w, wdir, ck, cr, cc, 4); //아
	}


	else if ((wdir == 3) || (wdir == 4)) { //2. wdir : 위 아 -> 위 아 확산

		CalSpread2(w, wdir, ck, cr, cc, 1); //오
		CalSpread2(w, wdir, ck, cr, cc, 2); //왼
	}
}


void WarmAir(void) {
	//warm 루프
		//각 warm BFS
			//spread에 n 저장
			//idx 같으면 가지치기, 다르면 ok
	//temp에 += spread[][] 모든 요소

	//spread 초기화
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			spread[r][c].clear();
		}
	}
	
	//각 warm BFS
	int Warm = warm.size();
	for (int w = 0; w < Warm; w++) { //e.dir : 온풍기 방향

		//초기화
		que = {};

		//처음값
		int wdir = warm[w].dir; //전체 확산 방향
		int fr = warm[w].r + dr[wdir];
		int fc = warm[w].c + dc[wdir];
		que.push({ 5, fr, fc }); //온도 행 열
		spread[fr][fc].push_back({ 5, w }); //온도 온풍기번호

		//확산
		while (!que.empty()) {
			QUE cur = que.front(); que.pop();

			if (cur.k == 1) continue; //확산 중지

			CalSpread(w, wdir, cur.k, cur.r, cur.c);
			
		}

	}

	//temp에 += spread[][] 모든 요소
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			for (auto e : spread[r][c]) {
				temp[r][c] += e.n;
			}
		}
	}

}

void ModerateTemp(void) { //전체 구하고  / 2 값 추가 (양방향 모두 고려되므로)

	memset(moderate, 0, sizeof(moderate));
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			for (int k = 1; k <= 4; k++) {
				int nr = r + dr[k];
				int nc = c + dc[k];

				if ((nr < 1) || (nr > R) || (nc < 1) || (nc > C)) continue; //범위 조건

				int flag = 0;
				for (auto e : wall[r][c]) { //벽 조건 //(r, c)에서 k 방향 (nr, nc)으로 벽 있는 경우
					if (e == k) {
						flag++;
						break;
					}
				}
				if (flag) continue;

				moderate[r][c] += (temp[nr][nc] - temp[r][c]) / 4;
			}
		}
	}

	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			temp[r][c] += moderate[r][c]; //온도 조절
			if (((r == R) || (r == 1) || (c == C) || (c == 1)) && (temp[r][c] > 0)) temp[r][c]--; // 가장자리 감소
		}
	}

}

bool InspectTemp(void) {
	int cnt = 0;

	for (auto e : inspect) {
		if (temp[e.r][e.c] >= K) cnt++;
	}

	if (cnt == inspect.size()) return true;
	return false;
}

int Solve(void) {

	//집에 있는 모든 온풍기에서 바람이 한 번 나옴
		//온도가 조절됨
		//온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
		//초콜릿을 하나 먹는다.
		//조사하는 모든 칸의 온도가 K 이상이 되었는지 검사.모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.

	int choco = 0;
	for (;;) {
		//집에 있는 모든 온풍기에서 바람이 한 번 나옴
		WarmAir();
		//온도가 조절됨
		//온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
		ModerateTemp();
		//초콜릿을 하나 먹는다.
		choco++;
		if (choco > 100) return 101;
		//조사하는 모든 칸의 온도가 K 이상이 되었는지 검사.모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
		if (InspectTemp()) break;
	}

	return choco;
}

void InputData(void) {
	memset(map, 0, sizeof(map));
	memset(temp, 0, sizeof(temp));

	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			wall[r][c].clear();
		}
	}

	scanf("%d %d %d", &R, &C, &K);
	
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			scanf("%d", &map[r][c]);

			if (map[r][c] == 5) inspect.push_back({ r, c, 0 });
			if ((1 <= map[r][c]) && (map[r][c] <= 4)) warm.push_back({ r, c, map[r][c] }); //행, 열, 방향
		}
	}

	int x, y, t;
	scanf("%d", &W);
	for (int w = 0; w < W; w++) {
		scanf("%d %d %d", &x, &y, &t);
		if (t == 0) { //위
			wall[x][y].push_back(3);
			wall[x - 1][y].push_back(4);
		}
		else if (t == 1) { //오
			wall[x][y].push_back(1);
			wall[x][y + 1].push_back(2);
		}
	}

}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}