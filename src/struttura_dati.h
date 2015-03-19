#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>	
#include <allegro5/allegro_image.h>
#include <iostream>
#include <math.h>
#define _USE_MATH_DEFINES

const int lschermo = 1000; 
const int hschermo = 750;
const int bordo_lat = 20;
const int bordo_alto = 50;
const int bordo_basso = 20;
const int FPS = 60;

const int ntasti = 7;
const int ncolori = 8;

enum KEYS{ W, S, A, D, SPAZIO, INVIO, P };
enum COLORI{ NERO, BIANCO, ROSSO, ARANCIONE, GIALLO, VERDE, BLU, VIOLA };
enum MURI{ M_ALTO, M_BASSO, M_DX, M_SX};

enum NEMICO_t{ QUADRATO, PENTAGONO, ESAGONO, EPTAGONO, OTTAGONO }; 


struct proiettile {
    float x, y, ang;
    float vel;

    bool rimbalza;
    
    proiettile *succ;
};

struct particle {
    float x, y, ang, alpha, vel;
    float disp, vita, vita_rim;
    ALLEGRO_COLOR colore;

    particle *succ;
};

struct navicella {
    float x, y, ang, l;
    float x1,y1, x2,y2, x3,y3;
    float xvel, yvel;
    
    int vita = 100;
        
    float tsparo, tsparo_max;
    proiettile *testa;  

}; 


struct nemico {
    float x, y, ang, l, vel;
    float xp[10];
    float yp[10];
    float angd;
    float xvel, yvel;
    float danno;
    
    ALLEGRO_COLOR colore;
    
    NEMICO_t tipo_nem;
    
    nemico *succ;
    
    bool da_eliminare;
};

