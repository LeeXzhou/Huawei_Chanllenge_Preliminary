#include "../h_folder/record.h"
using namespace std;
bool check_valid(const int& x, const int& y)
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

void Robot::find_goods()	//找货物
{
	priority_queue<MyPair> choices;	//value, time
	int cnt = 0;
	memset(pre, 0, sizeof(pre));
	memset(visited, false, sizeof(visited));
	memset(nxt, 0, sizeof(nxt));
	visited[x][y] = true;
	queue<MyPair> q;
	q.push({ x, y });
	bool found = false;
	int step = 0;
	while (cnt < 10 && !q.empty())
	{
		int q_size = q.size();
		for (int j = 1; j <= q_size; j++)
		{
			MyPair u = q.front();
			q.pop();
			if (goods_map[u.first][u.second].first && goods_map[u.first][u.second].second - id > step)
			{
				Search_Policy::policy.push(Plan(goods_map[u.first][u.second].first, step, robot_id, u));
				//放入Search_Policy类的优先队列中，利用启发式来决定去哪
				cnt += 1;
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

void Robot::find_berth() //找泊位
{
	target_x = berth[robot_id / 2].x;
	target_y = berth[robot_id / 2].y;
	/*
	不知道该放哪，先这么放着
	*/
	find_road();
}

void Robot::find_road()	//给定target下去找路
{
	memset(pre, 0, sizeof(pre));
	memset(visited, false, sizeof(visited));
	memset(nxt, 0, sizeof(nxt));
	visited[x][y] = true;
	queue<MyPair> q;
	q.push({ x, y });
	bool found = false;
	int step = 0;
	MyPair target = { target_x, target_y };
	while (!found && !q.empty())
	{
		int q_size = q.size();
		for (int j = 1; j <= q_size; j++)
		{
			MyPair u = q.front();
			q.pop();
			if (u == target)
			{
				found = true;
				MyPair now = u, tmp = { 0, 0 };
				while (tmp.first != x || tmp.second != y)
				{
					tmp = pre[now.first][now.second];
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
void Robot::robot_control()
{
	if (target_x == -1)
	{
		//定个目标地，货物地
		find_goods();
	}
	else if (target_x == x && target_y == y)
	{
		//修改目标地
		if (goods)	//身上有货物，所以当前位置是泊位
		{
			cout << "pull " << robot_id << endl;
			berth[robot_id / 2].num += 1;
			target_x = -1;
			target_y = -1;
		}
		else    //当前位置是货物点
		{
			cout << "get " << robot_id << endl;	//拿货物
			find_berth();
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

void Boat::boat_control()
{
	cerr << "I am " << boat_id << " " << status << " " << pos << endl;
	if (status == 0) //正在移动中
	{

	}
	else if (status == 1)
	{
		if (pos == -1)
		{
			//现在在-1，前往0，船转变为移动中
			num = 0;
			cout << "ship " << boat_id << " " << boat_id << endl; //先船后泊位
		}
		else
		{
			if (berth[pos].num > 0 && num < boat_capacity)
			{
				//船转变为移动中，现在在0，前往-1
				int add = min(berth[boat_id].loading_speed, min(boat_capacity - num, berth[boat_id].num));
				num += add;
				berth[pos].num -= add;
			}
			else
			{
				cout << "go " << boat_id << endl;
			}
		}
		status = 0;
	}
	else
	{
		//泊位外等待状态，暂时不考虑
	}
}

