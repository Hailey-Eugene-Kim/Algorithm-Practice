#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

int TN[4 + 10][8 + 10];
deque <int> T[4 + 10]; //4개 톱니바퀴
struct ROTATE {
	int num, dir; //톱니바퀴 번호, 방향 (0: N, 1: S)
};
queue <ROTATE> rt; //회전 정보
queue <ROTATE> others;
int K;

void CheckWheel(int num, int dir) { //회전할 톱니바퀴 결정

	others = {};

	//오른쪽

	int ndir1 = dir;
	for (int i = num; i < 4; i++) { //3번 톱니바퀴까지만
		ndir1 *= -1;
		if (T[i][2] == T[i + 1][6]) break;
		if (T[i][2] != T[i + 1][6]) {
			others.push({ i + 1, ndir1 });
		}
	}

	//왼쪽

	int ndir2 = dir;
	for (int i = num; i > 1; i--) { 
		ndir2 *= -1;
		if (T[i][6] == T[i - 1][2]) break;
		if (T[i][6] != T[i - 1][2]) {
			others.push({ i - 1, ndir2 });
		}
	}
}

void Rotate(int num, int dir) { //회전 //1:시계, -1: 반시계

	if (dir == 1) {
		int tmp = T[num].back(); T[num].pop_back();
		T[num].push_front(tmp);
	}

	if (dir == -1) {
		int tmp = T[num].front(); T[num].pop_front();
		T[num].push_back(tmp);
	}

}

int Solve(void) {
	int sol = 0;

	while (!rt.empty()) {

		ROTATE cur = rt.front(); rt.pop();

		CheckWheel(cur.num, cur.dir);

		Rotate(cur.num, cur.dir); //해당 톱니바퀴 회전

		while (!others.empty()) { //다른 톱니바퀴 회전

			ROTATE tmp = others.front(); others.pop();

			Rotate(tmp.num, tmp.dir);
		}
	}

	if (T[1][0] == 1) sol += 1;
	if (T[2][0] == 1) sol += 2;
	if (T[3][0] == 1) sol += 4;
	if (T[4][0] == 1) sol += 8;

	return sol;
}

void InputData(void) {
	//deque 초기화
	for (int i = 1; i <= 4; i++) {
		T[i].clear();
	}

	int t;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			scanf("%1d", &t);
			T[i].push_back(t);
		}
	}

	scanf("%d", &K);
	rt = {};
	int tn, td;
	for (int k = 1; k <= K; k++) {
		scanf("%d %d", &tn, &td);
		rt.push({ tn, td });
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}