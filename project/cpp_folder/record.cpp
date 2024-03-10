#include "../h_folder/record.h"
using namespace std;
using MyPair = std::pair<int, int>;

// 重载 pair 的加法运算符
const MyPair operator+(const MyPair& a, const MyPair& b) {
    int sum_first = a.first + b.first;
    int sum_second = a.second + b.second;
    return MyPair(sum_first, sum_second);
}

// 重载 pair 的减法运算符
const MyPair operator-(const MyPair& a, const MyPair& b) {
    int diff_first = a.first - b.first;
    int diff_second = a.second - b.second;
    return MyPair(diff_first, diff_second);
}

// 重载输出运算符
std::ostream& operator<<(std::ostream& os, const MyPair& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
Berth::Berth(int x, int y, int transport_time, int loading_speed) {
	this->x = x;
	this->y = y;
	this->transport_time = transport_time;
	this->loading_speed = loading_speed;
}

Robot::Robot(int startX, int startY) {
	x = startX;
	y = startY;
}


