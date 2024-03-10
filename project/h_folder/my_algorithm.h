#ifndef my_algorithm_h
#define my_algorithm_h
#include "record.h"
using namespace std;
static MyPair pre[205][205], nxt[205][205];

namespace my_alg {
	static MyPair dx_dy[4] = { {0, 1} , {0, -1}, {-1, 0}, {1, 0 } };
	void BFS();
	bool check_robot(int x, int y); //�ж�һ��λ���Ƿ�����û�����վ���Ϸ��Ҳ����ϰ�����ߺ�����trueΪ���Ե���
	//void init_dis(); // ���ÿ���㵽10���ۿڵ���̾���
	void test_player0();
	void robot_control();
	void boat_control();
	void find_road(int x = -1, int y = -1);
}
#endif // !my_algorithm_h
