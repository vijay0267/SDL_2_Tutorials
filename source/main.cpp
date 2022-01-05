/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <iostream>

//Screen dimension constants
#define SDL_WINDOWPOS_X		 200
#define SDL_WINDOWPOS_Y		 200
#define SCREEN_WIDTH  		 640
#define SCREEN_HEIGHT  		 480

//The window we'll be rendering to
SDL_Window* mainWindow = nullptr;

static bool init( void );

int main( int argc, char* args[] )
{
	bool u1initStatus = false;
	
	u1initStatus = init();
	if(true == u1initStatus)
	{
		// Created window stays for 3 sec
		SDL_Delay(3000);
		
		// We destroy our window. We are passing in the pointer
		// that points to the memory allocated by the 
		// 'SDL_CreateWindow' function. Remember, this is
		// a 'C-style' API, we don't have destructors.
		SDL_DestroyWindow( mainWindow );
	
		// We safely uninitialize SDL2, that is, we are
		// taking down the subsystems here before we exit
		// our program.
		SDL_Quit();
	}
	else
	{;}

	return 0;
}

//Starts up SDL and creates window
bool init( void )
{
	//Initialization success status flag
	bool u1successStatus = true;
	
	//When there's an error, SDL_Init returns -1, on success returns 0
	if( -1 == SDL_Init( SDL_INIT_VIDEO ) )
	{
		//When there's an error SDL_GetError() return string "SDL could not initialize! SDL_Error:"
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		u1successStatus = false;
	}
	else
	{
		u1successStatus = true;
		//Create a window with the specified position, dimensions, and flags.
		//Returns the window that was created or NULL on failure;
		mainWindow = SDL_CreateWindow(
										"An SDL2 window",                  // window title
										SDL_WINDOWPOS_X,        		   // initial x position
										SDL_WINDOWPOS_Y,		           // initial y position
										SCREEN_WIDTH,                      // width, in pixels
										SCREEN_HEIGHT,                     // height, in pixels
										SDL_WINDOW_SHOWN                   // flags - ignored
								     );
									 
		if(nullptr == mainWindow)
		{
			// In the case that the window could not be made...
			std::cout << "Could not create window: " << SDL_GetError() << std::endl;
			u1successStatus = false;
		}
		else
		{
			u1successStatus = true;
		}
	}
	
	return u1successStatus;
}

//Loads media
bool loadMedia(void)
{
	
}

//Frees media and shuts down SDL
void close(void)
{
	
}