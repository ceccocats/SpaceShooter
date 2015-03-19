#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>    
#include <allegro5/allegro_image.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <cassert>
#define _USE_MATH_DEFINES

#include "struttura_dati.h"
#include "system.h"
#include "logica_gioco.h"
#include "ia.h"

    
    extern ALLEGRO_MOUSE_STATE mouse;
    extern ALLEGRO_COLOR colore[ncolori];
    
    extern bool tasto[ntasti];

    extern float alpha_muri[4];

    extern particle *p_emit;

    extern int stat_proiettili;
    extern int stat_particle;
    
    extern nemico *nemici;





nemico *crea_nemico(nemico *nemici, nemico &camp) 
{

    nemico *n = new nemico;  
       
    if (nemici == NULL) {
        nemici = n;
        nemici->succ = NULL;
    } else {
        n->succ = nemici;
        nemici = n;
    }   

    
    nemici->x = camp.x; 
    nemici->y = camp.y; 
    nemici->vel = camp.vel; 
    nemici->l = camp.l; 
    nemici->danno = camp.danno;
    nemici->ang = camp.ang;
    nemici->angd = camp.ang;
    nemici->tipo_nem = camp.tipo_nem; 
    nemici->colore = camp.colore;
    nemici->da_eliminare= false;
    
    
    return nemici;
}






void muovi_nemici()
{


    nemico *p = nemici;
    nemico *prec = NULL;

    while(p != NULL) {
        
        if (p->da_eliminare) {
           
            p_emit = emetti_particle_esp(p_emit, p->x, p->y, 
             30, 5, 0, M_PI*2, 60, p->colore );
            
            
            nemici = elimina_nemico(nemici, p, prec);   
                                   
            if (prec != NULL)        
                p = prec->succ;
            else 
                p = NULL;

            continue;
        }
                
        switch(p->tipo_nem) {
            
        case QUADRATO:
            p->xp[0] = p->x + cos(p->angd+ M_PI/4)*p->l;
            p->yp[0] = p->y + sin(p->angd+ M_PI/4)*p->l;
            
            p->xp[1] = p->x + cos(p->angd- M_PI/4)*p->l;
            p->yp[1] = p->y + sin(p->angd- M_PI/4)*p->l;       
            
            p->xp[2] = p->x + cos(p->angd+ M_PI*3/4)*p->l;
            p->yp[2] = p->y + sin(p->angd+ M_PI*3/4)*p->l;       
            
            p->xp[3] = p->x + cos(p->angd- M_PI*3/4)*p->l;
            p->yp[3] = p->y + sin(p->angd- M_PI*3/4)*p->l;    
            
            break;
            
        default:
            break;
        
        }

        p->angd += 0.05f;

        
        if (p->x <=bordo_lat+5) {
            alpha_muri[M_SX] = 0.5f;
            p->x = bordo_lat+5.5;
            p->ang *= -1;
            p->ang += M_PI;
        }
        else if (p->x >= lschermo-bordo_lat-5) {
            alpha_muri[M_DX] = 0.5f;
            p->x = lschermo-bordo_lat-5.5;
            p->ang *= -1;
            p->ang += M_PI;
        }

        if (p->y <=bordo_alto+5) {
            alpha_muri[M_ALTO] = 0.5f;
            p->y = bordo_alto+5.1;
            p->ang *= -1;
        }
        else if (p->y >= hschermo-bordo_basso-5) {
            alpha_muri[M_BASSO] = 0.5f;
            p->y = hschermo-bordo_basso-5.1;
            p->ang *= -1;
        }      
           

        p->x -= cos(p->ang)*p->vel;
        p->y -= sin(p->ang)*p->vel;

    
        prec = p;
        p = p->succ;
    }


}


nemico *elimina_nemico(nemico *nemici, nemico *p, nemico *prec)
{
    if (prec == NULL) {
        nemici = p->succ;
        delete [] p;
        
        return nemici;
    }
        
    prec->succ = p->succ;
    
    delete [] p;
    

    return nemici;
}


void emetti_nemici(navicella &pl)
{
    static int deltat_quadrati = 100;
    static int tatt_quadrati = 0;
    
    
    tatt_quadrati++;
    
    if(tatt_quadrati > deltat_quadrati) {
        nemico camp;
        
        
        float angolo = ((rand() % 89)+1) * M_PI / 180; 
        
        int pos = (rand() % 4) +1;

        
        assert(pos>=1 && pos<=4);
        
        switch(pos) {
        
            case 1:
                camp.x = bordo_lat;
                camp.y = bordo_alto;
                camp.ang = angolo;
                break;
                
            case 2:
                camp.x = lschermo - bordo_lat;
                camp.y = bordo_alto;
                camp.ang = angolo;               
                break;
                
            case 3:
                camp.x = bordo_lat;
                camp.y = hschermo - bordo_alto;
                camp.ang = angolo;
                break;
                
            case 4:
                camp.x = lschermo - bordo_lat;
                camp.y = hschermo - bordo_alto;
                camp.ang = angolo;
                break;
        }
        


        camp.tipo_nem = QUADRATO;

        int rnd = rand() % 5;
        camp.l = rnd + 10;
        camp.vel = rnd/2 +3;
        camp.danno = rnd + 10;
        
        camp.colore = colore[ROSSO];
        

        nemici = crea_nemico(nemici, camp);
        
        
        tatt_quadrati=0;
        deltat_quadrati --;
        deltat_quadrati <-50? deltat_quadrati = 100 : true;
        
    }
    
    
    
    
}





nemico *collisone_nemico(int x, int y)
{
    nemico *p = nemici;
    
    
    
    while(p != NULL) {
    
        float nx = p->x, ny = p->y, l = p->l;
        
        if (x > nx-l && x < nx+l && y > ny-l && y< ny+l)
            return p;
        
        
        p = p->succ;
    }
    
    
    return NULL;
}