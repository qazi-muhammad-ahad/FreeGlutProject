#include <GL/freeglut.h>
#include <cmath>
#include <fstream>
#include <iostream>

const double PI = 3.14159265358979323846;
const int screenWidth = 800;
const int screenHeight = 600;

void question1()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);

    glBegin(GL_LINE_STRIP);
    for (double x = 0.0; x < 3.0 * PI; x += 0.01)
    {
        double scaledX = x * 100.0;
        double scaledY = std::sin(x) * 100.0;
        glVertex2d(scaledX, scaledY + screenHeight / 2.0);
    }
    glEnd();
}

void question2()
{
    glLineWidth(1.0f);
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINES);
    glVertex2i(50, 160);
    glVertex2i(50, 390);
    glVertex2i(740, 160);
    glVertex2i(740, 390);
    glVertex2i(50, 300);
    glVertex2i(740, 300);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_STRIP);
    for (int x = 0; x <= 300; x += 3)
    {
        double y = 300.0 - 100.0 * std::cos(2.0 * PI * x / 100.0)
                         + 30.0 * std::cos(4.0 * PI * x / 100.0)
                         + 6.0 * std::cos(6.0 * PI * x / 100.0);
        glVertex2d(50.0 + 2.3 * x, screenHeight - y);
    }
    glEnd();
}

void drawPolylineFile(const char* fileName)
{
    std::ifstream inStream(fileName);
    int numPolylines, numPoints, x, y;

    if (!(inStream >> numPolylines) || numPolylines <= 0)
    {
        std::cerr << "Cannot read dinosaur file: " << fileName << '\n';
        return;
    }

    for (int j = 0; j < numPolylines; ++j)
    {
        if (!(inStream >> numPoints) || numPoints <= 0)
        {
            std::cerr << "Invalid polyline in: " << fileName << '\n';
            return;
        }

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < numPoints; ++i)
        {
            if (!(inStream >> x >> y))
            {
                glEnd();
                std::cerr << "Invalid point in: " << fileName << '\n';
                return;
            }
            glVertex2i(x, y);
        }
        glEnd();
    }
}

void question3()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(4.0f);

    glPushMatrix();
    glTranslatef(60.0f, 70.0f, 0.0f);
    drawPolylineFile("dino.dat.txt");
    glPopMatrix();
}

void question4()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(4.0f);

    glPushMatrix();
    glTranslatef(60.0f, 70.0f, 0.0f);
    drawPolylineFile("dino_spikes.dat.txt");
    glPopMatrix();
}

void question5(float x, float y, float width, float height)
{
    if (width <= 0.0f || height <= 0.0f)
        return;

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(width / 60.0f, height / 80.0f, 1.0f);

    glBegin(GL_LINE_STRIP);
    glVertex2i(0, 0);
    glVertex2i(60, 0);
    glVertex2i(60, 45);
    glVertex2i(28, 80);
    glVertex2i(18, 68);
    glVertex2i(18, 80);
    glVertex2i(8, 80);
    glVertex2i(8, 55);
    glVertex2i(0, 45);
    glVertex2i(0, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(10, 0);
    glVertex2i(10, 33);
    glVertex2i(24, 33);
    glVertex2i(24, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(38, 29);
    glVertex2i(49, 29);
    glVertex2i(49, 40);
    glVertex2i(38, 40);
    glVertex2i(38, 29);
    glEnd();

    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Uncomment the question you want to display.
    // question1();
    // question2();
    // question3();
    // question4();
    question5(250.0f, 120.0f, 240.0f, 320.0f);
    question5(50.0f, 100.0f, 120.0f, 320.0f);
    question5(550.0f, 230.0f, 240.0f, 150.0f);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Qazi Muhammad Ahad (CT-24264)");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, screenWidth, 0.0, screenHeight, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
