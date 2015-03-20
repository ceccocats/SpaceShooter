#include <allegro5/allegro.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES

#include "struttura_dati.h"
#include "logica_gioco.h"
#include "system.h"
#include "ia.h"

    extern ALLEGRO_MOUSE_STATE mouse;
    extern ALLEGRO_COLOR colore[ncolori];
    
    extern bool tasto[ntasti];

    extern float alpha_muri[4];

    extern particle *p_emit;
    extern nemico *nemici;

    extern int stat_proiettili;
    extern int stat_particle;
    
    extern int score;
    extern bool game;


void inizializza_player(navicella &pl)
{
    pl.x = 300;
    pl.y = 300;
    pl.ang =0;
    pl.l = 15;

    pl.xvel =0;
    pl.yvel =0;

    pl.tsparo=0;
    pl.tsparo_max= 7;
    pl.testa = NULL;
    
    pl.vita = 100;

    esp_iniz_player(pl);
}

void muovi_player(navicella &pl, int mousex, int mousey)
{
    float &xvel = pl.xvel, &yvel = pl.yvel;
    float &x = pl.x, &y = pl.y, &ang = pl.ang, &l = pl.l;

    ang = atan2( y-mousey, x-mousex ) + M_PI/6;

    xvel <5? xvel += tasto[D]*0.2 : xvel;
    xvel >-5? xvel -= tasto[A]*0.2 : xvel;

    yvel <5? yvel += tasto[S]*0.2 : yvel;
    yvel >-5? yvel -= tasto[W]*0.2 : yvel;

    if ( (xvel <= -0.1 || xvel >= 0.1)  && !tasto[D] && !tasto[A])
        xvel>0? xvel -= 0.05 : xvel += 0.05;
    if ( xvel > -0.1 && xvel < 0.1 ) 
        xvel=0;

    if ( (yvel <= -0.1 || yvel >= 0.1)  && !tasto[S] && !tasto[W])
        yvel>0? yvel -= 0.05 : yvel += 0.05;
    if ( yvel > -0.1 && yvel < 0.1 ) 
        yvel=0;

    
    //emette particle 
    static int freq =0;
    freq++;
    
    if (freq >= 2) {
        if (tasto[D]) { 
            p_emit = emetti_particle(p_emit, x-l/2, y, 2,  
                                     2*M_PI, M_PI/3, 100, colore[ROSSO]);
        } 
        if (tasto[A]) { 
            p_emit = emetti_particle(p_emit, x+l/2, y, 2,  
                                     M_PI, M_PI/3, 100, colore[ROSSO]);
        } 
        if (tasto[W]) { 
            p_emit = emetti_particle(p_emit, x, y+l/2, 2,  
                                     M_PI+M_PI/2, M_PI/3, 100, colore[ROSSO]);
        } 
        if (tasto[S]) { 
            p_emit = emetti_particle(p_emit, x, y-l/2, 2,  
                                     2*M_PI+M_PI/2, M_PI/3, 100, colore[ROSSO]);
        } 
        
        freq =0;
    }


    
    float newx = x+ xvel; 
    float newy = y+ yvel;

    if (newx >=bordo_lat+5  && newx <= lschermo-bordo_lat-5 )
        x = newx;
    else {
        if (newx >=bordo_lat+5)
            alpha_muri[M_DX] = 0.5f;
        else
            alpha_muri[M_SX] = 0.5f;
     
        xvel = 0;

    }

    if (newy >=bordo_alto+5 && newy <= hschermo-bordo_basso-5   ) 
        y = newy;
    else {
        if (newy >=bordo_alto+5)
            alpha_muri[M_BASSO] = 0.5f;
        else  
            alpha_muri[M_ALTO] = 0.5f;

        yvel = 0;
    }  
    

    
    //collisoni con nemici
    nemico *colli = NULL;
    
    colli = collisone_nemico( pl.x-pl.l/2 , pl.y-pl.l/2 );
    if(colli != NULL) {
            colli->da_eliminare= true;
            pl.vita -= colli->danno;
            return;
    }
    
    colli = collisone_nemico( pl.x+pl.l/2 , pl.y-pl.l/2 );
    if(colli != NULL) {
            colli->da_eliminare= true;
            pl.vita -= colli->danno;
            return;
    }
    
    colli = collisone_nemico( pl.x-pl.l/2 , pl.y+pl.l/2 );
    if(colli != NULL) {
            colli->da_eliminare= true;
            pl.vita -= colli->danno;
            return;
    }
    
    colli = collisone_nemico( pl.x+pl.l/2 , pl.y+pl.l/2 );
    if(colli != NULL) {
            colli->da_eliminare= true;
            pl.vita -= colli->danno;
            return;
    }
    
    
    if(pl.vita <= 0) {
        game = false;
        esp_iniz_player(pl);
    }
    
}

static void esp_iniz_player(navicella &pl) {
    p_emit = emetti_particle_esp(p_emit, pl.x, pl.y, 15, 
                         5, 0, M_PI*2, 60, colore[GIALLO] );
    p_emit = emetti_particle_esp(p_emit, pl.x, pl.y, 15, 
                         5, 0, M_PI*2, 60, colore[ROSSO] );
    p_emit = emetti_particle_esp(p_emit, pl.x, pl.y, 15, 
                         5, 0, M_PI*2, 60, colore[BLU] );
}


void calcola_punti_triangolo(navicella &pl)
{
    float &x = pl.x, &y = pl.y, &ang = pl.ang, &l = pl.l; 
    float &x1 = pl.x1, &y1 = pl.y1, 
          &x2 = pl.x2, &y2 = pl.y2, 
          &x3 = pl.x3, &y3 = pl.y3;

    x1= x+ cos(ang+M_PI/6)*l*sqrt(3)/2;
    y1= y+ sin(ang+M_PI/6)*l*sqrt(3)/2;
    x2= x+ cos(ang-M_PI/2)*l*sqrt(3)/2;
    y2= y+ sin(ang-M_PI/2)*l*sqrt(3)/2;
    x3= x+ cos(ang-M_PI-M_PI/6)*l*sqrt(3)/2;
    y3= y+ sin(ang-M_PI-M_PI/6)*l*sqrt(3)/2;

    
}

static void distruggi_proiettile(navicella &pl, proiettile *p, proiettile *prec)
{
    if (prec == NULL) {
        delete [] p;
        pl.testa = p->succ;
        return;
    }
        
    prec->succ = p->succ;
    
    delete [] p;
}

static particle *distruggi_particle(particle *p_emit, particle *p, particle *prec)
{
    stat_particle--;
    if (prec == NULL) {
        p_emit = p->succ;
        delete [] p;
        return p_emit;
    }
        
    prec->succ = p->succ;
    
    delete [] p;
    

    return p_emit;
}

void muovi_proiettili(navicella &pl)
{
    proiettile *p = pl.testa;
    proiettile *prec = NULL;

    static int freq=0;
    freq++; 
    
    while(p != NULL) {

        if (p->x <=bordo_lat+5  || p->x >= lschermo-bordo_lat-5   || 
            p->y <=bordo_alto+5 || p->y >= hschermo-bordo_basso-5   ) {

            if (p->x <=bordo_lat+5) {
                alpha_muri[M_SX] = 0.5f;
                p_emit = emetti_particle_esp(p_emit, bordo_lat+8, p->y, 30, 
                             5, M_PI, M_PI/2, 60, colore[BLU] );
                
                if(p->rimbalza) {
                    p->x = bordo_lat+5.5;
                    p->ang *= -1;
                    p->ang += M_PI;
                }
            }
            else if (p->x >= lschermo-bordo_lat-5) {
                alpha_muri[M_DX] = 0.5f;
                p_emit = emetti_particle_esp(p_emit, lschermo-bordo_lat-8, p->y, 
                             30, 5, 0, M_PI/2, 60, colore[BLU] );
                
                if(p->rimbalza) {
                    p->x = lschermo-bordo_lat-5.5;
                    p->ang *= -1;
                    p->ang += M_PI;
                }
            }

            if (p->y <=bordo_alto+5) {
                alpha_muri[M_ALTO] = 0.5f;
                p_emit = emetti_particle_esp(p_emit, p->x, bordo_alto+8, 30, 
                             5, -M_PI/2, M_PI/2, 60, colore[BLU] );
                
                if(p->rimbalza) {
                    p->y = bordo_alto+5.1;
                    p->ang *= -1;
                }
            }
            else if (p->y >= hschermo-bordo_basso-5) {
                alpha_muri[M_BASSO] = 0.5f;
                p_emit = emetti_particle_esp(p_emit, p->x, hschermo-bordo_basso-8, 
                             30, 5, 2*M_PI+ M_PI/2, M_PI/2, 60, colore[BLU] );
                
                if(p->rimbalza) {
                    p->y = hschermo-bordo_basso-5.1;
                    p->ang *= -1;
                }
            }

            if(!p->rimbalza)
                distruggi_proiettile(pl, p, prec);   
            
            if (prec != NULL)        
                p = prec->succ;
            else
                p = NULL;
            continue;
        }



        if (freq%4 == 0)
            p_emit =  emetti_particle(p_emit, p->x, p->y, 2,  
                                      p->ang-M_PI, M_PI/3, 60, colore[BLU]);
       

            
        p->x -= cos(p->ang)*p->vel;
        p->y -= sin(p->ang)*p->vel;

        nemico *colli = collisone_nemico(p->x,p->y);
        
        if(colli != NULL) {
            colli->da_eliminare= true;
            score += (colli->l-5)*4 + (colli->danno-5)*4;
        }
       
        
        prec = p;
        p = p->succ;
    }

}

void gestisci_sparo(navicella &pl)
{
    float &x = pl.x, &y = pl.y, &ang = pl.ang;
    float &tsparo = pl.tsparo, &tsparo_max = pl.tsparo_max; 

    if (tsparo >= tsparo_max && (mouse.buttons & 1)) {
        stat_proiettili++;
        
        proiettile *p = new proiettile;  

        if (pl.testa == NULL) {
            pl.testa = p;
            pl.testa->succ = NULL;
        } else {
            p->succ = pl.testa;
            pl.testa = p;
        }   

        pl.testa->x = x;
        pl.testa->y = y;
        pl.testa->ang = ang - M_PI/6 +((rand()%(2*4*100) - 4*100)/100*M_PI /180);
        pl.testa->vel = 10;
        pl.testa->rimbalza = false;

        
        tsparo =0;
    }

    tsparo++;
}




particle *emetti_particle(particle *p_emit, float x, float y, float vel, 
                          float ang, float cono, float vita, ALLEGRO_COLOR colore)
{

    stat_particle++;

    particle *p = new particle;  

    if (p_emit == NULL) {
        p_emit = p;
        p_emit->succ = NULL;
    } else {
        p->succ = p_emit;
        p_emit = p;
    }   

    p_emit->x = x;
    p_emit->y = y;
    p_emit->ang = ang + (rand() % int(2*cono*1000))/1000.0f - cono;
    p_emit->alpha = 1.0f;

    colore.r += rand()%50/100.f;
    colore.g += rand()%50/80.f;
    colore.b += rand()%50/100.f;

    p_emit->colore = colore;
    p_emit->vel = vel;
    p_emit->vita = p_emit->vita_rim = vita;



    return p_emit;
}


particle *emetti_particle_esp(  particle *p_emit, float x, float y, int numero, 
                            float vel, float ang, float cono, float vita,
                            ALLEGRO_COLOR colore  )
{

    for (int i=0; i<numero; i++) {
        stat_particle++;
        
        particle *p = new particle;  

        if (p_emit == NULL) {
            p_emit = p;
            p_emit->succ = NULL;
        } else {
            p->succ = p_emit;
            p_emit = p;
        }   

        p_emit->x = x;
        p_emit->y = y;
        p_emit->ang = ang + (rand() % int(2*cono*1000))/1000.0f - cono;
        p_emit->alpha = 1.0f;

        colore.r += rand()%100/1600.f;
        colore.g += rand()%100/1600.f;
        colore.b += rand()%100/1600.f;


        p_emit->colore = colore;
        p_emit->vel = vel;
        p_emit->vita = p_emit->vita_rim = vita;
       
    }

    return p_emit;



}


particle *muovi_particle(particle *p_emit)
{


    particle *p = p_emit;
    particle *prec = NULL;

    while(p != NULL) {

        if (p->vita_rim <= 0) {
            p_emit = distruggi_particle(p_emit, p, prec);   
            
            if (prec != NULL)        
                p = prec->succ;
            else
                p = NULL;
            continue;
        }
        
        if (p->x <=bordo_lat+5) {
            p->x = bordo_lat+5.5;
            p->ang *= -1;
            p->ang += M_PI;
        }
        else if (p->x >= lschermo-bordo_lat-5) {
            p->x = lschermo-bordo_lat-5.5;
            p->ang *= -1;
            p->ang += M_PI;
        }

        if (p->y <=bordo_alto+5) {
            p->y = bordo_alto+5.1;
            p->ang *= -1;
        }
        else if (p->y >= hschermo-bordo_basso-5) {
            p->y = hschermo-bordo_basso-5.1;
            p->ang *= -1;
        }      
          

        p->x -= cos(p->ang)*p->vel;
        p->y -= sin(p->ang)*p->vel;

        
        p->vita_rim--;
        
        p->alpha = p->vita_rim / p->vita;
        
        prec = p;
        p = p->succ;
    }

    return p_emit;

}





