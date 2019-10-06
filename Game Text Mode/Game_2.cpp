#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

int score = 000000;
int cmd_width = 80;
int cmd_hight = 23;
int ship_initx = 38;
int ship_inity = 20;
int count_star = 0;

const int STAR_AREA_X_MIN = 10;
const int STAR_AREA_X_MAX = 70;
const int STAR_AREA_Y_MIN = 3;
const int STAR_AREA_Y_MAX = 6;

void setcolor(int, int);
void setcursor(bool);
void gotoxy(int, int);
void erase_bullet(int , int );
void erase_ship(int, int);
void draw_ship(int, int);
void random_star(int);
void check_star();
void setframe();

bool over_frame(int, int);
bool draw_bullet(bool, int, int);
char cursor(int , int);

int main() {

	setcursor(false);
	setframe();

	int ship_x;
	int ship_y;

	const int max_bullet = 10;

	bool bullet_shoot[max_bullet] = { false };
	int bullet_x[max_bullet] = { 0 };
	int bullet_y[max_bullet] = { 0 };
	int num_bullet = 0;

	ship_x = ship_initx;
	ship_y = ship_inity;

	draw_ship(ship_x, ship_y);

	srand(time(NULL));
	random_star(20);

	char ch = ' ';
	while (ch != 'x') {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				if (!over_frame(ship_x - 1 , ship_y)) {
					ship_x--;
				}
			}
			if (ch == 'd') {
				if (!over_frame(ship_x + 1, ship_y)) {
					ship_x++;
				}
			}
			if (ch == ' ') {
				bullet_shoot[num_bullet] = true;
				bullet_x[num_bullet] = ship_x + 2;
				bullet_y[num_bullet] = ship_y - 1;

				num_bullet++;
				if (num_bullet >= max_bullet && bullet_shoot[0] == false) {
					num_bullet = 0;
				}
			}
			fflush(stdin);
		}

		draw_ship(ship_x, ship_y);
		for (int i = 0; i < max_bullet; i++) {
			if (bullet_shoot[i] == true) {
				bullet_shoot[i] = draw_bullet(bullet_shoot[i], bullet_x[i], bullet_y[i]);
				bullet_y[i]--;
			}
		}
		Sleep(50);
		erase_ship(ship_x, ship_y);
		for (int i = 0; i < max_bullet; i++) {
			erase_bullet(bullet_x[i], bullet_y[i]+1);
		}

		check_star();
		

	}
	return 0;
}



void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void gotoxy(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(7, 1);
	printf("<-A->");
	gotoxy(32, 22);
	setcolor(0, 8);
	printf("x = %d y = %d", x,y);
}

bool over_frame(int x, int y) {
	if (x >= 0 && x <= cmd_width - 5 && y > 1 && y <= cmd_hight) return false;
	else return true;
}


bool draw_bullet(bool bullet_shoot, int x, int y) {
	if (!over_frame(20, y)) {
		if (cursor(x, y) != '*') {
			if (bullet_shoot) {
				gotoxy(x, y);
				setcolor(7, 0);
				printf("|");
				return true;
			}
		}
		else {
			Beep(2000, 50);
			return false;
		}
	}
	else {
		return false;
	}
}

void erase_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}

void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf("     ");
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void random_star(int set) {
	int rand_num_x = 0;
	int rand_num_y = 0;
	int round = 0;
	
		while (round < set) {
			rand_num_y = (rand() % 3) + 2;
			rand_num_x = (rand() % 61) + 10;
			gotoxy(rand_num_x, rand_num_y);
			if (cursor(rand_num_x, rand_num_y) == ' ' && cursor(rand_num_x, rand_num_y) != '*') {
				setcolor(6, 0);
				printf("*");
				round++;
			}
		}
}



void check_star() {
	int x, y;
	count_star = 0;

	for (x = 10; x <= 70;x++) {
		for (y = 2; y <= 5; y++) {
			if (cursor(x, y) == '*') { count_star++; }
		}
	}
	int point = 20 - count_star;
	while (point>0) {
		score = score + 10;
		point--;
	}	
	random_star(20 - count_star);
	gotoxy(0, 0);
	setcolor(0, 7);
	printf("Numstar: %d", count_star);

	gotoxy(65, 0);
	setcolor(0, 7);
	printf("SCORE : %d", score);
}

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)& num_read))
		return '\0';
	else return buf[0];
}


void setframe() {
	int i;
	for (i = 0; i < cmd_width; i++) {
		gotoxy(i, 0);
		setcolor(0, 8);
		printf(" ");
	}
	for (i = 0; i < cmd_width; i++) {
		gotoxy(i, 22);
		setcolor(0, 8);
		printf(" ");
	}
}

void setscoreframe() {
	gotoxy(cmd_width - 17, 0);
	setcolor(0, 15);
	printf(" Score : ");

}