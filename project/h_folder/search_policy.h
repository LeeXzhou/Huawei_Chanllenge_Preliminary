#ifndef search_policy_h
#define search_policy_h
#include "my_data_structure.h"
#include <queue>
using namespace std;
const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int N = 210;
extern MyPair pre_position[205][205];
const MyPair dx_dy[4] = { {0, 1} , {0, -1}, {-1, 0}, {1, 0} };
extern int money, boat_capacity, id;
extern char ch[N][N];
extern MyPair goods_map[N][N]; //first记录value， second记录到期时间
extern int dis[205][205][10];
/*
思路1：嗯贪，value/time最大的是最优方案
不变性条件：若干个参数去决定拿个方案是最优的，
*/
class Search_Policy {
public:
	static priority_queue<Plan, vector<Plan>, less<Plan>> policy;	//留到最后选择方案用
	static unique_ptr<MyPair[]> choose();
private:

};
#endif
