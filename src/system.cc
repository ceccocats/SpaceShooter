#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>    
#include <allegro5/allegro_image.h>
#include <iostream>

#include "struttura_dati.h"
#include "system.h"
#include "font.h"


    extern ALLEGRO_DISPLAY *display;
    extern ALLEGRO_EVENT_QUEUE *event_queue;
    extern ALLEGRO_TIMER *timer;
    extern ALLEGRO_COLOR colore[ncolori];
    
    extern bool tasto[ntasti];
    extern float alpha_muri[4];
    
    
bool inizializza_allegro()
{
    for (int i=0; i<ntasti; i++)
        tasto[i] = false;

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);


    if(!al_init())                  //inizializzo Allegro
        return false;


    //creo dysplay
    display = al_create_display(lschermo, hschermo); 


    if(!display)                    //test display
        return false;

    al_init_primitives_addon();
    al_init_image_addon();

    al_install_keyboard();
    al_install_mouse();

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    al_start_timer(timer);
    
    inizializza_font();
    
    return true;
}


void paletta_colori()
{
    colore[NERO]      = al_map_rgba_f(0.0, 0.0, 0.0, 1.0);
    colore[BIANCO]    = al_map_rgba_f(1.0, 1.0, 1.0, 1.0);
    colore[ROSSO]     = al_map_rgba_f(1.0, 0.0, 0.0, 1.0);
    colore[ARANCIONE] = al_map_rgba_f(1.0, 0.5, 0.0, 1.0);
    colore[GIALLO]    = al_map_rgba_f(1.0, 1.0, 0.0, 1.0);
    colore[VERDE]     = al_map_rgba_f(0.0, 1.0, 0.0, 1.0);
    colore[BLU]       = al_map_rgba_f(0.0, 0.0, 1.0, 1.0);
    colore[VIOLA]     = al_map_rgba_f(1.0, 0.0, 1.0, 1.0);
    
    
    for (int i = 0; i < 4; i++)
        alpha_muri[i] = 0.3f;
}


void aggiorna_tasti(ALLEGRO_EVENT &ev, bool tasto[], bool set)
{
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_W:
                    tasto[W] = set;
                    break;
                case ALLEGRO_KEY_S:
                    tasto[S] = set;
                    break;
                case ALLEGRO_KEY_D:
                    tasto[D] = set;
                    break;
                case ALLEGRO_KEY_A:
                    tasto[A] = set;
                    break;
                case ALLEGRO_KEY_SPACE:
                    tasto[SPAZIO] = set;
                    break;
                case ALLEGRO_KEY_ENTER:
                    tasto[INVIO] = set;
                    break;
                case ALLEGRO_KEY_P:
                    tasto[P] = set;
                    break;
            }
}   


ALLEGRO_COLOR trasp( ALLEGRO_COLOR c, float alpha)
{

    c.r *= alpha;
    c.g *= alpha;
    c.b *= alpha;
    c.a = alpha;
     
    return c;   
}

void int_to_string(int n, char* str, int cifre )
{
    
    
    for(int i=0; i<cifre; i++){
        int div = 0.1 *pow(10, cifre-i);
        int car = n / div;

        n -= car*div;
        char c = '0' + car;
        str[i] = c;
    }
    str[cifre] = '\0';
    
}



