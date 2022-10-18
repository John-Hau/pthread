#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<unistd.h>
#include<fcntl.h>
#include<ncurses.h>



#define DIR_UP     10
#define DIR_DOWN   11 
#define DIR_LEFT   12 
#define DIR_RIGHT  13 

#define HEAD 3
#define BODY 4

int jsnake_len;
int jsnake_dir;
int newx;
int newy;

struct snake 
{
	int x;
	int y;
//}jbody[LINES*COLS];
}jsnake[30];



void init_jsnake(void)
{


	jsnake_dir = DIR_RIGHT;
	jsnake_len =6;

	jsnake[0].x = COLS/2 -1;
	jsnake[0].y = LINES/2 ;

	jsnake[1].x = COLS/2 -2;
	jsnake[1].y = LINES/2 ;


	jsnake[2].x = COLS/2 -3;
	jsnake[2].y = LINES/2 ;


	jsnake[3].x = COLS/2 -4;
	jsnake[3].y = LINES/2 ;


	jsnake[4].x = COLS/2 -5;
	jsnake[4].y = LINES/2 ;


	jsnake[5].x = COLS/2 -6;
	jsnake[5].y = LINES/2 ;

	newx = jsnake[0].x;
	newy = jsnake[0].y;

}

void jsnake_print(void)
{

	int i;

	for(i=0;i<jsnake_len;i++)
	{
	
		move(jsnake[i].y, jsnake[i].x);	
		addch('X');
	}

	refresh();


}




void jsnake_move(void)
{

	int i;
	int oldx;
	int oldy;

	oldx = jsnake[jsnake_len -1].x; 
	oldy = jsnake[jsnake_len -1].y; 

	for(i=0;i<jsnake_len - 1;i++)
	{
		jsnake[jsnake_len -i -1].x = jsnake[jsnake_len - i -2].x;
		jsnake[jsnake_len -i -1].y = jsnake[jsnake_len - i -2].y;
	}


	jsnake[0].x = newx;
	jsnake[0].y = newy;


	for(i=0;i<jsnake_len - 1;i++)
	{
	
		move(jsnake[i].y, jsnake[i].x);	
		addch('X');
	}

	move(oldy, oldx);	
	addch(' ');

	refresh();


}


void jsnake_forward_move(void)
{

	int i;
	int oldx;
	int oldy;

	oldx = jsnake[jsnake_len -1].x; 
	oldy = jsnake[jsnake_len -1].y; 

	for(i=0;i<jsnake_len - 1;i++)
	{
		jsnake[jsnake_len -i -1].x = jsnake[jsnake_len - i -2].x;
		jsnake[jsnake_len -i -1].y = jsnake[jsnake_len - i -2].y;
	}


	jsnake[0].x = newx;
	jsnake[0].y = newy;


	for(i=0;i<jsnake_len - 1;i++)
	{
	
		move(jsnake[i].y, jsnake[i].x);	
		addch('X');
	}

	move(oldy, oldx);	
	addch(' ');

	refresh();


}






int main(int argc, char* argv[])
{

	initscr();
	cbreak();
	keypad(stdscr,TRUE);
	halfdelay(1);
	curs_set(false);

	init_jsnake();

	jsnake_print();

	while(1)
	{
		int ch = getch();
		mvprintw(2,2,"%d",ch);

		switch(ch)
		{

			case KEY_F(1):
				goto END;
				break;

			case KEY_UP:
				jsnake_dir = DIR_UP;
				newy--;
				break;

			case KEY_DOWN:
				jsnake_dir = DIR_DOWN;
				newy++;
				break;

			case KEY_LEFT:
				jsnake_dir = DIR_LEFT;
				newx--;
				break;

			case KEY_RIGHT:
				jsnake_dir = DIR_RIGHT;
				newx++;
				break;

			default:
				break;





		}

		if(ch < 0)
		{
			switch(jsnake_dir)
			{

				case DIR_UP:
				//	jsnake_dir = DIR_UP;
					newy--;
					break;

				case DIR_DOWN:
				//	jsnake_dir = DIR_DOWN;
					newy++;
					break;

				case DIR_LEFT:
				//	jsnake_dir = DIR_LEFT;
					newx--;
					break;

				case DIR_RIGHT:
				//	jsnake_dir = DIR_RIGHT;
					newx++;
					break;

				default:
					break;

			}

		}

		jsnake_move();

	}

END:
	endwin();
	return 0;

}
