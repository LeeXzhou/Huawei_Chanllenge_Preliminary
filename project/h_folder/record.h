#ifndef record_h
#define record_h
#include <queue>
#include "my_data_structure.h"
#include <cstring>
#include "search_policy.h"
using namespace std;
bool check_valid(const int& x, const int& y);
class Robot {
public:
	int x = -1, y = -1, goods = -1;
	int status = -1;
	int target_x = -1, target_y = -1;	
	MyPair pre[205][205], nxt[205][205];
	bool visited[205][205] = { false };
	int robot_id = 0;
	Robot() { };
	Robot(int startX, int startY);
	void robot_control();
	void find_goods();
	void find_berth();
	void find_road();
};

class Berth {
public:
	int x = -1;
	int y = -1;
	int transport_time = -1;
	int loading_speed = -1;
	int num = 0;
	Berth() { };
	Berth(int x, int y, int transport_time, int loading_speed);
};

class Boat {
public:
	int num = 0, pos = -1, status = -1, boat_id = -1;
	Boat() { };
	void boat_control();
};
extern Berth berth[berth_num + 10];
extern Robot robot[robot_num + 10];
extern Boat boat[10];
#endif // !record_h

