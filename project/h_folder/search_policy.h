#ifndef search_policy_h
#define search_policy_h
#include "record.h"
#include <queue>
using namespace std;
/*
˼·1����̰��value/time���������ŷ���
���������������ɸ�����ȥ�����ø����������ŵģ�
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
	static priority_queue<Plan, vector<Plan>, less<Plan>> policy;	//�������ѡ�񷽰���
	pair<int, int> choose();
	void BFS(int x, int y);
private:

};
#endif
