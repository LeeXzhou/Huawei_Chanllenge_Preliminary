#include "../h_folder/my_algorithm.h"
using namespace std;
bool visited[205][205];

namespace my_alg {
	void BFS()
	{
		return;
	}
	void boat_control()
	{
		cerr << boat[0].status << " " << boat[0].pos << " " << boat[0].num << endl;
		if (boat[0].status == 0) //正在移动中
		{

		}
		else if (boat[0].status == 1)
		{
			if (boat[0].pos == -1)
			{
				//现在在-1，前往0，船转变为移动中
				cout << "ship 0 0" << endl;
			}
			else
			{
				if (boat[0].num > 0)
				{
					//船转变为移动中，现在在0，前往-1
					boat[0].num -= berth[0].loading_speed;
				}
				else
				{
					cout << "go 0" << endl;
					boat[0].num = 0;
				}
			}
			boat[0].status = 0;
		}
		else
		{
			//泊位外等待状态，暂时不考虑
		}
	}
	void test_player0()
	{
		robot[0].robot_control();
		cerr << robot[0].target_x << robot[0].target_y;
		boat_control();
		if (!Search_Policy::policy.empty())
		{
			unique_ptr<MyPair[]> result(Search_Policy::choose());
			for (int i = 0; i < 10; i++)
			{
				if (result[i] != make_pair(0, 0))
				{
					robot[i].target_x = result[i].first;
					robot[i].target_y = result[i].second;
					MyPair now = result[i], tmp = { 0, 0 };
					while (tmp.first != robot[i].x || tmp.second != robot[i].y)
					{
						tmp = robot[i].pre[now.first][now.second];
						robot[i].nxt[tmp.first][tmp.second] = now;
						now = tmp;
					}
				}
			}
		}		
	}
}

