#include <GL/freeglut.h>
#include <windows.h>
#include <cmath>
#include <vector>
#include <fstream>

int ScreenWidth, ScreenHeight;

struct Point2D
{
    int x, y;
};

void lab3()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(1.0, 1.0, 1.0);

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2d(200, 200);
        glVertex2d(200, 600);

        glVertex2d(300, 200);
        glVertex2d(300, 600);

        glVertex2d(100, 467);
        glVertex2d(400, 467);

        glVertex2d(100, 333);
        glVertex2d(400, 333);
    glEnd();

    glLineWidth(6.0);
    glBegin(GL_LINES);
        glVertex2d(600, 200);
        glVertex2d(600, 600);

        glVertex2d(700, 200);
        glVertex2d(700, 600);

        glVertex2d(500, 467);
        glVertex2d(800, 467);

        glVertex2d(500, 333);
        glVertex2d(800, 333);
    glEnd();

    glFlush();
}

void lab4()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(1.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);
        glVertex2i(200, 200);
        glVertex2i(200, 600);
        glVertex2i(300, 600);
        glVertex2i(300, 200);
        glVertex2i(400, 200);
        glVertex2i(400, 600);
    glEnd();

    glFlush();
}

void lab4_2()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(1.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);

    for (float i = -100; i < 100; i += 0.01f)
    {
        glVertex2f(i * 100, std::sin(i) * 100);
    }

    glEnd();

    glFlush();
}

void sinewave_draw()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    int centerX = ScreenWidth / 2;
    int centerY = ScreenHeight / 2;

    glColor3d(1.0, 0.0, 0.0);
    glLineWidth(2.0);

    glBegin(GL_LINES);
        glVertex2i(0, centerY);
        glVertex2i(ScreenWidth, centerY);

        glVertex2i(centerX, 0);
        glVertex2i(centerX, ScreenHeight);
    glEnd();

    glColor3d(1.0, 1.0, 1.0);
    glLineWidth(2.0);

    float amplitude = ScreenHeight / 6.0f;
    float frequency = 0.02f;

    glBegin(GL_LINE_STRIP);

    for (float x = 0; x < ScreenWidth; x += 1.0f)
    {
        float y =
            centerY +
            amplitude * std::sin((x - centerX) * frequency);

        glVertex2f(x, y);
    }

    glEnd();

    glFlush();
}

void draw_dino()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    static std::vector<std::vector<Point2D>> shapes;
    static bool loaded = false;

    if (!loaded)
    {
        std::ifstream file("dino.dat.txt");

        if (!file.is_open())
            return;

        int numShapes;
        file >> numShapes;

        for (int i = 0; i < numShapes; i++)
        {
            int numPoints;
            file >> numPoints;

            std::vector<Point2D> shape;

            for (int j = 0; j < numPoints; j++)
            {
                Point2D point;

                file >> point.x >> point.y;

                shape.push_back(point);
            }

            shapes.push_back(shape);
        }

        file.close();

        loaded = true;
    }

    if (shapes.empty())
        return;

    int minX = shapes[0][0].x;
    int maxX = shapes[0][0].x;
    int minY = shapes[0][0].y;
    int maxY = shapes[0][0].y;

    for (int i = 0; i < shapes.size(); i++)
    {
        for (int j = 0; j < shapes[i].size(); j++)
        {
            if (shapes[i][j].x < minX)
                minX = shapes[i][j].x;
            if (shapes[i][j].x > maxX)
                maxX = shapes[i][j].x;
            if (shapes[i][j].y < minY)
                minY = shapes[i][j].y;
            if (shapes[i][j].y > maxY)
                maxY = shapes[i][j].y;
        }
    }

    float dinoWidth = maxX - minX;
    float dinoHeight = maxY - minY;

    float scaleX = (ScreenWidth * 0.8f) / dinoWidth;
    float scaleY = (ScreenHeight * 0.8f) / dinoHeight;

    float scale;

    if (scaleX < scaleY)
        scale = scaleX;
    else
        scale = scaleY;

    float scaledWidth = dinoWidth * scale;
    float scaledHeight = dinoHeight * scale;

    float offsetX = (ScreenWidth - scaledWidth) / 2.0f;
    float offsetY = (ScreenHeight - scaledHeight) / 2.0f;

    glColor3d(0.2, 0.8, 0.0);
    glLineWidth(4.0f);

    for (int i = 0; i < shapes.size(); i++)
    {
        glBegin(GL_LINE_STRIP);

        for (int j = 0; j < shapes[i].size(); j++)
        {
            float x =
                offsetX +
                (shapes[i][j].x - minX) * scale;

            float y =
                offsetY +
                (shapes[i][j].y - minY) * scale;

            glVertex2f(x, y);
        }

        glEnd();
    }

    glFlush();
}

void display()
{
    draw_dino();
}

int main(int argc, char** argv)
{
    ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(ScreenWidth, ScreenHeight);
    glutCreateWindow("Qazi Muhammad Ahad (CT-24264)");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, ScreenWidth, 0.0, ScreenHeight, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}