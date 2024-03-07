#ifndef record_h
#define record_h
const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int N = 210;
class Robot {
public:
	int x, y, goods;
	int status;
	int mbx, mby;
	Robot() { };
	Robot(int startX, int startY);
};

class Berth {
public:
	int x;
	int y;
	int transport_time;
	int loading_speed;
	Berth() { };
	Berth(int x, int y, int transport_time, int loading_speed);
};

class Boat {
public:
	int num, pos, status;
};
#endif // !record_h

