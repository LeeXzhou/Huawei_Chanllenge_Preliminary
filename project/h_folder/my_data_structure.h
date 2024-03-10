#ifndef my_data_structure_h
#define my_data_structure_h
#include <utility>
#include <iostream>
using namespace std;
using MyPair = std::pair<int, int>;

// ���� pair �ļӷ������
const MyPair operator+(const MyPair& a, const MyPair& b);

// ���� pair �ļ��������
const MyPair operator-(const MyPair& a, const MyPair& b);

// ������������
std::ostream& operator<<(std::ostream& os, const MyPair& p);
#endif // !my_data_structure_h
