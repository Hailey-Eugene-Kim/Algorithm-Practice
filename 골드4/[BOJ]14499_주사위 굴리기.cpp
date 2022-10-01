#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAX 20

int N, M, x, y, K;
deque <int> order;
deque <int> horz;
deque <int> vert;
int dice[7 + 2];
int diceR, diceC;
int map[MAX + 10][MAX + 10];

int dr[] = {0, 0, 0, -1, 1}; //동 서 북 남
int dc[] = {0, 1, -1, 0, 0}; //동 서 북 남

void Solve (void) {

	diceR = x; diceC = y;

	while (!order.empty()) {

		int cur = order.front(); order.pop_front();

		diceR += dr[cur];
		diceC += dc[cur];

		if ((diceR < 0) || (diceR >= N) || (diceC < 0) || (diceC >= M)) {
			diceR -= dr[cur];
			diceC -= dc[cur];
			continue;
		}

		//주사위 이동
		//동서
		if ((cur == 1) || (cur == 2)) {
			horz.clear();
			horz.push_back(dice[5]);
			horz.push_back(dice[2]);
			horz.push_back(dice[6]);
			horz.push_back(dice[4]);

			if (cur == 1) { //동
				int move = horz.back(); horz.pop_back();
				horz.push_front(move);
			}
			else if (cur == 2) { //서
				int move = horz.front(); horz.pop_front();
				horz.push_back(move);
			}

			dice[5] = horz[0];
			dice[2] = horz[1];
			dice[6] = horz[2];
			dice[4] = horz[3];
		}


		//남북
		if ((cur == 3) || (cur == 4)) { 
			vert.clear();
			vert.push_back(dice[1]);
			vert.push_back(dice[2]);
			vert.push_back(dice[3]);
			vert.push_back(dice[4]);

			if (cur == 3) { //북
				int move = vert.front(); vert.pop_front();
				vert.push_back(move);
			}
			else if (cur == 4) { //남
				int move = vert.back(); vert.pop_back();
				vert.push_front(move);
			}

			dice[1] = vert[0];
			dice[2] = vert[1];
			dice[3] = vert[2];
			dice[4] = vert[3];
		}

		if (map[diceR][diceC] == 0) map[diceR][diceC] = dice[4];
		else {
			dice[4] = map[diceR][diceC];
			map[diceR][diceC] = 0;
		}

		printf("%d\n", dice[2]);
	}
	
}

void InputData(void) {
	scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			scanf("%d", &map[r][c]);
		}
	}

	int a;
	for (int k = 1; k <= K; k++) {
		scanf("%d", &a);
		order.push_back(a);
	}

	memset(dice, 0, sizeof(dice));
}

int main(void) {
	InputData();
	Solve();
	return 0;
}