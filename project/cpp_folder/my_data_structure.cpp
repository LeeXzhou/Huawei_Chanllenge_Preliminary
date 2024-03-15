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

Record::Record(int t, int x, int y)
{
    time = t;
    cur_x = x;
    cur_y = y;
}
bool Record::operator < (const Record& tmp) const
{
    if (time != tmp.time)
    {
        return time < tmp.time;
    }
    else if(cur_x != tmp.cur_x)
    {
        return cur_x < tmp.cur_x;
    }
    else
    {
        return cur_y < tmp.cur_y;
    }
    
}

bool Plan::operator < (const Plan& tmp) const
{
    return value * tmp.time < time * tmp.value;
}

int my_abs(const int& a, const int& b)
{
    if (a > b)
    {
        return a - b;
    }
    else
    {
        return b - a;
    }
}
// �����������

