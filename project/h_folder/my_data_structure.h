#ifndef my_data_structure_h
#define my_data_structure_h
#include <utility>
#include <iostream>
#include <memory>
#include <stack>
#include<cstring>
using namespace std;
using MyPair = std::pair<int, int>;

// ���� pair �ļӷ������
const MyPair operator+(const MyPair& a, const MyPair& b);

// ���� pair �ļ��������
const MyPair operator-(const MyPair& a, const MyPair& b);

// ������������
std::ostream& operator<<(std::ostream& os, const MyPair& p);

struct Plan {
	int value = 0, time = 0, robot_id;
	MyPair target;
	Plan(int v, int t, int i, MyPair g);
	bool operator < (const Plan& tmp) const;
};
struct Record {
	int val, time, cur_x, cur_y;
};
#endif // !my_data_structure_h
