#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAX (20)
#define INF ((int)2e9)

int n, m, k;
int map[MAX + 10][MAX + 10]; //사람 갱신
int visited[MAX + 10][MAX + 10]; 
struct INFO {
	int r, c;
};
deque <INFO> train[5 + 5]; //열차 정보, 맨 앞이 사람 //1베이스
int tidx;
deque <INFO> change; //열차 정보, 맨 앞이 사람
int peoplenum[5 + 5]; //각 열차에 포함된 사람 수

int BR, BC, BD; //공 시작 행, 열, 방향

int dr[] = {0, 0, -1, 0, 1}; //오 위 왼 아
int dc[] = {0, 1, 0, -1, 0};

int score;

void FloodFill(int r, int c) {

	if ((r < 1) || (r > n) || (c < 1) || (c > n)) return;
	if (map[r][c] == 0) return;
	if (visited[r][c] == tidx) return;

	visited[r][c] = tidx;
	train[tidx].push_back({ r, c });

	for (int k = 1; k <= 4; k++) {
		int nr = r + dr[k];
		int nc = c + dc[k];

		if ((nr < 1) || (nr > n) || (nc < 1) || (nc > n)) continue; //범위
		if (map[nr][nc] == 0) continue; // 선이 아님
		if (visited[nr][nc] == tidx) continue; // 이미 방문

		FloodFill(nr, nc);
	}
}

void SetTeam(void) { //train[tidx] 총 m개 완성 , peoplenum 구하기
	
	//초기화
	for (int i = 1; i <= m; i++) {
		train[m].clear();
	}
	memset(peoplenum, 0, sizeof(peoplenum));

	//기차 덱 구하기
	memset(visited, -1, sizeof(visited));
	tidx = 0;
	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {

			if (visited[r][c] == tidx) continue;

			if (map[r][c] == 1) { //꼬리칸이면 확산
				tidx++;
				FloodFill(r, c);
			}
		}
	}

	for (int i = 1; i <= m; i++) {

		//기차 방향 바로 잡기
		if (map[train[i].back().r][train[i].back().c] == 2) {
			change.clear();
			change.push_back(train[i].front()); train[i].pop_front();
			int P = train[i].size();
			for (int p = P - 1; p >= 0; p--) {
				change.push_back(train[i][p]);
			}
			train[i] = change;
		}

		//사람 수
		int cnt = 0; 
		int P = train[i].size();
		for (int p = 0; p < P; p++) {
			if (map[train[i][p].r][train[i][p].c] == 4) break;
			cnt++;
		}
		peoplenum[i] = cnt;
		
	}
}

void MovePeople(void) {

	for (int i = 1; i <= m; i++) {
		//train 갱신
		INFO move = train[i].back(); train[i].pop_back();
		train[i].push_front(move);

		//map 갱신
		map[train[i][0].r][train[i][0].c] = 1;

		if (peoplenum[i] >= 3) { //조건 넣긴 했지만 어차피 문제 조건이 3명 이상..
			for (int p = 1; p <= peoplenum[i] - 2; p++) {
				map[train[i][p].r][train[i][p].c] = 2;
			}
		}

		map[train[i][peoplenum[i] - 1].r][train[i][peoplenum[i] - 1].c] = 3; 

		if (train[i].size() > peoplenum[i]) {
			map[train[i][peoplenum[i]].r][train[i][peoplenum[i]].c] = 4;//기존 꼬리 제거
		}
	}

}

void ThrowBall(int round) { //BR, BC, BR 설정

	if (round == 1) return;
	else if (round % n == 1) BD++;
	else if ((2 <= round) && (round <= n)) BR++;
	else if ((n + 2 <= round) && (round <= 2 * n)) BC++;
	else if ((2 * n + 2 <= round) && (round <= 3 * n)) BR--;
	else if ((3 * n + 2 <= round) && (round <= 4 * n)) BC--;

}

void GetScore(void) {
	//공 (BR, BC)에서 BD 방향으로 n만큼 이동 
		//map에서 사람 만나면 break , score

	int SR = 0;
	int SC = 0;

	for (int i = 0; i < n; i++) { // 첫 번째로 만나는 사람 좌표
		int nbr = BR + i * dr[BD];
		int nbc = BC + i * dc[BD];

		if ((map[nbr][nbc] == 1)|| (map[nbr][nbc] == 2) || (map[nbr][nbc] == 3)){
			SR = nbr;
			SC = nbc;
			break;
		}
	}

	if ((SR == 0) || (SC == 0)) return; //만나는 사람 없음
	
	//점수 획득
	int Sidx = visited[SR][SC];
	int P = train[Sidx].size();

	for (int p = 0; p < P; p++) {
		if ((train[Sidx][p].r == SR) && (train[Sidx][p].c == SC)) {
			score += (p + 1) * (p + 1);
			break;
		}
	}

	//기차 방향 변경
	change.clear();
	for (int p = peoplenum[Sidx] - 1; p >= 0; p--) {
		change.push_back(train[Sidx][p]);
	}
	for (int p = P - 1; p >= peoplenum[Sidx]; p--) {
		change.push_back(train[Sidx][p]);
	}
	train[Sidx] = change;

	map[train[Sidx][0].r][train[Sidx][0].c] = 1;
	map[train[Sidx][peoplenum[Sidx] - 1].r][train[Sidx][peoplenum[Sidx] - 1].c] = 3;
}

int Solve(void) {
	score = 0;

	SetTeam();
	BR = 1; BC = 1; BD = 1; //공 초기 : (1, 1), 오

	for (int i = 1; i <= k; i++) {
		MovePeople();
		ThrowBall(i);
		GetScore();
	}

	return score;
}

void InputData(void) {
	scanf("%d %d %d", &n, &m, &k);

	memset(map, 0, sizeof(map));
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
