#ifndef record_h
#define record_h
#include <queue>
#include "my_data_structure.h"
#include <cstring>
using namespace std;
const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int N = 210;
extern pair<int, int> pre_position[205][205];
const MyPair dx_dy[4] = { {0, 1} , {0, -1}, {-1, 0}, {1, 0} };
bool check_valid(int x, int y);
class Robot {
public:
	int x = -1, y = -1, goods = -1;
	int status = -1;
	int target_x = -1, target_y = -1;
	Robot() { };
	Robot(int startX, int startY);
	void robot_control();
	MyPair pre[205][205], nxt[205][205];
	bool visited[205][205];
	int robot_id = 0;
};

class Berth {
public:
	int x = -1;
	int y = -1;
	int transport_time = -1;
	int loading_speed = -1;
	Berth() { };
	Berth(int x, int y, int transport_time, int loading_speed);
};

class Boat {
public:
	int num = 0, pos = -1, status = -1;
	Boat() { };
};
extern Berth berth[berth_num + 10];
extern Robot robot[robot_num + 10];
extern Boat boat[10];
extern int money, boat_capacity, id;
extern char ch[N][N];
extern pair<int, int> goods_map[N][N]; //first记录value， second记录到期时间
extern short dis [205][205][10];
#endif // !record_h

