#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <SDL2/SDL.h>

#define total_frames 6569

using namespace std;

int main(int argc, char *argv[]){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Bad Apple", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	string line, content;
	clock_t start_t, curr_t;
	char path[19];
	int fms,x,y,tpf,count_t,wpos,wlen,bpos,blen = 0;
	fms = 0;
	PlaySound("res\\BA.wav", NULL, SND_ASYNC);
	Sleep(514);
	start_t = clock();
	count_t = start_t;
	while(fms <= total_frames){
		curr_t = clock();
		if(fms % 30 == 0)
			tpf = 43;
		else
			tpf = 33;
		if((curr_t - count_t) >= tpf){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			content = "";
			x = 0;
			y = 0;
			sprintf(path, "res\\BA%d.txt", fms);
			ifstream BAFile(path);
			while(getline(BAFile, line))
				content += line + "\n";
			BAFile.close();
			for(int pos = 0; pos < content.size(); pos++){
				if(content[pos] == '\n'){
					x = 0;
					y++;
				}else{
					if(content[pos] != ' '){
						SDL_RenderDrawLine(renderer, bpos*10, y*15, x*10+blen, y*15);
						SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
						wlen++;
						wpos = x;
						blen = 0;
					}else{
						SDL_RenderDrawLine(renderer, wpos*10, y*15, x*10+wlen, y*15);
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
						blen++;
						bpos = x;
						wlen = 0;
					}
				}
				x++;
			}
			SDL_RenderPresent(renderer);
			count_t += tpf;
			fms++;
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}