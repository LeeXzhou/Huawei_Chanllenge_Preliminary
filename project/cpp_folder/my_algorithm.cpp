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
			//����Ŀ��أ������
			bool visited[205][205];
			memset(visited, false, sizeof(visited));
			visited[cur_x][cur_y] = true;
			queue<pair<int, int>> q;
			q.push({ cur_x, cur_y });
		}
		else if (robot[0].target_x == cur_x && robot[0].target_y == cur_y)
		{
			//�޸�Ŀ���
			if (robot[0].target_x == berth[0].x && robot[0].target_y == berth[0].y)	//��ǰλ���ǲ�λ
			{
				cout << "pull 0" << endl;
				robot[0].target_x = -1;
				robot[0].target_y = -1;
			}
			else    //��ǰλ���ǻ����
			{
				cout << "get 0" << endl;	//�û���
				robot[0].target_x = berth[0].x;
				robot[0].target_y = berth[0].y;
			}
		}
		else
		{
			//�����߾�����
		}

		if (boat[0].status == 0) //�����ƶ���
		{

		}
		else if (boat[0].status == 1)
		{			
			if (boat[0].pos == -1)
			{
				//������-1��ǰ��0����ת��Ϊ�ƶ���
				cout << "ship 0 0" << endl;
			}
			else
			{
				if (boat[0].num > 10)	//��ǰ������������10
				{
					//��ת��Ϊ�ƶ��У�������0��ǰ��-1
					cout << "go 0" << endl;
				}				
			}			
		}
		else
		{
			//��λ��ȴ�״̬����ʱ������
		}
	}
}

