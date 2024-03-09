#ifndef my_algorithm_h
#define my_algorithm_h
#include "record.h"
using namespace std;
extern pair<int, int> pre[205][205], nxt[205][205];
/*
÷ÿ‘ÿpairº”ºı∑®
*/
template<class Ty1, class Ty2>
const pair<Ty1, Ty2> operator+(const pair<Ty1, Ty2>& p1, const pair<Ty1, Ty2>& p2);

template<class Ty1, class Ty2>
const pair<Ty1, Ty2> operator-(const pair<Ty1, Ty2>& p1, const pair<Ty1, Ty2>& p2);

template <class T, class U>
ostream& operator<<(std::ostream& os, const std::pair<T, U>& p);

namespace my_alg {
	void BFS();
	void test_player0();
	bool check_robot(int x, int y);
	void robot_control();
	void boat_control();
	void find_road(int x = -1, int y = -1);
}
#endif // !my_algorithm_h
