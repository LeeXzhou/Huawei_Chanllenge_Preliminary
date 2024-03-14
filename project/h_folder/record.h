#ifndef record_h
#define record_h
#include <queue>
#include "my_data_structure.h"
#include <cstring>
#include "search_policy.h"
using namespace std;
bool check_valid(const int& x, const int& y);
bool check_valid(const MyPair& x);
class Robot {
public:
	int x = -1, y = -1, goods = -1;
	int status = -1;
	int target_x = -1, target_y = -1;	
	MyPair pre[200][200], nxt[200][200];
	bool visited[200][200] = { false };
	int robot_id = 0;
	bool move_or_not = false;
	Robot() { };
	Robot(int startX, int startY);
	void robot_control();
	void find_goods();
	void find_berth();
	void find_road(const int& min_dis);
	void clash_solve();
	bool robot_dfs(const int& move_num, stack<MyPair>move_order);
};

class Berth {
public:
	int x = -1;
	int y = -1;
	bool aimed = false;
	int transport_time = -1;
	int loading_speed = -1;
	int num = 0;
	int berth_id = -1;
	Berth() { };
	Berth(int x, int y, int transport_time, int loading_speed);
	MyPair find_goods_from_berth();
	set<Record> goods_info;	//存储该泊位到每个货物的时间，货物x，y坐标，默认time从小到大
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

