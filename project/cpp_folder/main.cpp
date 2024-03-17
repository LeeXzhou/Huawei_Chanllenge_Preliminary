#include "../h_folder/search_policy.h"
#include "../h_folder/my_algorithm.h"
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
	//尾杀时间
	int temp_transport_time[10] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		temp_transport_time[i] = berth[i].transport_time;
	}
	sort(temp_transport_time, temp_transport_time + 10);
	tail_time = 15000 - (temp_transport_time[9] + temp_transport_time[8] + boat_capacity) * 2 - temp_transport_time[9] - 2 * boat_capacity;
	max_trans_time = temp_transport_time[9];
	second_max_trans = temp_transport_time[8];
	for (int i = 0; i < robot_num; i++)
	{
		robot[i].robot_id = i;
	}
	for (int i = 0; i < 5; i++)
	{
		boat[i].boat_id = i;
	}
	char okk[100];	//不知道干嘛的
	cin >> okk;
	my_alg::init_dis();
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
		for (int i = 0; i < 10; i++)
		{
			if (dis[x][y][i] != -1)
			{
				berth[i].goods_info.insert(Record(id + 1000 - dis[x][y][i], x, y));
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
	for (int zhen = 1; zhen <= 15000; zhen++)
	{
		id = Input();
		my_alg::test_player0();
		/*
		cerr << id << "!";
		for (int i = 0; i < robot_num; i++)
		{
			cout << "move " << i << " " << rand() % 4 << endl;
		}
		*/
		puts("OK");
		fflush(stdout);
	}

	return 0;
}
