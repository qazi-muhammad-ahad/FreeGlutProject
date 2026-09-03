#include <GL/freeglut.h>
#include <cmath> // Required for sin() and cos()

// Define Pi for trigonometric calculations
const float PI = 3.14159265358979323846f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // GL_TRIANGLE_FAN is perfect for circles: it fans out from a center point
    glBegin(GL_TRIANGLE_FAN);

    // Center point of the circle (blended color)
    glColor3f(1.0f, 1.0f, 1.0f); // White center makes a beautiful radial glow
    glVertex2f(0.0f, 0.0f);

    float radius = 0.5f;      // Size of the circle
    int numSegments = 360;    // Number of triangles used to draw the circle (higher = smoother)

    // Loop through 360 degrees to place vertices around the center
    for (int i = 0; i <= numSegments; ++i)
    {
        // Calculate the current angle in radians
        float angle = i * (2.0f * PI / numSegments);

        // Generate rainbow colors dynamically based on the current angle
        // This splits the circle into Red, Green, and Blue spectrums smoothly
        float r = 0.5f * (cos(angle) + 1.0f);
        float g = 0.5f * (cos(angle - 2.0f * PI / 3.0f) + 1.0f);
        float b = 0.5f * (cos(angle - 4.0f * PI / 3.0f) + 1.0f);
        glColor3f(r, g, b);

        // Calculate and plot X and Y positions
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);

    glutCreateWindow("OpenGL + FreeGLUT - Rainbow Circle");

    glutDisplayFunc(display);

    // Set a clean black background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

    glutMainLoop();

    return 0;
}
