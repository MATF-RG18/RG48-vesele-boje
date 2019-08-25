#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "mete.h"
#define EPSILON 0.05

const float DEGTORAD = 3.1415769/180.0f;

 
void on_keyboard(unsigned char key, int x, int y);
void on_display(void);
void on_reshape(int width, int height);
void on_timer(int value);
void on_timer1(int value);
static void on_mouse(int button, int state, int x, int y);
static void on_motion(int x, int y);


void draw_ball(float radius);
void draw_cannon(float radius,float height);
void draw_circle(float r);
void set_normal_and_vertex_tire(float u, float v, float r);
void draw_tire(float r, float h);


float cannon_movement_x;
float cannon_movement_y;
int animation_ongoing;
int animation_ongoing1;
float cannon_ball_x;
float cannon_ball_y;
float cannon_ball_z;


int ispaljena;
float brzina;
float brzinaY;
float brzinaZ;
float brzinaX;
float slucajni[15];

float brzina;

int i;

int windowWidth;
int windowHeight;


int main(int argc, char **argv){

    /* Inicijalizacija gluta */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
       
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Vesele boje");
    
	

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutPassiveMotionFunc(on_motion);
    glutMouseFunc(on_mouse);


    glClearColor(0.7, 0.7, 1, 0);
    glEnable(GL_DEPTH_TEST);
    cannon_movement_x=0;
    cannon_movement_y=0;
    cannon_ball_x = 0;
    cannon_ball_y = 0;
    cannon_ball_z = 0;

    brzinaZ = 0.0f;
    brzinaY = 0.0f;
    brzinaX = 0.0f;

    ispaljena=0;
    animation_ongoing=0;
    animation_ongoing1=0;



    windowWidth=600;
    windowHeight=600;
    
    for(i=0;i<15;i++) {
	double random_broj = rand()/(float)RAND_MAX;
	slucajni[i]=random_broj;
}
    i=0;
    inicijalizacija_meta();
    glutMainLoop();

    return 0;
}
void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    	case 27:
        	exit(0);
        	break;
	case 'r':
	case 'R':
	//Resetovanje loptice
		ispaljena=0;
        	animation_ongoing = 0;
        	cannon_ball_z = 0;
        	cannon_ball_y = 0;
        	cannon_ball_x = 0;

        	brzinaZ = 0;
        	brzinaY = 0;
        	brzinaX = 0;
		i++;
	break;
    	case 'g':
	case 'G': 
        animation_ongoing1 = 1;
        glutTimerFunc(17, on_timer1, 0);
	glutPostRedisplay();
        break;

}

}
void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width/height, 1, 1500);
}
void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat light_position[] = { 100, 100, 100, 0 };
    //Ambijentalna boja svetla
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    //Difuzna boja svetla
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    //Spekularna boja svetla
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,2, -1, 0, 1.1, 0, 0, 1, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_DEPTH_TEST);
    draw_cannon(0.2,0.5);
	draw_ball(0.19);
	nacrtaj_mete();

    glutSwapBuffers();
}
void draw_ball(float radius) {
    GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    GLfloat diffuse_coeffs[] = { 1.0, 0.37, 0.22525, 1 };
    GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };


    GLfloat ambient_coeffs1[] = { 0.05375, 0.05, 0.06625, 1 };
    GLfloat diffuse_coeffs1[] = { 0.0, 1.0, 0.22525, 1 };
    GLfloat specular_coeffs1[] = {  0.332741, 0.528634, 0.346435, 1 };

    GLfloat shininess = 0.3*128;
	if(slucajni[i]>0.5){

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
if(ispaljena==0) {
	glPushMatrix();
	glTranslatef(0,0,0);
        glRotatef(cannon_movement_x, 1, 0, 0);
        glRotatef(cannon_movement_y, 0, 1, 0);
	glTranslatef(0,0,0.5);
	glutSolidSphere(radius,25,25);
	glPopMatrix();
}
else if (ispaljena==1) {
	glPushMatrix();
        glTranslatef(cannon_ball_x, cannon_ball_y, cannon_ball_z+0.5);
        glutSolidSphere(0.1, 100, 100);
    glPopMatrix();
}
}
void draw_cannon(float radius, float height){
    GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    GLfloat diffuse_coeffs[] = { 0.28275, 0.37, 0.22525, 1 };
    GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };

    GLfloat shininess = 0.3*128;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


    float x = 0.0;  //x i y polarne koordinate
    float y = 0.0;
    float angle = 0.0; //ugao
    float angle_step = 0.005; //pomeraj ugla





    //Rotacija za pomeranje topa
    glPushMatrix();
        glRotatef(cannon_movement_x, 1, 0, 0);
        glRotatef(cannon_movement_y, 0, 1, 0);
        //Crtanje topa
        glBegin(GL_QUAD_STRIP);
            while(angle < 2*M_PI){
                x = radius*cos(angle);
                y = radius*sin(angle);
                glNormal3f(x / radius, y / radius, 0.0); 
                glVertex3f(x, y, height);
                glVertex3f(x, y, 0.0); 
                angle += angle_step; 
            }
            glVertex3f(radius, 0.0, height);
            glVertex3f(radius, 0.0, 0.0);
    glEnd();

    glutSolidSphere(radius, 100, 100);

	glTranslatef(radius,0,0);
    draw_tire(0.1,0.05);
	glTranslatef(-2*radius,0,0);
    draw_tire(0.1,0.05);

    glPopMatrix();
}
void set_normal_and_vertex_tire(float u, float v, float r)
{
    glNormal3f(0, r*cos(v), r*sin(v));
    glVertex3f(u, r*cos(v), r*sin(v));
}

 /* crtanje kruga */
void draw_circle(float r)
{
    float v;
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
    for (v = 0; v <= 2*M_PI+EPSILON; v += M_PI/1000) {
        glNormal3f(1, 0, 0);
        glVertex3f(0, r*cos(v), r*sin(v));
    }
    glEnd();
}
    
/* crtanje tocka */
void draw_tire(float r, float h)
{
    float u, v;
    
    for (u = -h/2; u < h/2; u += 0.01) {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.1, 0.1, 0.1);
        for (v = 0; v <= 2*M_PI+EPSILON; v += M_PI/20) {
            set_normal_and_vertex_tire(u, v, r);
            set_normal_and_vertex_tire(u + 0.01, v, r);
        }
        glEnd();
    }
    
    glPushMatrix();
        glTranslatef(h/2, 0, 0);
        glColor3f(0.1, 0.1, 0.1);
        draw_circle(r);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-h/2, 0, 0);
        glColor3f(0.1, 0.1, 0.1);
        draw_circle(r);
    glPopMatrix();
}
void on_motion(int x, int y){
      //Idea for this function is that we first find position X and Y where
      //posX represents pixel distance from the center of the screen in x coordinates
      //and posY represents pixel distance from the center of the screen in y coordinates
      //because of that our posX and posY are in interval [-height/2, height/2] for Y
      // since the biggest distance from the center of the screen is height/2 and smallest is -height/2
      // in the same respect posX is in interval [-width/2, width/2];
      //we want our cannon to rotate for -45 degrees around y axis when our mouse is on the left edge of the screen
      // and to rotate for 45 degrees when our mouse
      // is on the right edge of the screen
      //In the same manner we want our cannon to rotate around x axis for -30 degrees when our mouse is on the top
      //edge of the screen and for 30 degrees when our mouse is in the bottom of the screen.
      // Because of that we only need linear mapping between two intervals.

      double posY = y - windowHeight/2; // scaling [-height/2, height/2] -> [-45, 45]
      double posX = x - windowWidth/2; // scaling [-width/2, width/2] -> [30, -30]
      //using formula for scaling x from range [a, b] to range [c, d]
      // f(x) = (x-a) * ((d-c) / (b-a)) + c , where f(a) = c, f(b) = d;

      cannon_movement_x = (posY+(windowHeight*1.0)/2)*(90/(1.0*windowHeight)) - 45;
      if(cannon_movement_x > 5)
          cannon_movement_x = 5;

      cannon_movement_y = (posX+(windowWidth*1.0)/2)*(-60/(windowWidth*1.0)) + 30;

      glutPostRedisplay();

}
static void on_mouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && !animation_ongoing && state == GLUT_DOWN) {
		// ispaljivanje loptice
		animation_ongoing=1;
		ispaljena=1;
          	brzina = 0.2;
          	brzinaZ = brzina * cos(cannon_movement_x * DEGTORAD) * cos(cannon_movement_y * DEGTORAD);
          	brzinaY = -brzina* sin(cannon_movement_x * DEGTORAD);
          	brzinaX = brzina * cos(cannon_movement_x * DEGTORAD) * sin(cannon_movement_y * DEGTORAD);

          	glutTimerFunc(50, on_timer, 0);
          	glutPostRedisplay();
	}
	
}


 void on_timer(int value){
    if(value != 0)
        return ;

    if( cannon_ball_z <12){	
	//ispaljivanje loptice
        cannon_ball_z += brzinaZ;
        cannon_ball_y += brzinaY;
        cannon_ball_x += brzinaX;
	

	}
    else {	
	//vracanje loptice u top
	ispaljena=0;
        animation_ongoing = 0;
        cannon_ball_z = 0;
        cannon_ball_y = 0;
        cannon_ball_x = 0;

        brzinaZ = 0;
        brzinaY = 0;
        brzinaX = 0;
	//povecanje brojaca da bi se manjala boja loptice
	i++;
	}

    glutPostRedisplay();

    if(animation_ongoing) {
        glutTimerFunc(50, on_timer, 0);
    }
}

 void on_timer1(int value){
    if(value != 0)
        return ;
    azuriraj_mete();
    glutTimerFunc(17, on_timer, 0);
	if(animation_ongoing1)
	glutTimerFunc(17, on_timer1, 0);
}
