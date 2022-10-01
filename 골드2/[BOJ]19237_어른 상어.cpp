#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 20

int N, M, k;
int map[MAXN + 10][MAXN + 10];
//int smell[MAXN + 10][MAXN + 10]; //상어 죽어도 감소
int dr[] = {0, -1, 1, 0, 0}; // 1 2 3 4 위 아 왼 오
int dc[] = {0, 0, 0, -1, 1};
int SharkNum;
int time;

struct DIR {
	int num, r, c, dir; //상어 번호, 행, 열, 방향
};
vector <DIR> shark; //상어 위치 //0 베이스
vector <int> sharkmove[MAXN + 10][MAXN + 10]; //상어 이동 위치
vector <DIR> spread; //이번 회차 상어 냄새
vector <int> priority[MAXN * MAXN + 10][4 + 10]; //상어 방향 우선순위 //상어 0 베이스 //방향 0 베이스
vector <int> multi;
struct SMELL {
	int shark, num; //상어 번호, 남은 향
};
vector <SMELL> smell[MAXN + 10][MAXN + 10];

bool cmp (DIR a, DIR b) { //오름차순
	return a.num < b.num;
}

void Move(void) {
	for (int m = 0; m < M; m++) {
		sharkmove[shark[m].r][shark[m].c].clear(); //기존 위치 삭제
	}

	for (int m = 0; m < M; m++) { //shark 갱신, move 이동, 기존 move 제거
		//sharkmove, shark
		
		if (shark[m].dir == 0) continue; //삭제된 상어

		//ndir 찾기
		int ndir = shark[m].dir;
		int nr, nc;
		multi.clear();
		for (int i = 1; i <= 4; i++) { //인접 빈 칸
			nr = shark[m].r + dr[i];
			nc = shark[m].c + dc[i];

			if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue; //범위 N인데 예시 5로 실수

			if (smell[nr][nc].size() == 0) {
				ndir = i;
				multi.push_back(i);
			}
		}

		if (multi.size() == 0) { //인접 빈 칸 없는 경우
			for (int i = 1; i <= 4; i++) {
				nr = shark[m].r + dr[i];
				nc = shark[m].c + dc[i];

				if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue;

				if (smell[nr][nc][0].shark == m) {
					ndir = i; //smell에 상어 번호 저장으로 변경
					multi.push_back(i);
				}
			}
		}

		if (multi.size() > 1) { //여러개인 경우 우선순위
			for (auto p : priority[m][shark[m].dir]) { 
				for (auto e : multi) { //방향 복수
					if (p == e) {
						ndir = e;
						multi.clear();
						break; //실수 : for루프 하나만 탈출
					}
				}
				if (multi.size() == 0) break;
			}
		}
	

		//sharkmove 갱신
		//shark 갱신
		nr = shark[m].r + dr[ndir];
		nc = shark[m].c + dc[ndir];

		//sharkmove[shark[m].r][shark[m].c].clear(); //기존 위치 삭제 여기서 초기화 시키면 다른 상어 새로운 값 사라짐
		sharkmove[nr][nc].push_back(m); //새 위치 저장
		
		shark[m] = { m, nr, nc, ndir };
	}
}

void SmellReduce(void) {

	for (int i = 1; i <= N; i++) { //smell 감소
		for (int j = 1; j <= N; j++) {
			if (smell[i][j].size() >= 1) {
				smell[i][j][0].num--;
				if (smell[i][j][0].num == 0) smell[i][j].clear();
			}
		}
	}
}

void Spread(void) {

	for (int i = 1; i <= N; i++) { //move에 저장된 상어 향 smell에 입력, 중복 상어 제거 SharkNum--;
		for (int j = 1; j <= N; j++) {

			if (sharkmove[i][j].size() == 0) continue;

			if (sharkmove[i][j].size() > 1) {
				sort(sharkmove[i][j].begin(), sharkmove[i][j].end()); //오름차순 정렬
				//while (!sharkmove[i][j].size() == 1)) { //이렇게 하면 0도 걸림
				while (sharkmove[i][j].size() > 1) {
					shark[sharkmove[i][j].back()] = { 0, 0, 0, 0 }; //1마리 남을 때까지 삭제
					sharkmove[i][j].pop_back(); 
					SharkNum--;
				}
			}

			if (smell[i][j].size() > 0) smell[i][j][0] = { sharkmove[i][j][0], k }; //상어 있는 칸 향 확산 //기존 향 사라짐
			else smell[i][j].push_back({ sharkmove[i][j][0], k }); //상어 있는 칸 향 확산 
		}
	}
}

int Solve(void) { //1번 상어만 격자에 남게되는 시간
	
	//초기 Spread
	for (auto e : shark) {
		smell[e.r][e.c].push_back({ e.num, k }); //상어 향 확산
	}

	time = 0;
	for (;;) {
		time++;
		Move(); //이동
		SmellReduce(); //기존 향 감소
		Spread(); //이번 향 주입
		if (SharkNum == 1) break;
		if (time == 1000) return -1;
	}
	return time;
}

void InputData(void) { 
	scanf("%d %d %d", &N, &M, &k);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);

			if (map[i][j] >= 1) {
				shark.push_back({ map[i][j] - 1, i, j, 0}); //상어 번호(0 베이스), 행, 열, 방향
				sharkmove[i][j].push_back(map[i][j] - 1);
				SharkNum++;
			}
		}
	}

	sort(shark.begin(), shark.end(), cmp); //상어 번호 오름차순 정렬

	int sdir;
	for (int m = 0; m < M; m++) { //상어 0 베이스
		scanf("%d", &sdir);
		shark[m].dir = sdir; //상어 방향
	}

	int pd;
	for (int m = 0; m < M; m++) { //상어 우선순위 0 베이스
		for (int l = 1; l <= 4; l++) { //방향 1베이스
			for (int k = 0; k < 4; k++) { //우선순위 0베이스
				scanf("%d", &pd);
				priority[m][l].push_back(pd);
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