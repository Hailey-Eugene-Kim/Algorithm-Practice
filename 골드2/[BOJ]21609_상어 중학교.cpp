#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAXN (20)
#define INF ((int)2e9)

//일반블록 방문, 무지개블록 방문 따로
//해당 그룹 블록 모음 따로 => 벡터 벡터

int N, M;
int map[MAXN + 10][MAXN + 10];
int visited[MAXN + 10][MAXN + 10];
int visitedrb[MAXN + 10][MAXN + 10]; //무지개 방문 분리
int dr[] = { 0, 1, 0, -1 }; //동남서북
int dc[] = { 1, 0, -1, 0 }; //동남서북
struct QUE {
	int r, c; // cnt 무지개 포함
};
queue <QUE> que;
vector <QUE> blocksum;
vector<vector<QUE>> grpblock; //삭제할 블록 모음
struct GROUP {
	int color, rainbow, grpidx, r, c, block; //색, 무지개수 , 그룹 번호, 기준 행, 기준 열, 전체 블록
};
vector <GROUP> group;
int grpidx = 0;
int stdR, stdC;
int rainbow;

bool cmp(GROUP a, GROUP b) { 
	if (a.block == b.block) {
		if (a.rainbow == b.rainbow) {
			if (a.r == b.r) {
				return a.c > b.c;
			}
			return a.r > b.r;
		}
		return a.rainbow > b.rainbow;
	}
	return a.block > b.block;
}
int block;

void BFS(int r, int c, int color) {
	//초기화
	que = {};
	memset(visitedrb, 0, sizeof(visitedrb));
	blocksum.clear();

	//처음값
	que.push({ r, c});
	visited[r][c] = 1;
	blocksum.push_back({ r, c });
	block++;

	//반복
	while (!que.empty()) {
		QUE cur = que.front(); que.pop();
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue; //범위
			if (visited[nr][nc] == 1) continue; //이미 방문
			if (visitedrb[nr][nc] == 1) continue; //이미 방문
			if (map[nr][nc] > M) continue; //이미 삭제
			if ((map[nr][nc] == color) || (map[nr][nc] == 0)) {

				if (map[nr][nc] == 0) { //무지개
					rainbow++; //map 조건 따져준 후 갱신
					visitedrb[nr][nc] = 1;
				}
				else { //일반블록
					if (stdR > nr) {
						stdR = nr;
						stdC = nc;
					}
					else if ((stdR == nr) && (stdC > nc)) stdC = nc;

					visited[nr][nc] = 1;
				}

				block++; //전체 블록 수 => 나중에 점수에 이용
				que.push({ nr, nc });
				blocksum.push_back({ nr, nc });//전체 블록 쌓기
			}
		}
	}
}

void FindBlock(void) {
	//1. 크기가 가장 큰 블록 그룹
	//FloodFill 결과 각 그룹 vector에 저장
		//행열 기준블록 : 무지개 X, 작은행, 작은열 
			//확산: N ~ 1 방향, 서남동북 방향
			//무지개 x ->stR, stC 조건에 맞으면 계속 갱신, 마지막 값이 조건 충족 => BFS
	//그룹 vector 정렬 (무지개 cnt, 행 내림, 열 내림) / 유니크 idx, 전체 cnt

	int color = 0;
	grpidx = 0;
	memset(visited, 0, sizeof(visited));
	grpblock.clear();
	group.clear();
	blocksum.clear();

	while (color <= M) {
		color++;
		for (int i = N; i >= 1; i--) {
			for (int j = N; j >= 1; j--) {
				if (visited[i][j] == 1) continue;
				if (map[i][j] > M) continue; //삭제 후 빈 칸
				if (map[i][j] == color) {
					stdR = i;
					stdC = j;
					rainbow = 0;
					block = 0;

					BFS(i, j, color);

					if (block >= 2) {
						group.push_back({ color, rainbow, grpidx, stdR, stdC, block }); //grpidx = grpblock벡터 번호
						grpblock.push_back(blocksum); //쌓은 블록 저장
						grpidx++;
					}
				}
			}
		}
	}
}

void RemoveBlock(void) { //visited 그룹 컬러인 것
	sort(group.begin(), group.end(), cmp);

	int dl = group[0].grpidx;
	while (!grpblock[dl].empty()) {
		QUE tmp = grpblock[dl].back(); grpblock[dl].pop_back();
		//map[tmp.r][tmp.c] += (M + 1); //삭제 처리
		map[tmp.r][tmp.c] = (M + 1); //삭제 처리
	}
}

void Gravity(void) {
	//3. 중력 작용 -1(검정) 제외
	//제거할 때 최소 최대 행, 열 번호 저장 
	//for 루프 최소열~최대열 -> 최소행 -1 ~ 최대행  
	//제거한 값 나오면 -1행, 검정(-1) 제외하고 해당값 삭제
	//제거 아닌 값 만나면 -1행에 입력 

	for (int j = N; j >= 1; j--) {
		int vacant = 0;
		for (int i = N; i >= 1; i--) {
			//if (map[i][j] == M + 1) vacant++;
			if (map[i][j] == -1 ) vacant = 0;
			if (map[i][j] > M ) vacant++;
			if ((vacant > 0) && (map[i][j] <= M) && (map[i][j] != -1)) {
				map[i + vacant][j] = map[i][j]; //블록 내리기
				map[i][j] = (M + 1);
			}
		}
	}
}

void Rotate(void) {
	int map_c[MAXN + 10][MAXN + 10];
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map_c[N + 1 - j][i] = map[i][j];
		}
	}
	memcpy(map, map_c, sizeof(map_c));
}

int Solve(void) {
	int sol = 0;

	//블록그룹 존재하는 동안 반복 //=> map 훼손되면 안 됨 => visited에 갱신
	for (;;) {
		FindBlock(); //가장 큰 블록 그룹 찾기
		if (group.empty()) break; //블록 그룹 없으면 종료
		RemoveBlock();
		int score = group[0].block * group[0].block;
		sol += score;
		Gravity(); //중력, 인자 : 행열범위
		Rotate(); //90도 반시계 회전 //map, 지도 모두 회전
		Gravity();
	}

	return sol;
}

void InputData(void) {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]); //-1 검정, 0 무지개, 1~M 색상
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}