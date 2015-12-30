//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

//Button constants
const int BUTTON_WIDTH = 144;
const int BUTTON_HEIGHT = 144;
const int TOTAL_BUTTONS = 1;

//hive counts
const int TOTAL_HIVES = 5;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	bool iloadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mFileTexture;
	SDL_Texture* mTextTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//The mouse button
class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event& e);

	//Shows button sprite
	void render();

private:
	//Top left position
	SDL_Point mPosition;

	//Currently used global sprite
	LButtonSprite mCurrentSprite;
};

//The hives that will be the obstacles
class Hive
{
public:
	//The dimensions of the hive
	static const int HIVE_WIDTH = 80;
	static const int HIVE_HEIGHT = 435;

	//The X and Y offsets of the hive
	int htopPosY, hbottomPosY, hPosX;

	//Initializes the variables
	Hive();

	//shows the hives
	void render();

	//moves the hive
	void move();

	//gets the collision boxes
	std::vector<SDL_Rect>& gettopColliders();
	std::vector<SDL_Rect>& getbottomColliders();

private:
	//initialize velocity
	int hVelX;

	//hive collision's boxes
	std::vector<SDL_Rect> hivebottomCollider;
	std::vector<SDL_Rect> hivetopCollider;

	//moves the collision boxes relative to the hive's offset
	void shiftColliders();

};

//The bee that will move around on the screen
class Bee
{
public:
	//The dimensions of the bee
	static const int BEE_WIDTH = 36;
	static const int BEE_HEIGHT = 40;

	//Maximum axis velocity of the bee
	static const int BEE_VEL = 15;
	static const double gravity;
	//The X and Y offsets of the bee
	double mPosX, mPosY;

	double angle;

	//Initializes the variables
	Bee();

	//deallocate hives
	~Bee();

	//Takes key presses and adjusts the bee's velocity
	void handleEvent(SDL_Event& e);

	//Moves the bee
	void move();
	
	//shows the hives
	void renderHives();

	//move the hives
	void moveHives();

	//did score
	void didScore();

	//gets the collision boxes
	std::vector<SDL_Rect>& getColliders();

private:
	//the hives
	Hive* hives[TOTAL_HIVES];

	//The velocity of the bee
	double mVelX, mVelY;

	//bee collision's cirlce
	std::vector<SDL_Rect> beeCollider;

	void shiftColliders();

};

const double Bee::gravity = 3.5;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//show game intro
void showIntro(bool quit);

//show menu function
void showMenu(bool quit);

//start function
void isStarted(bool quit);

//game over
void gameOver(bool quit);

//Frees media and shuts down SDL
void close();

//set collision detector
bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;
SDL_Texture* gIntroTexture = NULL;
SDL_Texture* gGOTexture = NULL;

//Scene textures
LTexture gBeeTexture;
LTexture gBGTexture;
LTexture gHiveTexture;

//whether game has started
bool start = false;

//exit the game
bool isExit = false;

//score value
bool isScored = false;
static int score = 0;

//bee collides
bool isDead = false;

//Globally used font
TTF_Font *gFont = NULL;
TTF_Font *gInstruct = NULL;

//Scene textures
LTexture gInstructTexture1;
LTexture gInstructTexture2;
LTexture gpass_NoTexture;
LTexture gScoreTexture;

//The music that will be played
Mix_Music *gMusic = NULL;
//The sound effects that will be used
Mix_Chunk *gJump = NULL;
Mix_Chunk *gCollide = NULL;

//Mouse button sprites
LTexture gButtonSpriteSheetTexture;

//Buttons objects
LButton gButtons[TOTAL_BUTTONS];

//Walking animation
const int WALKING_ANIMATION_FRAMES = 4;

//Scene sprites
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
SDL_Rect gHiveClips[2];
SDL_Rect gButtonClips[WALKING_ANIMATION_FRAMES];
LTexture gSpriteSheetTexture;


LTexture::LTexture()
{
	//Initialize
	mFileTexture = NULL;
	mTextTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

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
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mFileTexture = newTexture;
	return mFileTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTextTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTextTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);

	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTextTexture != NULL;
}
bool LTexture::iloadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gInstruct, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		free();

		//Create texture from surface pixels
		mTextTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTextTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);

	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTextTexture != NULL;
}

#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mFileTexture != NULL)
	{
		SDL_DestroyTexture(mFileTexture);
		mFileTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
	if (mTextTexture != NULL)
	{
		SDL_DestroyTexture(mTextTexture);
		mTextTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mFileTexture, red, green, blue);
	SDL_SetTextureColorMod(mTextTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mFileTexture, blending);
	SDL_SetTextureBlendMode(mTextTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mFileTexture, alpha);
	SDL_SetTextureAlphaMod(mTextTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mFileTexture, clip, &renderQuad, angle, center, flip);
	SDL_RenderCopyEx(gRenderer, mTextTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event& e)
{
	//If mouse event happened
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				start = true;
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{

		if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
			start = true;
		}

	}
}

void LButton::render()
{
	//Show current button sprite
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gButtonClips[mCurrentSprite]);
}

Hive::Hive() {
	//initilize the offsets
	hPosX = 800;
	srand(time(NULL));

	//initialize velocity
	hVelX = 3;

	//create the necessary SDL_Rects
	hivetopCollider.resize(6);
	hivebottomCollider.resize(6);

	//initialize the collision boxes' dimensions
	hivetopCollider[0].w = 15;
	hivetopCollider[0].h = 130;

	hivetopCollider[1].w = 70;
	hivetopCollider[1].h = 80;

	hivetopCollider[2].w = 15;
	hivetopCollider[2].h = 105;

	hivetopCollider[3].w = 55;
	hivetopCollider[3].h = 35;

	hivetopCollider[4].w = 75;
	hivetopCollider[4].h = 75;

	hivetopCollider[5].w = 35;
	hivetopCollider[5].h = 10;

	hivebottomCollider[0].w = 35;
	hivebottomCollider[0].h = 20;

	hivebottomCollider[1].w = 75;
	hivebottomCollider[1].h = 70;

	hivebottomCollider[2].w = 35;
	hivebottomCollider[2].h = 50;

	hivebottomCollider[3].w = 65;
	hivebottomCollider[3].h = 35;

	hivebottomCollider[4].w = 30;
	hivebottomCollider[4].h = 75;

	hivebottomCollider[5].w = 15;
	hivebottomCollider[5].h = 190;

	//initialize colliders relative to position
	shiftColliders();

}

void Hive::render() {
	//show image
	gHiveTexture.render(hPosX, hbottomPosY, &gHiveClips[1]);
	gHiveTexture.render(hPosX, htopPosY, &gHiveClips[0]);

}

void Hive::shiftColliders() {
	//the row offset
	int rt = 0;
	int rb = 0;

	//go through the hive's collision boxes
	for (int set = 0; set < hivebottomCollider.size(); ++set) {
		//center the collision box
		hivetopCollider[set].x = hPosX + (HIVE_WIDTH - hivetopCollider[set].w) / 2;
		hivebottomCollider[set].x = hPosX + (HIVE_WIDTH - hivebottomCollider[set].w) / 2;

		//set the collision box at its row offset
		hivetopCollider[set].y = htopPosY + rt;
		hivebottomCollider[set].y = hbottomPosY + rb;

		//move the row offset down the height of the collision box
		rt += hivetopCollider[set].h;
		rb += hivebottomCollider[set].h;
	}
}

std::vector<SDL_Rect>& Hive::gettopColliders() {
	return hivetopCollider;
}

std::vector<SDL_Rect>& Hive::getbottomColliders() {
	return hivebottomCollider;
}

void Hive::move() {
	//set the new position
	if (hPosX <= -200) hPosX = SCREEN_WIDTH;

	if (hPosX == SCREEN_WIDTH) {
		hbottomPosY = rand() % 220 + 180;
		htopPosY = hbottomPosY - (120 + HIVE_HEIGHT);
	}
	
	//moves the hive
	hPosX -= hVelX;
	shiftColliders();
}

Bee::Bee()
{
	//Initialize the offsets
	mPosX = 200;
	mPosY = (SCREEN_HEIGHT - BEE_HEIGHT) / 2;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	//create the necessary SDL_Rects
	beeCollider.resize(2);

	//initialize the collision boxes' dimensions
	beeCollider[0].w = 15;
	beeCollider[0].h = 10;

	beeCollider[1].w = 36;
	beeCollider[1].h = 28;

	//initialize colliders relative to position
	shiftColliders();

	//initialize hives
	for (int i = 0; i < TOTAL_HIVES; ++i) {
		hives[i] = new Hive();
	}
}

Bee::~Bee() {
	for (int i = 0; i < TOTAL_HIVES; ++i) delete hives[i];
}

void Bee::handleEvent(SDL_Event& e)
{
	mVelY = gravity;
	angle = 0.0;
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		if (e.key.keysym.sym == SDLK_UP)
		{
			mVelY = mVelY + gravity - BEE_VEL;
			angle = -30.0;
			Mix_PlayChannel(-1, gJump, 0);
		}

	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		if (e.key.keysym.sym == SDLK_UP)
		{
			mVelY = gravity;
			angle = 0.0;
		}
	}
	
	if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
		//Set mouse over sprite
		switch (e.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			mVelY = mVelY + gravity - BEE_VEL;
			angle = -30.0;
			Mix_PlayChannel(-1, gJump, 0);
			break;

		case SDL_MOUSEBUTTONUP:
			mVelY = gravity;
			angle = 0.0;
			break;
		}
	}
}

void Bee::move()
{
	//Move the bee left or right
	mPosX += mVelX;
	shiftColliders();

	for (int i = 0; i < TOTAL_HIVES; i++) {
		if ((!isScored) && ((hives[i]->hPosX + (hives[i]->HIVE_WIDTH / 2)) < mPosX + BEE_WIDTH)) {
			didScore();
		}
		
		if (checkCollision(beeCollider, hives[i]->gettopColliders()) || checkCollision(beeCollider, hives[i]->getbottomColliders())) {
			//dead
			Mix_PlayChannel(-1, gCollide, 0);
			isDead = true;
			start = false;
		}

		if ((mPosX + BEE_WIDTH) - hives[i]->hPosX == 216) isScored = false;

	}

	//Move the bee up or down
	mPosY += mVelY;
	shiftColliders();

	//If the bee went too far up or down
	for (int i = 0; i < TOTAL_HIVES; ++i) {
		if ((mPosY < 0) || (mPosY + BEE_HEIGHT >= SCREEN_HEIGHT) || (checkCollision(beeCollider, hives[i]->gettopColliders())) || (checkCollision(beeCollider, hives[i]->gettopColliders()))) {
			//dead
			Mix_PlayChannel(-1, gCollide, 0);
			isDead = true;
			start = false;
		}
	}
}

void Bee::didScore() {
	score += 1;
	isScored = true;
}

void Bee::moveHives() {
	//move the hives
	hives[0]->move();

	for (int i = 0; i < 4; i++) {
		if (hives[i]->hPosX <= 600 || hives[i]->hPosX > hives[i+1]->hPosX) {
			hives[i+1]->move();
		}
	}
}

void Bee::renderHives() {
	//render the hives
	for (int i = 0; i < TOTAL_HIVES; i++) {
		hives[i]->render();
	}
}

void Bee::shiftColliders() {
	//The row offset
	int r = 0;

	//Go through the bee's collision boxes
	for (int set = 0; set < beeCollider.size(); ++set)
	{
		//Center the collision box
		beeCollider[set].x = mPosX + (BEE_WIDTH - beeCollider[set].w) / 2;

		//Set the collision box at its row offset
		beeCollider[set].y = mPosY + r;

		//Move the row offset down the height of the collision box
		r += beeCollider[set].h;
	}
}

std::vector<SDL_Rect>& Bee::getColliders() {
	return beeCollider;
}

void showIntro(bool quit) {
	//Event handler
	SDL_Event i;

	//While application is running
	while (!quit)
	{
		while (SDL_GetTicks() <= 5000) {
			//Handle events on queue
			while (SDL_PollEvent(&i) != 0)
			{
				//User requests quit
				if (i.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//Render texture to screen
			SDL_RenderCopy(gRenderer, gIntroTexture, NULL, NULL);

			//Update screen
			SDL_RenderPresent(gRenderer);

			if (quit) {
				isExit = true;
				break;
			}
		}
		break;
	}
}

void showMenu(bool quit) {
	//Event handler
	SDL_Event e;

	//Current animation frameButton
	int frameButton = 0;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			//Handle button events
			for (int i = 0; i < TOTAL_BUTTONS; ++i)
			{
				gButtons[i].handleEvent(e);
			}
		}

		//set text color
		SDL_Color instructColor = { 192, 57, 43, 255 };

		//Render text
		if (!gInstructTexture1.iloadFromRenderedText("Press START / ENTER to Start", instructColor)) {
			printf("Unable to render instruction texture!\n");
		}
		if (!gInstructTexture2.iloadFromRenderedText("CLICK on the screen / Press UP KEY for game control", instructColor)) {
			printf("Unable to render instruction texture!\n");
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render texture to screen
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

		//Render buttons
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			gButtons[i].render();
		}

		//Render current frameButton
		SDL_Rect* currentClip = &gSpriteClips[frameButton / 4];
		gSpriteSheetTexture.render(((SCREEN_WIDTH - 40) / 2), (2 * SCREEN_HEIGHT / 5) + 40, currentClip);

		//Render textures
		gInstructTexture1.render((SCREEN_WIDTH - gInstructTexture1.getWidth()) / 2, (SCREEN_HEIGHT / 3));
		gInstructTexture2.render((SCREEN_WIDTH - gInstructTexture2.getWidth()) / 2, (SCREEN_HEIGHT / 3) + gInstructTexture1.getHeight());

		//Update screen
		SDL_RenderPresent(gRenderer);

		//Go to next frameButton
		++frameButton;

		//Cycle animation
		if (frameButton / 4 >= WALKING_ANIMATION_FRAMES)
		{
			frameButton = 0;
		}

		if (start) {
			break;
		}
		if (quit) {
			isExit = true;
			break;
		}
	}
}

void isStarted(bool quit) {
	int frame = 0;
	SDL_Event b;
	Bee bee;
	int scrollingOffset = 0;
	isScored = false;

	//Set text color
	SDL_Color textColor = { 255, 165, 150, 255 };

	//In memory text stream
	std::stringstream  pass_No;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&b) != 0)
		{
			//User requests quit
			if (b.type == SDL_QUIT)
			{
				quit = true;
			}

			//Handle input for the bee
			bee.handleEvent(b);

		}

		//Set score to be rendered
		pass_No.str(" ");
		pass_No << score;

		//Render text
		if (!gpass_NoTexture.loadFromRenderedText(pass_No.str().c_str(), textColor))
		{
			printf("Unable to render score texture!\n");
		}

		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(gMusic, -1);
		}

		//Move the bee
		bee.move();

		//move the hives
		bee.moveHives();

		//Scroll background
		--scrollingOffset;
		if (scrollingOffset < -gBGTexture.getWidth())
		{
			scrollingOffset = 0;
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render background
		gBGTexture.render(scrollingOffset, 0);
		gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0);

		//render the hives
		bee.renderHives();

		//Render current frame
		SDL_Rect* currentClip = &gSpriteClips[frame / 4];
		gSpriteSheetTexture.render(bee.mPosX, bee.mPosY, currentClip, bee.angle);

		//Render textures
		gpass_NoTexture.render((SCREEN_WIDTH - gpass_NoTexture.getWidth()) / 2, 80);

		//Update screen
		SDL_RenderPresent(gRenderer);

		//Go to next frame
		++frame;

		//Cycle animation
		if (frame / 4 >= WALKING_ANIMATION_FRAMES)
		{
			frame = 0;
		}

		if (isDead) break;

		if (quit) {
			start = false;
			isExit = true;
			break;
		}
	}
}

void gameOver(bool quit) {
	//Event handler
	SDL_Event q;

	//Current animation frameButton
	int frameB = 0;

	//Set text color as red
	SDL_Color scoreColor = { 255, 0, 0, 255 };

	//In memory text stream
	std::stringstream  theScore;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&q) != 0)
		{
			//User requests quit
			if (q.type == SDL_QUIT)
			{
				quit = true;
			}

			//Handle button events
			for (int i = 0; i < TOTAL_BUTTONS; ++i)
			{
				gButtons[i].handleEvent(q);
			}
		}

		//Set score to be rendered
		theScore.str(" ");
		theScore << score;

		//Render text
		if (!gScoreTexture.loadFromRenderedText(theScore.str().c_str(), scoreColor))
		{
			printf("Unable to render score texture!\n");
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render texture to screen
		SDL_RenderCopy(gRenderer, gGOTexture, NULL, NULL);

		//Render buttons
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			gButtons[i].render();
		}

		//Render current frameB
		SDL_Rect* currentClip = &gSpriteClips[frameB / 4];
		gSpriteSheetTexture.render(((SCREEN_WIDTH - 40) / 2), 230, currentClip);

		//Render textures
		gScoreTexture.render((SCREEN_WIDTH - gScoreTexture.getWidth()) / 2, 160);

		//Update screen
		SDL_RenderPresent(gRenderer);

		//Go to next frameButton
		++frameB;

		//Cycle animation
		if (frameB / 4 >= WALKING_ANIMATION_FRAMES)
		{
			frameB = 0;
		}

		if (start) {
			score = 0;
			isDead = false;
			break;
		}

		if (quit) {
			isExit = true;
			break;
		}
	}
}