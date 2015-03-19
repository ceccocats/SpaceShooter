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

    extern ALLEGRO_MOUSE_STATE mouse;
    extern ALLEGRO_COLOR colore[ncolori];
    
    extern bool tasto[ntasti];

    extern float alpha_muri[4];

    extern particle *p_emit_esp;
    
    

void disegna_player(navicella &player)
{
    float &x = player.x, &y = player.y, l = player.l;

    al_draw_line( x-l/2, y-l/2, x+l/2, y-l/2, colore[BLU], 2 );
    al_draw_line( x-l/2, y-l/2, x-l/2, y+l/2, colore[BLU], 2 );
    al_draw_line( x+l/2, y-l/2, x+l/2, y+l/2, colore[BLU], 2 );
    al_draw_line( x-l/2, y+l/2, x+l/2, y+l/2, colore[BLU], 2 );

    al_draw_line( x-l/2, y-l/2, x+l/2, y-l/2, trasp(colore[BLU], 0.3f), 6 );
    al_draw_line( x-l/2, y-l/2, x-l/2, y+l/2, trasp(colore[BLU], 0.3f), 6 );
    al_draw_line( x+l/2, y-l/2, x+l/2, y+l/2, trasp(colore[BLU], 0.3f), 6 );
    al_draw_line( x-l/2, y+l/2, x+l/2, y+l/2, trasp(colore[BLU], 0.3f), 6 );
   
    al_draw_line( player.x1, player.y1, player.x2, player.y2,
                  colore[GIALLO], 1 );
    al_draw_line( player.x2, player.y2, player.x3, player.y3,
                  colore[GIALLO], 1 );
    al_draw_line( player.x1, player.y1, player.x3, player.y3,
                  colore[GIALLO], 1 );

    al_draw_line( player.x1, player.y1, player.x2, player.y2,
                  trasp(colore[GIALLO], 0.3f), 5 );
    al_draw_line( player.x2, player.y2, player.x3, player.y3,
                  trasp(colore[GIALLO], 0.3f), 5 );
    al_draw_line( player.x1, player.y1, player.x3, player.y3,
                  trasp(colore[GIALLO], 0.3f), 5 );

}

void disegna_proiettili(proiettile *p, float dim)
{
    ALLEGRO_COLOR col1 = al_map_rgba_f(0.0,1.0,1.0,1.0);
    ALLEGRO_COLOR col2 = trasp(col1, 0.3f);

    while(p != NULL) {
        float x1 = p->x, y1 = p->y;
        float x2 = x1 + cos(-p->ang)*dim, y2 = y1 - sin(-p->ang)*dim;

        al_draw_line(x1, y1, x2, y2, col1,  2);
        al_draw_line(x1, y1, x2, y2, col2,  10);

        p = p->succ;
    }
}


void disegna_particle(particle *part, float dim)
{
    while(part != NULL) {
       float x1 = part->x, y1 = part->y;
       float x2 = x1 - cos(-part->ang)*dim, y2 = y1 + sin(-part->ang)*dim;

       al_draw_line(x1, y1, x2, y2, trasp(part->colore, part->alpha), 1);
       al_draw_line(x1, y1, x2, y2, trasp(part->colore, part->alpha- 0.7f), 5);

       part = part->succ;
    }
}


void disegna_nemici(nemico *n)
{
    while(n != NULL) {
        
        switch (n->tipo_nem) {
        
        case QUADRATO:
            al_draw_line(n->xp[0], n->yp[0], n->xp[1], n->yp[1], n->colore, 1);
            al_draw_line(n->xp[0], n->yp[0], n->xp[1], n->yp[1], trasp(n->colore, 0.3f), 5);
            
            al_draw_line(n->xp[1], n->yp[1], n->xp[3], n->yp[3], n->colore, 1);
            al_draw_line(n->xp[1], n->yp[1], n->xp[3], n->yp[3], trasp(n->colore, 0.3f), 5);               
            
            al_draw_line(n->xp[2], n->yp[2], n->xp[3], n->yp[3], n->colore, 1);
            al_draw_line(n->xp[2], n->yp[2], n->xp[3], n->yp[3], trasp(n->colore, 0.3f), 5);              
            
            al_draw_line(n->xp[0], n->yp[0], n->xp[2], n->yp[2], n->colore, 1);
            al_draw_line(n->xp[0], n->yp[0], n->xp[2], n->yp[2], trasp(n->colore, 0.3f), 5);                
        break;
            
        default:
            break;
        }
        


       n = n->succ;
    }    
  
    
}


void disegna_bordi()
{    
    ALLEGRO_COLOR col = al_map_rgba_f(0.0, 1.0, 0.0, 1.0);


    al_draw_line(bordo_lat, bordo_alto, lschermo-bordo_lat, bordo_alto, 
                  col, 2 );

    al_draw_line(bordo_lat, bordo_alto, bordo_lat, hschermo-bordo_basso, 
                  col, 2 );

    al_draw_line(lschermo-bordo_lat, bordo_alto, lschermo-bordo_lat, 
                  hschermo-bordo_basso, col, 2 );

    al_draw_line(bordo_lat, hschermo-bordo_basso, lschermo-bordo_lat, 
                  hschermo-bordo_basso, col, 2 );


    al_draw_line(bordo_lat, bordo_alto, lschermo-bordo_lat, bordo_alto, 
                  trasp(col, alpha_muri[M_ALTO]), 6+ (alpha_muri[M_ALTO]-0.3)*10);

    al_draw_line(bordo_lat, bordo_alto, bordo_lat, hschermo-bordo_basso, 
                  trasp(col, alpha_muri[M_SX]), 6+ (alpha_muri[M_SX]-0.3)*10 );

    al_draw_line(lschermo-bordo_lat, bordo_alto, lschermo-bordo_lat, 
                  hschermo-bordo_basso, trasp(col, alpha_muri[M_DX]), 
                  6+ (alpha_muri[M_DX]-0.3)*10 );

    al_draw_line(bordo_lat, hschermo-bordo_basso, lschermo-bordo_lat, 
                 hschermo-bordo_basso, trasp(col, alpha_muri[M_BASSO]), 
                 6+ (alpha_muri[M_BASSO]-0.3)*10);


    for(int i=0; i<4; i++)
        alpha_muri[i] >0.3f? alpha_muri[i] -= 0.05f : true;

}



void disegna_vita(int vita, int x, int y, int dim)
{
    ALLEGRO_COLOR col = al_map_rgba_f(1.0,0.0,0.0,1.0); ;

    
    for (int i=0; i<100; i++) {
        if(i <=50) 
             col.g = i/50.f;
        else    
             col.r = 1.0 - (i-50)/50.f;  
        
        if(i<vita)
            al_draw_line(x+i*dim/5, y, x+i*dim/5, y-dim, col, 1);    
        else
            al_draw_line(x+i*dim/5, y, x+i*dim/5, y-dim, trasp(col,0.3f), 1); 
    }
}