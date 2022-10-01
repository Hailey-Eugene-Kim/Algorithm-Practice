#if 0

#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAXN 20 //N, M

int N, M, K;
int map[MAXN + 10][MAXN + 10];
int visited[MAXN + 10][MAXN + 10];
int DiceR = 1, DiceC = 1, DiceVal = 6; //이동 후 주사위 행, 열, 값
int DiceDir = 0; //주사위 방향 // 0:동 1:남 2:서 3:북
int dr[] = { 0, 1, 0, -1 }; //이동하는 Dice 행열 결정
int dc[] = { 1, 0, -1, 0 };
int Dice[] = { 3, 5, 4, 2, 1, 6 };
deque <int> Rotate;
int score = 0;

//주사위 한 칸 굴러감 => 마지막
//점수 획득
	//사방 중 지도값과 같은 경우 +지도값
//방향 결정
	//주사위의 바닥값과 지도값

void DiceMove(void) { //DiceVal 결정 //주사위 바닥값
	
	int nr = DiceR + dr[DiceDir];
	int nc = DiceC + dc[DiceDir];

	if ((nr < 1) || (nr > N) || (nc < 1) || (nc > M)) { //조건 빼먹음
		DiceDir = (DiceDir + 2) % 4; 
		DiceR += dr[DiceDir];
		DiceC += dc[DiceDir];
	}
	else {
		DiceR = nr;
		DiceC = nc;
	}
	DiceVal = Dice[DiceDir];

	Rotate.clear();

	//주사위 좌표 갱신
	//동서

	if ((DiceDir == 0) || (DiceDir == 2)) {
		Rotate.push_back(Dice[2]);
		Rotate.push_back(Dice[4]);
		Rotate.push_back(Dice[0]);
		Rotate.push_back(Dice[5]);

		if (DiceDir == 0) { //동
			int tmp = Rotate.back(); Rotate.pop_back();
			Rotate.push_front(tmp);
		}
		else if (DiceDir == 2) { //서
			int tmp = Rotate.front(); Rotate.pop_front();
			Rotate.push_back(tmp);
		}

		Dice[2] = Rotate[0];
		Dice[4] = Rotate[1];
		Dice[0] = Rotate[2];
		Dice[5] = Rotate[3];
	}

	//남북

	if ((DiceDir == 1) || (DiceDir == 3)) {
		Rotate.push_back(Dice[3]);
		Rotate.push_back(Dice[4]);
		Rotate.push_back(Dice[1]);
		Rotate.push_back(Dice[5]);
		 
		if (DiceDir == 1) { //남
			int tmp = Rotate.back(); Rotate.pop_back();
			Rotate.push_front(tmp);
		}
		else if (DiceDir == 3) { //북
			int tmp = Rotate.front(); Rotate.pop_front();
			Rotate.push_back(tmp);
		}

		Dice[3] = Rotate[0];
		Dice[4] = Rotate[1];
		Dice[1] = Rotate[2];
		Dice[5] = Rotate[3];
	}

}

void GetScore(int r, int c) { //FloodFill 확산

	//종료조건
	if ((r < 1) || (r > N) || (c < 1) || (c > M)) return;
	if (visited[r][c] == 1) return;
	if (map[r][c] != map[DiceR][DiceC]) return;

	visited[r][c] = 1;
	score++;

	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if ((nr < 1) || (nr > N) || (nc < 1) || (nc > M)) continue;
		if (visited[nr][nc] == 1) continue;
		if (map[nr][nc] != map[DiceR][DiceC]) continue;

		GetScore(nr, nc);
	}
}

void DecideDir(void) {

	int A = DiceVal;
	int B = map[DiceR][DiceC];

	//시계방향
	if (A > B) DiceDir = (DiceDir + 1) % 4;

	//반시계
	else if (A < B) DiceDir = (DiceDir + 3) % 4;

	//같으면 그대로
}


int Solve(void) {
	int sol = 0;

	for (int k = 1; k <= K; k++) {

		DiceMove(); //OK
		memset(visited, 0, sizeof(visited));
		score = 0; //초기화 실수 
		GetScore(DiceR, DiceC);
		sol += map[DiceR][DiceC] * score;
		DecideDir();

	}

	return sol;
}

void InputData(void) {
	scanf("%d %d %d", &N, &M, &K);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}

#endif