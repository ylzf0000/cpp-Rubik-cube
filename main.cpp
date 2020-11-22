#include "bits/stdc++.h"
using namespace std;
// 上黄 下白 前蓝 后绿 左橙 右红
enum Colors {
	empty_color,
	yellow,
	white,
	blue,
	green,
	orange,
	red,
};
enum Directions {
	EMPTY_Direction,
	U,
	D,
	F,
	B,
	L,
	R,
};
const int CUBE_SIZE = 3;

#define get_pos(arr, x, y, z) arr[x + 1][y + 1][z + 1]
//unordered_map<int, int> cube[3][3][3];
unordered_map<int, int> target_cube[3][3][3];
vector<int> cube_dirs[3][3][3];
void init_cube_dirs() {
	get_pos(cube_dirs, -1, -1, -1) = { L,D,B };
	get_pos(cube_dirs, -1, -1, +0) = { L,D };
	get_pos(cube_dirs, -1, -1, +1) = { L,D,F };

	get_pos(cube_dirs, -1, 0, -1) = { L,B };
	get_pos(cube_dirs, -1, 0, +0) = { L };
	get_pos(cube_dirs, -1, 0, +1) = { L,F };

	get_pos(cube_dirs, -1, 1, -1) = { L,U,B };
	get_pos(cube_dirs, -1, 1, +0) = { L,U };
	get_pos(cube_dirs, -1, 1, +1) = { L,U,F };

	get_pos(cube_dirs, 0, -1, -1) = { D,B };
	get_pos(cube_dirs, 0, -1, +0) = { D };
	get_pos(cube_dirs, 0, -1, +1) = { D,F };

	get_pos(cube_dirs, 0, 0, -1) = { B };
	get_pos(cube_dirs, 0, 0, +0) = {  };
	get_pos(cube_dirs, 0, 0, +1) = { F };

	get_pos(cube_dirs, 0, 1, -1) = { U,B };
	get_pos(cube_dirs, 0, 1, +0) = { U };
	get_pos(cube_dirs, 0, 1, +1) = { U,F };

	get_pos(cube_dirs, 1, -1, -1) = { R,D,B };
	get_pos(cube_dirs, 1, -1, +0) = { R,D };
	get_pos(cube_dirs, 1, -1, +1) = { R,D,F };

	get_pos(cube_dirs, 1, 0, -1) = { R,B };
	get_pos(cube_dirs, 1, 0, +0) = { R };
	get_pos(cube_dirs, 1, 0, +1) = { R,F };

	get_pos(cube_dirs, 1, 1, -1) = { U,R,B };
	get_pos(cube_dirs, 1, 1, +0) = { U,R };
	get_pos(cube_dirs, 1, 1, +1) = { U,R,F };
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
inline unordered_map<int, int>& get_block(unordered_map<int, int>(&cube)[3][3][3], const vector<int>& coord) {
	assert(coord.size() == 3);
	return cube[coord[0] + 1][coord[1] + 1][coord[2] + 1];
}
inline char get_color(unordered_map<int, int>(&cube)[3][3][3], int x, int y, int z, int f) {
	static unordered_map<int, char> colors = {
		{Colors::empty_color,'e'},
		{blue,'b'},
		{green,'g'},
		{yellow,'y'},
		{white,'w'},
		{orange,'o'},
		{red,'r'},
	};
	return colors[cube[x + 1][y + 1][z + 1][f]];
}
inline char get_color(unordered_map<int, int>(&cube)[3][3][3], const vector<int>& coord, int f) {
	return get_color(cube, coord[0], coord[1], coord[2], f);
}
void rotate_cube(unordered_map<int, int>(&cube)[3][3][3], const vector<int>& center, bool clockwise, bool show = false) {
	assert(center.size() == 3);
	int axis = -1;
	for (int i = 0; i < 3; ++i)
		if (center[i] == 1 || center[i] == -1) {
			axis = i;
			break;
		}
	bool _clockwise = clockwise;
	if (center[axis] == -1)
		_clockwise = !_clockwise;
	if (axis == 1)
		_clockwise = !_clockwise;
	//cout << "_clockwise: " << _clockwise << endl;
	//if (center[1] == -1)
	//	clockwise = !clockwise;
	// 默认顺时针顺序
	vector<vector<int>> corner_coords = { {-1,1},{1,1},{1,-1},{-1,-1} };
	vector<vector<int>> edge_coords = { {0,1},{1,0},{0,-1},{-1,0} };

	for (auto& c : corner_coords)
		c.insert(c.begin() + axis, center[axis]);
	for (auto& e : edge_coords)
		e.insert(e.begin() + axis, center[axis]);

	if (!_clockwise) {
		reverse(corner_coords.begin(), corner_coords.end());
		reverse(edge_coords.begin(), edge_coords.end());
	}

	// 平移块到正确位置
	auto translation = [&](const vector<vector<int>>& coord) {
		unordered_map<int, int> tail_coord = get_block(cube, coord.back());
		for (int i = coord.size() - 1; i > 0; --i) {
			get_block(cube, coord[i]) = get_block(cube, coord[i - 1]);
		}
		get_block(cube, coord[0]) = tail_coord;
	};
	translation(corner_coords);
	translation(edge_coords);

	// 旋转块到正确方向 
	// 存储顺时针转动时块的方向
	vector<int> rotate_face[3][3][3];
	get_pos(rotate_face, 0, 0, 1) = { L,U,R,D };
	get_pos(rotate_face, 0, 0, -1) = { D,R,U,L };

	get_pos(rotate_face, 0, 1, 0) = { L,B,R,F };
	get_pos(rotate_face, 0, -1, 0) = { F,R,B,L };

	get_pos(rotate_face, 1, 0, 0) = { F,U,B,D };
	get_pos(rotate_face, -1, 0, 0) = { D,B,U,F };

	if (!clockwise) {
		swap(get_pos(rotate_face, 0, 0, 1), get_pos(rotate_face, 0, 0, -1));
		swap(get_pos(rotate_face, 0, 1, 0), get_pos(rotate_face, 0, -1, 0));
		swap(get_pos(rotate_face, 1, 0, 0), get_pos(rotate_face, -1, 0, 0));
	}

	auto rotate_block = [&](unordered_map<int, int>& block) {
		vector<int> face = get_pos(rotate_face, center[0], center[1], center[2]);
		int tail_c = block[face.back()];
		for (int i = face.size() - 1; i > 0; --i) {
			block[face[i]] = block[face[i - 1]];
		}
		block[face[0]] = tail_c;
	};
	for (const auto& coord : corner_coords) {
		//cout << coord[0] << " " << coord[1] << " " << coord[2] << " \n";
		rotate_block(get_block(cube, coord));
	}
	for (const auto& coord : edge_coords) {
		rotate_block(get_block(cube, coord));
	}
	void print_cube(unordered_map<int, int>(&cube)[3][3][3]);
	if (show)
		print_cube(cube);
}

void print_cube(unordered_map<int, int>(&cube)[3][3][3]) {
	int x, y, z;
	cout << "----------Forward\n";
	z = 1;
	for (y = 1; y >= -1; --y) {
		for (x = -1; x <= 1; ++x) {

			cout << get_color(cube, x, y, z, F) << " ";
		}
		cout << endl;
	}
	cout << "----------Back\n";
	z = -1;
	for (y = 1; y >= -1; --y) {
		for (x = -1; x <= 1; ++x) {

			cout << get_color(cube, x, y, z, B) << " ";
		}
		cout << endl;
	}
	cout << "----------Upper\n";
	y = 1;
	for (z = -1; z <= 1; ++z) {
		for (x = -1; x <= 1; ++x) {
			cout << get_color(cube, x, y, z, U) << " ";
		}
		cout << endl;
	}
	cout << "----------Down\n";
	y = -1;
	for (z = 1; z >= -1; --z) {
		for (x = -1; x <= 1; ++x) {
			cout << get_color(cube, x, y, z, D) << " ";
		}
		cout << endl;
	}
	cout << "----------Right\n";
	x = 1;
	for (y = 1; y >= -1; --y) {
		for (z = 1; z >= -1; --z) {
			cout << get_color(cube, x, y, z, R) << " ";
		}
		cout << endl;
	}
	cout << "----------Left\n";
	x = -1;
	for (y = 1; y >= -1; --y) {
		for (z = -1; z <= 1; ++z) {
			cout << get_color(cube, x, y, z, L) << " ";
		}
		cout << endl;
	}
	cout << "----------Over\n\n";
}


static unordered_map<string, function<void(unordered_map<int, int>(&)[3][3][3])>> rotate_space = {
	{"F",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{0,0,1},true); }},
	{"F'",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{0,0,1},false); }},

	{"B",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{0,0,-1},true); }},
	{"B'",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{0,0,-1},false); }},

	{"R",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{1,0,0},true); }},
	{"R'",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{1,0,0},false); }},

	{"L",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{-1,0,0},true); }},
	{"L'",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{-1,0,0},false); }},

	{"U",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{0,1,0},true); }},
	{"U'",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{0,1,0},false); }},

	{"D",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{0,-1,0},true); }},
	{"D'",[&](unordered_map<int, int>(&cube)[3][3][3]) {rotate_cube(cube,{0,-1,0},false); }},
};



bool is_reach_target(const unordered_map<int, int>(&cube)[3][3][3]) {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				for (int x : cube_dirs[i][j][k])
					if (cube[i][j][k].at(x) != x)
						return false;
	return true;
}

int distance_to_target(const unordered_map<int, int>(&cube)[3][3][3]) {
	int res = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				for (int x : cube_dirs[i][j][k])
					res += cube[i][j][k].at(x) != x;
	return res;
}

vector<string> opers;

bool ida_star(int max_depth, int depth, unordered_map<int, int>(&cube)[3][3][3]) {
	if (depth > max_depth)
		return false;
	if (is_reach_target(cube))
		return true;
	//if (depth + distance_to_target(cube) > max_depth)
	//	return false;
	for (const string& s : { "F","B","R","L","U","D" }) {
		const string& s_ = s + "'";

		rotate_space[s](cube);
		if (ida_star(max_depth, depth + 1, cube)) {
			opers.push_back(s);
			return true;
		}
		rotate_space[s_](cube);
		rotate_space[s_](cube);
		if (ida_star(max_depth, depth + 1, cube)) {
			opers.push_back(s_);
			return true;
		}
		rotate_space[s](cube);
	}
	return false;
}

int main() {
	init_cube_dirs();
	init_target_cube();
	vector<string> vs = { "F","F'","B","B'","R","R'","L","L'","U","U'","D","D'", };

	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<> distrib(0, vs.size() - 1);

	int n;
	while (cin >> n) {
		opers.clear();
		// 初始化魔方
		unordered_map<int, int> cube[3][3][3];
		for (int i1 = 0; i1 < 3; ++i1)
			for (int i2 = 0; i2 < 3; ++i2)
				for (int i3 = 0; i3 < 3; ++i3)
					cube[i1][i2][i3] = target_cube[i1][i2][i3];
		// 随机生成魔方
		cout << "generate " << n << " order: \n";
		for (int i = 0; i < n; ++i) {
			string op = vs[distrib(gen)];
			cout << op << " ";
			rotate_space[op](cube);
		}
		//cout << "\ncube:\n";
		//print_cube(cube);
		// 求解魔方
		int max_depth = 20;
		bool ret = false;
		for (int depth = 1; depth <= max_depth; ++depth) {
			if (ida_star(depth, 0, cube)) {
				ret = true;
				break;
			}
		}
		//cout << "is_reach_target: " << is_reach_target(cube) << endl;
		//cout << "distance_to_target: " << distance_to_target(cube) << endl;

		//print_cube(cube);
		puts("");
		if (is_reach_target(cube)) {
			for (int i = opers.size() - 1; i >= 0; --i)
				cout << opers[i] << " ";
			cout << endl;
		}
	}

	return 0;
	//for (auto& s : vs) {
	//	cout << "rotate: " << s << endl;
	//	rotate_space()[s](target_cube);
	//	print_cube(target_cube);
	//}

}

