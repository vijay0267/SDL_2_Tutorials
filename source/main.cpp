//SDL and standard header files
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdint>

//Screen dimension constants
#define SDL_WINDOWPOS_X		 200
#define SDL_WINDOWPOS_Y		 100
#define SCREEN_WIDTH  		 640
#define SCREEN_HEIGHT  		 480

static SDL_Window* mainWindowSDL = nullptr;			//The window we'll be rendering to
static SDL_Surface* windowImageSDL = nullptr;
static SDL_Surface* screenSurfaceSDL = nullptr; 	//The surface contained by the window
static SDL_Event eventSDL;										   	//Event triggered by user

static bool initSDL(void);
static void closeSDL(void);
static bool loadImageToWindow(void);

int main(int argc, char* args[])
{
	bool isWindowOpen = true;
	if(true == initSDL())
	{
		if(true == loadImageToWindow())
		{
			;
		}
		
		while(true == isWindowOpen)
		{
			//A union that contains structures for the different event types.
			//SDL_PollEvent() removes the next event from the event queue.
			//If there are no events on the queue it returns 0, otherwise it returns 1. 
			while(SDL_PollEvent(&eventSDL))
			{
				switch(eventSDL.type)
				{
					case SDL_QUIT:
						isWindowOpen = false;
						closeSDL(); //To clean up code, destroy the window and quit SDL
						std::cout << "Window closed" << std::endl;
						break;
						
					case SDL_KEYDOWN:
						std::cout << (char)eventSDL.key.keysym.sym << " Key Pressed" << std::endl;
						break;
					
					default: // nothing
						break;
				}
			}
		}
		// Created window stays for 3 sec
		//SDL_Delay(3000);
		
		//To clean up code, destroy the window and quit SDL
		//closeSDL();
	}

	return 0;
}

//Starts up SDL and creates window
bool initSDL(void)
{
	//Initialization success status flag
	bool isInitSuccess = true;
	
	//When there's an error, SDL_Init returns -1, on success returns 0
	if( -1 == SDL_Init( SDL_INIT_VIDEO ) )
	{
		//When there's an error SDL_GetError() return string "SDL could not initialize! SDL_Error:"
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		isInitSuccess = false;
	}
	else
	{
		//Create a window with the specified position, dimensions, and flags.
		//Returns the window that was created or NULL on failure;
		mainWindowSDL = SDL_CreateWindow(
																				"An SDL2 window",              // window title
																				SDL_WINDOWPOS_X,        		   // initial x position
																				SDL_WINDOWPOS_Y,		           // initial y position
																				SCREEN_WIDTH,                  // width, in pixels
																				SCREEN_HEIGHT,                 // height, in pixels
																				SDL_WINDOW_SHOWN               // flags - ignored
																			);
									 
		if(nullptr == mainWindowSDL)
		{
			// In the case that the window could not be made...
			std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
			isInitSuccess = false;
		}
		else
		{
			//Get window surface
			screenSurfaceSDL = SDL_GetWindowSurface(mainWindowSDL);
		}
	}
	
	return isInitSuccess;
}

//Loads media
bool loadImageToWindow(void)
{
	bool isOpenImageSuccess = true;
	windowImageSDL = SDL_LoadBMP("images/hello_world.bmp");
	
	if(nullptr == windowImageSDL)
	{
		isOpenImageSuccess = false;
		std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
	}
	else
	{
		if(SDL_BlitSurface(windowImageSDL, nullptr, screenSurfaceSDL, nullptr) < 0U)
		{
			isOpenImageSuccess = false;
			std::cerr << "Image loading to surface failed! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			if(SDL_UpdateWindowSurface(mainWindowSDL) < 0U)
			{
				isOpenImageSuccess = false;
				std::cerr << "Image updation to surface failed! SDL_Error: " << SDL_GetError() << std::endl;
			}
			else
			{;}
		}
	}
	
	return isOpenImageSuccess;
}

//Frees media and shuts down SDL
void closeSDL(void)
{
	screenSurfaceSDL = nullptr;
	
	// Free an RGB surface.
	SDL_FreeSurface(windowImageSDL);
	windowImageSDL = nullptr;
	
	// Destroy a window.
  SDL_DestroyWindow(mainWindowSDL);
	mainWindowSDL = nullptr;
	
	// We safely uninitialize SDL2, that is, we are
	// taking down the subsystems here before we exit
	// our program. Quit SDL subsystems
  SDL_Quit();
}
