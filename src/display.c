#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define dt 0.005

int number_of_file = 499;
int count_step = 1;
int N;
int Nmax;

char prefixname[1024] = "position"; 
double radius_particle = 0.01;
double boxsize = 4.;



/* particle structure */
struct particle{
    double x;
    double y;
    double z;
};

struct particle *particles;

/* OpenGL parameters ------------------------ */
bool f = false;
int tpm = dt*1000;
bool fullscreen = false;
bool mouseDown = false;
float x_rot = 0.0f;
float y_rot = 0.0f;
float x_diff = 0.0f;
float y_diff = 0.0f;

void particle_add(struct particle pt){
    while (Nmax <= N){
        Nmax += 128;
        particles = realloc(particles, sizeof(struct particle)*Nmax);
    }
    particles[N] = pt;
    N++;
}

void readfile(char* filename){
    char fname[1024];
    sprintf(fname, "%s_%d.bin", filename, count_step);
    FILE *ptr_myfile; 
    ptr_myfile = fopen(fname,"rb");
    if (!ptr_myfile){
        printf("Unable to open file!\n");
        exit(EXIT_FAILURE);
    }
    
    N = 0; // number of particles in a file 
    struct particle pt;
    while (!feof(ptr_myfile)){
        fread(&pt,sizeof(struct particle),1,ptr_myfile);
        //printf("%d %lf %lf %lf\n", N, pt.x, pt.y, pt.z);
        particle_add(pt);
    }

    N = N-1; // bug, last particle 2 times
    fclose(ptr_myfile);
    //printf("%d %d\n", count_step, N);
    count_step++;
}

/* read binary file */
void read_inputfile(char* filename){
    if (count_step > number_of_file){
        f = false;
        printf("Finish. Press G to restart.\n");
    }
    else if (count_step < 1){
        f = false;
        count_step = 1;
        printf("Return to starting point.\n");
    }
    else{
        readfile(filename);
    }
}


void myIdleFunc(int a){
    read_inputfile(prefixname);
    glutPostRedisplay();
    if(f) glutTimerFunc(tpm, myIdleFunc,0);
}

void init(){
    GLfloat mat_specular[] = {1., 1., 1., 1.};
    GLfloat mat_shininess[] = {50.0};
    GLfloat light_pos[] = {1., 1., 1., 0.};

    glClearColor(1., 1., 1., 1.); // white
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glLoadIdentity();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot, 0.0f, 1.0f, 0.0f);

    glColor3f(0.0,0.0,1.0);
    glutWireCube(boxsize); // boxsize
    
    /* draw balls */
    /*
    for (int i=0; i<N; i++){
        glPushMatrix();
        glTranslatef(particles[i].x, particles[i].y, particles[i].z);
        glColor3f(0., (i+1)/(float)N, 0.);
        glutSolidSphere(radius_particle, 20, 18);
        glPopMatrix();
    }
    */

    /* draw points */
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glBegin(GL_POINTS);
    glColor3f( 1.0f, 0.2f, 0.2f);
    for (int i=0; i<N; i++){
        glVertex3f(particles[i].x, particles[i].y, particles[i].z);
    }
    glEnd();

    glFlush();
    glutSwapBuffers();
}


/* "smoothing" when resize the screen display */
void resize(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* keyboard control */
void keyboard(unsigned char key, int x, int y){
    if (key == 27){
        exit(1);
    }
    else if ((char)key == 'a'){ // play
        if (!f) glutTimerFunc(tpm,myIdleFunc, 0);
        f = true;
    }
    else if ((char)key == 's'){ // pause
        f = false;
    }
    else if ((char)key == 'd'){ // next step
        read_inputfile(prefixname);
        glutPostRedisplay();
    }
    else if ((char)key == 'f'){ // previous step
        count_step -= 2;
        read_inputfile(prefixname);
        glutPostRedisplay();
    }
    else if ((char)key == 'g'){ // restart
        count_step = 1;
        readfile(prefixname); 
        f = false;
        glutPostRedisplay();
    }
}

void specialKeyboard(int key, int x, int y){
    if (key == GLUT_KEY_F1){
        fullscreen = !fullscreen;
        if (fullscreen){
            glutFullScreen();
        } 
        else {
            glutPositionWindow(25, 25);
            glutReshapeWindow(700, 700);
        }
    }
}


/* rotate using mouse pointer */
void mouse(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        mouseDown = true;
        x_diff = x - y_rot;
        y_diff = -y + x_rot;
    }
    else{
        mouseDown = false;
    }
}

void mouseMotion(int x, int y){
    if (mouseDown){
        y_rot = x - x_diff;
        x_rot = y + y_diff;
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(25, 25);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Particle in motion");

    init();
    readfile(prefixname);    

    glutReshapeFunc(resize);
    glutTimerFunc(tpm, myIdleFunc, 0);
    glutDisplayFunc(display);
    
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();

    return 0;
}
