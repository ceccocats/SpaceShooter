#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>    
#include <allegro5/allegro_image.h>
#include <iostream>

#include "font.h"
#include "struttura_dati.h"
#include "system.h"

struct punto {
    float x,y;
};

static punto pt[9];

/*

 schema dei punti 
 
 *-*-*   0, 1, 2
 | | |
 *-*-*   3, 4, 5
 | | |
 *-*-*   6, 7, 8
 
 */

void inizializza_font()
{
    pt[0].x = 0;
    pt[0].y = -1;
    
    pt[1].x = 0.25;
    pt[1].y = -1;
    
    pt[2].x = 0.5;
    pt[2].y = -1;
    
    pt[3].x = 0;
    pt[3].y = -0.5;
    
    pt[4].x = 0.25;
    pt[4].y = -0.5;
    
    pt[5].x = 0.5;
    pt[5].y = -0.5;
    
    pt[6].x = 0;
    pt[6].y = 0;
    
    pt[7].x = 0.25;
    pt[7].y = 0;
    
    pt[8].x = 0.5;
    pt[8].y = 0;

}

void scrivi_char(char c, float x, float y, float h, ALLEGRO_COLOR col)
{
    float lcentro;
    h>40? lcentro = h / 40.0f : lcentro = 1;
    float lsfuma;
    h> 6.6f*2? lsfuma= h / 6.6f : lsfuma = 2;
    
    #define ln(a,b) \
    al_draw_line( x+h*pt[(a)].x, y+h*pt[(a)].y, x+h*pt[(b)].x, y+h*pt[(b)].y, col, lcentro);\
    al_draw_line( x+h*pt[(a)].x, y+h*pt[(a)].y, x+h*pt[(b)].x, y+h*pt[(b)].y, trasp(col, 0.3f), lsfuma)
    
    switch(c) {
        case 'a':
            ln(0,6);
            ln(0,2);
            ln(2,8);
            ln(3,5);
            break;
        case 'b':
            ln(0,6);
            ln(0,2);
            ln(6,8);
            ln(3,5);
            ln(2,8);
            break;
        case 'c':
            ln(0,2);
            ln(0,6);
            ln(6,8);
            break;
        case 'd':
            ln(0,2);
            ln(0,6);
            ln(6,8);
            ln(2,8);
            break;       
        case 'e':
            ln(0,2);
            ln(0,6);
            ln(6,8);
            ln(3,5);
            break;
        case 'f':
            ln(0,2);
            ln(0,6);
            ln(3,5);
            break;
        case 'g':
            ln(0,2);
            ln(0,6);
            ln(6,8);
            ln(8,5);
            ln(4,5);
            break;       
        case 'h':
            ln(2,8);
            ln(0,6);
            ln(3,5);
            break;            
        case 'i':
            ln(1,7);
            ln(0,2);
            ln(6,8);
            break;
        case 'j':
            ln(0,2);
            ln(1,7);
            ln(6,7);
            break;       
        case 'k':
            ln(0,6);
            ln(2,3);
            ln(3,8);
            break;
        case 'l':
            ln(0,6);
            ln(6,8);
            break;
        case 'm':
            ln(0,6);
            ln(2,8);
            ln(4,0);
            ln(4,2);
            break;       
        case 'n':
            ln(0,8);
            ln(0,6);
            ln(2,8);
            break;
        case 'o':
            ln(0,2);
            ln(0,6);
            ln(6,8);
            ln(2,8);
            break;
        case 'p':
            ln(0,2);
            ln(0,6);
            ln(3,5);
            ln(2,5);
            break;       
        case 'q':
            ln(0,2);
            ln(0,6);
            ln(6,8);
            ln(2,8);
            ln(4,8);
            break;
        case 'r':
            ln(0,2);
            ln(0,6);
            ln(3,5);
            ln(2,5);
            ln(4,8);
            break;
        case 's':
            ln(0,2);
            ln(3,5);
            ln(6,8);
            ln(0,3);
            ln(5,8);
            break;       
        case 't':
            ln(0,2);
            ln(1,7);
            break;            
        case 'u':
            ln(2,8);
            ln(0,6);
            ln(6,8);
            break;
        case 'v':
            ln(0,7);
            ln(7,2);
            break;       
        case 'w':
            ln(2,8);
            ln(0,6);
            ln(6,4);
            ln(4,8);
            break;
        case 'x':
            ln(0,8);
            ln(6,2);
            break;
        case 'y':
            ln(6,2);
            ln(0,4);
            break;       
        case 'z':
            ln(0,2);
            ln(2,6);
            ln(6,8);
            break;
        case '0':
            ln(0,2);
            ln(0,6);
            ln(6,8);
            ln(2,8);
            break;
        case '1':
            ln(2,8);
            break;
        case '2':
            ln(0,2);
            ln(2,5);
            ln(3,5);
            ln(3,6);
            ln(6,8);
            break;       
        case '3':
            ln(8,2);
            ln(0,2);
            ln(6,8);
            ln(3,5);
            break;            
        case '4':
            ln(0,3);
            ln(3,5);
            ln(2,8);
            break;
        case '5':
            ln(0,2);
            ln(0,3);
            ln(3,5);
            ln(5,8);
            ln(6,8);
            break;       
        case '6':
            ln(0,2);
            ln(0,6);
            ln(6,8);
            ln(5,8);
            ln(3,5);
            break;
        case '7':
            ln(0,2);
            ln(2,8);
            break;
        case '8':
            ln(0,2);
            ln(0,6);
            ln(6,8);
            ln(2,8);
            ln(3,5);
            break;       
        case '9':
            ln(0,2);
            ln(0,3);
            ln(3,5);
            ln(2,8);
            ln(6,8);
            break;
        case ' ':
            //nope
            break;
        default:
            ln(0,4);
            ln(1,3);
            ln(1,5);
            ln(4,2);
            ln(6,4);
            ln(3,7);
            ln(4,8);
            ln(7,5);
    }
    
    
    
}


void scrivi_testo(const char *txt, float x, float y, float h, ALLEGRO_COLOR col)
{
    
    for(int i=0; txt[i] != '\0'; i++) 
        scrivi_char(txt[i], x+i*(h/2+h/4), y, h, col);
            
  
}