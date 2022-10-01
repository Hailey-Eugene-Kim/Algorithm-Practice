#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAXN (20)

int N, M;
int map[MAXN + 10][MAXN + 10];
int visited[MAXN + 10][MAXN + 10];
int visited2[MAXN + 10][MAXN + 10];
long long int fuel;
int tR, tC;
struct POS {
	int sr, sc, er, ec;
};
vector <POS> people;
int dist = 0; //승객 운행 거리
struct QUE {
	int r, c, d; //행, 열 거리
};
queue <QUE> que;
queue <QUE> que2;
int dr[] = { -1, 0, 0, 1 }; //위 왼 오 아
int dc[] = { 0, -1, 1, 0 };

struct PERSON {
	int num, r, c, d;
};
vector <PERSON> selectP; //승객 최단거리 비교
bool cmp(PERSON a, PERSON b) {
	if (a.d == b.d) {
		if (a.r == b.r) {
			return a.c < b.c;
		}
		return a.r < b.r;
	}
	return a.d < b.d;
}

int FindPerson(void) { //최단거리 택시 번호 //map[][] - 2 //여러명 -> dr dc 우선순위

	//택시 위치에 승객 있는 경우
	if (map[tR][tC] >= 2) return map[tR][tC] - 2;

	//초기화
	memset(visited, 0, sizeof(visited));
	que = {};
	selectP.clear();

	//처음값
	que.push({ tR, tC, 0 });
	visited[tR][tC] = 1;
	//fuel--; 

	//반복
	while (!que.empty()) {
		QUE cur = que.front(); que.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			int nd = cur.d + 1;

			if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue;
			if (map[nr][nc] == 1) continue;
			if (visited[nr][nc] == 1) continue;
			if (map[nr][nc] >= 2) {
				visited[nr][nc] = 1;
				selectP.push_back({ map[nr][nc] - 2 , nr, nc, nd });
				continue;
			}

			que.push({ nr, nc, nd });
			visited[nr][nc] = 1;
			
		}
	}

	if (selectP.size() == 0) return -1; //승객 찾을 수 없는 경우

	sort(selectP.begin(), selectP.end(), cmp);
	fuel -= selectP[0].d;
	return selectP[0].num;
}

int TaxiMove(int num) { //승객 운행  //que2 인자에 d

	//최단거리 : fuel, dist
	//승객 map 삭제

	int sr = people[num].sr;
	int sc = people[num].sc;
	int er = people[num].er;
	int ec = people[num].ec;

	//초기화
	memset(visited2, 0, sizeof(visited2));
	que2 = {};
	//dist = 0;

	//처음값
	que2.push({ sr, sc, 0 });
	visited2[sr][sc] = 1;

	//반복
	while (!que2.empty()) {
		QUE cur = que2.front(); que2.pop();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			int nd = cur.d + 1;

			if ((nr == er) && (nc == ec)) {

				//목적지 도착
				map[sr][sc] = 0; //지도에서 승객 삭제
				tR = er; //택시 위치 갱신
				tC = ec;

				fuel -= nd;
				dist = nd;
				return 1;
			}
			if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue;
			//if (map[nr][nc] == 1) continue;
			if (map[nr][nc] >= 1) continue;
			if (visited2[nr][nc] == 1) continue;

			que2.push({ nr, nc, nd });
			visited2[nr][nc] = 1;
		}
	}
	return -1; //도착할 수 없는 경우
}

long long int Solve(void) {
	for (;;) {
		int num = FindPerson();
		if (num == -1) return -1;
		if (fuel <= 0) return -1;

		dist = 0;
		int move = TaxiMove(num);
		if (move == -1) return -1;
		if (fuel < 0) return -1;
		fuel += dist * 2;
		M--;
		if (M == 0) return fuel;
	}
}

void InputData(void) {
	scanf("%d %d %lld", &N, &M, &fuel);
	memset(map, 0, sizeof(map));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	scanf("%d %d", &tR, &tC);

	int a, b, c, d;
	people.clear();
	for (int m = 0; m < M; m++) { //승객 0베이스
		scanf("%d %d %d %d", &a, &b, &c, &d);
		people.push_back({ a, b, c, d });
		map[a][b] = m + 2;
	}
}

int main(void) {
	InputData();
	long long int ans = Solve();
	printf("%lld", ans);

	return 0;
}