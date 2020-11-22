//int cube[6][9];
//int target_cube[6][9];
//void set_target_cube() {
//	for (int i = 0; i < 6; ++i)
//		fill(target_cube[i], target_cube[i] + 9, i);
//}
//void transform_surface(int(&dst)[9], const vector<int>& n) {
//	int raw[9];
//	memcpy(raw, dst, sizeof(dst));
//	for (int i = 0; i < n.size(); ++i) {
//		dst[i] = raw[n[i]];
//	}
//}
//
////************************************
//// Method:    rotate_surface
//// Parameter: int surface 旋转面
//// Parameter: const vector<int> & s4 4个相邻面，0,1,2,3 -> 3,0,1,2
//// Parameter: const vector<int> & i3 旋转的块序号
//// Parameter: bool clockwise 是否顺时针
////************************************
//void rotate_surface(int surface, const vector<int>& s4, const vector<int>& i3, bool clockwise) {
//	int tail[] = { cube[s4[3]][i3[0]],cube[s4[3]][i3[1]], cube[s4[3]][i3[2]], };
//	for (int i = s4.size() - 1; i > 0; --i) {
//		cube[s4[i]][i3[0]] = cube[s4[i - 1]][i3[0]];
//		cube[s4[i]][i3[1]] = cube[s4[i - 1]][i3[1]];
//		cube[s4[i]][i3[2]] = cube[s4[i - 1]][i3[2]];
//	}
//	cube[s4[0]][i3[0]] = tail[0];
//	cube[s4[0]][i3[1]] = tail[1];
//	cube[s4[0]][i3[2]] = tail[2];
//	if (clockwise) {
//		transform_surface(cube[surface], {
//			6,3,0,
//			7,4,1,
//			8,5,2
//			});
//	}
//	else {
//		transform_surface(cube[surface], {
//			2,5,8,
//			1,4,7,
//			0,3,6,
//			});
//	}
//}
//void rotate_right_up() {
//	rotate_surface(red, { blue,yellow,green,white }, { 2,5,8 }, true);
//}
//
//void rotate_right_down() {
//	rotate_surface(red, { yellow,blue,white,green }, { 2,5,8 }, false);
//}
//
//void rotate_left_up() {
//	rotate_surface(orange, { blue,yellow,green,white }, { 0,3,6 }, false);
//}
//void rotate_left_down() {
//	rotate_surface(orange, { yellow,blue,white,green }, { 0,3,6 }, true);
//}
//void rotate_up_right() {
//	rotate_surface(red, { yellow,blue,white,green }, { 2,5,8 }, false);
//}
//int tmp_red[9];
//memcpy(tmp_red, cube[red], sizeof(cube[red]));
//cube[red][0] = tmp_red[6];
//cube[red][1] = tmp_red[3];
//cube[red][2] = tmp_red[0];
//cube[red][3] = tmp_red[7];
//cube[red][5] = tmp_red[1];
//cube[red][6] = tmp_red[8];
//cube[red][7] = tmp_red[5];
//cube[red][8] = tmp_red[2];

	//int tmp_red[9];
	//memcpy(tmp_red, cube[red], sizeof(cube[red]));
	//cube[red][0] = tmp_red[2];
	//cube[red][1] = tmp_red[5];
	//cube[red][2] = tmp_red[8];
	//cube[red][3] = tmp_red[1];
	//cube[red][5] = tmp_red[7];
	//cube[red][6] = tmp_red[0];
	//cube[red][7] = tmp_red[3];
	//cube[red][8] = tmp_red[6];

	//int blue_258[] = { cube[blue][2],cube[blue][5], cube[blue][8], };
	//auto lst = vector<int>{ white,green,yellow,blue, };
	//for (int i = lst.size() - 1; i > 0; --i) {
	//	cube[lst[i]][2] = cube[lst[(i + 3) % 4]][2];
	//	cube[lst[i]][5] = cube[lst[(i + 3) % 4]][5];
	//	cube[lst[i]][8] = cube[lst[(i + 3) % 4]][8];
	//}
	//cube[white][2] = blue_258[0];
	//cube[white][5] = blue_258[1];
	//cube[white][8] = blue_258[2];

	//transform_surface(cube[red], {
	//	2,5,8,
	//	1,4,7,
	//	0,3,6,
	//	});