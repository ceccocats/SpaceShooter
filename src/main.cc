#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>    
#include <allegro5/allegro_image.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#define _USE_MATH_DEFINES

#include "struttura_dati.h"
#include "system.h"
#include "logica_gioco.h"
#include "disegna.h"
#include "font.h"
#include "ia.h"

    
    bool tasto[ntasti];

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_MOUSE_STATE mouse;

    ALLEGRO_COLOR colore[ncolori];
    float alpha_muri[4];

    particle *p_emit = NULL;
    
    nemico *nemici = NULL;
    
    int stat_proiettili = 0;
    int stat_particle = 0;

int main() 
{

    bool done = false;
    bool redraw = true;

    paletta_colori();

    srand(time(0));

    if (!inizializza_allegro())
        return -1;



    navicella player;
    inizializza_player(player);
 


    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
            aggiorna_tasti(ev, tasto, true);

        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
            aggiorna_tasti(ev, tasto, false);

        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;

        else if (ev.type == ALLEGRO_EVENT_TIMER) {
            //update
            al_get_mouse_state(&mouse);

            muovi_player(player, mouse.x, mouse.y);
            calcola_punti_triangolo(player);

            gestisci_sparo(player);

            p_emit = muovi_particle(p_emit);
            
            emetti_nemici(player);
            
            muovi_nemici();

        

            redraw = true;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            //draw

            disegna_particle(p_emit, player.l / 2);

            disegna_proiettili(player.testa, player.l);

            disegna_nemici(nemici);
                    
            disegna_bordi();

            disegna_player(player);
            
            scrivi_testo("vita", 220, 35, 20, colore[ROSSO]);
            disegna_vita(player.vita,290,35, 20);
            
            static char str_proi[5];
            static char str_part[5];
            int_to_string(stat_proiettili, str_proi, 4);
            int_to_string(stat_particle, str_part, 4);
            
            static ALLEGRO_COLOR col_sem = colore[VERDE];
            
            if(stat_particle <=2000) 
                col_sem.r = stat_particle / 2000.0;
            
            if(stat_particle >2000 && stat_particle<3000) 
                col_sem.g =1.0 - (stat_particle-2000) / 1000.0;
                
             if(stat_particle >=3000) 
                col_sem =al_map_rgba_f(1.0,0.0,0.0,1.0);           
            
            scrivi_testo("shooter v1", 25, 35, 20, colore[ROSSO]);

            scrivi_testo("proiettili sparati", 725, 20, 12, colore[ROSSO]);
            scrivi_testo("particle in rendering", 725, 40, 12, colore[ROSSO]);
            scrivi_testo(str_proi, 940, 20, 12, colore[VERDE]);
            scrivi_testo(str_part, 940, 40, 12, col_sem);

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            redraw = false;
        }
    }


    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display); //distruggo tutto

    return 0;
}
