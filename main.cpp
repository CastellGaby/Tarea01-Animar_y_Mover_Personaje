#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *Backgrnd = NULL;
SDL_Surface *screen = NULL;
SDL_Event *event;

SDL_Surface *load_image( std::string filename )
{
    return IMG_Load(filename.c_str());
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Rectangle to hold the offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Tarea 01-Gabriela Castellanos", NULL );

    //If everything initialized fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface( Backgrnd );

    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    int x=50;
    int y=270;
    int pss=0;
    bool cont = true;
    //Initialize
    if( init() == false )
    {
        return 1;
    }

    SDL_Surface* Personita[4];
    Backgrnd = load_image("backgrounds.png");
    Personita[0]=load_image( "Personita/Personita01.png" );
    Personita[1]=load_image( "Personita/Personita02.png" );
    Personita[2]=load_image( "Personita/Personita03.png" );
    Personita[3]=load_image( "Personita/Personita04.png" );

    while(cont){

        if(pss>3){
            pss=0;
        }
        //If there was a problem in loading the image
        if( Personita == NULL )
        {
            return 1;
        }

        SDL_Event event;
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
//                quit = true;
                cont = false;
            }
        }

        Uint8 *keystates = SDL_GetKeyState( NULL );

        if(keystates[SDLK_RIGHT]){
            x += 10;
        }

        if(keystates[SDLK_LEFT]){
            x -= 10;
        }

        if(keystates[SDLK_UP]){
            y -= 10;
        }

        if(keystates[SDLK_DOWN]){
            y += 10;
        }

        //Apply the surface to the screen
        apply_surface(0,0, Backgrnd,screen);
        apply_surface( x, y, Personita[pss], screen );

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Wait 2 seconds
        SDL_Delay( 100 );

        pss++;
    }
    //Free the surface and quit SDL
    clean_up();

    return 0;
}
