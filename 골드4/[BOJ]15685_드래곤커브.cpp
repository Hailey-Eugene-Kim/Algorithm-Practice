#include <iostream>
#include <cstring>
#include <deque>
using namespace std;

int N;
struct POS {
	int x, y;
};
deque <POS> dots;
deque <deque <POS>> curve;
struct INFO {
	int x, y, d, g;
};
deque <INFO> dragoninfo;
int map[200][200];
int minR = ((int)2e9);
int minC = ((int)2e9);
int maxR = -1;
int maxC = -1;

void CalCurve(int x, int y, int d, int g) { //세대 반복 -> dots 저장 -> curve 저장

	dots.clear();
	dots.push_back({ x, y });

	switch (d) {
		case 0 :
			dots.push_back({ x + 1, y }); break;
		case 1:
			dots.push_back({ x , y - 1 }); break;
		case 2:
			dots.push_back({ x - 1, y }); break;
		case 3:
			dots.push_back({ x , y + 1}); break;
	}

	if (g > 0) {
		for (int i = 1; i <= g; i++) {

			POS end = dots.back();

			int J = dots.size();
			for (int j = J - 2; j >= 0; j--) {
				POS cur = dots[j];

				int nx, ny;
				if ((cur.x >= end.x) && (cur.y > end.y)) { //끝 점 기준 4사분면
					nx = end.x - abs(cur.y - end.y);
					ny = end.y + abs(cur.x - end.x);
				}
				else if ((cur.x < end.x) && (cur.y >= end.y)) { //3
					nx = end.x - abs(cur.y - end.y);
					ny = end.y - abs(cur.x - end.x);
				}
				else if ((cur.x <= end.x) && (cur.y < end.y)) { //2
					nx = end.x + abs(cur.y - end.y);
					ny = end.y - abs(cur.x - end.x);
				}
				else if ((cur.x > end.x) && (cur.y <= end.y)) { //1
					nx = end.x + abs(cur.y - end.y);
					ny = end.y + abs(cur.x - end.x);
				}

				dots.push_back({ nx, ny });
			}
		}
	}

	curve.push_back(dots);
}

void DrawCurve(void) { //curve 좌표 배열에 그리기 //(r, c) : (y : x)

	for (int n = 0; n < N; n++) {
		while (!curve[n].empty()) {
			POS cur = curve[n].front(); curve[n].pop_front();
			map[cur.y][cur.x] = 1;

			if (minR > cur.y) minR = cur.y;
			if (minC > cur.x) minC = cur.x;
			if (maxR < cur.y) maxR = cur.y;
			if (maxC < cur.x) maxC = cur.x;
		}
	}
}

int Solve(void) {

	curve.clear();

	for (int n = 0; n < N; n++) {
		INFO cur = dragoninfo[n];
		CalCurve(cur.x, cur.y, cur.d, cur.g); //curve에 좌표 저장
	}

	DrawCurve(); //map에 표기 , min, max R C 구하기

	int sol = 0;
	for (int r = minR; r <= maxR; r++) {
		for (int c = minC; c <= maxC; c++) {
			if (map[r][c] && map[r + 1][c] && map[r][c + 1] && map[r + 1][c + 1]) sol++;
		}
	}
	return sol;
}

void InputData(void) {
	scanf("%d", &N);

	int dx, dy, dd, dg;
	for (int n = 1; n <= N; n++) {
		scanf("%d %d %d %d", &dx, &dy, &dd, &dg);
		dragoninfo.push_back({ dx, dy, dd, dg });
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}