//Using SDL and standard IO
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "../emoticons.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;


int main(int argc, char** argv){
    // Variables
    SDL_Window* window = NULL;          // The SDL window 
    SDL_Surface* screenSurface = NULL;  // The surface contained by the window
    char quit = 0;                      // Main loop flag
    SDL_Event evt;                      // Event handler
    SDL_Renderer* renderer;             // Renderer
    TTF_Font*     font;                  // Font used    
    
    
    // ---------------------------------------------
    // START OF PROGRAM
    // ---------------------------------------------    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(100);
    }
    if( TTF_Init() < 0 ){
        printf( "TTF could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(101);
    }
    // Open font file	
    font = TTF_OpenFont("./fonts/NotoColorEmoji.ttf", 20); // OpenSansEmoji.ttf // DejaVuSansMono.ttf 
    if( font == NULL ){
        printf("Impossible to open the font file : %s\n", TTF_GetError()); 
        exit(102);
    }
    //Create window
    if( SDL_CreateWindowAndRenderer( SCREEN_WIDTH,
                                     SCREEN_HEIGHT,
                                     SDL_WINDOW_SHOWN,
                                     &window,
                                     &renderer ) < 0){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    // Set title
    SDL_SetWindowTitle(window, "CY-mon : cod'em ALL !");
    //Get window surface
    screenSurface = SDL_GetWindowSurface( window );


    // ---------------------------------------------
    // GAME LOOP
    // ---------------------------------------------
    //While application is running
    while( !quit ){
        // - - - - - - - - - - - - - - - - - -
        //Handle EVENTS on queue
        // - - - - - - - - - - - - - - - - - -
        // evt.type is UInt32
        // evt.key.keysym.sym is sInt32
        while( SDL_PollEvent( &evt ) != 0 ){
            // User requests quit
            if( evt.type == SDL_QUIT ){
                quit = 1;
            }
            // User released a key
            if( evt.type == SDL_KEYUP){
                printf("KEY %d has been RELEASED \n", evt.key.keysym.sym); 
                switch( evt.key.keysym.sym ){
                    // The escape key has been released : ask to quit
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    default :
                        break;
                }
                // TODO : send event to the user 
            }
            // User pressed a key
            if( evt.type == SDL_KEYDOWN){
                // Check if this is a first press or a repeat
                if( evt.key.repeat ){
                    printf("KEY %d is being REPEATED \n", evt.key.keysym.sym); 
                }
                else{
                    printf("KEY %d has been PRESSED \n", evt.key.keysym.sym);
                    // TODO : send event to the user
                }
            }
        }
        
        // - - - - - - - - - - - - - - - - - -
        // UPDATE data model
        // - - - - - - - - - - - - - - - - - -


        // - - - - - - - - - - - - - - - - - -
        // DRAW items from data model         
        // - - - - - - - - - - - - - - - - - -
        // Fill the surface BLACK
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw a 10x10 grid, with 32x32 cells
        // Prepare a text (use tmp memory for surface and texture)
        SDL_Color    color   = { 0, 0, 0 };
        SDL_Surface* fntSurf;
	    SDL_Texture* fntText;;
        for(int i=0;i<10;i++){
            for(int j=0;j<20;j++){
                SDL_Rect rect;
                rect.x = 64*j;
                rect.y = 64*i;
                rect.w = 64;
                rect.h = 64;
                SDL_SetRenderDrawColor(renderer, (255*i)/10, (255*j)/20, 128, 255);
                // Render background
                SDL_RenderFillRect(renderer, &rect);
                // Render text
                fntSurf = TTF_RenderUTF8_Blended(font, EMOT_BEE, color); //"😄"
                fntText = SDL_CreateTextureFromSurface(renderer, fntSurf);
                SDL_RenderCopy(renderer, fntText, NULL, &rect);
            }
        }
        // Remove font tmp memory
        SDL_DestroyTexture(fntText);
        SDL_FreeSurface   (fntSurf);



        // Update the surface
        SDL_RenderPresent(renderer);

        // - - - - - - - - - - - - - - - - - -
        // Wait for FPS
        // - - - - - - - - - - - - - - - - - -
        SDL_Delay( 17 );
    }
    

    // ---------------------------------------------
    // END OF PROGRAM
    // ---------------------------------------------
    // Release font	
    TTF_CloseFont(font);
    //Destroy window
    SDL_DestroyWindow( window );
    //Quit TTF
    TTF_Quit();
    //Quit SDL subsystems
    SDL_Quit();
    // Return error code
    return 0;
}

