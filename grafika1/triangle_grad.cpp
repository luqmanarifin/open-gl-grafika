#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

const char* vertex_shader =
"#version 150\n"
"in vec3 vp;"
"void main () {"
"  gl_Position = vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 150\n"
"precision mediump float;"
"uniform vec2 resolution;"
"void main () {"
"	vec2 position = gl_FragCoord.xy;"
"	float red = sin(position.y/20);"
"	float green = cos(position.y/20);"
"	float blue = tan(position.y/20);"
"	gl_FragColor = vec4(red, green, blue, 1.0);"
"}";


void printMachineSpecification() {
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);
}

void createShader(GLuint *shader_programme, const char* frsh, const char* vrsh) {
	GLuint vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vrsh, NULL);
	glCompileShader (vs);

	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &frsh, NULL);
	glCompileShader (fs);

	*shader_programme = glCreateProgram ();
	glAttachShader (*shader_programme, fs);
	glAttachShader (*shader_programme, vs);
	glLinkProgram (*shader_programme);
}

void createTriangle(GLuint *vao, float* points) {
	GLuint vbo = 0;
	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

	*vao = 0;
	glGenVertexArrays (1, vao);
	glBindVertexArray (*vao);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void drawTriangle(GLuint vao, GLuint shader_programme) {
	glUseProgram (shader_programme);
	glBindVertexArray (vao);
	glDrawArrays (GL_TRIANGLES, 0, 3);	
}

int main(int argc, char** argv) {
	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit ()) {
	fprintf (stderr, "ERROR: could not start GLFW3\n");
	return 1;
	} 
    
	GLFWwindow* window = glfwCreateWindow (640, 480, "Hello Triangle", NULL, NULL);
	if (!window) {
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent (window);

	glewInit ();

	printMachineSpecification();

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
	glShadeModel(GL_SMOOTH);


	float points[] = {
	   0.0f,  1.0f,  0.0f,
	   1.0f, -1.0f,  0.0f,
	   -1.0f, -1.0f,  0.0f
	};

	GLuint vao;
	createTriangle(&vao, points);
	GLuint shader_programme;
	createShader(&shader_programme, fragment_shader, vertex_shader);

	while (!glfwWindowShouldClose (window)) {
		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawTriangle(vao, shader_programme);
		// update other events like input handling 
		glfwPollEvents ();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (window);
	}

	glfwTerminate();
    return 0;
}