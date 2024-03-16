#include "../h_folder/search_policy.h"
using namespace std;
priority_queue<Plan, vector<Plan>, less<Plan>> Search_Policy::policy;

unique_ptr<MyPair[]> Search_Policy::choose()
{
	bool visited[10];
	memset(visited, false, 10);
	unique_ptr<MyPair[]> choice = make_unique<MyPair[]>(10);
	while (!policy.empty())
	{
		Plan tmp = policy.top();
		policy.pop();
		if (!visited[tmp.robot_id] && goods_map[tmp.target.first][tmp.target.second].first > 0)
		{
			visited[tmp.robot_id] = true;
			choice[tmp.robot_id] = tmp.target;	
			goods_map[tmp.target.first][tmp.target.second].first = -goods_map[tmp.target.first][tmp.target.second].first;
		}
	}
	return choice;
}
