#ifndef search_policy_h
#define search_policy_h
#include "record.h"
#include <queue>
using namespace std;
/*
思路1：嗯贪，value/time最大的是最优方案
不变性条件：若干个参数去决定拿个方案是最优的，
*/
struct Plan{
	int value = 0, time = 0, id, pre_x, pre_y;
	Plan(int v, int t, int i, int x, int y);
	bool operator < (const Plan& tmp) const;
};
struct Record {
	int val, time, cur_x, cur_y;
};
class Search_Policy {
public:
	static priority_queue<Plan, vector<Plan>, less<Plan>> policy;	//留到最后选择方案用
	pair<int, int> choose();
	void BFS(int x, int y);
private:

};
#endif
