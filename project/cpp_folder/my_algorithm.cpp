#include "../h_folder/my_algorithm.h"
using namespace std;
bool visited[205][205];
template<class Ty1, class Ty2>
const pair<Ty1, Ty2> operator+(const pair<Ty1, Ty2>& p1, const pair<Ty1, Ty2>& p2)
{
	return make_pair(p1.first + p2.first, p1.second + p2.second);
}

template<class Ty1, class Ty2>
const pair<Ty1, Ty2> operator-(const pair<Ty1, Ty2>& p1, const pair<Ty1, Ty2>& p2)
{
	return make_pair(p1.first - p2.first, p1.second - p2.second);
}

template <class T, class U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

namespace my_alg {
	void BFS()
	{
		return;
	}
	bool check_robot(int x, int y)//判断一个位置是否可以让机器人站（合法且不是障碍物或者海）
	{
		if (x < 200 && x >= 0 && y < 200 && y >= 0 && ch[x][y] != '*' && ch[x][y] != '#')
		{
			return true;
		}
		return false;
	}
	void find_road(int x = -1, int y = -1)
	{
		if (x != -1)	//找泊位
		{

		}
		else    //找货物
		{

		}
	}
	void robot_control()
	{
		cerr << robot[0].target_x << " " << robot[0].target_y << " " << robot[0].x << " " << robot[0].y << endl;
		if (id < 10)
		{
			return;
		}
		int cur_x = robot[0].x, cur_y = robot[0].y;
		
		if (robot[0].target_x == -1)
		{
			//定个目标地，货物地
			memset(pre, 0, sizeof(pre));
			int fx[4] = { 1,-1,0,0 };
			int fy[4] = { 0,0,-1,1 };
			memset(visited, false, sizeof(visited));
			memset(nxt, 0, sizeof(nxt));
			visited[cur_x][cur_y] = true;
			queue<pair<int, int>> q;
			q.push({ cur_x, cur_y });
			bool found = false;
			int step = 0;
			while (!found && !q.empty())
			{
				int q_size = q.size();
				for (int j = 1; j <= q_size; j++)
				{
					pair<int, int> u = q.front();
					q.pop();
					if (goods_map[u.first][u.second].first && goods_map[u.first][u.second].second - id > step)
					{
						found = true;
						robot[0].target_x = u.first;
						robot[0].target_y = u.second;
						pair<int, int> now = u, tmp = { 0, 0 };
						while (tmp.first != cur_x || tmp.second != cur_y)
						{
							tmp = pre[now.first][now.second];
							cerr << tmp;
							nxt[tmp.first][tmp.second] = now;
							now = tmp;
						}
						break;
					}

					for (int i = 0; i < 4; i++)
					{
						int temp_x = u.first + fx[i], temp_y = u.second + fy[i];
						if (check_robot(temp_x, temp_y) && (!visited[temp_x][temp_y]))
						{
							visited[temp_x][temp_y] = true;
							pre[temp_x][temp_y] = u;
							q.push({ temp_x, temp_y });
						}
					}
				}
				step++;
			}
			cerr << robot[0].target_x << " " << robot[0].target_y << endl;
		}
		else if (robot[0].target_x == cur_x && robot[0].target_y == cur_y)
		{
			//修改目标地
			if (robot[0].target_x == berth[0].x && robot[0].target_y == berth[0].y)	//当前位置是泊位
			{
				cout << "pull 0" << endl;
				boat[0].num += 1;
				robot[0].target_x = -1;
				robot[0].target_y = -1;
			}
			else    //当前位置是货物点
			{
				cout << "get 0" << endl;	//拿货物
				robot[0].target_x = berth[0].x;
				robot[0].target_y = berth[0].y;
				memset(pre, 0, sizeof(pre));
				int fx[4] = { 1,-1,0,0 };
				int fy[4] = { 0,0,-1,1 };
				memset(visited, false, sizeof(visited));
				visited[cur_x][cur_y] = true;
				memset(nxt, 0, sizeof(nxt));
				queue<pair<int, int>> q;
				q.push({ cur_x, cur_y });
				bool found = false;
				int step = 0;
				while (!found && !q.empty())
				{
					int q_size = q.size();
					for (int j = 1; j <= q_size; j++)
					{
						pair<int, int> u = q.front();
						q.pop();
						if (u.first == berth[0].x && berth[0].y)
						{
							found = true;
							pair<int, int> now = u, tmp = { 0, 0 };
							while (tmp.first != cur_x || tmp.second != cur_y)
							{
								tmp = pre[now.first][now.second];
								cerr << tmp;
								nxt[tmp.first][tmp.second] = now;
								now = tmp;
							}
							break;
						}
						for (int i = 0; i < 4; i++)
						{
							int temp_x = u.first + fx[i], temp_y = u.second + fy[i];
							if (check_robot(temp_x, temp_y) && (!visited[temp_x][temp_y]))
							{
								visited[temp_x][temp_y] = true;
								pre[temp_x][temp_y] = u;
								q.push({ temp_x, temp_y });
							}
						}
					}
					step++;
				}
			}
		}
		else
		{
			//继续走就是了
			pair<int, int> now = { cur_x, cur_y };
			for (int i = 0; i < 4; i++)
			{
				if (now + dx_dy[i] == nxt[cur_x][cur_y])
				{
					cout << "move 0 " << i << endl;
					cerr << now << i << endl;
					break;
				}
			}

		}
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
				if (boat[0].num)
				{
					//船转变为移动中，现在在0，前往-1
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
		robot_control();
		boat_control();
	}
}

