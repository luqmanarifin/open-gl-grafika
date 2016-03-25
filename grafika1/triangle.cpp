// Using GLEW Library for OpenGL
#include <GL/freeglut.h>

void renderScene() {

	// Clering the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    // Window Properties, Self-explanatory
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);

    // Window Display Mode
    // GLUT_DOUBLE = Doubel Buffer (Smooth Animation)
    // GLUT_RGBA = Default. Colors.
    // GLUT_DEPTH = Depth buffer, still doesnt know what it doing
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

    // Create Window
    glutCreateWindow("Grafika 01");

    // Call function to render
    glutDisplayFunc(renderScene);

    // Keep the window open and ready to receive input
    glutMainLoop();
    
    return 0;
}