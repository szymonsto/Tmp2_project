#include "MKL05Z4.h"

void init_buzzer(void);
void buzzer(char dlugosc); //dlugosc == 1 -> dlugi sygnal, dlugosc == 0 -> krotki sygnal, dlugosc == 2 -> brak sygnalu
void wpisz_do_pamieci(char znak);
void kasowanie_pamieci(void);
void wypisz_znak(void);
	
extern char pamiec_znakow[5]; //przechowuje 5 sostanich zankow
extern char accel_slider; // 0-> accel, 1 ->slider