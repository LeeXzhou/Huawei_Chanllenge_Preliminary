#include <iostream>
#include "../h_folder/search_policy.h"
using namespace std;

void Init()
{
	for (int i = 1; i <= n; i++)
	{
		cin >> ch[i] + 1;
	}
		
	for (int i = 0; i < berth_num; i++)
	{
		int id;
		cin >> id;
		cin >> berth[id].x >> berth[id].y >> berth[id].transport_time >> berth[id].loading_speed;
	}
	cin >> boat_capacity;
	char okk[100];
	cin >> okk;
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
		int id = Input();
		for (int i = 0; i < robot_num; i++)
		{
			cout << "move " << i << " " << rand() % 4 << endl;
		}
		puts("OK");
		fflush(stdout);
	}

	return 0;
}
