#include <GL/freeglut.h>
using namespace std;

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("My Window");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
