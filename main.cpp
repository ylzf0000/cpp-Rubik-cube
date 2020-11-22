#include "bits/stdc++.h"
using namespace std;
// 上黄 下白 前蓝 后绿 左橙 右红
enum Colors {
	yellow,
	white,
	blue,
	green,
	orange,
	red,
};
enum Directions {
	U,
	D,
	F,
	B,
	L,
	R,
};
const int CUBE_SIZE = 3;
int cube[3][3][3][6];
//int target_cube[3][3][3][6];
unordered_map<int, int> cube[3][3][3];
unordered_map<int, int> target_cube[3][3][3];
vector<int> cube_dirs[3][3][3];
void init_cube_dirs() {
	cube_dirs[0][0][0] = { F,L,D };
	cube_dirs[0][0][1] = { L,D };
	cube_dirs[0][0][2] = { B,L,D };

	cube_dirs[0][1][0] = { F,L };
	cube_dirs[0][1][1] = { L };
	cube_dirs[0][1][2] = { B,L };

	cube_dirs[0][2][0] = { F,L,U };
	cube_dirs[0][2][1] = { L,U };
	cube_dirs[0][2][2] = { U,B,L };

	cube_dirs[1][0][0] = { F,D };
	cube_dirs[1][0][1] = { D };
	cube_dirs[1][0][2] = { B,D };

	cube_dirs[1][1][0] = { F };
	cube_dirs[1][1][1] = {  };
	cube_dirs[1][1][2] = { B };

	cube_dirs[1][2][0] = { F,U };
	cube_dirs[1][2][1] = { U };
	cube_dirs[1][2][2] = { U,B };

	cube_dirs[2][0][0] = { F,R,D };
	cube_dirs[2][0][1] = { R,D };
	cube_dirs[2][0][2] = { B,R,D };

	cube_dirs[2][1][0] = { F,R };
	cube_dirs[2][1][1] = { R };
	cube_dirs[2][1][2] = { B,R };

	cube_dirs[2][2][0] = { F,U,R };
	cube_dirs[2][2][1] = { U,R };
	cube_dirs[2][2][2] = { U,B,R };
}
void init_target_cube() {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				for (int x : cube_dirs[i][j][k])
					target_cube[i][j][k][x] = x;
}
// [-1,1]
inline unordered_map<int, int>& get_block(unordered_map<int, int>(&cube)[3][3][3], int x, int y, int z) {
	return cube[x + 1][y + 1][z + 1];
}
void rotate_cube(unordered_map<int, int>(&cube)[3][3][3], const vector<int> &center, bool clockwise) {
	assert(center.size() == 3);

}
int main() {
	init_target_cube();
}

