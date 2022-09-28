#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<curses.h>

uint8_t LEDmap[26][2] =
{
	{1,  1},//1///0
	{2,  2},//2///1
	{3,  3},//3///2
	{4,  4},//4///3
	{5,  5},//8///4
	{6,  6},//12///5
	{7,  7},//15///6
	{8,  8},//16///7
	{9,  9},//5///8
	{10,  10},//6///9
	{11,  11},//7///10
	{12,  12},//9///11
	{13,  13},//17///12
	{14,  14},//18///13
	{15,  15},//19///14
	{16,  16},//20///15
	{17,  17},//22///16
	{18,  18},//23///17
	{19,  19},//24///18
	{20,  20},//25///19
	{21,  21},//14///20
	{22,  22},//10///21
	{23,  23},//11///22
	{24,  24},//13///23
	{25,  25},//21///24
	{26,  26},//21///24

};

int aa =9;
int bb = 12;

struct xtest
{
	int ma;
	int mb;
};

int main(int argc, char* arv[])
{
	uint8_t (*ledmap)[2];
	ledmap = LEDmap;


	struct xtest  xtt = {aa,bb};

	printf("hello world\n");
	return 0;

	printf("xtest.ma is %d  xtest.mb is %d\n",xtt.ma,xtt.mb);



	for(int i=0;i<26;i++)
	{
//		printf("value is %d %d\n",ledmap[i][0],ledmap[i][1]);

	}

#if 0
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr,TRUE);
	keypad(stdscr,TRUE);

	int x,y;
	getmaxyx(stdscr,y,x);

	move(2,2);
	printw("%d\t%d\n",y,x);



	move(5,5);
	addch('h');
	refresh();
	int c=getch();
	move(5,5);

	if(c != ERR)
		addch(c);

	refresh();
	sleep(3);

	endwin();
#endif

}
