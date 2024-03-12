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
bool check_valid(MyPair x)
{
	return check_valid(x.first, x.second);
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

bool Robot::robot_dfs(int move_num, stack<MyPair>move_order)
{
	if (robot[move_num].move_or_not)return 0;
	for (int i = 0; i < 4; i++)
	{
		bool robot_clash = false;
		if(!check_valid(dx_dy[i] + make_pair(robot[move_num].x, robot[move_num].y))){continue;}
		for (int j = 0; j < 10; j++)
		{
			
			if (move_num == j)continue;
			if (dx_dy[i] + make_pair(robot[move_num].x, robot[move_num].y) == make_pair(robot[j].x, robot[j].y))
			{
				robot_clash = true; break;
			}
		}
		
		if (robot_clash == false)
		{
			move_order.push({ move_num,i });
			
			while (!move_order.empty())
			{
				MyPair u = move_order.top();
				move_order.pop();
				int u_id = u.first;
				int u_op = u.second;
				robot[u_id].move_or_not = true;
				robot[u_id].target_x = -1;
				robot[u_id].target_y = -1;
				cerr << u_id << endl;
				cout << "move " << u_id << " " << u_op << endl;
				
				if (myfile.is_open())
				{
					myfile <<"cccc" << robot[u_id].x << " " << robot[u_id].y << "move " << u_id << " " << u_op << "\n";
				}
				robot[u_id].x += dx_dy[u_op].first;
				robot[u_id].y += dx_dy[u_op].second;
				robot[u_id].move_or_not = true;

				

			}
			return 1;
		}
	}
	int answer = 0;
	robot[move_num].move_or_not = true;
	for (int i = 0; i < 4; i++)
	{
		if (!check_valid(dx_dy[i] + make_pair(robot[move_num].x, robot[move_num].y)))continue;
		for (int j = 0; j < 10; j++)
		{
			if (dx_dy[i] + make_pair(robot[move_num].x, robot[move_num].y) == make_pair(robot[j].x, robot[j].y))
			{
				if (robot[j].move_or_not)continue;
				move_order.push({ move_num,i });
				answer = robot_dfs(j, move_order);
				move_order.pop();
				if (answer == 1)return 1;
			}
		}
	}
	robot[move_num].move_or_not = false;
	return 0;
}

void Robot::clash_solve()
{
	if (move_or_not)return;
	int flag = 1;
	for (int i = 0; i < 10; i++)
	{
		if (i == robot_id)continue;
		if (nxt[x][y] == make_pair(robot[i].x, robot[i].y)) { flag = 0; break; }
	}

	if (flag)//若下一步没有机器人
	{
		MyPair now = { x, y };
		for (int i = 0; i < 4; i++)
		{
			if (now + dx_dy[i] == nxt[x][y])
			{
				cout << "move " << robot_id << " " << i << endl;

				if (myfile.is_open())
				{
					myfile <<"aaaa" << x << " " << y << "move " << robot_id << " " << i << "\n";
				}

				x = nxt[now.first][now.second].first;
				y = nxt[now.first][now.second].second;
				move_or_not = true;
				
				
				break;
			}
		}
		return;
	}
	
	//for (int i = 0; i < robot_id; i++)
	//{
	//	if (nxt[x][y] == make_pair(robot[i].x, robot[i].y))return;
	//}
	int answer = 0;
	move_or_not = true;
	for (int i = 0; i < 10; i++)
	{
		if (nxt[x][y] == make_pair(robot[i].x, robot[i].y))
		{
			stack<MyPair> move_order;
			answer = robot_dfs(i, move_order);
			break;
		}
	}
	if (answer)
	{
		MyPair now = { x, y };
		for (int i = 0; i < 4; i++)
		{
			if (now + dx_dy[i] == nxt[x][y])
			{
				cout << "move " << robot_id << " " << i << endl;

				if (myfile.is_open())
				{
					myfile <<"bbbb" << x << " " << y << "move " << robot_id << " " << i << "\n";
				}

				x = nxt[now.first][now.second].first;
				y = nxt[now.first][now.second].second;
				move_or_not = true;
				
				break;
			}
		}
	}
	else
	{
		move_or_not = false;
	}
	
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
	while (cnt < 1 && !q.empty())
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
	//cerr << target_x << " " << target_y << endl;
}

void Robot::find_berth() //找泊位
{
	target_x = berth[robot_id/2].x;
	target_y = berth[robot_id/2].y;
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
	if (move_or_not)return;
	if (target_x == -1)
	{
		if (goods == false)
		{
			find_goods();
		}
		else
		{
			find_berth();
		}
	}
	else if (target_x == x && target_y == y)
	{
		//修改目标地
		if (goods)	//身上有货物，所以当前位置是泊位
		{
			cout << "pull " << robot_id << endl;
			boat[0].num += 1;
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
		/*MyPair now = {x, y};
		for (int i = 0; i < 4; i++)
		{
			if (now + dx_dy[i] == nxt[x][y])
			{
				cout << "move " << robot_id << " " << i << endl;
				cerr << now << i << endl;
				break;
			}
		}*/
		
		clash_solve();
	}
}

void boat_control()
{

}

