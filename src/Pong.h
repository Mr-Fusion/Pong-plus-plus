#ifndef PONG_H_INCLUDED
#define PONG_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <sstream>
#include "Const.h"
//#include "Grid.h"
#include "GameState.h"
//#include "Button.h"
#include "LTimer.h"
#include "LTexture.h"

class Pong : public GameState
{
    public:

    SDL_Rect paddle;
    SDL_Rect ball;

    VelocityVector bVel;

    int countedFrames;

    SDL_Color textColor;


    ///Constructor Function
    Pong(){

        paddle.x = 12;
        paddle.y = 0;
        paddle.w = PADDLE_WIDTH;
        paddle.h = PADDLE_HEIGHT;

        ball.x = SCREEN_WIDTH/2;
        ball.y = SCREEN_HEIGHT/2;
        ball.w = 6;
        ball.h = 6;

        bVel.xVel = 0;
        bVel.yVel = 0;


        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Initialize playing field dimensions, difficulty, and appearance

            newGame();

            //Initialize and display graphical interface
            SDL_SetWindowSize(gWindow,SCREEN_WIDTH,SCREEN_HEIGHT);
        }

    }

    ///Deconstructor
    ~Pong(){
        printf("Gamestate Object Deconstructing...\n");

        //Free loaded image


    }

    void newGame()
    {

        bVel.xVel = 5;
        bVel.yVel = 1;
    }

    //TODO: Can we streamline the sprite sheet creationg into a function?
    bool loadMedia()
    {
        //Loading success flag
        bool success = true;


        return success;
    }


    ///Routine for winning the game
    void victory(void){
    }

    ///Handles mouse event
    void handleEvent( SDL_Event* e){

        int x, y;

        //Get mouse position
        if( e->type == SDL_MOUSEMOTION ){
            SDL_GetMouseState( &x, &y );
            //paddle.x = x;
        paddle.y = y - (paddle.h/2);
            if ( y > SCREEN_HEIGHT - paddle.h/2 )
                paddle.y = SCREEN_HEIGHT - paddle.h;
            if ( y < paddle.h/2 )
                paddle.y = 0;
        }


        if( e->button.button == SDL_BUTTON_RIGHT && e->type == SDL_MOUSEBUTTONUP ){
            set_next_state(STATE_MENU);
        }
    }

    void logic(){

        ball.x += bVel.xVel;
        ball.y += bVel.yVel;


        if (ball.y > SCREEN_HEIGHT - ball.h)
            bVel.yVel *= -1;
        if (ball.x > SCREEN_WIDTH - ball.w)
            bVel.xVel *= -1;
        if (ball.y < 0)
            bVel.yVel *= -1;

        if (ball.x + bVel.xVel < paddle.x + PADDLE_WIDTH){
            if (ball.x > paddle.x){
                if (ball.y > paddle.y){
                    if (ball.y < paddle.y + PADDLE_HEIGHT){
                        bVel.xVel *= -1;
                        if (bVel.xVel < MAX_SPEED)
                            bVel.xVel += 1;
                        bVel.yVel = (ball.y - (paddle.y + paddle.h/2 ) ) /3;
                    }
                }
            }
        }
        if (ball.x < -10) {
            bVel.xVel *= -1;
            ball.x = SCREEN_WIDTH/2;
            ball.y = SCREEN_HEIGHT/2;
        }


    }

    void render(){


        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderFillRect(gRenderer, &paddle);
        SDL_RenderFillRect(gRenderer, &ball);

    }

};

#endif // PONG_H_INCLUDED