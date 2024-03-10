#include "../h_folder/record.h"
using namespace std;
bool check_valid(int x, int y)
{
	if (x < 200 && x >= 0 && y < 200 && y >= 0 && ch[x][y] != '*' && ch[x][y] != '#')
	{
		return true;
	}
	return false;
}

Berth::Berth(int x, int y, int transport_time, int loading_speed) {
	this->x = x;
	this->y = y;
	this->transport_time = transport_time;
	this->loading_speed = loading_speed;
}

Robot::Robot(int startX, int startY) {
	x = startX;
	y = startY;
}

void Robot::robot_control()
{
	if (id < 10)
	{
		return;
	}
	if (target_x == -1)
	{
		//定个目标地，货物地
		memset(pre, 0, sizeof(pre));
		memset(visited, false, sizeof(visited));
		memset(nxt, 0, sizeof(nxt));
		visited[x][y] = true;
		queue<MyPair> q;
		q.push({ x, y });
		bool found = false;
		int step = 0;
		while (!found && !q.empty())
		{
			int q_size = q.size();
			for (int j = 1; j <= q_size; j++)
			{
				MyPair u = q.front();
				q.pop();
				if (goods_map[u.first][u.second].first && goods_map[u.first][u.second].second - id > step)
				{
					goods_map[u.first][u.second].first = 0;
					found = true;
					target_x = u.first;
					target_y = u.second;
					MyPair now = u, tmp = { 0, 0 };
					while (tmp.first != x || tmp.second != y)
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
					MyPair tmp = u + dx_dy[i];
					if (check_valid(tmp.first, tmp.second) && (!visited[tmp.first][tmp.second]))
					{
						visited[tmp.first][tmp.second] = true;
						pre[tmp.first][tmp.second] = u;
						q.push(tmp);
					}
				}
			}
			step++;
		}
		cerr << target_x << " " << target_y << endl;
	}
	else if (target_x == x && target_y == y)
	{
		//修改目标地
		if (target_x == berth[0].x && target_y == berth[0].y)	//当前位置是泊位
		{
			cout << "pull " << robot_id << endl;
			boat[0].num += 1;
			target_x = -1;
			target_y = -1;
		}
		else    //当前位置是货物点
		{
			cout << "get " << robot_id << endl;	//拿货物
			target_x = berth[0].x;
			target_y = berth[0].y;
			/*
			不知道该放哪，先这么放着
			*/
			memset(pre, 0, sizeof(pre));
			memset(visited, false, sizeof(visited));		
			memset(nxt, 0, sizeof(nxt));
			visited[x][y] = true;
			queue<MyPair> q;
			q.push({ x, y });
			bool found = false;
			int step = 0;
			while (!found && !q.empty())
			{
				int q_size = q.size();
				for (int j = 1; j <= q_size; j++)
				{
					MyPair u = q.front();
					q.pop();
					if (u.first == berth[0].x && u.second == berth[0].y)
					{
						found = true;
						MyPair now = u, tmp = { 0, 0 };
						while (tmp.first != x || tmp.second != y)
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
						MyPair tmp = u + dx_dy[i];
						if (check_valid(tmp.first, tmp.second) && (!visited[tmp.first][tmp.second]))
						{
							visited[tmp.first][tmp.second] = true;
							pre[tmp.first][tmp.second] = u;
							q.push(tmp);
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
		MyPair now = { x, y };
		for (int i = 0; i < 4; i++)
		{
			if (now + dx_dy[i] == nxt[x][y])
			{
				cout << "move " << robot_id << " " << i << endl;
				cerr << now << i << endl;
				break;
			}
		}
	}
}


