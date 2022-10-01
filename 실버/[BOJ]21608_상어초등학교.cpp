#include <iostream>
#include <cstring>
using namespace std;
#define MAXN (20)

int N;
int st[MAXN * MAXN + 10]; //학생 수 실수 (N * N)
int like[MAXN * MAXN + 10][4 + 10];
int map[MAXN + 10][MAXN + 10];

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void FindSeat(void) {
	//지도에 자리 입력
	memset(map, 0, sizeof(map));

	for (int a = 1; a <= N * N; a++) {
		int like_max = 0;
		int vacant_max = 0;

		int dec_r = 0; //st[a] 담을 행, 열
		int dec_c = 0;

		for (int r = N; r >= 1; r--) {
			for (int c = N; c >= 1; c--) {
				if (map[r][c] != 0) continue; //중복 방지 조건 빠짐

				int like_cnt = 0;
				int vacant_cnt = 0;


				for (int i = 0; i < 4; i++) { //r, c 인접한 네 칸 조건 따지기
					int nr = r + dr[i];
					int nc = c + dc[i];

					if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue; //범위 조건

					if (map[nr][nc] == 0) vacant_cnt++; //인접한 칸 중 빈 칸

					else {
						for (int k = 0; k < 4; k++) { //인접한 칸 중 a가 좋아하는 학생
							if (map[nr][nc] == like[st[a]][k]) like_cnt++;
						}
					}
				}
				
				if (like_max < like_cnt) { //좋아하는 학생 수 더 많을 때
					like_max = like_cnt; //최대 좋아하는 학생수 갱신
					vacant_max = vacant_cnt; //빈칸 최대 기준 갱신
					dec_r = r; dec_c = c; //행열 저장

				}
				
				if (like_max == like_cnt) { //좋아하는 학생 수 같고
					if (vacant_max <= vacant_cnt) {  //비어있는 칸 더 많거나 같을 때 (행열 역순으로 가니까, 같은 경우 더 낮은 행열 번호로 갱신)
						vacant_max = vacant_cnt;
						dec_r = r; dec_c = c; //행열 저장
					}

				}

			}
		}
		map[dec_r][dec_c] = st[a]; //최종 행열에 벡터 마지막 요소 (해당 학생) 저장
	}

}

int Solve(void) {
	//만족도 합
	int score_sum = 0;

	FindSeat();

	//확인용
	/*for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			printf("%d ", map[r][c]);
		}
		printf("\n");
	}*/


	for (int r = N * N; r >= 1; r--) {
		for (int c = N * N; c >= 1; c--) {

			int like_sum = 0;
			int score = 0;

			for (int k = 0; k < 4; k++) {
				for (int i = 0; i < 4; i++) {
					int nr = r + dr[i];
					int nc = c + dc[i];

					if ((nr < 1) || (nr > N) || (nc < 1) || (nc > N)) continue; //범위 조건 빠짐

					if (map[nr][nc] == like[map[r][c]][k]) like_sum++;

				}
			}
			if (like_sum == 1) score = 1;
			if (like_sum == 2) score = 10;
			if (like_sum == 3) score = 100;
			if (like_sum == 4) score = 1000;

			score_sum += score;
		}
	}
	return score_sum;
}

void InputData(void) {
	scanf("%d", &N);
	memset(st, 0, sizeof(st));
	memset(like, 0, sizeof(like));

	for (int i = 1; i <= N * N; i++) {
		
		scanf("%d", &st[i]);
		for (int k = 0; k < 4; k++) {
			scanf("%d", &like[st[i]][k]);
			//v[i].push_back(like[st[i]][k]);
		}
	}

	//확인용 OK
	/*for (int i = 1; i <= N * N; i++) {
		for (int k = 0; k < 4; k++) {
			printf("%d ", like[i][k]);
		}
		printf("\n");
	}*/
}

int main(void) {

	InputData();

	int ans = Solve();
	printf("%d\n", ans);

	return 0;
}