bool inizializza_allegro();

void paletta_colori();

void aggiorna_tasti(ALLEGRO_EVENT &ev, bool tasto[], bool set);

ALLEGRO_COLOR trasp( ALLEGRO_COLOR c, float alpha);

void int_to_string(int n, char* str, int cifre );
