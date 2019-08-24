#ifndef _PREPREKE_H_
#define _PREPREKE_H_

#include <GL/glut.h>
#include <stdlib.h>

#define MAX_PREPREKA 15

typedef struct lopta {
    float x;
    float z;
} Lopta;


Lopta napravi_loptu();
void nacrtaj_loptu();
void inicijalizacija_prepreka();
void azuriraj_prepreke();
void nacrtaj_prepreke();

#endif
