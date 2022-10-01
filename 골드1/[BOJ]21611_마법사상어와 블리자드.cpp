#include <iostream>
#include <cstring>
#include <deque>
#include <queue>
using namespace std;
#define MAXN (49)

int N, M; //격자 크기, 블리자드 회수
int map[MAXN + 10][MAXN + 10];
int mapnumber[MAXN + 10][MAXN + 10];
struct QUE {
	int d, s;
};
queue <QUE> magic;
deque <int> stone; //상어 포함
queue <int> Berase;
struct EXP {
	int num, cnt;
};
queue <EXP> explode;
struct CH {
	int cnt, color;
};
queue <CH> change;
int score = 0;
int one, two, three = 0;

void NumberMap(void) {

	memset(mapnumber, 0, sizeof(mapnumber));
	int num = 0;
	int cr = (N + 1) / 2;
	int cc = (N + 1) / 2;
	mapnumber[cr][cc] = num;
	stone.push_back(map[cr][cc]);

	for (int i = 2; i <= N; i++) {

		if (i % 2 == 0) { //짝수
			for (int j = 1; j < i; j++) { //왼
				mapnumber[cr][cc--] = num++;
				stone.push_back(map[cr][cc]);
			}
			for (int j = 1; j < i; j++) { //아
				mapnumber[cr++][cc] = num++;
				stone.push_back(map[cr][cc]);
			}
		}

		else if (i % 2 == 1) { //홀수
			for (int j = 1; j < i; j++) { //오
				mapnumber[cr][cc++] = num++;
				stone.push_back(map[cr][cc]);
			}
			for (int j = 1; j < i; j++) { //위
				mapnumber[cr--][cc] = num++;
				stone.push_back(map[cr][cc]);
			}
		}

	}

	//마지막 행 : N
	for (int j = 1; j <= N; j++) { //왼 //확인 필요
		mapnumber[cr][cc--] = num++;
		stone.push_back(map[cr][cc]);
	}
	stone.pop_back();
}

void Blizard(int d, int s) { //map삭제 deque 삭제

	int cr = (N + 1) / 2;
	int cc = (N + 1) / 2;
	int dr[] = {0, -1, 1, 0, 0 }; //위 아 왼 오
	int dc[] = {0, 0, 0, -1, 1 };

	for (int i = 1; i <= s; i++) {
		int nr = cr + i * dr[d];
		int nc = cc + i * dc[d];

		map[nr][nc] = 0;
		Berase.push(mapnumber[nr][nc]);
	}

	int cnt = 0;
	for (int j = 0; j < s; j++) {
		int cur = Berase.front(); Berase.pop();
		if (cur - j < stone.size()) stone.erase(stone.begin() + (cur - j)); //구슬 범위 이내면 삭제
	}
}

int Explode(void) {
	//초기화
	explode = {};

	int cnt = 0;
	int I = stone.size();
	for (int i = 2; i < I; i++) { //2부터 시작, 이전값 비교
		if (stone[i] == stone[i - 1]) {
			cnt++;
		}
		else { 
			if (cnt < 3) cnt = 0;
			else {
				cnt++;
				explode.push({ i - cnt, cnt }); //구슬 위치, 개수
				cnt = 0;
			}
		}
	}

	if (explode.empty()) return 1;

	//삭제 & 구슬 개수
	//stone.erase -> 위치, 개수
	int erasecnt = 0;
	while (!explode.empty()) {
		EXP cur = explode.front(); explode.pop();

		int snum = cur.num - erasecnt;

		if (stone[snum] == 1) score += 1 * cur.cnt; //구슬 색 //실수 : stone[cur.num]으로 잘못된 색 반영
		else if (stone[snum] == 2) score += 2 * cur.cnt;
		else if (stone[snum] == 3) score += 3 * cur.cnt;

		stone.erase(stone.begin() + snum, stone.begin() + snum + cur.cnt);
		erasecnt += cur.cnt;
	}

	return 0;
}

void Change(void) { //stone 0 상어 포함

	int cnt = 0;
	stone.push_back(0); //마지막 돌 반영
	int I = stone.size();
	for (int i = 2; i < I; i++) { //2부터 시작, 이전값 비교
		if (stone[i] == stone[i - 1]) {
			cnt++;
		}
		else {
			cnt++;
			change.push({ cnt, stone[i - 1] }); //개수, 구슬 색
			cnt = 0;
		}
	}

	stone.clear();
	stone.push_back(0);

	while (!change.empty()) {
		CH cur = change.front(); change.pop();

		stone.push_back(cur.cnt);
		stone.push_back(cur.color);
	}

	while (stone.size() >  N * N) { //범위 조건
		stone.pop_back();
	}
}

int Solve(void) {
	int sol = 0;

	NumberMap();

	while (!magic.empty()) {
		QUE cur = magic.front(); magic.pop();
		Blizard(cur.d, cur.s);

		for (;;) {
			int finish = Explode();
			if (finish == 1) break;
		}

		Change();
	}

	return score;
	//return 1 * one + 2 * two + 3 * three;
}

void InputData(void) {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	int md, ms;
	for (int m = 1; m <= M; m++) {
		scanf("%d %d", &md, &ms);
		magic.push({ md, ms });
	}
}

int main(void) {

	InputData();
	int ans = Solve();
	printf("%d", ans);
	
	return 0;
}