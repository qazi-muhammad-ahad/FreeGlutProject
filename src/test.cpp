#include <GL/freeglut.h>
#include <cmath> // Required for sin() and cos()

// Define Pi for trigonometric calculations
const float PI = 3.14159265358979323846f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Using GL_TRIANGLE_FAN is ideal for stars as all vertices connect back to a central point
    glBegin(GL_TRIANGLE_FAN);

    // Center point of the star (blended color)
    glColor3f(1.0f, 1.0f, 1.0f); // White center
    glVertex2f(0.0f, 0.0f);

    float rOuter = 0.5f; // Radius of the outer points (tips)
    float rInner = 0.2f; // Radius of the inner points (valleys)

    // Pre-defined rainbow colors for the 10 points of the star
    float colors[10][3] = {
        {1.0f, 0.0f, 0.0f}, // Red
        {1.0f, 0.5f, 0.0f}, // Orange
        {1.0f, 1.0f, 0.0f}, // Yellow
        {0.5f, 1.0f, 0.0f}, // Lime green
        {0.0f, 1.0f, 0.0f}, // Green
        {0.0f, 1.0f, 1.0f}, // Cyan
        {0.0f, 0.0f, 1.0f}, // Blue
        {0.5f, 0.0f, 1.0f}, // Purple
        {1.0f, 0.0f, 1.0f}, // Magenta
        {1.0f, 0.0f, 0.5f}  // Pink
    };

    // Loop 11 times to close the fan perfectly (10 points + repeating the first point)
    for (int i = 0; i <= 10; ++i)
    {
        // 5 outer points + 5 inner points = 10 points total. 
        // Each point is separated by 360 / 10 = 36 degrees (or PI / 5 radians).
        // Subtracting PI/2 rotates the star so the first tip points straight up.
        float angle = i * (PI / 5.0f) - (PI / 2.0f);
        
        // Alternate between outer radius and inner radius
        float r = (i % 2 == 0) ? rOuter : rInner;

        // Apply the rainbow color (wrap around using modulo for the 11th vertex)
        glColor3f(colors[i % 10][0], colors[i % 10][1], colors[i % 10][2]);

        // Calculate and plot X and Y positions
        float x = r * cos(angle);
        float y = r * sin(angle);
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

    glutCreateWindow("OpenGL + FreeGLUT - Rainbow Star");

    glutDisplayFunc(display);

    // Optional: Set a clean black background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

    glutMainLoop();

    return 0;
}
