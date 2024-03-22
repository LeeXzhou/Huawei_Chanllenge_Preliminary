#ifndef my_algorithm_h
#define my_algorithm_h
#include "record.h"
using namespace std;

namespace my_alg {
	void BFS();
	void init_dis(); // 求出每个点到10个港口的最短距离
	void test_player0();
	void berth_num_update();
}
extern int min_trans_time;
#endif // !my_algorithm_h
