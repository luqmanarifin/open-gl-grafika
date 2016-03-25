// Using GLEW Library for OpenGL
#include <GL/freeglut.h>

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    // Window Properties, Self-explanatory
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1024, 768);

    // Window Display Mode
    // GLUT_DOUBLE = Doubel Buffer (Smooth Animation)
    // GLUT_RGBA = Default. Colors.
    // GLUT_DEPTH = Depth buffer, still doesnt know what it doing
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

    // Create Window
    glutCreateWindow("Grafika 01");
    
    return 0;
}