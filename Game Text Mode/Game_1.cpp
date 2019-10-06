#include <stdio.h>
#include <Windows.h>
#include <conio.h>

void gotoxy2(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship2(int x, int y) {
	gotoxy2(x, y); 
	printf("<-0->");
}

void erase_ship2(int x, int y) {
	gotoxy2(x,y);
	printf("     ");
}

int main2() {
	char ch = ' ';
	int x = 38, y = 20;
	draw_ship2(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x>0) { --x; }
			if (ch == 'd' && x <= 80) { ++x; }
			if (ch == 'w' && y > 0) { --y; }
			if (ch == 's' && y <= 20) { ++y; }
			fflush(stdin);
		}
		draw_ship2(x, y);
		Sleep(10);
		erase_ship2(x, y);
	} while (ch != 'x');
	return 0;
}