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
			//����Ŀ���
		}
		else if (robot[0].target_x == cur_x && robot[0].target_y == cur_y)
		{
			//�޸�Ŀ���
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
				boat[0].pos = 0;	//������-1��ǰ��0
				boat[0].status = 0;	//��ת��Ϊ�ƶ���
				cout << "ship 0 0" << endl;
			}
			else
			{
				if (boat[0].num > 10)	//��ǰ������������10
				{
					boat[0].status = 0;	//��ת��Ϊ�ƶ���
					boat[0].pos = -1;	//������0��ǰ��-1
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

