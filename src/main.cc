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
    bool game=true;

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
    
    int score=0;



/**
	Space Shooter
	Just a simple game of a goemetric based space shooter
*/

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
 
    float trasp_score = 1.0f;

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
            if(game) {
                al_get_mouse_state(&mouse);

                muovi_player(player, mouse.x, mouse.y);
                calcola_punti_triangolo(player);  
                emetti_nemici(player);
                gestisci_sparo(player);
            }
            
            muovi_proiettili(player);
            muovi_nemici();
            p_emit = muovi_particle(p_emit);

            if(!game) {
                if(player.vita >= 100) {
                    player.vita=100;
                    
                    if(trasp_score <1)
                        trasp_score += 0.01f;
                    else {
                        trasp_score=1;
                        score=0;
                        elimina_nemici_tutti();
                        inizializza_player(player);
                        game=true;
                    }
                } else {
                    player.vita += 0.2;
                    trasp_score >= 0 ? trasp_score -= 0.01f : trasp_score =0;
                }
            }
            
            
            
            redraw = true;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            //draw

            disegna_particle(p_emit, player.l / 2);
            disegna_proiettili(player.testa, player.l);
            disegna_nemici(nemici);
                    
            disegna_bordi();

            if(game)
                disegna_player(player);
            
            
            scrivi_testo("shooter v1", 25, 35, 20, colore[ROSSO]);
            scrivi_testo("vita", 220, 35, 20, colore[ROSSO]);
            disegna_vita(player.vita,290,35, 20);       
                                
            static char str_score[9];
            int_to_string(score, str_score, 8);
            
            scrivi_testo("score", 725, 35, 20, colore[ROSSO]);
            scrivi_testo(str_score, 860, 35, 20, colore[ROSSO]);

            if(!game)
               scrivi_testo(str_score, 210, 450, 100, trasp(colore[VERDE], 1.0f -trasp_score));
            
            
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
