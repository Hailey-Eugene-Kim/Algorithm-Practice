#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define INF ((int)2e9)

int N;
int map[20 + 10][20 + 10];
int visited[20 + 10][20 + 10];
int time;  //시간
int sr, sc, ssize; //상어 행, 열, 사이즈
int fishnum, sharkeat;
struct FISH {
	int r, c, size, dist; //물고기 행, 열, 크기, 거리
};
vector <FISH> fish;
vector <FISH> fish2;
struct QUE {
	int r, c, dist;
};
queue <QUE> que;
bool cmp(FISH a, FISH b) { //a 기준
	if (a.dist == b.dist) {
		if (a.r == b.r) {
			return a.c < b.c;
		}
		return a.r < b.r;
	}
	return a.dist < b.dist;
}
int dr[] = { -1, 0, 1, 0 }; //위왼아오
int dc[] = { 0, -1, 0, 1 };
int sol;

void EatFish(void) {
	sort(fish2.begin(), fish2.end(), cmp);

	FISH eat = fish2.front();
	map[eat.r][eat.c] = 0; //빼먹음
	time += eat.dist;
	sr = eat.r;
	sc = eat.c;
	sharkeat++;
	fishnum--;
	//if ((sharkeat >= 1) && (sharkeat % ssize == 0)) { //문제 이해 잘못, 먹은 양 갱신 필요
	if (sharkeat == ssize) { //문제 이해 잘못, 먹은 양 갱신 필요
		ssize++;
		sharkeat = 0;
	}
}

int BFS(int r, int c, int er, int ec) { //상어 위치에서 해당 물고기까지의 거리
	//초기화
	que = {};
	QUE cur = {};
	memset(visited, 0, sizeof(visited));
	//int cnt = 0;

	//처음값
	que.push({ r, c , 0 });
	visited[r][c] = 1;

	//반복
	while (!que.empty()) {
		cur = que.front(); que.pop();

		if ((cur.r == er) && (cur.c == ec)) return cur.dist; //도착하면 종료 //cnt로 실수 //최단 경로로 구하려면?

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue; //범위 밖
			if (visited[nr][nc] == 1) continue; //이미 방문
			if (map[nr][nc] > ssize) continue; //상어보다 큼

			que.push({ nr, nc, cur.dist + 1 });
			visited[nr][nc] = 1;
		}
	}

	return 0; //갈 수 없는 경우
}

void FindFish(void) {
	fish.clear();
	fish2.clear(); //초기화 빼먹음
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if ((map[i][j] != 0) && (map[i][j] < ssize)) fish.push_back({ i, j, map[i][j], 0 }); 
			//0 조건 빼먹음 
			//상어 자기 자신도 안 먹게 해야 함 => 입력에서 
		}
	}
}

int Solve(void) {
	time = 0;
	sharkeat = 0;

	while (fishnum) { //물고기 없으면 종료

		//현재 상어 위치에서 먹을 수 있는 물고기 모두  fish 벡터 저장
		FindFish();

		if (fish.size() == 0) return time; //현재 먹을 수 있는 물고기 없으면 종료 

		for (auto e : fish) { //1마리 이상이면 가장가까운 물고기 탐색
			int d = BFS(sr, sc, e.r, e.c); //현재 상어 위치에서 물고기 위치까지 거리, dist값 갱신
			if (d == 0) continue;
			fish2.push_back({ e.r, e.c, e.size, d });
		}
		if (fish2.empty()) return time; //먹을 수 있는데 모두 갈 수 없는 경우

		EatFish(); //조건에 맞는 물고기 먹음, 상어값 갱신, time 갱신
	}

	return time;
}

void InputData(void) {
	scanf("%d", &N);
	fishnum = 0;
	memset(map, 0, sizeof(map));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				sr = i;
				sc = j;
				ssize = 2;
				map[i][j] = 0; //자기 자신을 갱신해줘야 FindFish, BFS에서 조건에 안 걸림
			}

			if ((map[i][j] != 0) && (map[i][j] != 9)) fishnum++;
		}
	}
}

int main(void) {

	InputData();
	int ans = Solve();
	printf("%d", ans);

	return 0;
}
