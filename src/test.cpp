#include <GL/freeglut.h>
#include <cmath> 

void display (){


    glBegin(GL_QUADS);
        glVertex2f(10, 10);
        glVertex2f(20, 10);
        glVertex2f(10, 20);
        glVertex2f(20, 20);

        glEnd();
        glFlush();
}

int main(int argc, char** argv){

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(600, 600);
    glutCreateWindow("Window Banade");

    glutDisplayFunc(display);

    glutMainLoop();


    return 0; 
}