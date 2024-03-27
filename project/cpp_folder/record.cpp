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
				//需要优化
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
void Robot::find_goods()	//只有起始和目的地找货物
{
	if (goods_map[x][y].first > 0 && goods_map[x][y].second > id)
	{
		target_x = x; target_y = y;
		return;
	}
	int cnt = 0;
	memset(pre, 0, sizeof(pre));
	memset(visited, false, sizeof(visited));
	memset(nxt, 0, sizeof(nxt));
	visited[x][y] = true;
	queue<MyPair> q;
	q.push({ x, y });
	bool found = false;
	int step = 0;
	priority_queue<Plan> choice;
	//find_max = round_robot_num(x, y);	//附近有几个人决定了需要找几个货物，如果机器人相隔太远他们就不需要找那么多防止找重了
	while (cnt < 6 && !q.empty())	//测下来6效果较好
	{
		int q_size = q.size();
		for (int j = 1; j <= q_size; j++)
		{
			MyPair u = q.front();
			q.pop();
			if (goods_map[u.first][u.second].first > 0 && goods_map[u.first][u.second].second - id > step + 1)	//给一点容错
			{
				int good_to_berth_dis = 30000;
				for (int i = 0; i < 10; i++)
				{
					if (dis[u.first][u.second][i] > 0)
					{
						good_to_berth_dis = min(good_to_berth_dis, dis[u.first][u.second][i]);
					}
				}
				choice.push(Plan(goods_map[u.first][u.second].first, step + good_to_berth_dis, robot_id, u));
				//Search_Policy::policy.push(Plan(goods_map[u.first][u.second].first, step + good_to_berth_dis, robot_id, u));
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
	if (!choice.empty())
	{
		no_goods = false;
		MyPair now = choice.top().target, tmp = {-1, -1};
		target_x = now.first, target_y = now.second;
		goods_map[target_x][target_y].first = -goods_map[target_x][target_y].first;
		while (tmp.first != x || tmp.second != y)
		{
			tmp = pre[now.first][now.second];
			nxt[tmp.first][tmp.second] = now;
			now = tmp;
		}
	}
}

void Robot::find_berth() //找泊位
{
	int aim_num = -1;
	int min_dis = 30000;
	for (int i = 0; i < 10; i++)
	{
		if (dis[x][y][i] < 0 || dis[x][y][i] + id > berth[i].close_time)continue;	//判0是防止图不连通
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
	不知道该放哪，先这么放着
	*/
	find_road(min_dis);
}

void Robot::find_road(const int& min_dis)	//给定target下去找路
{
	if (x == target_x && y == target_y)
	{
		return;
	}
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
				if (my_abs(tmp.first, target_x) + my_abs(tmp.second, target_y) > min_dis + 1 - step)
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
	if (target_x == -1 && !no_goods)
	{
		//定个目标地，货物地
		if (goods == 0)
		{
			find_goods();
		}
		else
		{
			find_berth();
		}
	}
	if (!no_goods)
	{
		clash_solve();
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (x == berth[i].x && y == berth[i].y)
			{
				MyPair target = berth[i].find_goods_from_berth();
				target_x = -1; target_y = -1;
				if (target.first == -1)
				{
					no_goods = true;
				}
				else
				{
					target_x = target.first, target_y = target.second;
					goods_map[target_x][target_y].first = -goods_map[target_x][target_y].first;
					find_road(dis[target_x][target_y][i]);
					no_goods = false;
				}
				return;
			}
		}
		find_goods();
	}
	if (target_x == x && target_y == y)
	{
		//修改目标地
		if (goods == 1)	//身上有货物，判断当前位置是不是泊位
		{
			for (int i = 0; i < 10; i++)
			{
				if (x >= berth[i].x && x <= berth[i].x + 3 && y <= berth[i].y + 3 && y >= berth[i].y)
				{
					cout << "pull " << robot_id << endl;
					goods = 0;
					berth[i].num += 1;
					MyPair target = berth[i].find_goods_from_berth();
					if (target.first == -1)
					{
						no_goods = true;
						target_x = -1; target_y = -1;
					}
					else
					{
						target_x = target.first, target_y = target.second;
						goods_map[target_x][target_y].first = -goods_map[target_x][target_y].first;
						find_road(dis[target_x][target_y][i]);
						no_goods = false;
					}
					return;
				}
			}

			find_berth();
		}
		else    //身上没有货物，判断当前位置是不是泊位
		{
			/*
			for (int i = 0; i < 10; i++)
			{
				if (x >= berth[i].x && x <= berth[i].x + 3 && y <= berth[i].y + 3 && y >= berth[i].y)
				{
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
			*/
			cout << "get " << robot_id << endl;	//拿货物
			find_berth();
		}
	}
}

//tail_status=-1的时候代表船没进入尾杀阶段
//tail_status=0的时候代表船在尾杀阶段锁定了第一个港口
//tail_status=1的时候代表船在尾杀阶段锁定了第二个港口

void Boat::boat_control()
{
	if (tail_status == 2)return;
	if (status == 0) //正在移动中
	{
		//left_time -= 1;
	}
	else if (status == 1)
	{
		if (pos == -1)
		{
			//现在在-1，前往0，船转变为移动中
			num = 0;
			int aim_berth_temp = -1;
			int temp_goods_num = -1;
			for (int i = 0; i < 10; i++)
			{
				if (berth[i].num > temp_goods_num && berth[i].aimed == false)//选取一个没有被锁定且驳口货物量最大的驳口
				{
					temp_goods_num = berth[i].num;
					aim_berth_temp = i;
				}
			}
			

			//判进入三角杀
			if (trian_on||(!trian_on && id + berth[aim_berth_temp].transport_time * 2 + boat_capacity / berth[aim_berth_temp].loading_speed + 1 > threshold__time))
			{
				if (!trian_on)tail_time = id;
				trian_on = true;
				//这里有个优先性，触发尾杀越早的去货物和越少的驳口组
				//berth_pair的first比second小，先去远的，再用500ms去近的。
				int temp_num = 1000000, pair_id = -1;
				for (int i = 0; i < 5; i++)
				{
					if (trian_or_not[i])continue;
					if (berth_pair[i].first + berth_pair[i].second < temp_num)
					{
						temp_num = berth_pair[i].first + berth_pair[i].second;
						pair_id = i;
					}
				}
				trian_or_not[pair_id] = true;
				tail_status = 0;
				aim_berth_temp = berth_pair[pair_id].second;
				
				berth[aim_berth_temp].close_time = 15000 - berth[berth_pair[pair_id].first].transport_time - 500 - (boat_capacity / berth[berth_pair[pair_id].first].loading_speed) - 2;
				berth[berth_pair[pair_id].first].close_time = 15000 - berth[berth_pair[pair_id].first].transport_time - 1;
			}


			berth[aim_berth_temp].aimed = true;
			aim_berth = aim_berth_temp;
			//left_time = berth[aim_berth].transport_time;


			cout << "ship " << boat_id << " " << aim_berth_temp << endl; //先船后泊位
		}
		else//在装货
		{
			if (tail_status==0)
			{
				if (id >= berth[pos].close_time)
				{
					cout << "ship " << boat_id << " " << couple_berth[pos] << endl;
					tail_status = 1;
				}
			}
			else if (tail_status == 1)
			{
				if (id >= berth[pos].close_time)
				{
					cout << "go " << boat_id << endl;
					tail_status = 2;
				}
			}
			else
			{
				if (berth[pos].num > 0 && num < boat_capacity)
				{
					//船转变为移动中，现在在0，前往-1
					int add = min(berth[pos].loading_speed, min(boat_capacity - num, berth[pos].num));
					num += add;
					berth[pos].num -= add;
				}
				else
				{
					berth[pos].aimed = false;
					//left_time = berth[aim_berth].transport_time;
					aim_berth = -1;
					cout << "go " << boat_id << endl;
				}
			}
			
		}
		status = 0;
	}
	else
	{
		//泊位外等待状态，暂时不考虑
	}
}

bool Robot::robot_dfs(const int& move_num, stack<MyPair> move_order)
{
	//cerr << "I am in dfs" << endl;
	if (robot[move_num].move_or_not)return false;
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

				if (robot[u_id].goods == 0)	//存在隐患
				{
					goods_map[robot[u_id].target_x][robot[u_id].target_y].first = -goods_map[robot[u_id].target_x][robot[u_id].target_y].first;
				}
				robot[u_id].target_x = -1;
				robot[u_id].target_y = -1;
				cout << "move " << u_id << " " << u_op << endl;

				robot[u_id].x += dx_dy[u_op].first;
				robot[u_id].y += dx_dy[u_op].second;
				robot[u_id].move_or_not = true;
				//robot[u_id].no_goods = false;	
				//若此时恰好在泊位还无货物，则no_goods为true，移动后不在泊位了不会再有置为false的机会
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
	bool answer = false;
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
				if (answer == true)return true;
			}
		}
	}
	if(answer==false)robot[move_num].move_or_not = false;
	return false;
}

void Robot::clash_solve()
{
	if (move_or_not)return;
	bool flag = true;
	for (int i = 0; i < 10; i++)
	{
		if (i == robot_id)continue;
		if (nxt[x][y] == make_pair(robot[i].x, robot[i].y)) { flag = false; break; }
	}

	if (flag)//若下一步没有机器人
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

	bool answer = false;
	move_or_not = true;
	for (int i = 0; i < 10; i++)
	{
		if (nxt[x][y] == make_pair(robot[i].x, robot[i].y))
		{
			stack<MyPair> move_order;

			answer = robot_dfs(i, move_order);

			answer = robot_dfs(i, move_order);	
			break;
		}
	}
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
