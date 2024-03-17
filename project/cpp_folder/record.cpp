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

const int round_robot_num(const int& x, const int& y)
{
	int ans = 0;
	for (int i = 0; i < 10; i++)
	{
		if (my_abs(robot[i].x, x) <= 3 && my_abs(robot[i].y, y) <= 3)
		{
			ans += 1;
		}
	}
	return ans;
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

MyPair Berth::find_goods_from_berth()
{
	priority_queue<Plan> q;
	for (auto cur = goods_info.begin(); cur != goods_info.end();)
	{
		if (cur->time <= id)
		{
			cur = goods_info.erase(cur);
		}
		else
		{
			if (goods_map[cur->cur_x][cur->cur_y].first > 0)
			{
				//��Ҫ�Ż�
				q.push(Plan(goods_map[cur->cur_x][cur->cur_y].first, dis[cur->cur_x][cur->cur_y][berth_id], -1, { cur->cur_x,cur->cur_y }));
			}
			cur++;
		}
	}
	if (!q.empty())
	{
		MyPair ret = q.top().target;
		return ret;
	}
	else
	{
		return make_pair(-1, -1);
	}

}
void Robot::find_goods()	//ֻ����ʼ��Ŀ�ĵ��һ���
{
	int cnt = 0;
	memset(pre, 0, sizeof(pre));
	memset(visited, false, sizeof(visited));
	memset(nxt, 0, sizeof(nxt));
	visited[x][y] = true;
	queue<MyPair> q;
	q.push({ x, y });
	bool found = false;
	int step = 0;
	//find_max = round_robot_num(x, y);	//�����м����˾�������Ҫ�Ҽ������������������̫Զ���ǾͲ���Ҫ����ô���ֹ������
	while (cnt < 6 && !q.empty())	//������6Ч���Ϻ�
	{
		int q_size = q.size();
		for (int j = 1; j <= q_size; j++)
		{
			MyPair u = q.front();
			q.pop();
			if (goods_map[u.first][u.second].first > 0 && goods_map[u.first][u.second].second - id > step + 1)	//��һ���ݴ�
			{
				int good_to_berth_dis = 30000;
				for (int i = 0; i < 10; i++)
				{
					if (dis[u.first][u.second][i] > 0)
					{
						good_to_berth_dis = min(good_to_berth_dis, dis[u.first][u.second][i]);
					}
				}
				Search_Policy::policy.push(Plan(goods_map[u.first][u.second].first, step + good_to_berth_dis, robot_id, u));
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
}

void Robot::find_berth() //�Ҳ�λ
{
	int aim_num = -1;
	int min_dis = 30000;
	for (int i = 0; i < 10; i++)
	{
		if (dis[x][y][i] < 0 || dis[x][y][i] + id > berth[i].close_time)continue;	//��0�Ƿ�ֹͼ����ͨ
		if (dis[x][y][i] > 0 && dis[x][y][i] < min_dis)
		{
			aim_num = i;
			min_dis = dis[x][y][i];
		}
	}
	if (aim_num == -1)aim_num = 0;
	target_x = berth[aim_num].x;
	target_y = berth[aim_num].y;
	/*
	��֪���÷��ģ�����ô����
	*/
	find_road(min_dis);
}

void Robot::find_road(const int& min_dis)	//����target��ȥ��·
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
				if (my_abs(tmp.first, target_x) + my_abs(tmp.second, target_y) > min_dis + 1)
				{
					continue;
				}
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
	clash_solve();
	if (target_x == x && target_y == y)
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
					MyPair target = berth[i].find_goods_from_berth();
					if (target.first == -1)
					{
						find_goods();
					}
					else
					{
						target_x = target.first, target_y = target.second;
						goods_map[target_x][target_y].first = -goods_map[target_x][target_y].first;
						find_road(dis[target_x][target_y][i]);
					}
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
					MyPair target = berth[i].find_goods_from_berth();
					target_x = target.first, target_y = target.second;
					goods_map[target_x][target_y].first = -goods_map[target_x][target_y].first;
					find_road(dis[target_x][target_y][i]);
					return;
				}
			}
			cout << "get " << robot_id << endl;	//�û���
			find_berth();
		}
	}
}

//tail_status=-1��ʱ�����û����βɱ�׶�
//tail_status=0��ʱ�������βɱ�׶������˵�һ���ۿ�
//tail_status=1��ʱ�������βɱ�׶������˵ڶ����ۿ�
void Boat::boat_control()
{
	if (status == 0) //�����ƶ���
	{
		left_time -= 1;
		if (id >= tail_time && tail_status == -1)
		{
			if (num == 0)//��ۿ��ƶ�����Ŀ��ۿڴ��ȣ�����ۿں�Ҫ���������̣��������̼��������ʱ��Ϊ2 * max_trans_time + second_max_trans
			{
				berth[aim_berth].close_time = 15000 - 2 * max_trans_time - second_max_trans - boat_capacity - boat_capacity / berth[aim_berth].loading_speed - 10;
				berth[aim_berth].close_time = max(berth[aim_berth].close_time, id + berth[aim_berth].transport_time + boat_capacity / berth[aim_berth].loading_speed + 10);
			}
			else
			{
				//ɶҲ����
			}
		}

	}
	else if (status == 1)
	{
		if (pos == -1)
		{
			//������-1��ǰ��0����ת��Ϊ�ƶ���
			num = 0;
			int aim_berth_temp = -1;
			int temp_goods_num = -1;
			for (int i = 0; i < 10; i++)
			{
				if (berth[i].num > temp_goods_num && berth[i].aimed == false)//ѡȡһ��û�б������Ҳ��ڻ��������Ĳ���
				{
					if (id >= tail_time)
					{
						if (tail_status == -1 || tail_status == 0)//���Ŀ����ȣ���ѡ
						{
							if (berth[i].close_time < 15000)continue;
						}
						else//������������ʱ������������������βɱ�ˣ�������������㲻���ˣ�����жϿ���д��ѭ������
						{
							return;
						}
					}
					temp_goods_num = berth[i].num;
					aim_berth_temp = i;
				}
			}
			berth[aim_berth_temp].aimed = true;
			aim_berth = aim_berth_temp;
			if (id > tail_time)
			{
				if (tail_status == -1)
				{//��һ��βɱ��Ŀ��ۿ��趨����ʱ�䣬����ʱ��Ϊ��������
					berth[aim_berth].close_time = 15000 - 2 * max_trans_time - second_max_trans - boat_capacity - boat_capacity / berth[aim_berth].loading_speed - 10;
					berth[aim_berth].close_time = max(berth[aim_berth].close_time, id + berth[aim_berth].transport_time + boat_capacity / berth[aim_berth].loading_speed + 10);
				}
				else
				{//�ڶ���βɱ��Ŀ��ۿ��趨����ʱ�䣬����ʱ��ΪĿ��ۿڵĵ���ʱ��
					berth[aim_berth].close_time = 15000 - berth[aim_berth].transport_time - 2;
				}
				tail_status++;
			}

			left_time = berth[aim_berth].transport_time;

			cout << "ship " << boat_id << " " << aim_berth_temp << endl; //�ȴ���λ
		}
		else//��װ��
		{
			if (id >= tail_time)
			{
				if (id >= berth[pos].close_time || num == boat_capacity)//�����˾���
				{
					berth[pos].aimed = false;
					left_time = berth[aim_berth].transport_time;
					aim_berth = -1;
					cout << "go " << boat_id << endl;
				}
				else
				{
					int add = min(berth[pos].loading_speed, min(boat_capacity - num, berth[pos].num));
					num += add;
					berth[pos].num -= add;
				}
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
					left_time = berth[aim_berth].transport_time;
					aim_berth = -1;
					cout << "go " << boat_id << endl;
				}
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

				if (robot[u_id].goods == 0)	//��������
				{
					goods_map[robot[u_id].target_x][robot[u_id].target_y].first = -goods_map[robot[u_id].target_x][robot[u_id].target_y].first;
				}
				robot[u_id].target_x = -1;
				robot[u_id].target_y = -1;
				cout << "move " << u_id << " " << u_op << endl;


				robot[u_id].x += dx_dy[u_op].first;
				robot[u_id].y += dx_dy[u_op].second;
				robot[u_id].move_or_not = true;
				if (robot[u_id].goods == 0)
				{
					robot[u_id].find_goods();
				}
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
