#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAX 10
#define INF ((int)2e9)

int m, t; //몬스터 수, 턴 수
int PR, PC; //팩맨 위치

deque <int> monster[4 + 2][4 + 2];
deque <int> monster_cpy[4 + 2][4 + 2];
deque <int> monster_move[4 + 2][4 + 2];
int corp[4 + 2][4 + 2];
int visited[4 + 2][4 + 2];
deque <int> pmmove;
deque <int> pmdec;
int sol; //dfs

int mdr[] = {0, -1, -1, 0, 1, 1, 1, 0, -1}; //↑, ↖, ←, ↙, ↓, ↘, →, ↗
int mdc[] = {0, 0, -1, -1, -1, 0, 1, 1, 1}; //↑, ↖, ←, ↙, ↓, ↘, →, ↗

int pdr[] = {0, -1, 0, 1, 0}; //상 좌 하 우
int pdc[] = {0, 0, -1, 0, 1}; 

void Copy(void) {

	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			monster_cpy[r][c].clear();
			monster_cpy[r][c] = monster[r][c];
		}
	}
}

void MoveMonster(void) {

	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			monster_move[r][c].clear();
		}
	}

	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			while (!monster[r][c].empty()) {
				int cur = monster[r][c].front(); monster[r][c].pop_front();
				int nr = r + mdr[cur];
				int nc = c + mdc[cur];

				int flag = 0;
				if (corp[nr][nc] > 0) flag++;
				if ((nr == PR) && (nc == PC)) flag++;
				if ((nr < 1) || (nr > 4) || (nc < 1) || (nc > 4))  flag++;

				int cnt = 0;
				//while (flag  > 0) { 
				// QQQQ 이렇게 하면 안 되는 이유..? 
				//루프 밖에 flag 변수 또 있으니까 flag2로 변수 다르게 지정해 줄 것
				if (flag > 0) {
					for (;;) {
						cnt++;
						if (cur == 8) cur = 1;
						else cur++;

						nr = r + mdr[cur];
						nc = c + mdc[cur];

						int flag2 = 0;
						if (corp[nr][nc] > 0) flag2++;
						if ((nr == PR) && (nc == PC)) flag2++;
						if ((nr < 1) || (nr > 4) || (nc < 1) || (nc > 4)) flag2++;

						if (flag2 == 0) break;

						if (cnt == 8) {
							nr = r;
							nc = c;
							break;
						}
					}
				}

				monster_move[nr][nc].push_back(cur);
			}
		}
	}

	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			monster[r][c].clear();
			while (!monster_move[r][c].empty()) {
				int cur = monster_move[r][c].front(); monster_move[r][c].pop_front();
				monster[r][c].push_back(cur);
			}
		}
	}

}

int CheckNum(void) { //pmmove 이동 시 물고기
	int fishcnt = 0;
	memset(visited, 0, sizeof(visited));

	int P = pmmove.size();
	int npr = PR;
	int npc = PC;
	for (int p = 0; p < P; p++) {
		int npd = pmmove[p];
		npr += pdr[npd];
		npc += pdc[npd];

		if (visited[npr][npc] == 1) continue;

		fishcnt += monster[npr][npc].size();
		visited[npr][npc] = 1;
	}

	return fishcnt;
}

void MovePackman(int r, int c, int cnt) { //DFS

	if (cnt == 3) {
		int num = CheckNum();
		if (sol < num) {
			sol = num;
			pmdec.clear();
			pmdec = pmmove;
		}
		return;
	}

	for (int pd = 1; pd <= 4; pd++) { //상 좌 하 우 탐색

		int npr = r + pdr[pd];
		int npc = c + pdc[pd];

		if ((npr < 1) || (npr > 4) || (npc < 1) || (npc > 4)) continue;

		pmmove.push_back(pd);
		MovePackman(npr, npc, cnt + 1);
		pmmove.pop_back();
	}

}

void KillMonster(int turn) {

	while (!pmdec.empty()) {
		int cur = pmdec.front(); pmdec.pop_front();

		PR += pdr[cur];
		PC += pdc[cur];

		if (!monster[PR][PC].empty())corp[PR][PC] = turn + 2;
		monster[PR][PC].clear();
	}
	pmdec.clear();
}

void DeleteMonster(int turn) {

	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			//if (corp[r][c] == turn - 2) corp[r][c] = 0; //이렇게 하면 turn = 2일 때 모두 해당
			if (corp[r][c] == turn) corp[r][c] = 0;
		}
	}

}
void Paste(void) {

	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			while (!monster_cpy[r][c].empty()) {
				int cur = monster_cpy[r][c].front(); monster_cpy[r][c].pop_front();
				monster[r][c].push_back(cur);
			}
		}
	}

}

int Solve(void) {

	for (int i = 1; i <= t; i++) {


		Copy();
		MoveMonster();

		pmmove.clear();
		sol = -1;
		MovePackman(PR, PC, 0); //DFS
		KillMonster(i);

		DeleteMonster(i);
		Paste();

	}

	int sol = 0;
	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			sol += monster[r][c].size();
		}
	}
	return sol;
}

void InputData(void) {
	scanf("%d %d", &m, &t);

	scanf("%d %d", &PR, &PC);

	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			monster[r][c].clear();
		}
	}

	int r, c, d;
	for (int n = 0; n < m; n++) {
		scanf("%d %d %d", &r, &c, &d);
		monster[r][c].push_back(d);
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}