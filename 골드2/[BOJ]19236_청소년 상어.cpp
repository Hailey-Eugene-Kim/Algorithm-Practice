#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXN (16)
#define INF ((int)2e9)

struct FISH {
	int num, dir;
};
struct INFO {
	int r, c, num, dir; //행 열 방향 정보
};
vector <FISH> pos[4 + 4][4 + 4];
vector <INFO> shark;
vector <INFO> fish;
//int SR, SC, SNum, SDir; //DFS 사용해야되니까 전역변수 X, 인자로 받기
int sol;
int dr[] = {0, -1, -1, 0, 1, 1, 1, 0, -1}; //1~ 8
int dc[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

bool cmp(INFO &a, INFO &b) {
	return a.num < b.num;
}

void FishMove(int Sr, int Sc) {
	//(Sr, Sc) 제외, 경계 내, 이동 가능
	//이동 결과 pos 배열 저장 => shark 경우의 수 
	//번호 작은 물고기부터 순서대로
	sort(fish.begin(), fish.end(), cmp); //Q 오류 //그냥 컴파일러 문제

	int P = fish.size();
	for (int p = 0; p < P; p++) { //값 변화시켜야 하니까 auto e 안 됨
		if (fish[p].num == 0) continue; //먹힌 물고기 패스 //= 실수

		int nr = fish[p].r + dr[fish[p].dir]; //1회
		int nc = fish[p].c + dc[fish[p].dir];

		if (((nr < 0) || (nr >= 4) || (nc < 0) || (nc >= 4)) || ((nr == Sr) && (nc == Sc))) { //경계 밖이거나 상어 좌표와 같으면
			int flag = 0;
			for (int i = 0; i < 8; i++) {

				//(Sr, Sc), 경계 밖이면 회전 
				if (((nr < 0) || (nr >= 4) || (nc < 0) || (nc >= 4)) || ((nr == Sr) && (nc == Sc))) { //nc 실수

					fish[p].dir++;
					if (fish[p].dir >= 9) fish[p].dir -= 8;

					nr = fish[p].r + dr[fish[p].dir];
					nc = fish[p].c + dc[fish[p].dir];
					flag++;
				}
			}
			if (flag == 7) {
				nr = fish[p].r;
				nc = fish[p].c;
			}
		}

		//빈 칸인 경우 //값 갱신해야 되니까 삭제 순서 주의
		if (pos[nr][nc].empty()) {
			pos[nr][nc].push_back({ fish[p].num, fish[p].dir });
			pos[fish[p].r][fish[p].c].clear(); //빼먹음
			fish[p].r = nr;
			fish[p].c = nc;
		}

		//이동하는 위치 물고기 좌표 switch
		else {
			int Q = fish.size();
			for (int q = 0; q < Q; q++) {
				if (fish[q].num == pos[nr][nc][0].num) {
					fish[q].r = fish[p].r;
					fish[q].c = fish[p].c;
					break;
				}
			}

			//pos 변경
			pos[fish[p].r][fish[p].c][0] = { pos[nr][nc][0].num , pos[nr][nc][0].dir };
			pos[nr][nc][0] = { fish[p].num, fish[p].dir };

			//p 물고기 좌표 변경
			fish[p].r = nr;
			fish[p].c = nc;
		}
	}
}

void SharkMove(int Sr, int Sc, int Sdir) { //상어 좌표
	shark.clear();
	//새로 shark 만들기
	//물고기 없는 칸 X => pos 확인

	int nsr = Sr;
	int nsc = Sc;
	for (int i = 0; i < 3; i++) { //최대 3회
		nsr = nsr + dr[Sdir];
		nsc = nsc + dc[Sdir];

		if ((nsr < 0) || (nsr >= 4) || (nsc < 0) || (nsc >= 4)) continue;
		if (pos[nsr][nsc].empty()) continue;
		shark.push_back({nsr, nsc, pos[nsr][nsc][0].num, pos[nsr][nsc][0].dir });
	}
}

void DFS(int r, int c, int sum, int num, int dir) {

	FishMove(r, c); //상어의 위치 
	SharkMove(r, c, dir); //가능한 상어 좌표 저장 //경우의 수 => 모두 DFS

	//상어, 물고기 복제
	vector <INFO> shark_c = shark;
	vector <INFO> fish_c = fish;
	vector <FISH> pos_c[4 + 4][4 + 4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			pos_c[i][j] = pos[i][j];
		}
	}

	if ((shark.empty())||(fish.empty())){ //상어 이동 못 하는 경우, 물고기 다 먹은 경우 리턴
		if (sol < sum) sol = sum;
		return;
	}

	for (auto e: shark) { //경우의 수 보내기
		
		//e 물고기 먹기
		int P = fish.size();
		int val;
		for (int p = 0; p < P; p++) {
			if (fish[p].num == e.num) val = p;
		}
		fish.erase(fish.begin() + val);
		pos[e.r][e.c].clear();

		DFS(e.r, e.c, sum + e.num, e.num, e.dir); 
		//QQQQ. 위에서 먹은 물고기 지우는 처리 하고 DFS 보냈는데도 안 지워져서 FishMove에서 vector range error
		//얘네만이 아니라 전체를 원복해야 함
		//fish.push_back({ e.r, e.c, e.num, e.dir });
		//pos[e.r][e.c].push_back({ e.num, e.dir });

		//상어, 물고기 원복
		shark = shark_c;
		fish = fish_c;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				pos[i][j] = pos_c[i][j];
			}
		}
	}
}

int Solve(void) {
	sol = 0;

	int Firstnum = pos[0][0][0].num;
	int Firstdir = pos[0][0][0].dir;

	int P = fish.size();
	int val;
	for (int p = 0; p < P; p++) { //첫 물고기 먹기
		if (fish[p].num == pos[0][0][0].num) {
			fish.erase(fish.begin() + p);
			break;
		}
	}
	pos[0][0].clear(); 

	DFS(0, 0, Firstnum, Firstnum, Firstdir);

	return sol; //물고기 번호의 합의 최대값
}

void InputData(void) {
	int a, b;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			scanf("%d %d", &a, &b);
			fish.push_back({ i, j, a, b });
			pos[i][j].push_back({ a, b });
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}