#ifndef search_policy_h
#define search_policy_h
#include "record.h"
#include <queue>
using namespace std;
/*
思路1：嗯贪，value/time最大的是最优方案
*/
struct plan{
	int value = 0, time = 0, id, pre_x, pre_y;
	plan(int v, int t, int i, int x, int y);
	bool operator < (const plan& tmp) const;
};
struct record {
	int val, time, cur_x, cur_y;
};
class search_policy {
public:
	static priority_queue<plan, vector<plan>, less<plan>> policy;	//留到最后选择方案用
	pair<int, int> choose();
	void BFS(int x, int y);
private:

};
#endif
