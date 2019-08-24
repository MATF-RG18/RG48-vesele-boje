#include "prepreke.h"
const float korak_prepreke = 5;
const float brzina_prepreke = 0.05;
Lopta lopte[MAX_PREPREKA];

Lopta napravi_loptu() {
    Lopta tmp_lopta;
    tmp_lopta.x = -1.0 + rand() / (float)RAND_MAX * 2.0;
    tmp_lopta.z = -5 + korak_prepreke * MAX_PREPREKA; 

    return tmp_lopta;
}



void inicijalizacija_prepreka() {
    int i;
    for(i = 0; i < MAX_PREPREKA; i++) {
        
            lopte[i] = napravi_loptu();
            lopte[i].z = -korak_prepreke * i;
        

    }
}

void azuriraj_prepreke() {
    int i;
    for (i = 0; i < MAX_PREPREKA; i++) {
            if (lopte[i].z > 5)
                lopte[i] = napravi_loptu();
            lopte[i].z += brzina_prepreke;
      
    }
}

void nacrtaj_loptu(Lopta l) {
glPushMatrix();
        glTranslatef(l.x, 0,l.z );
        glutSolidSphere(0.15, 500, 500);
    glPopMatrix();
}


void nacrtaj_prepreke() {
    int i;
    for (i = 0; i < MAX_PREPREKA; i++) {
            nacrtaj_loptu(lopte[i]);
        }
    }
