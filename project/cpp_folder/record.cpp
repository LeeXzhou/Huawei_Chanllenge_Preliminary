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

bool check_valid(const MyPair& x)
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

void Robot::find_goods()	//�һ���
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
			if (goods_map[u.first][u.second].first >0&& goods_map[u.first][u.second].second - id > step + 2)	//��һ���ݴ�
			{
				short good_to_berth_dis = 30000;
				for (int i = 0; i < 10; i++)
				{
					good_to_berth_dis = min(good_to_berth_dis, dis[u.first][u.second][i]);
				}
				Search_Policy::policy.push(Plan(goods_map[u.first][u.second].first, step+good_to_berth_dis, robot_id, u));
				//����Search_Policy������ȶ����У���������ʽ������ȥ��
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

void Robot::find_berth() //�Ҳ�λ
{
	int aim_num = -1;
	short min_dis = 30000;
	for (int i = 0; i < 10; i++)
	{
		if (dis[x][y][i] < min_dis)
		{
			aim_num = i;
			min_dis = dis[x][y][i];
		}
	}
	target_x = berth[aim_num].x;
	target_y = berth[aim_num].y;
	/*
	��֪���÷��ģ�����ô����
	*/
	find_road();
}

void Robot::find_road()	//����target��ȥ��·
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
	if (move_or_not)
	{
		return;
	}
	if (target_x == -1)
	{
		//����Ŀ��أ������
		if (goods == 0)
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
		//�޸�Ŀ���
		if (goods == 1)	//�����л���жϵ�ǰλ���ǲ��ǲ�λ
		{
			for (int i = 0; i < 10; i++)
			{
				if (x >= berth[i].x && x <= berth[i].x + 3 && y <= berth[i].y + 3 && y >= berth[i].y)
				{
					cout << "pull " << robot_id << endl;
					berth[i].num += 1;
					target_x = -1;
					target_y = -1;
					move_or_not = true;
					find_goods();
					return;
				}
			}
			
			find_berth();
		}
		else    //����û�л���жϵ�ǰλ���ǲ��ǲ�λ
		{
			for (int i = 0; i < 10; i++)	//
			{
				if (x >= berth[i].x && x <= berth[i].x + 3 && y <= berth[i].y + 3 && y >= berth[i].y)
				{
					find_goods();
					return;
				}
			}
			cout << "get " << robot_id << endl;	//�û���
			find_berth();
		}
	}
	else
	{
		//����ײ
		clash_solve();
	}
}

void Boat::boat_control()
{
	if (status == 0) //�����ƶ���
	{

	}
	else if (status == 1)
	{
		if (pos == -1)
		{
			//������-1��ǰ��0����ת��Ϊ�ƶ���
			num = 0;
			int aim_berth = -1;
			int temp_goods_num = -1;
			for (int i = 0; i < 10; i++)
			{
				if (berth[i].num > temp_goods_num && berth[i].aimed == false)
				{
					temp_goods_num = berth[i].num;
					aim_berth = i;
				}
			}
			berth[aim_berth].aimed = true;
			cout << "ship " << boat_id << " " << aim_berth << endl; //�ȴ���λ
		}
		else
		{
			if (berth[pos].num > 0 && num < boat_capacity)
			{
				//��ת��Ϊ�ƶ��У�������0��ǰ��-1
				int add = min(berth[pos].loading_speed, min(boat_capacity - num, berth[pos].num));
				num += add;
				berth[pos].num -= add;
			}
			else
			{
				berth[pos].aimed = false;
				cout << "go " << boat_id << endl;
			}
		}
		status = 0;
	}
	else
	{
		//��λ��ȴ�״̬����ʱ������
	}
}

bool Robot::robot_dfs(const int& move_num, stack<MyPair>move_order)
{
	if (robot[move_num].move_or_not)return 0;
	for (int i = 0; i < 4; i++)
	{
		int ran_i = (i + id) % 4;
		bool robot_clash = false;
		if (!check_valid(dx_dy[ran_i] + make_pair(robot[move_num].x, robot[move_num].y))) { continue; }
		for (int j = 0; j < 10; j++)
		{

			if (move_num == j)continue;
			if (dx_dy[ran_i] + make_pair(robot[move_num].x, robot[move_num].y) == make_pair(robot[j].x, robot[j].y))
			{
				robot_clash = true; break;
			}
		}

		if (robot_clash == false)
		{
			move_order.push({ move_num,ran_i });

			while (!move_order.empty())
			{
				MyPair u = move_order.top();
				move_order.pop();
				int u_id = u.first;
				int u_op = u.second;
				robot[u_id].move_or_not = true;
				
				if (robot[u_id].goods == 0)
				{
					goods_map[robot[u_id].target_x][robot[u_id].target_y].first = -goods_map[robot[u_id].target_x][robot[u_id].target_y].first;
				}
				robot[u_id].target_x = -1;
				robot[u_id].target_y = -1;
				cerr << u_id << endl;
				cout << "move " << u_id << " " << u_op << endl;


				robot[u_id].x += dx_dy[u_op].first;
				robot[u_id].y += dx_dy[u_op].second;
				robot[u_id].move_or_not = true;
				if(!robot[u_id].goods)robot[u_id].find_goods();
				else
				{
					robot[u_id].find_berth();
				}



			}
			return true;
		}
	}
	int answer = 0;
	robot[move_num].move_or_not = true;
	for (int i = 0; i < 4; i++)
	{
		int ran_i = (i + id) % 4;
		if (!check_valid(dx_dy[ran_i] + make_pair(robot[move_num].x, robot[move_num].y)))continue;
		for (int j = 0; j < 10; j++)
		{
			if (dx_dy[ran_i] + make_pair(robot[move_num].x, robot[move_num].y) == make_pair(robot[j].x, robot[j].y))
			{
				if (robot[j].move_or_not)continue;
				move_order.push({ move_num,ran_i });
				answer = robot_dfs(j, move_order);
				move_order.pop();
				if (answer == 1)return true;
			}
		}
	}
	robot[move_num].move_or_not = false;
	return false;
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

	if (flag)//����һ��û�л�����
	{
		MyPair now = { x, y };
		for (int i = 0; i < 4; i++)
		{
			if (now + dx_dy[i] == nxt[x][y])
			{
				cout << "move " << robot_id << " " << i << endl;



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
