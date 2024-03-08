#include "../h_folder/search_policy.h"
using namespace std;
Berth berth[berth_num + 10];
Robot robot[robot_num + 10];
Boat boat[10];
int money, boat_capacity, id;
char ch[N][N];
pair<int, int> goods_map[N][N];
short dis[205][205][10];	//-1表示不可达
void Init()
{
	for (int i = 1; i <= n; i++)
	{
		cin >> ch[i] + 1;
	}
		
	for (int i = 0; i < berth_num; i++)
	{
		cin >> id;
		cin >> berth[id].x >> berth[id].y >> berth[id].transport_time >> berth[id].loading_speed;
	}
	cin >> boat_capacity;
	char okk[100];
	cin >> okk;
	/*
	求出每个点到10个港口的最短距离
	4e5的空间大小 short
	？将地图信息降维处理
	
	*/
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
		goods_map[x][y] = { val, id + 1000 };
	}
	for (int i = 0; i < robot_num; i++)
	{
		int sts;
		cin >> robot[i].goods >> robot[i].x >> robot[i].y >> sts;
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
		cerr << id << "!";
		for (int i = 0; i < robot_num; i++)
		{
			cout << "move " << i << " " << rand() % 4 << endl;
		}
		puts("OK");
		fflush(stdout);
	}

	return 0;
}
