#include "../h_folder/search_policy.h"
using namespace std;
priority_queue<Plan, vector<Plan>, less<Plan>> Search_Policy::policy;
Plan::Plan(int v, int t, int i, int x, int y)
{
	value = v, time = t, id = i, pre_x = x, pre_y = y;
}

bool Plan::operator < (const Plan& tmp) const
{
	return value * tmp.time < time * tmp.value;
}

pair<int, int> Search_Policy::choose()
{
	return { 0, 0 };
}

void Search_Policy::BFS(int x, int y)
{
	int cur_x = x, cur_y = y, pre_x = -1, pre_y = -1, num = 0, val, time;
	queue<Record> rec;	//记录当前这个点的耗时以及能拿到的最多value
	while (true)
	{
		Record tmp = rec.front();
		val = tmp.val, time = tmp.time, cur_x = tmp.cur_x, cur_y = tmp.cur_y;	
		if (cur_x == 1 && cur_y == 1) //判断是否在港口
		{
			policy.push(Plan(val, time, num, pre_x, pre_y));
		}
	}
}