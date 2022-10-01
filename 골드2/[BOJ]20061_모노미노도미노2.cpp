#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
#define MAXN ((int)1e4)

int N;

//파랑 : t, x (행)
//초록 : t, y (열)

//입력 : 이동
//0 - 5 이동
	//blue, green 한 번씩
	//타일 있으면 break
//꽉 찬 행 , 열 확인 => vector
//특별구역 확인 => vector

struct MOVE {
	int t, x, y; // t 2 가로 3 세로
};
queue <MOVE> tile;
int tilenumG[6 + 10]; //꽉 찼는지 확인 
int tilenumB[6 + 10];

int Green[6 + 10][4 + 10];
int Blue[4 + 10][6 + 10];

int score = 0;

void CheckGreen(int idxX) { //행 번호

	if ((idxX == 0) || (idxX == 1)) { //5부터 당겨오기
		for (int i = 5; i >= idxX + 1; i--) { //부호 실수  //점수 배열 이동 빼먹음
			for (int j = 0; j <= 3; j++) {
				Green[i][j] = Green[i - 1][j];
				tilenumG[i] = tilenumG[i - 1];
			}
		}

		for (int j = 0; j <= 3; j++) { //당겨오고 마지막 행
			Green[idxX][j] = 0;
			tilenumG[idxX] = 0;
		}
	}

	else if (tilenumG[idxX] == 4) { //행 꽉 찼을 때
		
		tilenumG[idxX] = 0;
		score++;

		for (int i = idxX; i >= 1; i--) { //실수
			for (int j = 0; j <= 3; j++) {
				Green[i][j] = Green[i - 1][j];
				tilenumG[i] = tilenumG[i - 1];
			}
		}
	}

}

void MoveGreen(int t, int y) { 

	if (t == 1) {
		for (int i = 0; i <= 6; i++) {
			if ((Green[i][y] == 1)||(i == 6)) {

				Green[i - 1][y] = 1; //타일 표시
				tilenumG[i - 1]++; //행 타일 증가

				CheckGreen(i - 1);
				break;
			}
		}
	}

	else if (t == 3) { //행 2
		for (int i = 0; i <= 6; i++) {
			if ((Green[i][y] == 1) || (i == 6)) {

				Green[i - 1][y] = 1; //타일 표시
				tilenumG[i - 1]++; //행 타일 증가

				Green[i - 2][y] = 1; //타일 표시
				tilenumG[i - 2]++; //행 타일 증가

				if (i - 2 == 0) {
					CheckGreen(i - 2);
					CheckGreen(i - 1);
				}
				else if (i - 2 == 1) {
					CheckGreen(i - 1);
					if (tilenumG[i - 2] != 0) CheckGreen(i - 2); //행 없어진 경우 제외
				}
				else {
					CheckGreen(i - 2);
					CheckGreen(i - 1);
				}

				break;
			}
		}
	}

	else { // t = 2 , 열 2개
		for (int i = 0; i <= 6; i++) {
			if (((Green[i][y] == 1) || (Green[i][y + 1] == 1)) || (i == 6)){

				Green[i - 1][y] = 1; //타일 표시
				tilenumG[i - 1]++; //행 타일 증가

				Green[i - 1][y + 1] = 1; //타일 표시
				tilenumG[i - 1]++; //행 타일 증가

				CheckGreen(i - 1);
				break;
			}
		}
	}
}

void CheckBlue(int idxY) { //열 번호

	if ((idxY == 0) || (idxY == 1)) { //5부터 당겨오기
		for (int i = 5; i >= idxY + 1; i--) {
			for (int j = 0; j <= 3; j++) {
				Blue[j][i] = Blue[j][i - 1];
				tilenumB[i] = tilenumB[i - 1];
			}
		}

		for (int j = 0; j <= 3; j++) { //당겨오고 마지막 행
			Blue[j][idxY] = 0;
			tilenumB[idxY] = 0;
		}
	}

	else if (tilenumB[idxY] == 4) { //행 꽉 찼을 때

		tilenumB[idxY] = 0;
		score++;

		for (int i = idxY; i >= 1; i--) { //1도 포함해야 함 (특별구역 한 칸 걸쳐지는 경우)
			for (int j = 0; j <= 3; j++) {
				Blue[j][i] = Blue[j][i - 1];
				tilenumB[i] = tilenumB[i - 1];
			}
		}
	}

}

void MoveBlue(int t, int x) {

	if (t == 1) {
		for (int i = 0; i <= 6; i++) {
			if ((Blue[x][i] == 1) || (i == 6)) {

				//if (i == 5) i++;

				Blue[x][i - 1] = 1; //타일 표시
				tilenumB[i - 1]++; //행 타일 증가

				CheckBlue(i - 1);
				break;
			}
		}
	}

	else if (t == 2) { //열 2
		for (int i = 0; i <= 6; i++) {
			if ((Blue[x][i] == 1) || (i == 6)) {

				//if (i == 5) i++;

				Blue[x][i - 1] = 1; //타일 표시
				tilenumB[i - 1]++; //행 타일 증가

				Blue[x][i - 2] = 1; //타일 표시
				tilenumB[i - 2]++; //행 타일 증가

				if (i - 2 == 0) {
					CheckBlue(i - 2);
					CheckBlue(i - 1);
				}
				else if (i - 2 == 1) {
					CheckBlue(i - 1);
					if (tilenumB[i - 2] != 0) CheckBlue(i - 2); //열 없어진 경우 제외
				}
				else {
					CheckBlue(i - 2);
					CheckBlue(i - 1);
				}

				break;
			}
		}
	}

	else { // t = 3 , 행 2개
		for (int i = 0; i <= 6; i++) {
			if (((Blue[x][i] == 1) || (Blue[x + 1][i] == 1)) || (i == 6)) {

				//if (i == 5) i++;

				Blue[x][i - 1] = 1; //타일 표시
				tilenumB[i - 1]++; //행 타일 증가

				Blue[x + 1][i - 1] = 1; //타일 표시
				tilenumB[i - 1]++; //행 타일 증가

				CheckBlue(i - 1);
				break;
			}
		}
	}
}

void Solve(void) {

	while (!tile.empty()) {
		MOVE cur = tile.front(); tile.pop();
		
		MoveBlue(cur.t, cur.x);
		MoveGreen(cur.t, cur.y);
	}
}

void OutputData(void) {

	printf("%d\n", score);

	int cnt = 0;
	for (int i = 2; i <= 5; i++) {
		cnt += tilenumG[i];
		cnt += tilenumB[i];
	}

	printf("%d", cnt);
}

void InputData(void) {
	int a, b, c;

	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		tile.push({ a, b, c });
	}
}

int main(void) {


	InputData();
	Solve();
	OutputData();

	return 0;
}