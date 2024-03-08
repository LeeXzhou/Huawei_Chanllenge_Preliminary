#include "../h_folder/my_algorithm.h"
using namespace std;
bool visited[205][205];
pair<int, int>pre[205][205];
int robot_op[15010];
namespace my_alg {
	void BFS()
	{
		return;
	}
	bool check_robot(int x, int y)//�ж�һ��λ���Ƿ�����û�����վ���Ϸ��Ҳ����ϰ�����ߺ���
	{
		if (x < 200 && x >= 0 && y < 200 && y >= 0 && ch[x][y] != '*' && ch[x][y] != '#')
		{
			return true;
		}
		return false;
	}
	void test_player0()
	{
		int cur_x = robot[0].x, cur_y = robot[0].y;
		if (robot[0].target_x == -1)
		{
			//����Ŀ��أ������

			memset(pre, 0, sizeof(pre));
			int fx[4] = { 1,-1,0,0 };
			int fy[4] = { 0,0,-1,1 };
			memset(visited, false, sizeof(visited));
			visited[cur_x][cur_y] = true;
			queue<pair<int, int>> q;
			q.push({ cur_x, cur_y });
			int found = 0;
			int step = 0;
			while (!found)
			{
				int q_size = q.size();
				for (int j = 1; j <= q_size; j++)
				{
					pair<int, int> u = q.front();
					q.pop();
					if (goods_map[u.first][u.second].second - id < step)
					{
						found = 1;
						robot[0].target_x = u.first;
						robot[0].target_y = u.second;
						pair<int, int>now = u;
						for (int i = 1; i <= step; i++)
						{
							for (int ii = 0; ii < 4; ii++)
							{
								if (pre[now.first][now.second].first + fx[ii] == now.first && pre[now.first][now.second].second + fy[ii] == now.second)
								{
									robot_op[id + step - i] = ii; break;
								}
							}
							now = pre[now.first][now.second];
						}
						break;
					}
					
					for (int i = 0; i < 4; i++)
					{
						int temp_x = u.first + fx[i], temp_y = u.second + fy[i];
						if (check_robot(temp_x, temp_y) && (!visited[temp_x][temp_y]))
						{
							visited[temp_x][temp_y] = 1;
							pre[temp_x][temp_y] = u;
						}
					}
				}
				step++;
			}
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
			cout << "move 0 " << robot_op[id] << endl;
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

