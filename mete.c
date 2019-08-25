#include <stdio.h>
#include "prepreke.h"
const float korak_prepreke = 3;
const float brzina_prepreke = 0.02;
Lopta lopte[MAX_PREPREKA];

Lopta napravi_loptu() {
    Lopta tmp_lopta;
    tmp_lopta.x =  -5 +rand() % 10;
    tmp_lopta.z = 10;
    tmp_lopta.boja= rand()/(float)RAND_MAX;;

    return tmp_lopta;
}



void inicijalizacija_meta() {
    for(int i = 0; i < MAX_PREPREKA; i++) {
            lopte[i] = napravi_loptu();
            lopte[i].z = lopte[i].z +korak_prepreke * i ;
		
    }
}

void azuriraj_mete() {
    int i;
    for (i = 0; i < MAX_PREPREKA; i++) {
            lopte[i].z -= brzina_prepreke;
      
    }
}



void nacrtaj_mete() {
GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    GLfloat diffuse_coeffs[] = { 1.0, 0.37, 0.22525, 1 };
    GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };


    GLfloat ambient_coeffs1[] = { 0.05375, 0.05, 0.06625, 1 };
    GLfloat diffuse_coeffs1[] = { 0.0, 1.0, 0.22525, 1 };
    GLfloat specular_coeffs1[] = {  0.332741, 0.528634, 0.346435, 1 };

    GLfloat shininess = 0.3*128;

    for (int i = 0; i < MAX_PREPREKA; i++) {
	for(int j=0;j<4;j++) {
	if(lopte[i].boja>0.5){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}
	else   {  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs1);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
       glPushMatrix();
            glTranslatef(lopte[i].x+ j*0.3, 0,lopte[i].z );
            glutSolidSphere(0.15, 25, 25);
       glPopMatrix();
    }
}
}
