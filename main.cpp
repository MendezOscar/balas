//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include "Enemies.h"
#include <list>
#include "derecha.h"
#include "abajo.h"
#include "arriba.h"
#include <sstream>
#include <fstream>
#include "SDL/SDL_ttf.h"

using namespace std;
//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;


int FRAMES_PER_SECOND =60 ;

//The surfaces
SDL_Surface *buttonSheet = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *seconds = NULL;
//The event structure
SDL_Surface *background = NULL;
SDL_Event event;
stringstream stream;


TTF_Font *font = NULL;

int x = 0, y = 0;

//The clip regions of the sprite sheet
SDL_Color textColor = { 0, 0, 0 };
class Timer
{
private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};
Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}
//The button
class Button
{
private:
    //The attributes of the button
    SDL_Rect box;

    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;

public:
    //Initialize the variables
    int x;
    int y;
    Button( int x, int y, int w, int h);

    //Handles events and set the button's sprite region
    void handle_events();

    //Shows the button on the screen
    void show();
};

SDL_Surface *load_image( std::string filename )
{

    //Return the optimized surface
    return IMG_Load( filename.c_str() );

}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
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

    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Button Test", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the button sprite sheet
    buttonSheet = load_image( "button.png" );
    background = load_image("background.png");
    font = TTF_OpenFont( "letter.ttf", 20 );
    //If there was a problem in loading the button sprite sheet
    if( buttonSheet == NULL )
    {
        return false;
    }
    if(font ==NULL)
        return false;

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface( buttonSheet );

    //Quit SDL
    SDL_Quit();
}

Button::Button( int x, int y,int w, int h)
{
    box.x =x;
    box.y = y;
    box.w = w;
    box.h = h;
}

void Button::handle_events()
{
    //The mouse offsets

    //If the mouse moved
    if( event.type == SDL_MOUSEMOTION )
    {
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;

        box.x = x-139;
        box.y = y-115;

    }
    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button


        }
    }
    //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( y > box.y ) )
            {
                //Set the button sprite

            }
        }
    }
}

void Button::show()
{
    //Show the button
    apply_surface( box.x, box.y, buttonSheet, screen,NULL );
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }
    srand(time(NULL));
    //Make the button
    int gastar = 0;
    int vida = 0;
    int reload = 13;
    SDL_Surface *cargar = load_image("cargar.png");
    SDL_Surface *balas_disponibles[14];
    balas_disponibles[0] = load_image("balas01.png");
    balas_disponibles[1] = load_image("balas02.png");
    balas_disponibles[2] = load_image("balas03.png");
    balas_disponibles[3] = load_image("balas04.png");
    balas_disponibles[4] = load_image("balas05.png");
    balas_disponibles[5] = load_image("balas06.png");
    balas_disponibles[6] = load_image("balas07.png");
    balas_disponibles[7] = load_image("balas08.png");
    balas_disponibles[8] = load_image("balas09.png");
    balas_disponibles[9] = load_image("balas10.png");
    balas_disponibles[10] = load_image("balas11.png");
    balas_disponibles[11] = load_image("balas12.png");
    balas_disponibles[12] = load_image("balas13.png");
    balas_disponibles[13] = load_image("reload.png");
    Button myButton(120,120,277,229);
    int frames=0;
    list<Enemies*>enem;
    bool arr= true;
    bool aba= true;
    bool izq= true;
    bool der = true;
    Uint32 startin =0;
    Timer fps;
    Timer myTimer;
    myTimer.start();
    int x = 0;
    int y = 460;
    while( quit == false )
    {

        fps.start();
        if(frames%250 == 0 && izq)
        {
            enem.push_back(new Enemies(rand()%SCREEN_WIDTH/3,rand()%SCREEN_HEIGHT/2,screen,load_image("mal.png")));
            izq = false;
        }
        if(frames%1500==0 && der)
        {
            enem.push_back(new derecha(rand()%SCREEN_WIDTH/2,rand()%SCREEN_HEIGHT/3,screen,load_image("mal1.png")));
            der = false;
        }
        if(frames%2900==0 && aba )
        {
            enem.push_back(new abajo(rand()%2*SCREEN_WIDTH/4,rand()%SCREEN_HEIGHT/2,screen,load_image("mal2.png")));
            aba = false;
        }
        if(frames%3800==0 && arr )
        {
            enem.push_back(new arriba(rand()%2*SCREEN_WIDTH/4,rand()%SCREEN_HEIGHT/3,screen,load_image("mal3.png")));
            arr = false;
        }

        int clickx =-1;
        int clicky= -1;
        //If there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle button events
            myButton.handle_events();
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {

                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if (gastar >=0 || gastar <=12)
                    {
                        clickx = event.button.x;
                        clicky = event.button.y;
                        gastar++;
                        if (gastar > 13)
                        gastar = 13;

                        if(clickx >= x && clickx <= x + cargar->w && clicky >= y && clicky <= y + cargar->h)
                        {

                            apply_surface(0,0, balas_disponibles[0], screen);

                        }

               }
            }
            }
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //Fill the screen white


        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        apply_surface(0,0,background,screen);
        list<Enemies*>::iterator i=enem.begin();
        while(i!=enem.end())
        {
            if((*i)->borrar)
            {
                if((*i)->tipo=="n")
                    izq = true;
                if((*i)->tipo=="d")
                    der = true;
                if((*i)->tipo=="ab")
                    aba = true;
                if((*i)->tipo=="ar")
                    arr = true;

                Enemies*temp = (*i);
                i = enem.erase(i);
                delete temp;

            }
            else
            {
                (*i)->dibujar();
                if((*i)->tipo=="n")
                {
                    if((*i)->x<=SCREEN_WIDTH-(*i)->surface->w*2)
                        (*i)->mover();
                }
                else if((*i)->tipo == "d")
                {
                    if((*i)->x>=SCREEN_WIDTH/3-(*i)->surface->w*2)
                        (*i)->mover();

                }
                else if((*i)->tipo == "ab")
                {
                    if((*i)->y>50)
                        (*i)->mover();

                }
                else if((*i)->tipo == "ar")
                {
                    if((*i)->y<SCREEN_HEIGHT/5)
                        (*i)->mover();
                }
                (*i)->logica(clickx,clicky);

            }
            i++;
        }

        //Show the button
        myButton.show();

        //Update the screen
        frames++;

        std::stringstream time;
        time << "Timer: " <<30- ((myTimer.get_ticks()-startin)/1000);
        seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );
        apply_surface( ( SCREEN_WIDTH - seconds->w ) / 1, 0, seconds, screen );

        //apply_surface(0,0, balas_disponibles[vida], screen);

        apply_surface(0,0, balas_disponibles[gastar], screen);
        if (gastar >= 12)
        {
            apply_surface(0,0, balas_disponibles[reload], screen);

        }//if(gastar == 14){

        apply_surface(x,y, cargar, screen);
        //}



        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    //Clean up
    clean_up();

    return 0;
}
