#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

//The window renderer
extern SDL_Renderer* gRenderer = NULL;

//The window we'll be rendering to
extern SDL_Window* gWindow = NULL;

//Globally used font
extern TTF_Font *gFont = NULL;

const bool DBG_SHOW_FPS = false;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

const int BUTTON_SPRITE_NUM = 4;
const int BUTTON_SS_ROWS = 2;
const int BUTTON_SS_COLUMNS = 2;

const int BUTTON_HEIGHT = 100;
const int BUTTON_WIDTH = 100;

const int PADDLE_HEIGHT = 60;
const int PADDLE_WIDTH = 8;

const int BALL_WIDTH = 8;
const int BALL_HEIGHT = 8;

const int MAX_SPEED = 15;

const int POINTS_TO_WIN = 15;

const int MAJOR_REV = 0;
const int MINOR_REV = 9;
const int INCREMENTAL_REV = 0;

enum direction
{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
    NORTHEAST = 4,
    SOUTHEAST = 5,
    SOUTHWEST = 6,
    NORTHWEST = 7
};

typedef struct _Direction_Vector{
  int yDif, xDif;
} DirectionVector;

typedef struct _Velocity_Vector{
  int yVel, xVel;
} VelocityVector;

DirectionVector DIRECTIONS[] = {
    {-1,0},
    {0,1},
    {1,0},
    {0,-1},
    {-1,1},
    {1,1},
    {1,-1},
    {-1,-1}
};

//Game states
enum GameStates
{
    STATE_NULL,
    STATE_MENU,
    STATE_GAME_EASY,
    STATE_GAME_MED,
    STATE_GAME_HARD,
    STATE_EXIT
};

#endif // CONST_H_INCLUDED
