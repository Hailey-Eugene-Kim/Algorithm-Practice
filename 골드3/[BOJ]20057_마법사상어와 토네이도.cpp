#include <iostream>
#include <cstring>
using namespace std;
#define MAXN (499)

int N;
int A[MAXN + 20][MAXN + 20];
int Tdir, Tlen;
int TR, TC;

void TornadoMove(int Tdir, int Tlen) {
	static int dr[] = {0, 1, 0, -1}; //서 남 동 북
	static int dc[] = {-1, 0, 1, 0}; //서 남 동 북 //실수

	TR = TR + Tlen * dr[Tdir];
	TC = TC + Tlen * dc[Tdir]; //실수
}

void SandSpread(int TR, int TC, int Tdir) { //A[TR][TC]의 모래 확산 , Tdir에 따라 //서 남 동 북

	//소수점 아래는 버린다,,,
	//버릴 경우 이동 안 하는 거니까 a에 그대로 쌓여야함

	int a = 0;
	if (Tdir == 0) { //서 //기준
		A[TR - 1][TC + 1] += A[TR][TC] * 0.01; //소수점 아래는 버림
		a += A[TR][TC] * 0.01; //소수점 아래는 버림
		A[TR + 1][TC + 1] += A[TR][TC] * 0.01;
		a += A[TR][TC] * 0.01;
		A[TR - 1][TC] += A[TR][TC] * 0.07;
		a += A[TR][TC] * 0.07;
		A[TR + 1][TC] += A[TR][TC] * 0.07;
		a += A[TR][TC] * 0.07;
		A[TR - 2][TC] += A[TR][TC] * 0.02;
		a += A[TR][TC] * 0.02;
		A[TR + 2][TC] += A[TR][TC] * 0.02;
		a += A[TR][TC] * 0.02;
		A[TR - 1][TC - 1] += A[TR][TC] * 0.1;
		a += A[TR][TC] * 0.1;
		A[TR + 1][TC - 1] += A[TR][TC] * 0.1;
		a += A[TR][TC] * 0.1;
		A[TR][TC - 2] += A[TR][TC] * 0.05;
		a += A[TR][TC] * 0.05;

		A[TR][TC - 1] += A[TR][TC] - a;
		A[TR][TC] = 0; //해당칸 소멸
	}

	//동 => 열만 부등호 반대 //2
	if (Tdir == 2) {
		A[TR - 1][TC - 1] += A[TR][TC] * 0.01; //소수점 아래는 버림
		a += A[TR][TC] * 0.01; //소수점 아래는 버림
		A[TR + 1][TC - 1] += A[TR][TC] * 0.01;
		a += A[TR][TC] * 0.01;
		A[TR - 1][TC] += A[TR][TC] * 0.07;
		a += A[TR][TC] * 0.07;
		A[TR + 1][TC] += A[TR][TC] * 0.07;
		a += A[TR][TC] * 0.07;
		A[TR - 2][TC] += A[TR][TC] * 0.02;
		a += A[TR][TC] * 0.02;
		A[TR + 2][TC] += A[TR][TC] * 0.02;
		a += A[TR][TC] * 0.02;
		A[TR - 1][TC + 1] += A[TR][TC] * 0.1;
		a += A[TR][TC] * 0.1;
		A[TR + 1][TC + 1] += A[TR][TC] * 0.1;
		a += A[TR][TC] * 0.1;
		A[TR][TC + 2] += A[TR][TC] * 0.05;
		a += A[TR][TC] * 0.05;

		A[TR][TC + 1] += A[TR][TC] - a; //a
		A[TR][TC] = 0; //해당칸 소멸
	}

	//북 => 행, 열 반대 //3
	if (Tdir == 3) { 
		A[TR + 1][TC - 1] += A[TR][TC] * 0.01; //소수점 아래는 버림
		a += A[TR][TC] * 0.01; //소수점 아래는 버림
		A[TR + 1][TC + 1] += A[TR][TC] * 0.01;
		a += A[TR][TC] * 0.01;
		A[TR][TC - 1] += A[TR][TC] * 0.07;
		a += A[TR][TC] * 0.07;
		A[TR][TC + 1] += A[TR][TC] * 0.07;
		a += A[TR][TC] * 0.07;
		A[TR][TC - 2] += A[TR][TC] * 0.02;
		a += A[TR][TC] * 0.02;
		A[TR][TC +2] += A[TR][TC] * 0.02;
		a += A[TR][TC] * 0.02;
		A[TR - 1][TC - 1] += A[TR][TC] * 0.1;
		a += A[TR][TC] * 0.1;
		A[TR - 1][TC + 1] += A[TR][TC] * 0.1;
		a += A[TR][TC] * 0.1;
		A[TR - 2][TC] += A[TR][TC] * 0.05;
		a += A[TR][TC] * 0.05;

		A[TR - 1][TC] += A[TR][TC] - a; //a
		A[TR][TC] = 0; //해당칸 소멸
	}
	
	//남 => 행, 열 반대, 행 부등호 반대 //1
	if (Tdir == 1) {
		A[TR - 1][TC - 1] += A[TR][TC] * 0.01;
		a += A[TR][TC] * 0.01;
		A[TR - 1][TC + 1] += A[TR][TC] * 0.01;
		a += A[TR][TC] * 0.01;
		A[TR][TC - 1] += A[TR][TC] * 0.07;
		a += A[TR][TC] * 0.07;
		A[TR][TC + 1] += A[TR][TC] * 0.07;
		a += A[TR][TC] * 0.07;
		A[TR][TC - 2] += A[TR][TC] * 0.02;
		a += A[TR][TC] * 0.02;
		A[TR][TC + 2] += A[TR][TC] * 0.02;
		a += A[TR][TC] * 0.02;
		A[TR + 1][TC - 1] += A[TR][TC] * 0.1;
		a += A[TR][TC] * 0.1;
		A[TR + 1][TC + 1] += A[TR][TC] * 0.1;
		a += A[TR][TC] * 0.1;
		A[TR + 2][TC] += A[TR][TC] * 0.05;
		a += A[TR][TC] * 0.05;

		A[TR + 1][TC] += A[TR][TC] - a; //a
		A[TR][TC] = 0; //해당칸 소멸
	}
}

int SumSand(void) {
	//가장자리 3 합산
	int sum = 0;

	for (int i = 1; i <= 3; i++) { //위
		for (int j = 1; j <= N + 6; j++) {
			sum += A[i][j];
			//A[i][j] = 1;
		}
	}

	for (int i = N + 4; i <= N + 6; i++) { //아
		for (int j = 1; j <= N + 6; j++) {
			sum += A[i][j];
			//A[i][j] = 2;
		}
	}

	for (int i = 4; i <= N + 3; i++) { //왼
		for (int j = 1; j <= 3; j++) {
			sum += A[i][j];
			//A[i][j] = 3;
		}
	}

	for (int i = 4; i <= N + 3; i++) { //오
		for (int j = N + 4; j <= N + 6; j++) {
			sum += A[i][j];
			//A[i][j] = 4;
		}
	}

	return sum;
}

int Solve(void) {
	//토네이도 규칙에 맞게 for 루프
	//토네이도 한 번에 한 칸 이동 조건 놓침

	Tdir = 0;
	TR = (N / 2 + 1) + 3; //실수
	TC = (N / 2 + 1) + 3;

	//Tlen N - 1까지 토네이도 ,Tlen 당 2번 //N - 1일 때 한 번 더
	for (Tlen = 1; Tlen <= N - 1; Tlen++) { 

		int num = 2;
		if (Tlen == N - 1) num = 3;
		for (int i = 1; i <= num; i++) { //Tlen 당 2번 //N - 1일 때 한 번 더
			 
			//현재 토네이도 위치부터 다음 토네이도 위치까지 이동
			static int dr[] = { 0, 1, 0, -1 }; //서 남 동 북
			static int dc[] = { -1, 0, 1, 0 }; //서 남 동 북 //실수

			for (int j = 1; j <= Tlen; j++) {
				int nr = TR + j * dr[Tdir];
				int nc = TC + j * dc[Tdir];

				//A[nr][nc] = 8;
				SandSpread(nr, nc, Tdir); 
			}

			TR = TR + Tlen * dr[Tdir]; //위치 갱신
			TC = TC + Tlen * dc[Tdir]; //실수
			Tdir = (Tdir + 1) % 4; //방향 갱신
		}
	}

	//최종
	int sol = SumSand(); //OK
	return sol;
}

void InputData(void) {
	scanf("%d", &N);
	memset(A, 0, sizeof(A));
	for (int i = 4; i <= N + 3; i++) {
		for (int j = 4; j <= N + 3; j++) {
			scanf("%d", &A[i][j]);
		}
	}
}

int main(void) {
	InputData();
	int ans = Solve();
	printf("%d", ans);
	return 0;
}