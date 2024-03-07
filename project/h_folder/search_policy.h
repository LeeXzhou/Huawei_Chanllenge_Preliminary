#ifndef search_policy_h
#define search_policy_h
#include "record.h"
#include <queue>
using namespace std;
/*
˼·1����̰��value/time���������ŷ���
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
	static priority_queue<plan, vector<plan>, less<plan>> policy;	//�������ѡ�񷽰���
	pair<int, int> choose();
	void BFS(int x, int y);
private:

};
#endif
