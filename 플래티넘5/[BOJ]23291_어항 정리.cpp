#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAX 100
#define INF ((int)2e9)

int N, K;
deque <int> horz;
deque <deque <int> > bowl;
int Fmin, Fmax;

void AddFish(void) {
	deque <int> minidx;
	Fmin = INF;
	minidx.clear();

	int I = bowl[0].size() - 1;
	for (int i = 0; i <= I; i++) {
		if (Fmin > bowl[0][i]) {
			Fmin = bowl[0][i];
			minidx.clear();
			minidx.push_back(i);
		}
		else if (Fmin == bowl[0][i]) {
			minidx.push_back(i);
		}
	}

	for (auto e : minidx) {
		bowl[0][e]++;
	}
}

void FirstAir(void) {
	//행  rownum= bowl.size() - 1
	//열  = addidx
		//초기 = 0
		//이후 = bowl[1].size() - 1
	//한 열 씩 쌓기
		//addidx ~ 1 바닥부터 horz2.push_back , addbowl.push_back
	//addbowl [0] ~ [rownum] => bowl.push_back
	//rownum, addidx 갱신 
	//종료 : if ( bowl.size() > bowl[0].size() - bowl[1].size() )

	int rownum, addidx;
	deque <int> horz;
	deque <deque <int>> addbowl;
	
	rownum = bowl.size() - 1;
	addidx = 0;

	for (;;) {

		addbowl.clear();
		for (int j = addidx; j >= 0; j--) {
			horz.clear();
			for (int i = 0; i <= rownum; i++) {
				horz.push_back(bowl[i][j]);
			}
			addbowl.push_back(horz);
		}

		for (int i = 0; i <= rownum; i++) {
			for (int j = addidx; j >= 0; j--) {
				bowl[i].pop_front();
			}
		}
		while (bowl.size() > 1) bowl.pop_back(); //bowl[0]남기고 pop

		for (auto e : addbowl) {
			bowl.push_back(e);
		}

		rownum = bowl.size() - 1;
		addidx = bowl[1].size() - 1;

		if (bowl.size() > bowl[0].size() - bowl[1].size()) return;
	}
}

void SecondAir(void) {

	int rownum, addidx;
	deque <int> horz;

	for (int n = 1; n <= 2; n++) {
		rownum = bowl.size() - 1;
		addidx = bowl[0].size() / 2 - 1;

		for (int i = rownum; i >= 0; i--) {
			horz.clear();
			for (int j = 0; j <= addidx; j++) {
				int half = bowl[i].front(); bowl[i].pop_front();
				horz.push_front(half);
			}
			bowl.push_back(horz);
		}
	}

}

void AdjustFish(void) {

	int dr[] = {-1, 1, 0, 0};
	int dc[] = {0, 0, -1, 1};

	deque <deque <int> > bowl_cpy;
	deque <deque <int> > adjust;
	bowl_cpy = bowl;
	adjust = bowl; //adjust 전체 구조 복사

	int R = bowl.size() - 1;
	int lastidx = bowl[0].size() - 1;
	for (int r = 0; r <= R; r++) { //빈 칸 -1 채우기
		int mididx = bowl[r].size();
		for (int c = mididx; c <= lastidx; c++) {
			bowl_cpy[r].push_back(-1);
		}
	}

	for (int r = 0; r <= R; r++) { //adjust 값 초기화
		int C = bowl[r].size() - 1;
		for (int c = 0; c <= C; c++) {
			adjust[r][c] = 0;
		}
	}

	for (int r = 0; r <= R; r++) {
		int C = bowl[r].size() - 1;
		for (int c = 0; c <= C; c++) {
			
			for (int k = 0; k < 4; k++) {
				int nr = r + dr[k];
				int nc = c + dc[k];

				if ((nr < 0) || (nr > R) || (nc < 0) || (nc > C)) continue;
				if (bowl_cpy[nr][nc] == -1) continue;

				int d = 0;
				if (bowl[r][c] != bowl[nr][nc]) d = abs(bowl[r][c] - bowl[nr][nc]) / 5;
				if (d > 0) {
					//QQQQ 삼항 조건식 어떻게 쓰더라

					if (bowl[r][c] > bowl[nr][nc]) {
						adjust[r][c] -= d;
						adjust[nr][nc] += d;
					}
					else {
						adjust[r][c] += d;
						adjust[nr][nc] -= d;
					}
				}
			}
		}
	}

	for (int r = 0; r <= R; r++) {
		int C = bowl[r].size() - 1;
		for (int c = 0; c <= C; c++) {
			if (adjust[r][c] != 0) bowl[r][c] += adjust[r][c] / 2;
		}
	}
	
}

void MakeOne(void) { 

	deque <int> one;

	int R = bowl.size() - 1; //행
	int C = bowl[0].size() - 1; //전체 열
	int mididx = bowl[1].size() - 1; //행 2 이상 열

	one.clear();

	for (int c = 0; c <= mididx; c++) { //행 2 이상
		for (int r = 0; r <= R; r++) {
			one.push_back(bowl[r][c]);
		}
	}

	if (C > mididx) { //행 1
		for (int c = mididx + 1; c <= C; c++) {
			one.push_back(bowl[0][c]);
		}
	}

	bowl.clear();
	bowl.push_back(one);
}

int Solve(void) {
	//최소 물고기 어항 물고기 추가
	//가장 왼쪽 한 칸 쌓기
	//공중부양 반복 90
	//물고기 수 조절
	//어항 일렬 조정
	//공중부양 2회 180
	//물고기 수 조절
	//어항 일렬 조정

	int turn = 0;

	for (;;) {
		turn++;
		//최소 물고기 어항 물고기 추가
		AddFish();

		//가장 왼쪽 한 칸 쌓기
		int left = bowl[0].front(); bowl[0].pop_front();
		horz.push_back(left);
		bowl.push_back(horz);
		horz.clear();

		//공중부양 반복 90
		FirstAir();

		//물고기 수 조절
		AdjustFish();

		//어항 일렬 조정
		MakeOne();

		//공중부양 2회 180
		SecondAir();

		//물고기 수 조절
		AdjustFish();

		//어항 일렬 조정
		MakeOne();

		//최소 최대
		Fmin = INF;
		Fmax = -1;
		for (auto e : bowl[0]) {
			if (Fmin > e) Fmin = e;
			if (Fmax < e) Fmax = e;
		}

		if (Fmax - Fmin <= K) return turn;
	}

}

void InputData(void) {
	scanf("%d %d", &N, &K);
	int num;
	for (int n = 0; n < N; n++) {
		scanf("%d", &num);
		horz.push_back(num);
	}
	bowl.push_back(horz);
	horz.clear();
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
}