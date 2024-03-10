#ifndef my_data_structure_h
#define my_data_structure_h
#include <utility>
#include <iostream>
using namespace std;
using MyPair = std::pair<int, int>;

// 重载 pair 的加法运算符
const MyPair operator+(const MyPair& a, const MyPair& b);

// 重载 pair 的减法运算符
const MyPair operator-(const MyPair& a, const MyPair& b);

// 重载输出运算符
std::ostream& operator<<(std::ostream& os, const MyPair& p);
#endif // !my_data_structure_h
