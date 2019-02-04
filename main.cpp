#include "SDL.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <string>
#include <time.h>
#include <iostream>


#ifndef _WIN32
#include <jni.h>
#endif

#define	IMG_DIR "images"
#define SND_DIR "sounds"
#define FNT_DIR "fonts"

#define SCREEN_WIDTH 	480
#define SCREEN_HEIGHT   800

const SDL_Color GRAY 		= {.r = 127  , .g = 127   , .b = 127   , .a = 255};
const SDL_Color SILVER		= {.r = 192  , .g = 192   , .b = 192   , .a = 255};
const SDL_Color RED			= {.r = 255  , .g = 0     , .b = 0     , .a = 255};
const SDL_Color GREEN		= {.r = 0    , .g = 255   , .b = 0     , .a = 255};
const SDL_Color BLUE		= {.r = 0    , .g = 0     , .b = 255   , .a = 255};
const SDL_Color YELLOW		= {.r = 255  , .g = 255   , .b = 0     , .a = 255};
const SDL_Color CYAN		= {.r = 0    , .g = 255   , .b = 255   , .a = 255};
const SDL_Color MAGENTA		= {.r = 255  , .g = 0     , .b = 255   , .a = 255};
const SDL_Color BLACK		= {.r = 0    , .g = 0     , .b = 0     , .a = 255};
const SDL_Color WHITE		= {.r = 255  , .g = 255   , .b = 255   , .a = 255};
const SDL_Color DARK_RED	= {.r = 100  , .g = 0     , .b = 0     , .a = 255};
const SDL_Color DARK_GREEN	= {.r = 0    , .g = 100   , .b = 0     , .a = 255};
const SDL_Color DARK_BLUE	= {.r = 0    , .g = 0     , .b = 100   , .a = 255};
const SDL_Color DARK_YELLOW	= {.r = 100  , .g = 100   , .b = 0     , .a = 255};
const SDL_Color DARK_CYAN	= {.r = 0    , .g = 100   , .b = 100   , .a = 255};
const SDL_Color DARK_MAGENTA= {.r = 100  , .g = 0     , .b = 100   , .a = 255};
const SDL_Color PURPLE		= {.r = 85   , .g = 26    , .b = 139   , .a = 255};
const SDL_Color GOLDEN		= {.r = 255  , .g = 215   , .b = 0     , .a = 255};
const SDL_Color ORANGE		= {.r = 255  , .g = 128   , .b = 0     , .a = 255};

const SDL_Rect SOUND_ON   	= {.x = 0    , .y = 0     , .w = 24    , .h = 24 };
const SDL_Rect SOUND_OFF 	= {.x = 24   , .y = 0     , .w = 24    , .h = 24 };

int shapes[7][4][16] = {   {{0, 1, 0, 0, 	// Line
                                    0, 1, 0, 0,
                                    0, 1, 0, 0,
                                    0, 1, 0, 0},
                                   {0, 0, 0, 0,
                                           1, 1, 1, 1,
                                           0, 0, 0, 0,
                                           0, 0, 0, 0},
                                   {0, 0, 1, 0,
                                           0, 0, 1, 0,
                                           0, 0, 1, 0,
                                           0, 0, 1, 0},
                                   {0, 0, 0, 0,
                                           0, 0, 0, 0,
                                           1, 1, 1, 1,
                                           0, 0, 0, 0}},

                           {{0, 0, 0, 0,	// Square
                                    0, 2, 2, 0,
                                    0, 2, 2, 0,
                                    0, 0, 0, 0},
                                   {0, 0, 0, 0,
                                           0, 2, 2, 0,
                                           0, 2, 2, 0,
                                           0, 0, 0, 0},
                                   {0, 0, 0, 0,
                                           0, 2, 2, 0,
                                           0, 2, 2, 0,
                                           0, 0, 0, 0},
                                   {0, 0, 0, 0,
                                           0, 2, 2, 0,
                                           0, 2, 2, 0,
                                           0, 0, 0, 0}},

                           {{3, 3, 0, 0,	// L-shape
                                    0, 3, 0, 0,
                                    0, 3, 0, 0,
                                    0, 0, 0, 0},
                                   {0, 0, 3, 0,
                                           3, 3, 3, 0,
                                           0, 0, 0, 0,
                                           0, 0, 0, 0},
                                   {0, 3, 0, 0,
                                           0, 3, 0, 0,
                                           0, 3, 3, 0,
                                           0, 0, 0, 0},
                                   {0, 0, 0, 0,
                                           3, 3, 3, 0,
                                           3, 0, 0, 0,
                                           0, 0, 0, 0}},

                           {{0, 4, 4, 0,	// J-shape
                                    0, 4, 0, 0,
                                    0, 4, 0, 0,
                                    0, 0, 0, 0},
                                   {0, 0, 0, 0,
                                           4, 4, 4, 0,
                                           0, 0, 4, 0,
                                           0, 0, 0, 0},
                                   {0, 4, 0, 0,
                                           0, 4, 0, 0,
                                           4, 4, 0, 0,
                                           0, 0, 0, 0},
                                   {4, 0, 0, 0,
                                           4, 4, 4, 0,
                                           0, 0, 0, 0,
                                           0, 0, 0, 0}},

                           {{0, 5, 0, 0,	// Tee
                                    5, 5, 5, 0,
                                    0, 0, 0, 0,
                                    0, 0, 0, 0},
                                   {0, 5, 0, 0,
                                           0, 5, 5, 0,
                                           0, 5, 0, 0,
                                           0, 0, 0, 0},
                                   {0, 0, 0, 0,
                                           5, 5, 5, 0,
                                           0, 5, 0, 0,
                                           0, 0, 0, 0},
                                   {0, 5, 0, 0,
                                           5, 5, 0, 0,
                                           0, 5, 0, 0,
                                           0, 0, 0, 0}},

                           {{0, 6, 0, 0,	// Z-shape
                                    6, 6, 0, 0,
                                    6, 0, 0, 0,
                                    0, 0, 0, 0},
                                   {6, 6, 0, 0,
                                           0, 6, 6, 0,
                                           0, 0, 0, 0,
                                           0, 0, 0, 0},
                                   {0, 0, 6, 0,
                                           0, 6, 6, 0,
                                           0, 6, 0, 0,
                                           0, 0, 0, 0},
                                   {0, 0, 0, 0,
                                           6, 6, 0, 0,
                                           0, 6, 6, 0,
                                           0, 0, 0, 0}},

                           {{7, 0, 0, 0,	// S-shape
                                    7, 7, 0, 0,
                                    0, 7, 0, 0,
                                    0, 0, 0, 0},
                                   {0, 7, 7, 0,
                                           7, 7, 0, 0,
                                           0, 0, 0, 0,
                                           0, 0, 0, 0},
                                   {0, 7, 0, 0,
                                           0, 7, 7, 0,
                                           0, 0, 7, 0,
                                           0, 0, 0, 0},
                                   {0, 0, 0, 0,
                                           0, 7, 7, 0,
                                           7, 7, 0, 0,
                                           0, 0, 0, 0}}};

class helper {
public:
    static void 		 drawText(TTF_Font * font, const char * text, SDL_Color color, int x, int y, SDL_Renderer * screen);
    static void 		 drawTextCentered(TTF_Font * font, const char * text, SDL_Color color, int x, int y, int sideX, int sideY, SDL_Renderer * screen);
    static std::string 	 int2string(int value);
    static SDL_Surface * load_image(std::string fileName, std::string path);
    static TTF_Font * 	 load_text_font(std::string fileName, std::string path, int tamanyo);
    static Mix_Music *	 load_sound(std::string fileName, std::string path);
	static SDL_Texture * loadSpriteSheet(SDL_Renderer* renderer, std::string fileName, std::string path);
#ifndef _WIN32
    static void doVibrateFromJNI(int duration);
#endif
};

#ifndef _WIN32
void helper::doVibrateFromJNI(int duration) {
    // retrieve the JNI environment.
    JNIEnv * javaEnviron = (JNIEnv *)SDL_AndroidGetJNIEnv();
    if (javaEnviron != NULL) {
        jclass clazz = javaEnviron->FindClass("com/game/tetris/TetrisActivity");
        if (clazz == 0) {
            SDL_Log("Error JNI: Class com/game/tetris/TetrisActivity not found!");
            return;
        }
        jmethodID method_id = javaEnviron->GetStaticMethodID(clazz, "doVibrate", "(I)V");
        if (method_id == 0) {
            SDL_Log("Error JNI: methodId is 0, method doVibrate (I)V not found!");
            return;
        }
        // Call Java-method
        javaEnviron->CallStaticVoidMethod(clazz, method_id, (jint)duration);
        javaEnviron->DeleteLocalRef(clazz);
    }
}
#endif

void helper::drawText(TTF_Font * font, const char * text, SDL_Color color, int x, int y, SDL_Renderer * screen) {
    SDL_Surface * textMessage = textMessage = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(screen, textMessage);
    SDL_FreeSurface(textMessage);
    int h, w;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(screen, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

void helper::drawTextCentered(TTF_Font * font, const char * text, SDL_Color color, int x, int y, int sideX, int sideY, SDL_Renderer * screen) {
    SDL_Surface * textMessage = textMessage = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(screen, textMessage);
    SDL_FreeSurface(textMessage);
    int h, w;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dst;
    dst.x = x + (sideX/2) - (w/2);
    dst.y = y + (sideY/2) - (h/2);
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(screen, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

std::string helper::int2string(int value) {
    char buffer[20]; // Max num of digits for 64 bit number
    sprintf(buffer,"%d", value);
    return std::string(buffer);
}

SDL_Surface * helper::load_image(std::string fileName, std::string path) {
#ifdef _WIN32
    std::string imagePath = path + "\\" + fileName;
#else
    std::string imagePath = path + "/" + fileName;
#endif
    SDL_Surface *image = IMG_Load(imagePath.c_str());
    if (image == NULL)
        SDL_Log("Unable to load image %s! SDL_image Error: %s\n", imagePath.c_str(), IMG_GetError());
    return image;
}

TTF_Font * helper::load_text_font(std::string fileName, std::string path, int tamanyo) {
#ifdef _WIN32
    std::string fontPath = path + "\\" + fileName;
#else
    std::string fontPath = path + "/" + fileName;
#endif
    TTF_Font * font = TTF_OpenFont(fontPath.c_str(), tamanyo);
    if (font == NULL)
        SDL_Log("TTF_OpenFont Error: %s\r\n", TTF_GetError());
    return font;
}

Mix_Music * helper::load_sound(std::string fileName, std::string path) {
#ifdef _WIN32
    std::string musicPath = path + "\\" + fileName;
#else
    std::string musicPath = path + "/" + fileName;
#endif
    Mix_Music * music = Mix_LoadMUS(musicPath.c_str());
    if (music == NULL)
        SDL_Log("Mix_LoadMUS Error: %s\r\n", Mix_GetError());
    return music;
}

SDL_Texture * helper::loadSpriteSheet(SDL_Renderer* renderer, std::string fileName, std::string path) {
#ifdef _WIN32
    std::string imagePath = path + "\\" + fileName;
#else
    std::string imagePath = path + "/" + fileName;
#endif	
    SDL_Surface * spriteSheet = IMG_Load(imagePath.c_str());
	if (spriteSheet == NULL) {
        SDL_Log("Unable to load image %s! SDL_image Error: %s\n", imagePath.c_str(), IMG_GetError());
		return NULL;
	}
	SDL_Texture * texture 	  = SDL_CreateTextureFromSurface(renderer, spriteSheet);   	
   	SDL_FreeSurface(spriteSheet);
   	return texture;
}

class Cell {
public:
    Cell();
    ~Cell(){};
    void init(int x, int y, int side, int value);
    void setValue(int value);
    int getValue(void);
    void plot(SDL_Renderer * screen);
private:
    int x, y, side, value;
};

Cell::Cell() {
}

void Cell::setValue(int value) {
    this->value = value;
}

void Cell::init(int x, int y, int side, int value) {
    this->x = x;
    this->y = y;
    this->side = side;
    this->value = value;
}

int Cell::getValue(void) {
    return this->value;
}

void Cell::plot(SDL_Renderer * screen) {
    SDL_Rect box;
    switch(this->value) {
        case 0x00: // BLACK
        	/*
            SDL_SetRenderDrawColor(screen, 0    , 0     , 0     , 255); // BLACK
            box.x = this->x;
            box.y = this->y;
            box.w = this->side;
            box.h = this->side;
            SDL_RenderFillRect(screen, &box);
            SDL_SetRenderDrawColor(screen, 255  , 255   , 255   , 255); // WHITE
            */
            break;
        case 0x01: // BLUE
            SDL_SetRenderDrawColor(screen, 0    , 0     , 255   , 255); // BLUE
            box.x = this->x+1;
            box.y = this->y+1;
            box.w = this->side-1;
            box.h = this->side-1;
            SDL_RenderFillRect(screen, &box);
            SDL_SetRenderDrawColor(screen, 255  , 255   , 255   , 255); // WHITE
            SDL_RenderDrawLine(screen, this->x, this->y, this->x, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y, this->x + this->side, this->y);
            SDL_SetRenderDrawColor(screen, 0    , 0     , 100   , 255); // DARK BLUE
            SDL_RenderDrawLine(screen, this->x + this->side, this->y, this->x + this->side, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y + this->side, this->x + this->side, this->y + this->side);
            break;
        case 0x02: // RED
            SDL_SetRenderDrawColor(screen, 255  , 0     , 0     , 255); // RED
            box.x = this->x+1;
            box.y = this->y+1;
            box.w = this->side-1;
            box.h = this->side-1;
            SDL_RenderFillRect(screen, &box);
            SDL_SetRenderDrawColor(screen, 255  , 255   , 255   , 255); // WHITE
            SDL_RenderDrawLine(screen, this->x, this->y, this->x, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y, this->x + this->side, this->y);
            SDL_SetRenderDrawColor(screen, 100  , 0     , 0     , 255);	// DARK RED
            SDL_RenderDrawLine(screen, this->x + this->side, this->y, this->x + this->side, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y + this->side, this->x + this->side, this->y + this->side);
            break;
        case 0x03: // GREEN
            SDL_SetRenderDrawColor(screen, 0    , 255   , 0     , 255); // GREEN
            box.x = this->x+1;
            box.y = this->y+1;
            box.w = this->side-1;
            box.h = this->side-1;
            SDL_RenderFillRect(screen, &box);
            SDL_SetRenderDrawColor(screen, 255  , 255   , 255   , 255); // WHITE
            SDL_RenderDrawLine(screen, this->x, this->y, this->x, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y, this->x + this->side, this->y);
            SDL_SetRenderDrawColor(screen, 0    , 100   , 0     , 255); // DARK GREEN
            SDL_RenderDrawLine(screen, this->x + this->side, this->y, this->x + this->side, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y + this->side, this->x + this->side, this->y + this->side);
            break;
        case 0x04: // YELLOW
            SDL_SetRenderDrawColor(screen, 255  , 255   , 0     , 255); // YELLOW
            box.x = this->x+1;
            box.y = this->y+1;
            box.w = this->side-1;
            box.h = this->side-1;
            SDL_RenderFillRect(screen, &box);
            SDL_SetRenderDrawColor(screen, 255  , 255   , 255   , 255); // WHITE
            SDL_RenderDrawLine(screen, this->x, this->y, this->x, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y, this->x + this->side, this->y);
            SDL_SetRenderDrawColor(screen, 100  , 100   , 0     , 255); // DARK YELLOW
            SDL_RenderDrawLine(screen, this->x + this->side, this->y, this->x + this->side, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y + this->side, this->x + this->side, this->y + this->side);
            break;
        case 0x05: // CYAN
            SDL_SetRenderDrawColor(screen, 0    , 255   , 255   , 255); // CYAN
            box.x = this->x+1;
            box.y = this->y+1;
            box.w = this->side-1;
            box.h = this->side-1;
            SDL_RenderFillRect(screen, &box);
            SDL_SetRenderDrawColor(screen, 255  , 255   , 255   , 255); // WHITE
            SDL_RenderDrawLine(screen, this->x, this->y, this->x, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y, this->x + this->side, this->y);
            SDL_SetRenderDrawColor(screen, 0    , 100   , 100   , 255); // DARK CYAN
            SDL_RenderDrawLine(screen, this->x + this->side, this->y, this->x + this->side, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y + this->side, this->x + this->side, this->y + this->side);
            break;
        case 0x06: // MAGENTA
            SDL_SetRenderDrawColor(screen, 255  , 0     , 255   , 255); // MAGENTA
            box.x = this->x+1;
            box.y = this->y+1;
            box.w = this->side-1;
            box.h = this->side-1;
            SDL_RenderFillRect(screen, &box);
            SDL_SetRenderDrawColor(screen, 255  , 255   , 255   , 255); // WHITE
            SDL_RenderDrawLine(screen, this->x, this->y, this->x, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y, this->x + this->side, this->y);
            SDL_SetRenderDrawColor(screen, 100  , 0     , 100   , 255); // DARK MAGENTA
            SDL_RenderDrawLine(screen, this->x + this->side, this->y, this->x + this->side, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y + this->side, this->x + this->side, this->y + this->side);
            break;
        case 0x07: // PURPLE
            SDL_SetRenderDrawColor(screen, 85   , 26    , 139   , 255); // PURPLE
            box.x = this->x+1;
            box.y = this->y+1;
            box.w = this->side-1;
            box.h = this->side-1;
            SDL_RenderFillRect(screen, &box);
            SDL_SetRenderDrawColor(screen, 255  , 255   , 255   , 255); // WHITE
            SDL_RenderDrawLine(screen, this->x, this->y, this->x, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y, this->x + this->side, this->y);
            SDL_SetRenderDrawColor(screen, 40   , 10    , 70    , 255); // DARK PURPLE
            SDL_RenderDrawLine(screen, this->x + this->side, this->y, this->x + this->side, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y + this->side, this->x + this->side, this->y + this->side);
            break;
        case 0x08: // GREY
            SDL_SetRenderDrawColor(screen, 127  , 127   , 127   , 255); // GREY
            box.x = this->x+1;
            box.y = this->y+1;
            box.w = this->side-1;
            box.h = this->side-1;
            SDL_RenderFillRect(screen, &box);
            SDL_SetRenderDrawColor(screen, 255  , 255   , 255   , 255); // WHITE
            SDL_RenderDrawLine(screen, this->x, this->y, this->x, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y, this->x + this->side, this->y);
            SDL_SetRenderDrawColor(screen, 63   , 63    , 63    , 255); // DARK GREY
            SDL_RenderDrawLine(screen, this->x + this->side, this->y, this->x + this->side, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y + this->side, this->x + this->side, this->y + this->side);
            break;
        case 0x09: // GOLDEN
            SDL_SetRenderDrawColor(screen, 255  , 215   , 0     , 255); // GOLDEN
            box.x = this->x+1;
            box.y = this->y+1;
            box.w = this->side-1;
            box.h = this->side-1;
            SDL_RenderFillRect(screen, &box);
            SDL_SetRenderDrawColor(screen, 255  , 255   , 255   , 255); // WHITE
            SDL_RenderDrawLine(screen, this->x, this->y, this->x, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y, this->x + this->side, this->y);
            SDL_SetRenderDrawColor(screen, 127  , 107   , 0     , 255); // DARK GOLDEN
            SDL_RenderDrawLine(screen, this->x + this->side, this->y, this->x + this->side, this->y + this->side);
            SDL_RenderDrawLine(screen, this->x, this->y + this->side, this->x + this->side, this->y + this->side);
            break;
    }
    SDL_SetRenderDrawColor(screen, 0    , 0     , 0     , 255);	// BLACK
}

class Table {
public:
    Table(int width, int height);
    ~Table();
    void drawTable(SDL_Renderer * screen);
    SDL_bool play(SDL_Renderer * screen, SDL_Event & event, int * points, int * level, SDL_bool * isMusic);
    SDL_bool isCollision(int x, int y, int shape[16]);
private:
    int width, height, side, ttime, speed, maxY, lines;
    int currentPiece, currentPosition, xP, yP;
    SDL_bool isShape;
    Cell cells[10][20];
};

Table::Table(int width, int height) {
    this->isShape	= SDL_FALSE;
    this->speed 	= 1000; // 1 second
    this->lines		= 0;
    this->ttime		= SDL_GetTicks();
    this->side 		= width / 10;
    this->width	 	= width;
    this->height	= height;
    this->maxY		= (height / this->side) - 1;
    if (this->maxY > 20) this->maxY = 20;
    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 20; y++)
            this->cells[x][y].init(x * this->side, y * this->side, this->side, 0);
    srand(time(NULL));
}

Table::~Table() {
}

void Table::drawTable(SDL_Renderer * screen) {
    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 20; y++)
            this->cells[x][y].plot(screen);
}

SDL_bool Table::isCollision(int x, int y, int shape[16]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (((this->cells[x+i][y+j].getValue() == 8) && (shape[i+4*j] > 0)) ||
                ((shape[i+4*j] > 0) && (y+j > this->maxY)) ||
                ((shape[i+4*j] > 0) && (x+i > 9)) ||
                ((shape[i+4*j] > 0) && (x+i < 0)))
                return SDL_TRUE;
    return SDL_FALSE;
}

SDL_bool Table::play(SDL_Renderer * screen, SDL_Event & event, int * points, int * level, SDL_bool * isMusic) {
    SDL_bool retorno = SDL_FALSE;
    int x, y, temp;
    // -- Check if there is a previous marked lines in order to remove them
    temp = 0;
    for (int j = 0; j < 20; j++) {
        if (this->cells[0][j].getValue() == 9) {
            for (int k = j; k > 0; k--)
                for (int i = 0; i < 10; i++)
                    this->cells[i][k].setValue(this->cells[i][k-1].getValue());
            temp++;
        }
    }
    if (temp > 0) {
        this->lines += temp;
        *points += (temp * temp) * 100;
        SDL_Delay(300);
    }
    // -- Check if it's necessary to increase speed
    if (this->lines > 10) {
        this->speed -= 100;
        this->lines = 0;
        *level += 1;
    }
    // -- Check if there is a line and add points
    for (int j = 0; j < 20; j++) {
        temp = 0;
        for (int i = 0; i < 10; i++)
            if (this->cells[i][j].getValue() == 8) temp++;
        if (temp == 10) // there is a line
            for (int i = 0; i < 10; i++) this->cells[i][j].setValue(9);
    }
    // -- If there is no piece, put another-one in the table
    if (this->isShape == SDL_FALSE) {
        this->currentPiece 		= (rand() % 7) + 1;
        this->currentPosition 	= 0;
        this->xP				= 3;
        this->yP				= 0;
        // Check if there is a collision
        if (this->isCollision(xP, yP, shapes[this->currentPiece-1][this->currentPosition]) == SDL_TRUE)	retorno = SDL_TRUE; // FAIL
        this->isShape = SDL_TRUE;
        this->ttime = SDL_GetTicks();
    }
    // -- Check keyboard
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            SDL_Log("TODO: Salir\r\n");
            return SDL_TRUE;
        }
        else if (event.type == SDL_WINDOWEVENT) {
            //Window resize/orientation change
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)	{
                //w = e.window.data1; h = e.window.data2;
                SDL_RenderPresent(screen);
            }
        }
        else if ((event.type == SDL_FINGERDOWN) || (event.type == SDL_MOUSEBUTTONDOWN)) {
#ifdef _WIN32
            x = event.button.x;
			y = event.button.y;
#else
            x = (event.tfinger.x * this->width);
            y = (event.tfinger.y * this->height);
#endif
            if ((x > 0) && (x < this->width) && (y > 0) && (y < this->height)) { // If X and Y coordinates are OK
                if ((x > this->width * 9 / 10) && (y < this->side)) {
					if (*isMusic == SDL_TRUE) {
            			*isMusic = SDL_FALSE;
            			Mix_PauseMusic();								
					} else {
						*isMusic = SDL_TRUE;
						Mix_ResumeMusic();
					}
				} else {
					if (y < (this->height * 3 / 8)) {						// Upper side -> rotate piece
						temp = this->currentPosition + 1;
						if (temp > 3) temp = 0;
						if (this->isCollision(this->xP, this->yP, shapes[this->currentPiece-1][temp]) == SDL_FALSE) this->currentPosition = temp;
					} else {
						if (y > (this->height * 7 / 8)) {	// Down side -> move down
							if (this->isCollision(this->xP, this->yP+1, shapes[this->currentPiece-1][this->currentPosition]) == SDL_TRUE) {
								for (int i = 0; i < 4; i++)
									for (int j = 0; j < 4; j++)
										if (shapes[this->currentPiece-1][this->currentPosition][i+j*4] != 0)
											this->cells[this->xP+i][this->yP+j].setValue(8);
								isShape = SDL_FALSE;
							} else {
								this->yP++;
							}
						} else {
							if (x > (this->width / 2)) {				// Left side -> move left
								temp = xP + 1;
								if (this->isCollision(temp, this->yP, shapes[this->currentPiece-1][this->currentPosition ]) == SDL_FALSE) this->xP = temp;
							} else{										// Right side -> move right
								temp = xP - 1;
								if (this->isCollision(temp, this->yP, shapes[this->currentPiece-1][this->currentPosition ]) == SDL_FALSE) this->xP = temp;
							}
						}
					}
				}
            }
        }
#ifdef _WIN32
        else if (event.type == SDL_KEYDOWN) {
		    switch (event.key.keysym.sym)  {
        		case SDLK_LEFT:
					temp = xP - 1;
					if (this->isCollision(temp, this->yP, shapes[this->currentPiece-1][this->currentPosition ]) == SDL_FALSE) this->xP = temp;
				break;
        		case SDLK_RIGHT:
        			temp = xP + 1;
					if (this->isCollision(temp, this->yP, shapes[this->currentPiece-1][this->currentPosition ]) == SDL_FALSE) this->xP = temp;
				break;
        		case SDLK_UP:
        			temp = this->currentPosition + 1;
					if (temp > 3) temp = 0;
					if (this->isCollision(this->xP, this->yP, shapes[this->currentPiece-1][temp]) == SDL_FALSE) this->currentPosition = temp;
				break;
        		case SDLK_DOWN:
					if (this->isCollision(this->xP, this->yP+1, shapes[this->currentPiece-1][this->currentPosition]) == SDL_TRUE) {
						for (int i = 0; i < 4; i++)
							for (int j = 0; j < 4; j++)
								if (shapes[this->currentPiece-1][this->currentPosition][i+j*4] != 0)
									this->cells[this->xP+i][this->yP+j].setValue(8);
						isShape = SDL_FALSE;
					} else {
						this->yP++;
					}
				break;
    		}
    	}
#endif
    }
    // -- Check if it is time to move down
    if ((SDL_GetTicks() - this->ttime) > this->speed) {
        if (this->isCollision(this->xP, this->yP+1, shapes[this->currentPiece-1][this->currentPosition]) == SDL_TRUE) {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (shapes[this->currentPiece-1][this->currentPosition][i+j*4] != 0)
                        this->cells[this->xP+i][this->yP+j].setValue(8);
            isShape = SDL_FALSE;
        } else {
            this->yP++;
        }
        this->ttime = SDL_GetTicks();
    }
    // -- Draw current status of the table
    // Clear Table
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 20; j++)
            if ((this->cells[i][j].getValue() < 8) && (this->cells[i][j].getValue() > 0))
                this->cells[i][j].setValue(0);
    // plot Piece
    if (isShape == SDL_TRUE)
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (shapes[this->currentPiece-1][this->currentPosition][i+j*4] != 0)
                    this->cells[this->xP+i][this->yP+j].setValue(shapes[this->currentPiece-1][this->currentPosition][i+j*4]);
    this->drawTable(screen);
    return retorno;
}

int main(int argc, char *argv[]) {
    Mix_Music * music = NULL;
    SDL_Renderer * screen = NULL;
    SDL_Window * window = NULL;
    TTF_Font * font_30pp = NULL, * font_20pp = NULL, * font_16pp = NULL, * font_12pp = NULL;
	SDL_Texture * soundIconSheet = NULL;
    SDL_DisplayMode displayMode;
    SDL_Event event;
    SDL_bool exit = SDL_FALSE, isMusic = SDL_TRUE;
	SDL_Rect srcrect, dstrect;
    std::string texto;
    int points, level;
    int clock, time;
    int width, height;
    int x, y;
    Table * table = NULL;
    //Initialize SDL
    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
        SDL_Log("SDL could not initialize! SDL Error: %s\r\n", SDL_GetError());
    } else {
#ifndef _WIN32
        if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG) {
            SDL_Log("SDL Mixer could not initialize! Mix Error: %s\r\n", Mix_GetError());
        } else {
#endif
            // Initialize PNG loading
            if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
                SDL_Log("SDL_image could not initialize! %s\r\n", IMG_GetError());
            } else {
                //Initialize SDL_ttf
                if (TTF_Init() < 0) {
                    SDL_Log("TTF could not initialize! TTF Error: %s\r\n", TTF_GetError());
                } else {
                    //Initialize SDL_mixer
                    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0) {
                        SDL_Log("MIX could not initialize! MIX Error: %s\r\n", Mix_GetError());
                    } else {
                        //Get device display mode
#ifdef _WIN32
                        width = SCREEN_WIDTH;
						height = SCREEN_HEIGHT;
#else
                        if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
                            width  = displayMode.w;
                            height = displayMode.h;
                        } else {
                            width = SCREEN_WIDTH;
                            height = SCREEN_HEIGHT;
                        }
#endif
                        // Create window
                        window = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
                        if (window == NULL) {
                            SDL_Log("Window could not be created! SDL Error: %s\r\n", SDL_GetError());
                        } else {
                            //Create renderer for window
                            screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                            if (screen == NULL) {
                                SDL_Log("Renderer could not be created! SDL Error: %s\r\n", SDL_GetError());
                            } else {
								soundIconSheet = helper::loadSpriteSheet(screen, "mute.png", IMG_DIR);
								if (soundIconSheet == NULL ) {
                                    SDL_Log("Icon sheet not loaded!\r\n");
                                } else {									
									font_30pp = helper::load_text_font("tetris_block.ttf", FNT_DIR, (width / 30));
									font_12pp = helper::load_text_font("tetris_block.ttf", FNT_DIR, (width / 12));								
									font_20pp = helper::load_text_font("tetris_block.ttf", FNT_DIR, (width / 20));								
									font_16pp = helper::load_text_font("tetris_block.ttf", FNT_DIR, (width / 16));								
									if (font_30pp == NULL ) {
										SDL_Log("Font not loaded!\r\n");
									} else {
										level = 0;
										points = 0;
										music = helper::load_sound("tetris_theme.ogg", SND_DIR);
										if (music != NULL) Mix_PlayMusic(music, -1);
										exit = SDL_FALSE;
										while (exit == SDL_FALSE) {
											SDL_RenderClear(screen);
											SDL_SetRenderDrawColor(screen, 0, 0, 0, 0xFF);
											helper::drawTextCentered(font_12pp, "TETRIS", GOLDEN, 0, 0, width, height / 2, screen);
											helper::drawTextCentered(font_20pp, "start", ORANGE, 0, height / 4, width, height / 2, screen);
											if (isMusic == SDL_TRUE)
												helper::drawTextCentered(font_20pp, "sound off", ORANGE, 0, height / 2, width, height / 4, screen);
											else
												helper::drawTextCentered(font_20pp, "sound on", ORANGE, 0, height / 2, width, height / 4, screen);
											helper::drawTextCentered(font_20pp, "exit", ORANGE, 0, height * 10 / 16, width, height / 4, screen);											
											SDL_RenderPresent(screen);
											while (SDL_PollEvent(&event) != 0) {
												if ((event.type == SDL_FINGERUP) || (event.type == SDL_MOUSEBUTTONUP)) {
#ifdef _WIN32
													x = event.button.x;
													y = event.button.y;
#else
													x = (event.tfinger.x * width);
													y = (event.tfinger.y * height);
	#endif
													if ((x > 0) && (x < width) && (y > 0) && (y < height)) { // If X and Y coordinates are OK
														if ((y > (height * 7 / 16)) && (y < (height * 9 / 16))) {
															// Creamos los objetos del juego
															table = new Table(width, height);
															if (table != NULL) {
																exit = SDL_FALSE;
																clock = SDL_GetTicks();
																SDL_Rect leftRect 	= {.x = 0, .y = (int)(height * 3 / 8), .w = (int)(width / 2), .h = (int)((height * 7 / 8) - (height * 3 / 8))},
																		 rightRect 	= {.x = (int)(width / 2), .y =  (int)(height * 3 / 8), .w = (int)(width / 2), .h = (int)((height * 7 / 8) - (height * 3 / 8))},
																		 upRect 	= {.x = 0, .y = 0, .w = width, .h = (int)(height * 3 / 8)},
																		 downRect 	= {.x = 0, .y = (int)(height * 7 / 8), .w = width, .h = (int)(height / 8)};
																SDL_SetRenderDrawBlendMode(screen, SDL_BLENDMODE_BLEND); // To allow alpha blending
																dstrect.x = width * 9 / 10;
																dstrect.y = 0;
																dstrect.w = width/10;
																dstrect.h = width/10;
																while (exit == SDL_FALSE) {
																	SDL_RenderClear(screen);
																	if (isMusic == SDL_TRUE)
																		srcrect = SOUND_OFF;
																	else
																		srcrect = SOUND_ON;
																	SDL_SetRenderDrawColor(screen, RED.r, RED.g, RED.b, 32);
																	SDL_RenderFillRect(screen, & leftRect);
																	SDL_SetRenderDrawColor(screen, GREEN.r, GREEN.g, GREEN.b, 32);
																	SDL_RenderFillRect(screen, & rightRect);
																	SDL_SetRenderDrawColor(screen, BLUE.r, BLUE.g, BLUE.b, 32);
																	SDL_RenderFillRect(screen, & upRect);
																	SDL_SetRenderDrawColor(screen, YELLOW.r, YELLOW.g, YELLOW.b, 32);
																	SDL_RenderFillRect(screen, & downRect);
																	exit = table->play(screen, event, &points, &level, &isMusic);
																	texto = "Pts: "+helper::int2string(points);
																	helper::drawTextCentered(font_30pp, texto.c_str(), GOLDEN, 0, 0, width / 2, width / 10, screen);
																	texto = "Lvl: "+helper::int2string(level);
																	helper::drawTextCentered(font_30pp, texto.c_str(), GOLDEN, width / 2, 0, width / 2, width / 10, screen);
																	SDL_RenderCopy(screen, soundIconSheet, &srcrect, &dstrect);
																	SDL_RenderPresent(screen);
																	SDL_SetRenderDrawColor(screen, 0, 0, 0, 0xFF);
																	time = SDL_GetTicks();
																	if (time - clock < 60) {
																		SDL_Delay(60 - (time - clock));
																		clock = SDL_GetTicks();
																	}
																	if (level == 11) exit = SDL_TRUE;
																}
																SDL_RenderClear(screen);
																SDL_SetRenderDrawColor(screen, 0, 0, 0, 0xFF);

																if (level == 11)
																	helper::drawTextCentered(font_16pp, "YOU WIN", GREEN, 0, 0, width, height, screen);
																else
																	helper::drawTextCentered(font_16pp, "YOU LOSE", RED, 0, 0, width, height, screen);
																SDL_RenderPresent(screen);
#ifndef _WIN32
																helper::doVibrateFromJNI(1000);
#endif
																exit = SDL_FALSE;								
																SDL_Delay(1000);
																delete(table);
															} else 
																exit = SDL_TRUE;
														} else
														if ((y > (height * 9 / 16)) && (y < (height * 11 / 16))) {
															if (isMusic == SDL_TRUE) {
																isMusic = SDL_FALSE;
																Mix_PauseMusic();
															} else {
																isMusic = SDL_TRUE;
																Mix_ResumeMusic();
															}
														} else
														if ((y > (height * 11 / 16)) && (y < (height * 13 / 16))) {
															exit = SDL_TRUE;
														}
													}
												}
    	    	                    		}
	            	               		}
	            	               	}
                                }
                            }
                        }
                    }
                }
            }
#ifndef _WIN32
        }
#endif
    }

	if (soundIconSheet != NULL) SDL_DestroyTexture(soundIconSheet); 

    if (font_12pp != NULL) TTF_CloseFont(font_12pp);
	if (font_16pp != NULL) TTF_CloseFont(font_16pp);
	if (font_20pp != NULL) TTF_CloseFont(font_20pp);
	if (font_30pp != NULL) TTF_CloseFont(font_30pp);

    if (screen != NULL) SDL_DestroyRenderer(screen);
    if (window != NULL) SDL_DestroyWindow(window);
    if (music != NULL) 	Mix_FreeMusic(music);

    Mix_CloseAudio();	// Quit SDL_mixer
    TTF_Quit();    		// Quit SDL_ttf
    IMG_Quit();			// Quit SDL_image
    SDL_Quit();			// Quit SDL

    return 0;
}


