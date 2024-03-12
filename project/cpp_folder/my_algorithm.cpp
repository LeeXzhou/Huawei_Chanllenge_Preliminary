#include "../h_folder/my_algorithm.h"
using namespace std;
bool visited[205][205];

namespace my_alg {
	void BFS()
	{
		return;
	}
<<<<<<< Updated upstream
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
=======
	void boat_control(int boat_num)
>>>>>>> Stashed changes
	{
		//cerr << boat[0].status << " " << boat[0].pos << " " << boat[0].num << endl;
		if (boat[boat_num].status == 0) //正在移动中
		{

		}
		else if (boat[boat_num].status == 1)
		{
			if (boat[boat_num].pos == -1)
			{
				//现在在-1，前往0，船转变为移动中
				cout << "ship " <<boat_num<<" "<<boat_num<< endl;
			}
			else
			{
				if (boat[boat_num].num > 0)
				{
					//船转变为移动中，现在在0，前往-1
					boat[boat_num].num -= berth[0].loading_speed;
				}
				else
				{
					cout << "go " <<boat_num<< endl;
					boat[boat_num].num = 0;
				}
			}
			boat[boat_num].status = 0;
		}
		else
		{
			//泊位外等待状态，暂时不考虑
		}
	}
	void test_player0()
	{
<<<<<<< Updated upstream
		robot[0].robot_control();
		cerr << "OK!!!" << endl;
		boat_control();
		if (!Search_Policy::policy.empty())
=======
		
		for (int j = 0; j < 10; j++)
>>>>>>> Stashed changes
		{
			robot[j].robot_control();
			//cerr << robot[j].target_x << robot[j].target_y;
			for (int uu = 0; uu < 5; uu++)
			{
				boat_control(uu);
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
<<<<<<< Updated upstream
=======
		
>>>>>>> Stashed changes
	}
}

