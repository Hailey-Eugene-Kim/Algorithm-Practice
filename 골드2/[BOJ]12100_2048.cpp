#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
#define MAX 20

int N;
struct BLOCK {
	int val, flag;
};
BLOCK map[MAX + 10][MAX + 10];
BLOCK map_cpy[MAX + 10][MAX + 10];
deque <BLOCK> block[MAX + 10];

deque <int> selectDir; //상 하 좌 우 1 2 3 4 

int sol;

int CalBlock(void) { //selectDir 이동 후 가장 큰 블록

	//block에 map 행 or 열 입력
			//0 ~  N - 1 0값 삭제, 0 push
			//연속 체크 : r == r+1 , 둘 다 flag == 0
				//앞 값에 합치고, flag = 1, 뒷 값 erase
			//map 열에 block으로 갱신
				//최대값 체크

			//block에 map 행 or 열 입력

	//한 번의 이동에서 이미 합쳐진 블록은 또 다른 블록과 다시 합쳐질 수 없다. 
	//=> 해당 이동에서만 flag 유효

	int max = -1;
	memcpy(map_cpy, map, sizeof(map));

	int P = selectDir.size();
	for (int p = 0; p < P; p++) {
		int cur = selectDir[p];

		if ((cur == 1) || (cur == 2)) { //상 하

			for (int c = 1; c <= N; c++) {
				block[c].clear();
				for (int r = 1; r <= N; r++) {
					block[c].push_back(map_cpy[r][c]);
				}
			}

			if (cur == 1) {//상
				for (int c = 1; c <= N; c++) {
					int cnt = 0;
					for (int r = 0; r <= N - 2; r++) { //deque 0 베이스 
						//0 값 삭제
						if (block[c][r - cnt].val == 0) {
							block[c].erase(block[c].begin() + (r - cnt));
							block[c].push_back({ 0, 0 });
							cnt++;
						}
					}

					for (int r = 0; r < N - 1 - cnt; r++) { //deque 0 베이스 
						
						//0이 아닌 연속 값 삭제
						if ((block[c][r].val == block[c][r + 1].val) && (block[c][r].flag == 0) && (block[c][r + 1].flag == 0)) {
							block[c][r].val *= 2;
							block[c][r].flag = 1;
							block[c].erase(block[c].begin() + (r + 1));
							block[c].push_back({ 0, 0 });
						}
					}
				}
			}

			if (cur == 2) { //하
				for (int c = 1; c <= N; c++) {
					int cnt = 0;
					for (int r = N - 1; r > 0; r--) { //deque 0 베이스 
						//0 값 삭제
						if (block[c][r + cnt].val == 0) {
							block[c].erase(block[c].begin() + (r + cnt));
							block[c].push_front({ 0, 0 });
							cnt++;
						}

					}

					for (int r = N - 1; r > cnt; r--) { 
						//0이 아닌 연속 값 삭제
						if ((block[c][r].val == block[c][r - 1].val) && (block[c][r].flag == 0) && (block[c][r - 1].flag == 0)) {
							block[c][r].val *= 2;
							block[c][r].flag = 1;
							block[c].erase(block[c].begin() + (r - 1));
							block[c].push_front({ 0, 0 });
						}
					}
				}
			}

			//map 열에 block으로 갱신
				//flag 제외하고 입력 (다음 턴에서는 합치는 것 가능)
			for (int c = 1; c <= N; c++) {
				for (int r = 0; r < N; r++) {
					map_cpy[r + 1][c] = {};
					map_cpy[r + 1][c].val = block[c][r].val;
					if (max < map_cpy[r + 1][c].val) max = map_cpy[r + 1][c].val;
				}
			}

		}

		else if ((cur == 3) || (cur == 4)) { //좌 우

			for (int r = 1; r <= N; r++) {
				block[r].clear();
				for (int c = 1; c <= N; c++) {
					block[r].push_back(map_cpy[r][c]);
				}
			}

			if (cur == 3) {//좌
				for (int r = 1; r <= N; r++) {
					int cnt = 0;
					for (int c = 0; c < N - 1; c++) { //deque 0 베이스 
						//0 값 삭제
						if (block[r][c - cnt].val == 0) {
							block[r].erase(block[r].begin() + (c - cnt));
							block[r].push_back({ 0, 0 });
							cnt++;
						}
					}

					for (int c = 0; c < N - 1 - cnt; c++) { //deque 0 베이스 
						//0이 아닌 연속 값 삭제
						if ((block[r][c].val == block[r][c + 1].val) && (block[r][c].flag == 0) && (block[r][c + 1].flag == 0)) {
							block[r][c].val *= 2;
							block[r][c].flag = 1;
							block[r].erase(block[r].begin() + (c + 1));
							block[r].push_back({ 0, 0 });
						}
					}
				}
			}

			if (cur == 4) { //우
				for (int r = 1; r <= N; r++) {
					int cnt = 0;
					for (int c = N - 1; c > 0; c--) { //deque 0 베이스 
						//0 값 삭제
						if (block[r][c + cnt].val == 0) {
							block[r].erase(block[r].begin() + (c + cnt));
							block[r].push_front({ 0, 0 });
							cnt++;
						}
					}

					for (int c = N - 1; c > cnt; c--) { //deque 0 베이스 
						//0이 아닌 연속 값 삭제
						if ((block[r][c].val == block[r][c - 1].val) && (block[r][c].flag == 0) && (block[r][c - 1].flag == 0)) {
							block[r][c].val *= 2;
							block[r][c].flag = 1;
							block[r].erase(block[r].begin() + (c - 1));
							block[r].push_front({ 0, 0 });
						}
					}
				}
			}

			//map 열에 block으로 갱신
			for (int r = 1; r <= N; r++) {
				for (int c = 0; c < N; c++) {
					map_cpy[r][c + 1] = {};
					map_cpy[r][c + 1].val = block[r][c].val;
					if (max < map_cpy[r][c + 1].val) max = map_cpy[r][c + 1].val;
				}
			}

		}
	}

	return max;
}

void DFS(int cnt) {

	if (cnt > 5) return;

	if (cnt > 0) {

		if ((selectDir.size() == 5) && (selectDir[0] == 3) && (selectDir[1] == 3) && (selectDir[2] == 3) && (selectDir[3] == 3) && (selectDir[4] == 1)) {
			int a = 0;
		}

		int maxBlock = CalBlock();

		if (sol < maxBlock) sol = maxBlock;
	}

	for (int d = 1; d <= 4; d++) {

		selectDir.push_back(d);
		DFS(cnt + 1);
		selectDir.pop_back();

	}
}

void InputData(void) {
	scanf("%d", &N);

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			scanf("%d", &map[r][c].val);
			map[r][c].flag = 0;
		}
	}
}

int main(void) {
	InputData();
	sol = -1;
	DFS(0);
	printf("%d", sol);
	return 0;
}
