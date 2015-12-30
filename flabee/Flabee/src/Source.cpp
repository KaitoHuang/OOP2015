#include "Header.h"

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Flabee", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(32000, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gIntroTexture = loadTexture("image/intro.png");
	if (gIntroTexture == NULL) {
		printf("Failed to load texture image!\n");
		success = false;
	}
	gTexture = loadTexture("image/menu.png");
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	gGOTexture = loadTexture("image/gameover.png");
	if (gGOTexture == NULL) {
		printf("Failed to load texture image!\n");
		success = false;
	}

	//Load background texture
	if (!gBGTexture.loadFromFile("image/day.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	//Load sprites
	if (!gButtonSpriteSheetTexture.loadFromFile("image/start.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else
	{
		//Set sprites
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
		{
			gButtonClips[i].x = 0;
			gButtonClips[i].y = i * 144;
			gButtonClips[i].w = BUTTON_WIDTH;
			gButtonClips[i].h = BUTTON_HEIGHT;
		}

		//Set buttons in corners
		gButtons[0].setPosition(330, 300);

	}

	//Load hive sprite sheet texture
	if (!gHiveTexture.loadFromFile("image/hive.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips
		gHiveClips[0].x = 0;
		gHiveClips[0].y = 0;
		gHiveClips[0].w = 80;
		gHiveClips[0].h = 435;

		gHiveClips[1].x = 00;
		gHiveClips[1].y = 465;
		gHiveClips[1].w = 80;
		gHiveClips[1].h = 435;

	}

	//Load sprite sheet texture
	if (!gSpriteSheetTexture.loadFromFile("image/bee.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 35.5;
		gSpriteClips[0].h = 40;

		gSpriteClips[1].x = 35.5;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 35.5;
		gSpriteClips[1].h = 40;

		gSpriteClips[2].x = 71;
		gSpriteClips[2].y = 0;
		gSpriteClips[2].w = 35.5;
		gSpriteClips[2].h = 40;

		gSpriteClips[3].x = 106.5;
		gSpriteClips[3].y = 0;
		gSpriteClips[3].w = 35.5;
		gSpriteClips[3].h = 40;
	}

	//Load sound effects
	gJump = Mix_LoadWAV("sound/jump.wav");
	if (gJump == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gCollide = Mix_LoadWAV("sound/pa.wav");
	if (gCollide == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load music
	gMusic = Mix_LoadMUS("sound/bgm.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont("font/KING_ROOSTER.ttf", 48);
	if (gFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	gInstruct = TTF_OpenFont("font/EHSMB.ttf", 18);
	if (gInstruct == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	
	return success;
}

void close() {
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;
	SDL_DestroyTexture(gIntroTexture);
	gIntroTexture = NULL;
	SDL_DestroyTexture(gGOTexture);
	gGOTexture = NULL;
	gButtonSpriteSheetTexture.free();
	gSpriteSheetTexture.free();
	gBeeTexture.free();
	gHiveTexture.free();
	gpass_NoTexture.free();
	gScoreTexture.free();
	gInstructTexture1.free();
	gInstructTexture2.free();

	//Free the sound effects
	Mix_FreeChunk(gJump);

	gJump = NULL;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Free global font
	TTF_CloseFont(gFont);
	TTF_CloseFont(gInstruct);
	gFont = NULL;
	gInstruct = NULL;

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b) {
	//the sides of the rectangles
	int leftA, rightA, topA, bottomA;
	int leftB, rightB, topB, bottomB;

	//go through the A boxes
	for (int Abox = 0; Abox < a.size(); Abox++) {
		//calculate the sides of rect A
		leftA = a[Abox].x;
		rightA = a[Abox].x + a[Abox].w;
		topA = a[Abox].y;
		bottomA = a[Abox].y + a[Abox].h;

		//go through the B boxes
		for (int Bbox = 0; Bbox < b.size(); Bbox++) {
			//calculate the sides of rect B
			leftB = b[Bbox].x;
			rightB = b[Bbox].x + b[Bbox].w;
			topB = b[Bbox].y;
			bottomB = b[Bbox].y + b[Bbox].h;

			//If no sides from A are outside of B
			if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false) {
				return true;
			}
		}
	}
		return false;
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			showIntro(quit);
			if (isExit) goto closeWindow;

			showMenu(quit);
			if (isExit) goto closeWindow;

		restart:
			isStarted(quit);
			if (isExit) goto closeWindow;

			gameOver(quit);
			if (isExit) goto closeWindow;

			closeWindow:
			if (start) goto restart;
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}