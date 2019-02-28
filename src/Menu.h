#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdlib.h>
#include "Button.h"

class Menu : public GameState
{
    public:

    
    //LButton eButton;    
    LButton mButton;
    //LButton hButton;

    LTexture ButtonSpriteSheet;

    LTexture titleText;
    LTexture eText;
    LTexture mText;
    LTexture hText;
    LTexture creditText;

    LTexture cautionBackdrop;
    LTexture menuPlate;

    SDL_Rect ButtonSpriteClips[ BUTTON_SPRITE_NUM ];

    SDL_Rect paddle;

    ///Constructor Function
    Menu(){

        paddle.x = 12;
        paddle.y = 0;
        paddle.w = PADDLE_WIDTH;
        paddle.h = PADDLE_HEIGHT;

        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
        	//Initialize Menu here
            //eButton = LButton(SCREEN_WIDTH/4 - BUTTON_WIDTH/2, 200, BUTTON_WIDTH, BUTTON_HEIGHT);
        	mButton = LButton(0, SCREEN_HEIGHT/2, SCREEN_WIDTH, mText.getHeight() );
            //hButton = LButton(SCREEN_WIDTH*3/4 - BUTTON_WIDTH/2, 200, BUTTON_WIDTH, BUTTON_HEIGHT);

        	SDL_SetWindowSize(gWindow,SCREEN_WIDTH, SCREEN_HEIGHT);
        }

    }

    ///Deconstructor
    ~Menu(){
        printf("Menu Object Deconstructing...\n");

		//Destroy Menu assets here

        //Free loaded image
        ButtonSpriteSheet.free();
        titleText.free();
        eText.free();
        mText.free();
        hText.free();
        creditText.free();
        cautionBackdrop.free();
        menuPlate.free();

    }

    bool loadMedia()
    {
        //Loading success flag
        bool success = true;

        //Load sprite sheet texture



        //Open the font
        gFont = TTF_OpenFont( "../assets/SAMSRG__.TTF", 60 );
        if( gFont == NULL )
        {
            printf( "Failed to load Pong Title font! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
        else
        {
            //Render text
            SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
            if( !titleText.loadFromRenderedText( "PONG", textColor ) )
            {
                printf( "Failed to render title text!\n" );
                success = false;
            }
        }

        gFont = TTF_OpenFont( "../assets/PressStart2P.ttf", 14 );
        if( gFont == NULL )
        {
            printf( "Failed to load Minesweeper font! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
        else
        {
            //Render text
            SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
            if( !creditText.loadFromRenderedText( "By Joel Turner | Version: 1.0.0", textColor ) )
            {
                printf( "Failed to render credit text!\n" );
                success = false;
            }
        }

        gFont = TTF_OpenFont( "../assets/SAMST___.TTF", 40 );
        if( gFont == NULL )
        {
            printf( "Failed to load Pong font! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
        else
        {
            //Render text
            SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
            if( !eText.loadFromRenderedText( "Easy", textColor ) )
            {
                printf( "Failed to render eText!\n" );
                success = false;
            }
            if( !mText.loadFromRenderedText( "BEGIN", textColor ) )
            {
                printf( "Failed to render mText!\n" );
                success = false;
            }
            if( !hText.loadFromRenderedText( "Hard", textColor ) )
            {
                printf( "Failed to render hText!\n" );
                success = false;
            }
        }
        return success;
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

        //Handle button events first
        //eButton.handleEvent(e);
        mButton.handleEvent(e);
       // hButton.handleEvent(e);

        //if (eButton.isClicked)
            //set_next_state(STATE_GAME_EASY);

        if (mButton.isClicked)
            set_next_state(STATE_GAME_MED);

        //if (hButton.isClicked)
            //set_next_state(STATE_GAME_HARD);
    }

    void logic(){

        if (mButton.inside){
            SDL_Color textColor = { 0xFF, 0x00, 0x00, 0x00 };
            if( !mText.loadFromRenderedText( "BEGIN", textColor ) )
            {
                printf( "Failed to render mText!\n" );
            }
        }
        else {
            SDL_Color textColor = { 0x0FF, 0xFF, 0xFF, 0xFF };
            if( !mText.loadFromRenderedText( "BEGIN", textColor ) )
            {
                printf( "Failed to render mText!\n" );
            }
        }
    	//eButton.logic();
        mButton.logic();
        //hButton.logic();


    }

    void render(){

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderFillRect(gRenderer, &paddle);
    	//cautionBackdrop.render(0,0);
    	//menuPlate.render(32,32);
        //eButton.render(ButtonSpriteClips, &ButtonSpriteSheet);
        //mButton.render(ButtonSpriteClips, &ButtonSpriteSheet);
        //hButton.render(ButtonSpriteClips, &ButtonSpriteSheet);
        titleText.render(SCREEN_WIDTH/2 - titleText.getWidth()/2, 30);
        //eText.render(SCREEN_WIDTH/4 - BUTTON_WIDTH/2 + eButton.mDimension.w/2 - eText.getWidth()/2, 200 + BUTTON_HEIGHT + 10);
        mText.render(SCREEN_WIDTH/2 - mText.getWidth()/2, SCREEN_HEIGHT/2);
        //hText.render(SCREEN_WIDTH*3/4 - BUTTON_WIDTH/2 + hButton.mDimension.w/2 - hText.getWidth()/2, 200 + BUTTON_HEIGHT + 10);
        creditText.render(SCREEN_WIDTH/2 - creditText.getWidth()/2, SCREEN_HEIGHT - 60);
    }

};

#endif // MENU_H_INCLUDED