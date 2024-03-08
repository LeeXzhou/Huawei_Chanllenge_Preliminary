#include "../h_folder/search_policy.h"
#include "../h_folder/my_algorithm.h"
using namespace std;
Berth berth[berth_num + 10];
Robot robot[robot_num + 10];
Boat boat[10];
int money, boat_capacity, id;
char ch[N][N];
pair<int, int> goods_map[N][N];
short dis[205][205][10];	//-1表示不可达

// 求出每个点到10个港口的最短距离
void init_dis() {
	bool vis[205][205][10];	    //在BFS中判断是否使用过
	int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
    	memset(dis, -1, sizeof(dis));
	queue<pair<int, int> > q;

	auto check_boundary = [&](int x, int y)->bool {
		return x < 0 || x >= n || y < 0 || y >= n || ch[x][y] == '*' || ch[x][y] == '#';
	};

    auto cal_dis = [&](int id)->void {
        while(q.size()) {
            pair<int, int> tp = q.front(); q.pop();
            int x = tp.first, y = tp.second;
            for(int i = 0; i < 4; i++) {
                int _x = x + dx[i], _y = y + dy[i];
                if(vis[_x][_y][id] || check_boundary(_x, _y)) 
                    continue;
                vis[_x][_y][id] = 1;
                dis[_x][_y][id] = dis[x][y][id] + 1;
                q.push({_x, _y});
            }
        }
    };

	// 可优化：港口的半岛形态可以只BFS一侧
    for(int i = 0; i < berth_num; i++) {
        for(int x = 0; x < 4; x++) {
            for(int y = 0; y < 4; y++) {
                int _x = berth[i].x + x, _y = berth[i].y + y;
                q.emplace(_x, _y);
                dis[_x][_y][id] = 0;
                vis[_x][_y][id] = 1;
            }
	}
        cal_dis(i);
    }

}
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
	}
	cin >> boat_capacity;
	char okk[100];	//不知道干嘛的
	cin >> okk;

	init_dis();
	
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
