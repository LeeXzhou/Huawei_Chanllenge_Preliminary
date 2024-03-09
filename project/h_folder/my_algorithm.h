#ifndef my_algorithm_h
#define my_algorithm_h
#include "record.h"
using namespace std;
static pair<int, int> pre[205][205], nxt[205][205];
/*
重载pair加减法
*/
template<class Ty1, class Ty2>
const pair<Ty1, Ty2> operator+(const pair<Ty1, Ty2>& p1, const pair<Ty1, Ty2>& p2);

template<class Ty1, class Ty2>
const pair<Ty1, Ty2> operator-(const pair<Ty1, Ty2>& p1, const pair<Ty1, Ty2>& p2);

template <class T, class U>
ostream& operator<<(std::ostream& os, const std::pair<T, U>& p);

namespace my_alg {
	static pair<int, int> dx_dy[4] = { {0, 1} , {0, -1}, {-1, 0}, {1, 0 } };
	void BFS();
	bool check_robot(int x, int y); //判断一个位置是否可以让机器人站（合法且不是障碍物或者海），true为可以到达
	//void init_dis(); // 求出每个点到10个港口的最短距离
	void test_player0();
	void robot_control();
	void boat_control();
	void find_road(int x = -1, int y = -1);
}
#endif // !my_algorithm_h
