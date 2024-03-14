#ifndef search_policy_h
#define search_policy_h
#include "my_data_structure.h"
#include <queue>
using namespace std;
const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int N = 210;
extern MyPair pre_position[205][205];
const MyPair dx_dy[4] = { {0, 1} , {0, -1}, {-1, 0}, {1, 0} };
extern int money, boat_capacity, id;
extern char ch[N][N];
extern MyPair goods_map[N][N]; //first��¼value�� second��¼����ʱ��
extern int dis[205][205][10];
/*
˼·1����̰��value/time���������ŷ���
���������������ɸ�����ȥ�����ø����������ŵģ�
*/
class Search_Policy {
public:
	static priority_queue<Plan, vector<Plan>, less<Plan>> policy;	//�������ѡ�񷽰���
	static unique_ptr<MyPair[]> choose();
private:

};
#endif
