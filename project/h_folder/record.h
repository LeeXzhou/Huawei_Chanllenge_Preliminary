#ifndef record_h
#define record_h
const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int N = 210;
class Robot {
public:
	int x = -1, y = -1, goods = -1;
	int status = -1;
	int mbx = -1, mby = -1;
	Robot() { };
	Robot(int startX, int startY);
};

class Berth {
public:
	int x = -1;
	int y = -1;
	int transport_time = -1;
	int loading_speed = -1;
	Berth() { };
	Berth(int x, int y, int transport_time, int loading_speed);
};

class Boat {
public:
	int num = -1, pos = -1, status = -1;
	Boat() { };
};
#endif // !record_h

