#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;
#define MAXN (100)

int N, K, L;
int map[MAXN + 10][MAXN + 10];
int ar, ac; //사과 행, 열
int x;
char c;

int dr[] = { 0, 1, 0, -1 }; //오아왼위
int dc[] = { 1, 0, -1, 0 };

int sr, sc, sl; //뱀 행, 열, 길이

struct QUE {
	int t;
	char d;
};
deque <QUE> que; //방향 전환 정보

struct DIR {
	int r, c;
};
deque <DIR> apple; //사과
deque <DIR> snake; //뱀

int Solve(void) {
	int time_cnt = 0;
	int dir_cnt = 0; //방향 정보

	snake = {};
	snake.push_front({ 1, 1 }); //초기값

	for (;;) {

		time_cnt++; //머리 늘리는 시간

		int nr = snake[0].r + dr[dir_cnt]; //머리 늘리기 
		int nc = snake[0].c + dc[dir_cnt];
		
		if ((nr < 1)|| (nr > N)|| (nc < 1) || (nc > N)) return time_cnt; //종료 조건: 벽에 부딪치면 종료

		int I = snake.size();
		for (int i = 0; i < I; i++) {
			if ((nr == snake[i].r) && (nc == snake[i].c)) return time_cnt; //종료 조건: 몸통이랑 부딪히면 종료
		}

		snake.push_front({ nr, nc }); //종료조건 아니면 꼬리 저장
		
		//time_cnt++; //꼬리 없애는 시간 or 사과 먹는 시간 //=> 문제 이해 잘못: 이 때는 시간 추가 X

		if (map[nr][nc] == 1) map[nr][nc] = 0; //사과 O 꼬리 안 없앰, 사과 먹음
		else snake.pop_back(); //사과 X 꼬리 없앰

		if (!que.empty()) { //남은 방향 전환 정보 //있으면 방향 갱신 //없으면 마지막 방향정보 유지
			QUE cur = que.front(); //방향 전환 정보 
			if (cur.t == time_cnt) { //시간이 현재 시간에 해당하면 //방향 정보 갱신
				if (cur.d == 'L') dir_cnt = (dir_cnt + 3) % 4; //L 반시계
				else if (cur.d == 'D') dir_cnt = (dir_cnt + 1) % 4; //D 시계

				que.pop_front(); //사용한 방향 전환 정보 삭제
			}
		}
	}
}

void InputData(void) {
	memset(map, 0, sizeof(map));
	apple = {};
	que = {};
	
	scanf("%d", &N);
	scanf("%d", &K);
	for (int i = 1; i <= K; i++) {
		scanf("%d %d", &ar, &ac);
		map[ar][ac] = 1;
		apple.push_back({ ar, ac });
	}

	scanf("%d", &L);
	for (int i = 1; i <= L; i++) {
		scanf("%d %c", &x, &c);
		que.push_back({x, c});
	}
}

int main(void) {

	InputData();
	int ans = Solve();
	printf("%d", ans);

	return 0;
}
