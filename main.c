#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#define EPSILON 0.05


void on_keyboard(unsigned char key, int x, int y);
void on_display(void);
void on_reshape(int width, int height);
void on_timer(int value);
static void on_motion(int x, int y);
static void draw_cannon(float radius,float height);
float cannon_movement_x;
float cannon_movement_y;
void draw_circle(float r);
void set_normal_and_vertex_tire(float u, float v, float r);
void draw_tire(float r, float h);

int windowWidth;
int windowHeight;


int main(int argc, char **argv){

    /* Inicijalizacija gluta */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
       
    //glutInitWindowSize(500, 500);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Vesele boje");
    
	

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutPassiveMotionFunc(on_motion);


    glClearColor(0.7, 0.7, 1, 0);
    glEnable(GL_DEPTH_TEST);
    cannon_movement_x=0;
    cannon_movement_y=0;
    windowWidth=600;
    windowHeight=600;
    glutMainLoop();

    return 0;
}
void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
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

    glutSwapBuffers();
}
static void draw_cannon(float radius, float height){
     //setting the material lighting attributes
    GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    GLfloat diffuse_coeffs[] = { 0.28275, 0.37, 0.22525, 1 };
    GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };

    GLfloat shininess = 0.3*128;
    //Setting material lighting properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


    float x = 0.0;  //x and y are polar coordinates
    float y = 0.0;
    float angle = 0.0; //initial angle which will be used for calculating polar coordinates
    float angle_step = 0.005; //value for increasing of the angle in the loop

    /*
     The tube of the cylinder is drawn by drawing 2 vertices in each iteration, and connecting
     them in a quad strip.
     When the loop is exited we need to draw two 2 more vertices to complete the tube, since
     the angle will never be exactly equal to 2pi, so the last strip needs to be drawn explicitly.
     */





    //Rotations for aiming
    glPushMatrix();
        glRotatef(cannon_movement_x, 1, 0, 0);
        glRotatef(cannon_movement_y, 0, 1, 0);
        //begin to draw cylinder from quad stripes
        glBegin(GL_QUAD_STRIP);
            while(angle < 2*M_PI){
                x = radius*cos(angle);//x polar coordinate
                y = radius*sin(angle);//y polar coordinate
                glNormal3f(x / radius, y / radius, 0.0); //normal for each vertex (important for lighting)
                glVertex3f(x, y, height);//draw upper vertex
                glVertex3f(x, y, 0.0); // draw lower vertex
                angle += angle_step; // increase angle
            }
            glVertex3f(radius, 0.0, height); // draw last two vertices
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
	printf("%f",cannon_movement_x);
	printf("%f",cannon_movement_y);
      glutPostRedisplay();

}
