#ifndef record_h
#define record_h
const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int N = 210;
int money, boat_capacity, id;
char ch[N][N];
int gds[N][N];
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
Berth berth[berth_num + 10];
Robot robot[robot_num + 10];
Boat boat[10];
#endif // !record_h

