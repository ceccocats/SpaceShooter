void inizializza_player(navicella &pl);

void muovi_player(navicella &pl, int mousex, int mousey);

void calcola_punti_triangolo(navicella &pl);

void gestisci_sparo(navicella &pl);  

particle *emetti_particle(particle *p_emit, float x, float y, float vel, 
                          float ang, float cono, float vita, ALLEGRO_COLOR colore);

particle *emetti_particle_esp(  particle *p_emit, float x, float y, int numero, 
                            float vel, float ang, float cono, float vita,
                            ALLEGRO_COLOR colore  );

particle *muovi_particle(particle *p_emit);
