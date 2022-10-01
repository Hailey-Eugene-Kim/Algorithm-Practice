#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN (20)
#define INF ((int)2e9)
int N;
int ppl[MAXN + 10][MAXN + 10]; //인구 수
int map[MAXN + 10][MAXN + 10]; //선거 구역
int num[5 + 10]; //각 선거 구 인구 수
//int x, y, d1, d2;
struct STD {
	int x, y, d1, d2;
};
queue <STD> standard;

//기준점 큐에 저장
void DecideStandard(void) { 


	for (int x = 1; x <= N - 2; x++) { //모든 x
		for (int d1 = 1; d1 <= N - x - 1; d1++) { //모든 d1
			for (int d2 = 1; d2 <= N - x - d1; d2++) { //모든 d2
				for (int y = d1 + 1; y <= N - d2; y++) { //모든 y
					//if (x + d1 + d2 > N) continue;
					standard.push({ x, y, d1, d2 });
				}
			}
		}
	}

}

void MakeLine(int x, int y, int d1, int d2) {

	int a, b, cnt;
	a = x;
	b = y;
	cnt = 0;
	while (cnt <= d1) {
		map[a++][b--] = 5;
		cnt++;
	}

	a = x;
	b = y;
	cnt = 0;
	while (cnt <= d2) {
		map[a++][b++] = 5;
		cnt++;
	}
	 
	a = x + d1;
	b = y - d1;
	cnt = 0;
	while (cnt <= d2) {
		map[a++][b++] = 5;
		cnt++;
	}

	a = x + d2;
	b = y + d2;
	cnt = 0;
	while (cnt <= d1) {
		map[a++][b--] = 5;
		cnt++;
	}
}

void DecideNum(int x, int y, int d1, int d2) { //부등호 <, <= 조건
	for (int r = 1; r < x + d1; r++) { //1번
		for (int c = 1; c <= y; c++) {
			if (map[r][c] == 5) break; //Q 순서 아래랑 바꾸니까 break가 안 걸림
			if (map[r][c] != 0) continue;
			map[r][c] = 1;
			num[1] += ppl[r][c];
		}
	}

	for (int r = x + d1; r <= N; r++) { //3번
		for (int c = 1; c < y - d1 + d2; c++) {
			if (map[r][c] == 5) break;
			if (map[r][c] != 0) continue;
			map[r][c] = 3;
			num[3] += ppl[r][c];
		}
	}

	for (int r = x + d2; r >= 1; r--) { //2번
		for (int c = N; c > y; c--) {
			if (map[r][c] == 5) break;
			if (map[r][c] != 0) continue;
			map[r][c] = 2;
			num[2] += ppl[r][c];
		}
	}

	for (int r = N; r > d2; r--) { //4번
		for (int c = N; c >= y - d1 + d2; c--) {
			if (map[r][c] == 5) break;
			if (map[r][c] != 0) continue;
			map[r][c] = 4;
			num[4] += ppl[r][c];
		}
	}

	for (int r = 1; r <= N; r++) { //5번
		for (int c = 1; c <= N; c++) {
			if (map[r][c] == 5) num[5] += ppl[r][c];
			if (map[r][c] != 0) continue;

			map[r][c] = 5;
			num[5] += ppl[r][c];
		}
	}
}

int Solve(void) {
	int sol = INF;

	DecideStandard(); //x, y, d1, d2 설정 => 그 값에 따라 다음 반복 //큐에 저장

	while (!standard.empty()) {
		memset(map, 0, sizeof(map));
		memset(num, 0, sizeof(num));

		STD cur = standard.front(); standard.pop();

		MakeLine(cur.x, cur.y, cur.d1, cur.d2); // 5번 선거구 경계선
		DecideNum(cur.x, cur.y, cur.d1, cur.d2); //1 ~4번, 빈칸 5번 //각 선거구 인구 ppl -> num에 저장

		sort(num, num + 6); //1베이스([0]: 0) //오름차순 정렬 
		int a = num[5] - num[1]; //
		if (sol > a) sol = a;
	}

	return sol;
}

void InputData(void) {
	scanf("%d", &N);
	memset(ppl, 0, sizeof(ppl));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &ppl[i][j]);
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}