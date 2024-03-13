#include "../h_folder/my_algorithm.h"
using namespace std;
bool visited[205][205];

namespace my_alg {
	void BFS()
	{
		return;
	}
	void init_dis()
	{
		memset(dis, -1, sizeof(dis));
		unique_ptr<unique_ptr<unique_ptr<bool[]>[]>[]> vis(new unique_ptr<unique_ptr<bool[]>[]>[205]);
		for (int i = 0; i < 205; ++i)
		{
			vis[i].reset(new std::unique_ptr<bool[]>[205]);
			for (int j = 0; j < 205; ++j)
			{
				vis[i][j].reset(new bool[10]);
				for (int k = 0; k < 10; ++k)
				{
					vis[i][j][k] = false;
				}
			}
		}
		queue<MyPair> q;
		for (int i = 0; i < berth_num; i++)
		{
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					int _x = berth[i].x + x, _y = berth[i].y + y;
					q.push({ _x, _y });
					dis[_x][_y][i] = 0;
					vis[_x][_y][i] = true;
				}
			}
			while (!q.empty())
			{
				MyPair tmp = q.front();
				q.pop();
				for (int j = 0; j < 4; j++)
				{
					MyPair cur = tmp + dx_dy[j];
					if (check_valid(cur.first, cur.second) && !vis[cur.first][cur.second][i])
					{
						vis[cur.first][cur.second][i] = true;
						dis[cur.first][cur.second][i] = dis[tmp.first][tmp.second][i] + 1;
						q.push(cur);
					}
				}
			}
		}
	}
	void boat_control()
	{
		if (boat[0].status == 0) //正在移动中
		{

		}
		else if (boat[0].status == 1)
		{
			if (boat[0].pos == -1)
			{
				//现在在-1，前往0，船转变为移动中
				boat[0].num = 0;
				cout << "ship 0 0" << endl;
			}
			else
			{
				if (berth[boat[0].pos].num > 0)
				{
					//船转变为移动中，现在在0，前往-1
					int add = max(berth[0].loading_speed, berth[0].num);
					boat[0].num += add;
					berth[boat[0].pos].num -= add;
				}
				else
				{
					cout << "go 0" << endl;
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
		for (int i = 0; i < 10; i++)
		{
			robot[i].robot_control();
		}
		for (int i = 0; i < 5; i++)
		{
			boat[i].boat_control();
		}
		for (int i = 0; i < 10; i++)
		{
			cerr <<i<<" "<< berth[i].num << endl;
		}
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

