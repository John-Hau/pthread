#include<stdio.h>
#include <SDL2/SDL.h>



typedef struct  
{
	int x,y;
	int life;
	char *name;
}Man;


int process_events(SDL_Window *window,Man *m)
{

	SDL_Event event;
	int done = 0;

	//check for events
	while(SDL_PollEvent(&event))
	{


		switch(event.type)
		{

			case SDL_WINDOWEVENT_CLOSE:
				if(window)
				{
					SDL_DestroyWindow(window);
					window = NULL;
				}
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						done =1;
						break;
#if 0
					case SDLK_RIGHT:
						m->x += 10;

						break;

					case SDLK_LEFT:
						m->x -= 10;
						break;
#endif


				}
				break;

			case SDL_QUIT:
				//quit out of the game
				done =1;
				break;




		}


	}





const uint8_t *state = SDL_GetKeyboardState(NULL);
//if(state[SDL_SCANCODE_RETURN])
if(state[SDL_SCANCODE_LEFT])
{
//	printf("<RETURN is down\n>");
	m->x --;
}


if(state[SDL_SCANCODE_RIGHT])
{
	//printf("<RETURN is down\n>");
	m->x ++;
}

if(state[SDL_SCANCODE_UP])
{
//	printf("<RETURN is down\n>");
	m->y --;
}


if(state[SDL_SCANCODE_DOWN])
{
	//printf("<RETURN is down\n>");
	m->y ++;
}








	return done;

}



int do_render(SDL_Renderer *renderer,Man*m)
{



	//Render display


	//set the drawing color to blue
	SDL_SetRenderDrawColor(renderer,0,0,255,255);
	//clear the screen (to blue)
	SDL_RenderClear(renderer);


	//set the drawing color to white 
	SDL_SetRenderDrawColor(renderer,255,255,255,255);


	SDL_Rect rect = {m->x,m->y,200,200};
	SDL_RenderFillRect(renderer,&rect);

	//we are done drawing, "present" or show to the sreen waht we've draw
	SDL_RenderPresent(renderer);


	//don't burn up the CPU
	//SDL_Delay(100);




	return 0;

}
















int main(int argc, char* argv[])
{


	SDL_Window*window;
	SDL_Renderer*renderer;

	SDL_Init(SDL_INIT_VIDEO);


	Man man;

	man.x = 220;
	man.y = 140;


	window =  SDL_CreateWindow("Game Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			640,
			480,
			0);


	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


	//====================
	//Event loop
	int done =0;
	while(!done)
	{

		done = process_events(window,&man);
		do_render(renderer,&man);
		SDL_Delay(100);

	}




	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();





	return 0;
}

