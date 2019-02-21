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

    SDL_Rect lPaddle;
    SDL_Rect rPaddle;
    SDL_Rect field;

    int lScore;
    int rScore;

    bool lGoal;
    bool rGoal;
    bool newGame;
    bool victory;

    SDL_Rect ball;

    VelocityVector bVel;
    VelocityVector pVel;

    SDL_Color textColor;

    // Background color
    int bgR, bgG, bgB;

    // Sprite color
    int spR, spG, spB;

    //In memory text stream
    std::stringstream lScoreText;
    std::stringstream rScoreText;
    std::stringstream msgText;

    //Scene textures
    LTexture lScoreTextTexture;
    LTexture rScoreTextTexture;
    LTexture msgTextTexture;

    LTimer delayTimer;

    //The sound effects that will be used
    Mix_Chunk *gHigh = NULL;
    Mix_Chunk *gLow = NULL;

    ///Constructor Function
    Pong(){

        lPaddle.x = 12;
        lPaddle.y = SCREEN_HEIGHT/2;
        lPaddle.w = PADDLE_WIDTH;
        lPaddle.h = PADDLE_HEIGHT;

        rPaddle.x = SCREEN_WIDTH - 12 - PADDLE_WIDTH;
        rPaddle.y = SCREEN_HEIGHT/2;
        rPaddle.w = PADDLE_WIDTH;
        rPaddle.h = PADDLE_HEIGHT;

        ball.x = SCREEN_WIDTH/2;
        ball.y = SCREEN_HEIGHT/2;
        ball.w = BALL_WIDTH;
        ball.h = BALL_HEIGHT;

        field.x = 0;
        field.y = 0;
        field.w = SCREEN_WIDTH;
        field.h = SCREEN_HEIGHT;

        bVel.xVel = 0;
        bVel.yVel = 0;

        pVel.xVel = 0;
        pVel.yVel = 0;

        lScore = 0;
        rScore = 0;

        lGoal = false;
        rGoal = false;
        victory = false;

        bgR = bgG = bgB = 0x00;

        spR = spG = spB = 0xFF;

        textColor = { spR, spG, spB, 0xFF};

        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Initialize playing field dimensions, difficulty, and appearance

            startGame();

            //Initialize and display graphical interface
            SDL_SetWindowSize(gWindow,SCREEN_WIDTH,SCREEN_HEIGHT);
        }

    }

    ///Deconstructor
    ~Pong(){
        printf("Gamestate Object Deconstructing...\n");

        //Free loaded image

        //Free the sound effects
        Mix_FreeChunk( gLow );
        gLow = NULL;
        Mix_FreeChunk( gHigh );
        gHigh = NULL;

        rScoreTextTexture.free();
        lScoreTextTexture.free();
        msgTextTexture.free();

    }

    void startGame()
    {

        ball.x = SCREEN_WIDTH/2;
        ball.y = SCREEN_HEIGHT/2;

        //Set text to be rendered
        msgText.str( "" );
        msgText << "" << POINTS_TO_WIN << " Points to Win!";

        //Render text
        if( !msgTextTexture.loadFromRenderedText( msgText.str().c_str(), textColor ) )
        {
            printf( "Unable to render Left Score texture!\n" );
        }

        delayTimer.start();

        newGame = true;

    }

    //TODO: Can we streamline the sprite sheet creationg into a function?
    bool loadMedia()
    {
        //Loading success flag
        bool success = true;

        //Load sound effects
        gLow = Mix_LoadWAV( "../assets/sfx_sounds_Blip7.wav" );
        if( gLow == NULL )
        {
            printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        gHigh = Mix_LoadWAV( "../assets/sfx_sounds_Blip9.wav" );
        if( gHigh == NULL )
        {
            printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        //Set text to be rendered
        rScoreText.str( "" );
        rScoreText << "" << rScore;

        //Render text
        if( !rScoreTextTexture.loadFromRenderedText( rScoreText.str().c_str(), textColor ) )
        {
            printf( "Unable to render Right Score texture!\n" );
        }

        //Set text to be rendered
        lScoreText.str( "" );
        lScoreText << "" << lScore;

        //Render text
        if( !lScoreTextTexture.loadFromRenderedText( lScoreText.str().c_str(), textColor ) )
        {
            printf( "Unable to render Left Score texture!\n" );
        }

        //Set text to be rendered
        msgText.str( "" );
        msgText << "" << POINTS_TO_WIN << " Points to Win!";

        //Render text
        if( !msgTextTexture.loadFromRenderedText( msgText.str().c_str(), textColor ) )
        {
            printf( "Unable to render Left Score texture!\n" );
        }


        return success;
    }

    void setMessage(char* text){
        //Set text to be rendered
        msgText.str( "" );
        msgText << text;

        //Render text
        if( !msgTextTexture.loadFromRenderedText( msgText.str().c_str(), textColor ) )
        {
            printf( "Unable to render Left Score texture!\n" );
        }

    }


    ///Routine for winning the game
    void gameOver(){
        lGoal = false;
        rGoal = false;
        delayTimer.stop();

        if (victory)
            setMessage("You Win!");
        else 
            setMessage("You Lose...");
    }

    ///Handles mouse event
    void handleEvent( SDL_Event* e){

        int x, y;

        //Get mouse position
        if( e->type == SDL_MOUSEMOTION ){
            SDL_GetMouseState( &x, &y );
            //lPaddle.x = x;
        lPaddle.y = y - (lPaddle.h/2);
            if ( y > SCREEN_HEIGHT - lPaddle.h/2 )
                lPaddle.y = SCREEN_HEIGHT - lPaddle.h;
            if ( y < lPaddle.h/2 )
                lPaddle.y = 0;
        }


        if( e->button.button == SDL_BUTTON_RIGHT && e->type == SDL_MOUSEBUTTONUP ){
            set_next_state(STATE_MENU);
        }
    }

    void logic(){

        ball.x += bVel.xVel;
        ball.y += bVel.yVel;


        if (ball.y + bVel.yVel > SCREEN_HEIGHT - ball.h){
            bVel.yVel *= -1;
            Mix_PlayChannel( -1, gLow, 0 );
        }
        //if (ball.x > SCREEN_WIDTH - ball.w)
            //bVel.xVel *= -1;
        if (ball.y < 0){
            bVel.yVel *= -1;
            Mix_PlayChannel( -1, gLow, 0 );
        }

        //Left Paddle
        if (ball.x + bVel.xVel < lPaddle.x + PADDLE_WIDTH){
            if (ball.x > lPaddle.x ){
                if (ball.y + ball.h > lPaddle.y){
                    if (ball.y < lPaddle.y + PADDLE_HEIGHT){
                        bVel.xVel *= -1;
                        if (bVel.xVel < MAX_SPEED)
                            bVel.xVel += 1;
                        bVel.yVel = (ball.y - (lPaddle.y + lPaddle.h/2 ) ) /3;
                        Mix_PlayChannel( -1, gHigh, 0 );
                    }
                }
            }
        }
        if ( (ball.x < -20) && (!rGoal) ){

            rGoal = true;
            rScore++;

            ball.x = -10;
            bVel.yVel = 0;
            bVel.xVel = 0;

            delayTimer.start();
            //INSERT SCORE SOUND EFFECT HERE

            //Set text to be rendered
            rScoreText.str( "" );
            rScoreText << "" << rScore;

            //Render text
            if( !rScoreTextTexture.loadFromRenderedText( rScoreText.str().c_str(), textColor ) )
            {
                printf( "Unable to render Right Score texture!\n" );
            }  
        }

        //Right Paddle
        if (ball.x + bVel.xVel > rPaddle.x){
            if (ball.x < rPaddle.x + PADDLE_WIDTH){
                if (ball.y + ball.h > rPaddle.y){
                    if (ball.y < rPaddle.y + PADDLE_HEIGHT){
                        if (bVel.xVel < MAX_SPEED)
                            bVel.xVel += 1;
                        bVel.xVel *= -1;
                        bVel.yVel = (ball.y - (rPaddle.y + rPaddle.h/2 ) ) /3;
                        Mix_PlayChannel( -1, gHigh, 0 );
                    }
                }
            }
        }
        if ( (ball.x > SCREEN_WIDTH + 20) && (!lGoal) ) {
            ball.x = SCREEN_WIDTH+10;

            lGoal = true;
            lScore++;
            bVel.yVel = 0;
            bVel.xVel = 0;

            delayTimer.start();

            //Set text to be rendered
            lScoreText.str( "" );
            lScoreText << "" << lScore;

            //Render text
            if( !lScoreTextTexture.loadFromRenderedText( lScoreText.str().c_str(), textColor ) )
            {
                printf( "Unable to render Left Score texture!\n" );
            }
        }

        //Right Paddle AI
        // NOTES: Velocity 8-9 is a good challenge. Nearly impossible to score until the ball gains x velocity,
        // and even then, scoring against the AI requires a sharp bank shot

        // 10 is technically possibly, but requires nearly perfect play

        // Need to determine what the easiest difficulty should be. 5 is a good candidate

        // 3 is piss easy. Babby mode. Doesn't even look like the paddle is trying

        rPaddle.y += pVel.yVel;

        if (rPaddle.y < 0)
            rPaddle.y = 0;
        if (rPaddle.y > SCREEN_HEIGHT - PADDLE_HEIGHT)
            rPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;

        if (ball.y < rPaddle.y + PADDLE_HEIGHT/4)
            pVel.yVel = -6;
        else if (ball.y > rPaddle.y + PADDLE_HEIGHT * 3/4)
            pVel.yVel = 6;
        else
            pVel.yVel = 0;

        //Reset Serve after scoring
        if (lGoal){
            if (delayTimer.getTicks() > 2000){
                bVel.xVel = -5;
                bVel.yVel = rand() % 10 - 5;
                ball.x = SCREEN_WIDTH/2;
                ball.y = SCREEN_HEIGHT/2;
                delayTimer.stop();
                lGoal = false;
            }
        }
        if (rGoal){
            if (delayTimer.getTicks() > 2000){
                bVel.xVel = 5;
                bVel.yVel = rand() % 10 - 5;
                ball.x = SCREEN_WIDTH/2;
                ball.y = SCREEN_HEIGHT/2;
                delayTimer.stop();
                rGoal = false;
            }
        }

        if (newGame){
            if (delayTimer.getTicks() > 3000){
                bVel.xVel = 5;
                bVel.yVel = 1;

                lScore = 0;
                rScore = 0;

                lGoal = false;
                rGoal = false;

                setMessage("");

                newGame = false;
            }
        }

        if (lScore == POINTS_TO_WIN) {
            victory = true;
            gameOver();
        }
        if (rScore == POINTS_TO_WIN) {
            gameOver();
        }

        //spR = ball.y % 256;
        //spG = lPaddle.y % 256;
        //spB = rPaddle.y % 256;
        //bgR = 0x80;

    }

    void render(){


        //SDL_SetRenderDrawColor( gRenderer, ball.x % 256, ball.y % 256, 0xFF , 0xFF );
        SDL_SetRenderDrawColor( gRenderer, bgR, bgG, bgB, 0xFF );
        SDL_RenderFillRect(gRenderer, &field);
        SDL_SetRenderDrawColor( gRenderer, spR, spG, spB, 0xFF );
        //SDL_SetRenderDrawColor( gRenderer, rPaddle.y % 256, ball.y % 256, lPaddle.y % 256, 0xFF );
        //SDL_SetRenderDrawColor( gRenderer, ball.x % 256, ball.y % 256, 0xFF , 0xFF );
        SDL_RenderFillRect(gRenderer, &lPaddle);
        SDL_RenderFillRect(gRenderer, &rPaddle);
        SDL_RenderFillRect(gRenderer, &ball);
        lScoreTextTexture.render( PADDLE_WIDTH * 10, lScoreTextTexture.getHeight() / 2 );
        rScoreTextTexture.render( SCREEN_WIDTH - rScoreTextTexture.getWidth() - (PADDLE_WIDTH * 10), rScoreTextTexture.getHeight() / 2 );
        msgTextTexture.render(SCREEN_WIDTH/2 - msgTextTexture.getWidth()/2, msgTextTexture.getHeight() / 2 );
    }

};

#endif // PONG_H_INCLUDED