
nemico *crea_nemico(nemico *nemici, nemico &camp); 

void muovi_nemici();

void emetti_nemici(navicella &player);

nemico *collisone_nemico(int x, int y);

nemico *elimina_nemico(nemico *nemici, nemico *p, nemico *prec);