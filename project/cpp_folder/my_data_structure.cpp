#include "../h_folder/my_data_structure.h"

// ���� pair �ļӷ������
const MyPair operator+(const MyPair& a, const MyPair& b) {
    int sum_first = a.first + b.first;
    int sum_second = a.second + b.second;
    return MyPair(sum_first, sum_second);
}

// ���� pair �ļ��������
const MyPair operator-(const MyPair& a, const MyPair& b) {
    int diff_first = a.first - b.first;
    int diff_second = a.second - b.second;
    return MyPair(diff_first, diff_second);
}

// ������������
std::ostream& operator<<(std::ostream& os, const MyPair& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

Plan::Plan(int v, int t, int i, MyPair g)
{
    value = v, time = t, robot_id = i, target = g;
}

bool Plan::operator < (const Plan& tmp) const
{
    return value * tmp.time < time * tmp.value;
}
// �����������

