#ifndef record_h
#define record_h
#include <queue>
#include "my_data_structure.h"
#include <cstring>
#include "search_policy.h"

using namespace std;
bool check_valid(const int& x, const int& y);
bool check_valid(const MyPair& x);
const int round_robot_num(const int& x, const int& y);
class Robot {
public:
	int x = -1, y = -1, goods = -1;
	int status = -1;
	int target_x = -1, target_y = -1;	
	MyPair pre[200][200], nxt[200][200];
	bool visited[200][200] = { false };
	int robot_id = 0;
	bool move_or_not = false, no_goods = false;		//地图上没有货物
	Robot() { };
	Robot(int startX, int startY);
	void robot_control();
	void find_goods();
	void find_berth();
	void find_road(const int& min_dis);
	void clash_solve();
	bool robot_dfs(const int& move_num, stack<MyPair> move_order);
};

class Berth {
public:
	int x = -1;
	int y = -1;
	int aimed_num = 0;
	int transport_time = -1;
	int loading_speed = -1;
	int num = 0;
	int berth_id = -1;
	int close_time = 15000;
	int temp_berth_num = 0;
	Berth() { };
	Berth(int x, int y, int transport_time, int loading_speed);
	MyPair find_goods_from_berth();
	set<Record> goods_info;	//存储该泊位到每个货物的时间，货物x，y坐标，默认time从小到大
};

class Boat {
public:
	int num = 0, pos = -1, status = -1, boat_id = -1;

	int tail_status = -1;
	int aim_berth = -1, left_time = -1;
	Boat() { };
	void boat_control();
};

extern Berth berth[berth_num + 10];
extern Robot robot[robot_num + 10];
extern Boat boat[10];
extern int tail_time;
extern int max_trans_time;
extern int second_max_trans;

extern int threshold__time;
extern int trian_time;
extern MyPair berth_pair[5];
static bool trian_on = false;
static bool trian_or_not[5];
extern int couple_berth[10];
#endif // !record_h

