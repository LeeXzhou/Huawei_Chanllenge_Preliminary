#ifndef record_h
#define record_h
#include <utility>
using namespace std;
const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int N = 210;
extern pair<int, int> pre_position[205][205];
class Robot {
public:
	int x = -1, y = -1, goods = -1;
	int status = -1;
	int mbx = -1, mby = -1;
	Robot() { };
	Robot(int startX, int startY);
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
	int num = -1, pos = -1, status = -1;
	Boat() { };
};
extern Berth berth[berth_num + 10];
extern Robot robot[robot_num + 10];
extern Boat boat[10];
extern int money, boat_capacity, id;
extern char ch[N][N];
extern pair<int, int> goods_map[N][N]; //first记录value， second记录到期时间
extern short dis[40005][10];
#endif // !record_h

