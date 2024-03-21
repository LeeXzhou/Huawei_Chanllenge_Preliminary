#include "../h_folder/search_policy.h"
#include "../h_folder/my_algorithm.h"
#include<fstream>
using namespace std;
Berth berth[berth_num + 10];
Robot robot[robot_num + 10];
Boat boat[10];
int money, boat_capacity, id;
char ch[N][N];
MyPair goods_map[N][N];
int dis[205][205][10];	//-1表示不可达
int tail_time;
int max_trans_time;
int second_max_trans;
int threshold__time;
int trian_time;
MyPair berth_pair[5];
int couple_berth[10];
int area[200][200];
double fertile[10];
double num[10];
MyPair robot_start[10];

void Init()
{
	for (int i = 0; i < n; i++)
	{
		cin >> ch[i];
	}
		
	for (int i = 0; i < berth_num; i++)
	{
		cin >> id;
		cin >> berth[id].x >> berth[id].y >> berth[id].transport_time >> berth[id].loading_speed;
		berth[id].berth_id = id;
	}
	cin >> boat_capacity;
	char okk[100];	//不知道干嘛的
	cin >> okk;
	my_alg::init_dis();


	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			if (ch[i][j] == '.')
			{
				int mindis = 1e9;
				int num = -1;
				for (int b = 0; b < 10; b++)
				{
					if (dis[i][j][b] != -1)
					{
						if (dis[i][j][b] < mindis)
						{
							num = b;
							mindis = dis[i][j][b];
						}
					}

				}
				area[i][j] = num;
			}
		}
	}

	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			if (ch[i][j] == '.')
			{
				fertile[area[i][j]] += 1000.0 / ((30 + dis[i][j][area[i][j]]) * (30 + dis[i][j][area[i][j]]));
			}

		}
	}
	for (int i = 0; i < 10; i++)
	{
		int robot_access = 0;
		for (int j = 0; j < 10; j++)
		{
			if (dis[robot_start[i].first][robot_start[i].second][j] >= 0)
			{
				robot_access++;
			}
		}
		fertile[i] *= robot_access;
		//cerr << i << ' ' << fertile[i] << endl;
	}

	pair<int, int> temp_fertile[10];
	for (int i = 0; i < 10; i++)
	{
		temp_fertile[i] = { fertile[i],i };
	}
	sort(temp_fertile, temp_fertile + 10);
	for (int i = 0; i < 5; i++)
	{
		boat[i].first_aim = temp_fertile[i].second;
		boat[i].second_aim = temp_fertile[9 - i].second;
		if (berth[boat[i].first_aim].transport_time < berth[boat[i].second_aim].transport_time)
		{
			swap(boat[i].first_aim, boat[i].second_aim);
		}
		int toto_trans_time = berth[boat[i].first_aim].transport_time + berth[boat[i].second_aim].transport_time + 500 +
			boat_capacity / min(berth[boat[i].first_aim].loading_speed, berth[boat[i].second_aim].loading_speed) + 1;

		boat[i].total_wave = 15000 / (toto_trans_time);
		boat[i].wait_time = 15000 % toto_trans_time;
	}


	//for (int i = 0; i < 5; i++)
	//{
	//	cerr << boat[i].total_wave << '\t';
	//}
	//cerr << endl;
	/// <summary>
	/// 尾杀时间四个单程加两个容量加一个容错
	/// 到虚拟点去刷新第一个，先到的找剩余量少的
	/// </summary>



	for (int i = 0; i < robot_num; i++)
	{
		robot[i].robot_id = i;
	}
	for (int i = 0; i < 5; i++)
	{
		boat[i].boat_id = i;
	}
	cout << "OK" << endl;
	fflush(stdout);
}

int Input()
{
	cin >> id >> money;
	int num;
	cin >> num;
	for (int i = 1; i <= num; i++)
	{
		int x, y, val;
		cin >> x >> y >> val;
		for (int j = 0; j < 10; j++)
		{
			if (dis[x][y][j] != -1)
			{
				berth[j].goods_info.insert(Record(id + 1000 - dis[x][y][j], x, y));
			}
		}
		goods_map[x][y] = { val, id + 1000 };
	}
	for (int i = 0; i < robot_num; i++)
	{
		int sts;
		cin >> robot[i].goods >> robot[i].x >> robot[i].y >> sts;
		robot[i].move_or_not = false;
	}
	for (int i = 0; i < 5; i++)
	{
		cin >> boat[i].status >> boat[i].pos;
	}
	char okk[100];
	cin >> okk;
	return id;
}

int main()
{
	Init();
	/*
	id = Input();
	for (int i = 0; i < 10; i++)
	{
		robot[i].find_berth();
	}
	puts("OK");
	fflush(stdout);
	for (int zhen = 0; zhen < 18; zhen++)
	{
		id = Input();
		my_alg::test_player0();
		if (zhen % 2)
		{
			robot[zhen / 2].target_x = -1;
			robot[zhen / 2].target_y = -1;
		}		
		puts("OK");
		fflush(stdout);
	}
	*/
	for (int zhen = 1; zhen <= 15000; zhen++)
	{
		id = Input();
		my_alg::test_player0();
		puts("OK");
		fflush(stdout);
	}

	return 0;
}
