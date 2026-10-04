#include <GL/freeglut.h>
#include <math.h>

#define MAX_CIRCLES   1000
#define GROWTH_RATE   0.6f 
#define TIMER_MS      16
#define START_RADIUS  2.0f

typedef struct {
    float x, y;
    float radius;
} Circle;

static Circle circles[MAX_CIRCLES];
static int numCircles = 0;
static int growingIndex = -1;   /* index of circle currently growing, -1 = none */

static int windowWidth = 800, windowHeight = 600;

void drawCircle(float cx, float cy, float r) {
    const int segments = 64;
    int i;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (i = 0; i <= segments; i++) {
        float theta = 2.0f * 3.14159265f * (float)i / (float)segments;
        glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
    }
    glEnd();
}

void display(void) {
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.55f, 1.0f);
    for (i = 0; i < numCircles; i++) {
        drawCircle(circles[i].x, circles[i].y, circles[i].radius);
    }
    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* y-down projection so it matches GLUT's mouse coordinates directly */
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    if (growingIndex != -1) {
        circles[growingIndex].radius += GROWTH_RATE;
        glutPostRedisplay();
    }
    glutTimerFunc(TIMER_MS, timer, 0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (numCircles < MAX_CIRCLES) {
                circles[numCircles].x = (float)x;
                circles[numCircles].y = (float)y;
                circles[numCircles].radius = START_RADIUS;
                growingIndex = numCircles;
                numCircles++;
                glutPostRedisplay();
            }
        } else if (state == GLUT_UP) {
            growingIndex = -1;   /* stop growing, circle stays as-is */
        }
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        numCircles = 0;
        growingIndex = -1;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Qazi Muhammad Ahad (CT-24264)");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutTimerFunc(TIMER_MS, timer, 0);

    glutMainLoop();
    return 0;
}