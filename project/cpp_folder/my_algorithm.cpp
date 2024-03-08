#include "../h_folder/my_algorithm.h"
using namespace std;
namespace my_alg{
	void BFS()
	{
		return;
	}
	void test_player0()
	{
		int cur_x = robot[0].x, cur_y = robot[0].y;
		if (robot[0].target_x == -1)
		{
			//定个目标地
		}
		else if (robot[0].target_x == cur_x && robot[0].target_y == cur_y)
		{
			//修改目标地
		}
		else
		{
			//继续走就是了
		}
		if (boat[0].status == 0) //正在移动中
		{

		}
		else if (boat[0].status == 1)
		{			
			if (boat[0].pos == -1)
			{
				boat[0].pos = 0;	//现在在-1，前往0
				boat[0].status = 0;	//船转变为移动中
				cout << "ship 0 0" << endl;
			}
			else
			{
				if (boat[0].num > 10)	//当前货物数量大于10
				{
					boat[0].status = 0;	//船转变为移动中
					boat[0].pos = -1;	//现在在0，前往-1
					cout << "go 0" << endl;
				}				
			}			
		}
		else
		{
			//泊位外等待状态，暂时不考虑
		}
	}
}

