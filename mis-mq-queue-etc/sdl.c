#include<SDL/SDL.h>
#include<stdlib.h>
int main(){
  SDL_Surface *screen;
  Uint32 color;
  int x;
  if(SDL_Init(SDL_INIT_VIDEO)<0){
    fprintf(stderr,"无法初始化:%s\n",SDL_GetError());
    exit(1);
  }
  screen = SDL_SetVideoMode(640,480,16,SDL_SWSURFACE);/*640 X 480 X 16位色*/
  if(screen == NULL){
    fprintf(stderr,"无法设置640x480x16位色的视频模式:%s\n",SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
  color = SDL_MapRGB(screen->format,0,0,255);/*蓝色*/
  SDL_FillRect(screen,&screen->clip_rect,color); /*整个屏幕填充颜色*/
  SDL_UpdateRect(screen,0,0,0,0); /*更新整个屏幕*/
  SDL_Delay(5000);/*延迟５秒钟*/
  return 0;
}
