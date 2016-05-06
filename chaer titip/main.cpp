//
// This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
//
// If you've found this code useful, please let me know.
//
// Visit me at www.demonews.com/hosted/nehe
// (email Richard Campbell at ulmont@bellsouth.net)
//
#ifdef __APPLE__
//#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h> // Header File For The GLUT Library
#include <OpenGL/gl.h>  // Header File For The OpenGL32 Library
#include <OpenGL/glu.h> // Header File For The GLu32 Library
#else
#include <GL/glut.h> // Header File For The GLUT Library
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#endif

#include <unistd.h>     // Header File For sleeping.
#include <cstdio>
#include <stack>
#include <cstring>
#include <map>

using namespace std;

/*** BEGIN RUBIK.H ***/

/* How smooth the animation of rotation. makin kecil, putarannya makin halus. ANGLE in degree */
float ANGLE = 10;
const int inf = -1e9;

struct Color {
    Color() : r(0), g(0), b(0) {}
    Color(float r, float g, float b) : r(r), g(g), b(b) {}
    Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}
    void operator=(const Color& c) {
        r = c.r; g = c.g; b = c.b;
    }
    float r, g, b;
};

const Color RED     = Color(1, 0, 0);
const Color BLUE    = Color(0, 0, 1);
const Color WHITE   = Color(1, 1, 1);
const Color YELLOW  = Color(1, 1, 0);
const Color ORANGE  = Color(1, 0.5, 0);
const Color GREEN   = Color(0, 1, 0);
const Color BLACK   = Color(0, 0, 0);

/* Constant for side */
float c[54][3];  // bottom left
float d[54][3];  // bottom right
float p[54][3];  // top right
float q[54][3];  // top left

/* Constant for sceleton */
float ci[54][3];  // bottom left
float di[54][3];  // bottom right
float pi[54][3];  // top right
float qi[54][3];  // top left

Color a[54];

float sumbu[3], pusat[3];
bool isRotated[54];
float sudut;

map<unsigned char, unsigned char> vs;

void pairing(unsigned char e, unsigned char f) {
    vs[e] = f;
    vs[f] = e;
}

void bind(unsigned char e, unsigned char f) {
    pairing(e, f);
    pairing(e - 'a' + 'A', f - 'a' + 'A');
}

void rubik_init() {
    bind('a', 's');
    bind('d', 'f');
    bind('c', 'v');
    bind('y', 'u');
    bind('h', 'j');
    bind('k', 'l');
    pairing(']', '\'');
    pairing('.', '/');
    pairing('p', ';');
    pairing('P', ';');
    
    memset(sumbu, 0, sizeof(sumbu));
    memset(isRotated, 0, sizeof(isRotated));
    int pt = 0;
    
    // face
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < 3; i++) {
            c[pt][0] = i + 0.1; c[pt][1] = j + 0.1; c[pt][2] = 0;
            d[pt][0] = i + 0.9; d[pt][1] = j + 0.1; d[pt][2] = 0;
            p[pt][0] = i + 0.9; p[pt][1] = j + 0.9; p[pt][2] = 0;
            q[pt][0] = i + 0.1; q[pt][1] = j + 0.9; q[pt][2] = 0;
            a[pt] = RED;
            ci[pt][0] = i + 0; ci[pt][1] = j + 0; ci[pt][2] = -0.1;
            di[pt][0] = i + 1; di[pt][1] = j + 0; di[pt][2] = -0.1;
            pi[pt][0] = i + 1; pi[pt][1] = j + 1; pi[pt][2] = -0.1;
            qi[pt][0] = i + 0; qi[pt][1] = j + 1; qi[pt][2] = -0.1;
            pt++;
        }
    }
    
    // right
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < 3; i++) {
            c[pt][0] = 3; c[pt][1] = j + 0.1; c[pt][2] = -i - 0.1;
            d[pt][0] = 3; d[pt][1] = j + 0.1; d[pt][2] = -i - 0.9;
            p[pt][0] = 3; p[pt][1] = j + 0.9; p[pt][2] = -i - 0.9;
            q[pt][0] = 3; q[pt][1] = j + 0.9; q[pt][2] = -i - 0.1;
            a[pt] = BLUE;
            ci[pt][0] = 2.9; ci[pt][1] = j + 0; ci[pt][2] = -i;
            di[pt][0] = 2.9; di[pt][1] = j + 0; di[pt][2] = -i - 1;
            pi[pt][0] = 2.9; pi[pt][1] = j + 1; pi[pt][2] = -i - 1;
            qi[pt][0] = 2.9; qi[pt][1] = j + 1; qi[pt][2] = -i;
            pt++;
        }
    }
    
    // top
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < 3; i++) {
            c[pt][0] = i + 0.1; c[pt][1] = 3; c[pt][2] = -j - 0.1;
            d[pt][0] = i + 0.9; d[pt][1] = 3; d[pt][2] = -j - 0.1;
            p[pt][0] = i + 0.9; p[pt][1] = 3; p[pt][2] = -j - 0.9;
            q[pt][0] = i + 0.1; q[pt][1] = 3; q[pt][2] = -j - 0.9;
            a[pt] = WHITE;
            ci[pt][0] = i + 0; ci[pt][1] = 2.9; ci[pt][2] = -j;
            di[pt][0] = i + 1; di[pt][1] = 2.9; di[pt][2] = -j;
            pi[pt][0] = i + 1; pi[pt][1] = 2.9; pi[pt][2] = -j - 1;
            qi[pt][0] = i + 0; qi[pt][1] = 2.9; qi[pt][2] = -j - 1;
            pt++;
        }
    }
    
    // back
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < 3; i++) {
            c[pt][0] = i + 0.1; c[pt][1] = j + 0.1; c[pt][2] = -3;
            d[pt][0] = i + 0.9; d[pt][1] = j + 0.1; d[pt][2] = -3;
            p[pt][0] = i + 0.9; p[pt][1] = j + 0.9; p[pt][2] = -3;
            q[pt][0] = i + 0.1; q[pt][1] = j + 0.9; q[pt][2] = -3;
            a[pt] = ORANGE;
            ci[pt][0] = i + 0; ci[pt][1] = j + 0; ci[pt][2] = -2.9;
            di[pt][0] = i + 1; di[pt][1] = j + 0; di[pt][2] = -2.9;
            pi[pt][0] = i + 1; pi[pt][1] = j + 1; pi[pt][2] = -2.9;
            qi[pt][0] = i + 0; qi[pt][1] = j + 1; qi[pt][2] = -2.9;
            pt++;
        }
    }
    
    // left
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < 3; i++) {
            c[pt][0] = 0; c[pt][1] = j + 0.1; c[pt][2] = -i - 0.1;
            d[pt][0] = 0; d[pt][1] = j + 0.1; d[pt][2] = -i - 0.9;
            p[pt][0] = 0; p[pt][1] = j + 0.9; p[pt][2] = -i - 0.9;
            q[pt][0] = 0; q[pt][1] = j + 0.9; q[pt][2] = -i - 0.1;
            a[pt] = GREEN;
            ci[pt][0] = 0.1; ci[pt][1] = j + 0; ci[pt][2] = -i;
            di[pt][0] = 0.1; di[pt][1] = j + 0; di[pt][2] = -i - 1;
            pi[pt][0] = 0.1; pi[pt][1] = j + 1; pi[pt][2] = -i - 1;
            qi[pt][0] = 0.1; qi[pt][1] = j + 1; qi[pt][2] = -i;
            pt++;
        }
    }
    
    // bottom
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < 3; i++) {
            c[pt][0] = i + 0.1; c[pt][1] = 0; c[pt][2] = -j - 0.1;
            d[pt][0] = i + 0.9; d[pt][1] = 0; d[pt][2] = -j - 0.1;
            p[pt][0] = i + 0.9; p[pt][1] = 0; p[pt][2] = -j - 0.9;
            q[pt][0] = i + 0.1; q[pt][1] = 0; q[pt][2] = -j - 0.9;
            a[pt] = YELLOW;
            ci[pt][0] = i + 0; ci[pt][1] = 0.1; ci[pt][2] = -j;
            di[pt][0] = i + 1; di[pt][1] = 0.1; di[pt][2] = -j;
            pi[pt][0] = i + 1; pi[pt][1] = 0.1; pi[pt][2] = -j - 1;
            qi[pt][0] = i + 0; qi[pt][1] = 0.1; qi[pt][2] = -j - 1;
            pt++;
        }
    }
}

void reset() {
    memset(isRotated, 0, sizeof(isRotated));
    memset(sumbu, 0, sizeof(sumbu));
    sudut = 0;
}

void chain(int e, int f, int g, int h) {
    Color temp;
    temp = a[e]; a[e] = a[f]; a[f] = a[g]; a[g] = a[h]; a[h] = temp;
}

void R_before() {
    for(int i = 9; i <= 17; i++) {
        isRotated[i] = 1;
    }
    isRotated[2] = isRotated[5] = isRotated[8] = 1;
    isRotated[29] = isRotated[32] = isRotated[35] = 1;
    isRotated[20] = isRotated[23] = isRotated[26] = 1;
    isRotated[47] = isRotated[50] = isRotated[53] = 1;
    pusat[0] = 2.5; pusat[1] = 1.5; pusat[2] = -1.5;
    sumbu[0] = 1; sumbu[1] = 0; sumbu[2] = 0;
}

void R_after() {
    chain(9, 15, 17, 11);
    chain(10, 12, 16, 14);
    chain(2, 20, 35, 53);
    chain(5, 23, 32, 50);
    chain(8, 26, 29, 47);
    reset();
}

void L_before() {
    for(int i = 36; i <= 44; i++) {
        isRotated[i] = 1;
    }
    isRotated[0] = isRotated[3] = isRotated[6] = 1;
    isRotated[18] = isRotated[21] = isRotated[24] = 1;
    isRotated[27] = isRotated[30] = isRotated[33] = 1;
    isRotated[45] = isRotated[48] = isRotated[51] = 1;
    pusat[0] = 0; pusat[1] = 1.5; pusat[2] = -1.5;
    sumbu[0] = 1; sumbu[1] = 0; sumbu[2] = 0;
}

void L_after() {
    chain(9+27, 15+27, 17+27, 11+27);
    chain(10+27, 12+27, 16+27, 14+27);
    chain(0, 18, 33, 51);
    chain(3, 21, 30, 48);
    chain(6, 24, 27, 45);
    reset();
}

void U_before() {
    for(int i = 18; i <= 26; i++) {
        isRotated[i] = 1;
    }
    isRotated[6] = isRotated[7] = isRotated[8] = 1;
    isRotated[15] = isRotated[16] = isRotated[17] = 1;
    isRotated[33] = isRotated[34] = isRotated[35] = 1;
    isRotated[42] = isRotated[43] = isRotated[44] = 1;
    pusat[0] = 1.5; pusat[1] = 2.5; pusat[2] = -1.5;
    sumbu[0] = 0; sumbu[1] = 1; sumbu[2] = 0;
}

void U_after() {
    chain(26, 20, 18, 24);
    chain(23, 19, 21, 25);
    chain(17, 8, 42, 33);
    chain(16, 7, 43, 34);
    chain(15, 6, 44, 35);
    reset();
}

void D_before() {
    for(int i = 18+27; i <= 26+27; i++) {
        isRotated[i] = 1;
    }
    isRotated[0] = isRotated[1] = isRotated[2] = 1;
    isRotated[9] = isRotated[10] = isRotated[11] = 1;
    isRotated[27] = isRotated[28] = isRotated[29] = 1;
    isRotated[36] = isRotated[37] = isRotated[38] = 1;
    pusat[0] = 1.5; pusat[1] = 0.5; pusat[2] = -1.5;
    sumbu[0] = 0; sumbu[1] = 1; sumbu[2] = 0;
}

void D_after() {
    chain(26+27, 20+27, 18+27, 24+27);
    chain(23+27, 19+27, 21+27, 25+27);
    chain(11, 2, 36, 27);
    chain(10, 1, 37, 28);
    chain(9, 0, 38, 29);
    reset();
}

void F_before() {
    for(int i = 0; i <= 8; i++) {
        isRotated[i] = 1;
    }
    isRotated[9] = isRotated[12] = isRotated[15] = 1;
    isRotated[18] = isRotated[19] = isRotated[20] = 1;
    isRotated[36] = isRotated[39] = isRotated[42] = 1;
    isRotated[45] = isRotated[46] = isRotated[47] = 1;
    pusat[0] = 1.5; pusat[1] = 1.5; pusat[2] = -0.5;
    sumbu[0] = 0; sumbu[1] = 0; sumbu[2] = 1;
}

void F_after() {
    chain(6, 8, 2, 0);
    chain(7, 5, 1, 3);
    chain(18, 15, 47, 36);
    chain(19, 12, 46, 39);
    chain(20, 9, 45, 42);
    reset();
}

void B_before() {
    for(int i = 0+27; i <= 8+27; i++) {
        isRotated[i] = 1;
    }
    isRotated[11] = isRotated[14] = isRotated[17] = 1;
    isRotated[24] = isRotated[25] = isRotated[26] = 1;
    isRotated[38] = isRotated[41] = isRotated[44] = 1;
    isRotated[51] = isRotated[52] = isRotated[53] = 1;
    pusat[0] = 1.5; pusat[1] = 1.5; pusat[2] = -2.5;
    sumbu[0] = 0; sumbu[1] = 0; sumbu[2] = 1;
}

void B_after() {
    chain(6+27, 8+27, 2+27, 0+27);
    chain(7+27, 5+27, 1+27, 3+27);
    chain(24, 17, 53, 38);
    chain(25, 14, 52, 41);
    chain(26, 11, 51, 44);
    reset();
}

void down_before() {
    for(int i = 0; i < 54; i++) isRotated[i] = 1;
    pusat[0] = 1.5; pusat[1] = 1.5; pusat[2] = -1.5;
    sumbu[0] = 1; sumbu[1] = 0; sumbu[2] = 0;
}

void down_after() {
    chain(9, 15, 17, 11);
    chain(12, 16, 14, 10);
    chain(9+27, 15+27, 17+27, 11+27);
    chain(12+27, 16+27, 14+27, 10+27);
    chain(0, 18, 6+27, 24+27);
    chain(1, 19, 7+27, 25+27);
    chain(2, 20, 8+27, 26+27);
    chain(3, 21, 3+27, 21+27);
    chain(4, 22, 4+27, 22+27);
    chain(5, 23, 5+27, 23+27);
    chain(6, 24, 0+27, 18+27);
    chain(7, 25, 1+27, 19+27);
    chain(8, 26, 2+27, 20+27);
    reset();
}

void right_before() {
    for(int i = 0; i < 54; i++) isRotated[i] = 1;
    pusat[0] = 1.5; pusat[1] = 1.5; pusat[2] = -1.5;
    sumbu[0] = 0; sumbu[1] = 1; sumbu[2] = 0;
}

void right_after() {
    chain(20, 18, 24, 26);
    chain(19, 21, 25, 23);
    chain(20+27, 18+27, 24+27, 26+27);
    chain(19+27, 21+27, 25+27, 23+27);
    chain(9, 0, 11+27, 2+27);
    chain(10, 1, 10+27, 1+27);
    chain(11, 2, 9+27, 0+27);
    chain(12, 3, 14+27, 5+27);
    chain(13, 4, 13+27, 4+27);
    chain(14, 5, 12+27, 3+27);
    chain(15, 6, 17+27, 8+27);
    chain(16, 7, 16+27, 7+27);
    chain(17, 8, 15+27, 6+27);
    reset();
}

void through_before() {
    for(int i = 0; i < 54; i++) isRotated[i] = 1;
    pusat[0] = 1.5; pusat[1] = 1.5; pusat[2] = -1.5;
    sumbu[0] = 0; sumbu[1] = 0; sumbu[2] = 1;
}

void through_after() {
    chain(6, 8, 2, 0);
    chain(7, 5, 1, 3);
    chain(6+27, 8+27, 2+27, 0+27);
    chain(7+27, 5+27, 1+27, 3+27);
    chain(18, 15, 20+27, 9+27);
    chain(19, 12, 19+27, 12+27);
    chain(20, 9, 18+27, 15+27);
    chain(21, 16, 23+27, 10+27);
    chain(22, 13, 22+27, 13+27);
    chain(23, 10, 21+27, 16+27);
    chain(24, 17, 26+27, 11+27);
    chain(25, 14, 25+27, 14+27);
    chain(26, 11, 24+27, 17+27);
    reset();
}

/*** END RUBIK.H ***/

/*** BEGIN RUBIK.C ***/



/*** END RUBIK.C ***/

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int window;

/* rotation angle for the triangle. */
float rtri = 0.0f;

/* rotation angle for the quadrilateral. */
float rquad = 0.0f;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
    
    glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
    if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
        Height=1;
    
    glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

/*** BEGIN RUBIK.C ***/

/* Draw the sceleton rubik (colored black), to avoid drawing rear of rubik */
void DrawRubikSceleton() {
    glColor3f(0.0f,0.0f,0.0f);
    
    glBegin(GL_POLYGON);              // start drawing a polygon
    glVertex3f( 0, 0, -0.1);    // Bottom Left
    glVertex3f( 3, 0, -0.1);    // Bottom Right
    glVertex3f( 3, 3, -0.1);    // Top Right
    glVertex3f( 0, 3, -0.1);    // Top Left
    glEnd();           // we're done with the polygon (smooth color interpolation)
    
    glBegin(GL_POLYGON);              // start drawing a polygon
    glVertex3f( 2.9, 0, 0);    // Bottom Left
    glVertex3f( 2.9, 0, -3);    // Bottom Right
    glVertex3f( 2.9, 3, -3);    // Top Right
    glVertex3f( 2.9, 3, 0);    // Top Left
    glEnd();           // we're done with the polygon (smooth color interpolation)
    
    glBegin(GL_POLYGON);              // start drawing a polygon
    glVertex3f( 0, 2.9, 0);    // Bottom Left
    glVertex3f( 3, 2.9, 0);    // Bottom Right
    glVertex3f( 3, 2.9, -3);    // Top Right
    glVertex3f( 0, 2.9, -3);    // Top Left
    glEnd();           // we're done with the polygon (smooth color interpolation)
}

/* The main drawing function. */
void DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear The Screen And The Depth Buffer
    
    glLoadIdentity();       // Reset The View
    glTranslatef(0.0f,0.0f,-6.0f);   // Move Left 1.5 Units And Into The Screen 6.0
    gluLookAt(  2, 2, -1,
              0, 0, -3,
              0, 1, 0);
    
    glTranslatef(pusat[0], pusat[1], pusat[2]);
    glRotatef(sudut, sumbu[0], sumbu[1], sumbu[2]);
    glTranslatef(-pusat[0], -pusat[1], -pusat[2]);
    for(int i = 0; i < 54; i++) {
        if(isRotated[i]) {
            glBegin(GL_POLYGON);
            glColor3f(a[i].r, a[i].g, a[i].b);
            glVertex3f(c[i][0], c[i][1], c[i][2]);
            glVertex3f(d[i][0], d[i][1], d[i][2]);
            glVertex3f(p[i][0], p[i][1], p[i][2]);
            glVertex3f(q[i][0], q[i][1], q[i][2]);
            glEnd();
            
            glBegin(GL_POLYGON);
            glColor3f(BLACK.r, BLACK.g, BLACK.b);
            glVertex3f(ci[i][0], ci[i][1], ci[i][2]);
            glVertex3f(di[i][0], di[i][1], di[i][2]);
            glVertex3f(pi[i][0], pi[i][1], pi[i][2]);
            glVertex3f(qi[i][0], qi[i][1], qi[i][2]);
            glEnd();
        }
    }
    
    glLoadIdentity();       // Reset The View
    glTranslatef(0.0f,0.0f,-6.0f);   // Move Left 1.5 Units And Into The Screen 6.0
    gluLookAt(  2, 2, -1,
              0, 0, -3,
              0, 1, 0);
    
    for(int i = 0; i < 54; i++) {
        if(!isRotated[i]) {
            glBegin(GL_POLYGON);
            glColor3f(a[i].r, a[i].g, a[i].b);
            glVertex3f(c[i][0], c[i][1], c[i][2]);
            glVertex3f(d[i][0], d[i][1], d[i][2]);
            glVertex3f(p[i][0], p[i][1], p[i][2]);
            glVertex3f(q[i][0], q[i][1], q[i][2]);
            glEnd();
            
            glBegin(GL_POLYGON);
            glColor3f(BLACK.r, BLACK.g, BLACK.b);
            glVertex3f(ci[i][0], ci[i][1], ci[i][2]);
            glVertex3f(di[i][0], di[i][1], di[i][2]);
            glVertex3f(pi[i][0], pi[i][1], pi[i][2]);
            glVertex3f(qi[i][0], qi[i][1], qi[i][2]);
            glEnd();
        }
    }
    
    // swap the buffers to display, since double buffering is used.
    glutSwapBuffers();
}

stack<unsigned char> st;

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y)
{
    /* sleep to avoid thrashing this procedure */
    usleep(100);
    
    if(key == 'K' || key == 'k') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        R_before();
        for(int i = 0; i < cnt; i++) {
            sudut += ANGLE;
            DrawGLScene();
        }
        R_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'L' || key == 'l') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        R_before();
        for(int i = 0; i < cnt; i++) {
            sudut -= ANGLE;
            DrawGLScene();
        }
        R_after();
        R_after();
        R_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'A' || key == 'a') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        L_before();
        for(int i = 0; i < cnt; i++) {
            sudut += ANGLE;
            DrawGLScene();
        }
        L_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'S' || key == 's') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        L_before();
        for(int i = 0; i < cnt; i++) {
            sudut -= ANGLE;
            DrawGLScene();
        }
        L_after();
        L_after();
        L_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'Y' || key == 'y') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        U_before();
        for(int i = 0; i < cnt; i++) {
            sudut += ANGLE;
            DrawGLScene();
        }
        U_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'U' || key == 'u') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        U_before();
        for(int i = 0; i < cnt; i++) {
            sudut -= ANGLE;
            DrawGLScene();
        }
        U_after();
        U_after();
        U_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'C' || key == 'c') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        D_before();
        for(int i = 0; i < cnt; i++) {
            sudut += ANGLE;
            DrawGLScene();
        }
        D_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'V' || key == 'v') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        D_before();
        for(int i = 0; i < cnt; i++) {
            sudut -= ANGLE;
            DrawGLScene();
        }
        D_after();
        D_after();
        D_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'D' || key == 'd') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        F_before();
        for(int i = 0; i < cnt; i++) {
            sudut += ANGLE;
            DrawGLScene();
        }
        F_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'F' || key == 'f') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        F_before();
        for(int i = 0; i < cnt; i++) {
            sudut -= ANGLE;
            DrawGLScene();
        }
        F_after();
        F_after();
        F_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'H' || key == 'h') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        B_before();
        for(int i = 0; i < cnt; i++) {
            sudut += ANGLE;
            DrawGLScene();
        }
        B_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'J' || key == 'j') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        B_before();
        for(int i = 0; i < cnt; i++) {
            sudut -= ANGLE;
            DrawGLScene();
        }
        B_after();
        B_after();
        B_after();
        if(y != inf) st.push(key);
        
    } else if(key == '\'') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        down_before();
        for(int i = 0; i < cnt; i++) {
            sudut += ANGLE;
            DrawGLScene();
        }
        down_after();
        if(y != inf) st.push(key);
        
    } else if(key == ']') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        down_before();
        for(int i = 0; i < cnt; i++) {
            sudut -= ANGLE;
            DrawGLScene();
        }
        down_after();
        down_after();
        down_after();
        if(y != inf) st.push(key);
        
    } else if(key == '/') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        right_before();
        for(int i = 0; i < cnt; i++) {
            sudut += ANGLE;
            DrawGLScene();
        }
        right_after();
        if(y != inf) st.push(key);
        
    } else if(key == '.') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        right_before();
        for(int i = 0; i < cnt; i++) {
            sudut -= ANGLE;
            DrawGLScene();
        }
        right_after();
        right_after();
        right_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'p' || key == 'P') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        through_before();
        for(int i = 0; i < cnt; i++) {
            sudut += ANGLE;
            DrawGLScene();
        }
        through_after();
        if(y != inf) st.push(key);
        
    } else if(key == ';') {
        int cnt = (int)(90.0 / ANGLE + 0.5);
        through_before();
        for(int i = 0; i < cnt; i++) {
            sudut -= ANGLE;
            DrawGLScene();
        }
        through_after();
        through_after();
        through_after();
        if(y != inf) st.push(key);
        
    } else if(key == 'z' || key == 'Z') {
        float temp = ANGLE;
        ANGLE = 30;
        while(!st.empty()) {
            unsigned char now = st.top();
            st.pop();
            keyPressed(vs[now], inf, inf);
        }
        ANGLE = temp;
        
    }
    
    /* If escape is pressed, kill everything. */
    if (key == ESCAPE) 
    { 
        /* shut down our window */
        glutDestroyWindow(window); 
        
        /* exit the program...normal termination. */
        //exit(0);
    } 
}

/*** END RUBIK.C ***/


/*** BEGIN OLD ***/

/* The main drawing function. */
/*
void DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
    
    glLoadIdentity();				// Reset The View
    // gluLookAt( 0.0, 10.0f, -5.5,
    // 0.0f, 0.0f, -6.0,
    // 0.0f, 1.0f, 0.0f);
    glTranslatef(-1.5f,0.0f,-6.0f);		// Move Left 1.5 Units And Into The Screen 6.0
    
    glRotatef(rtri,0.0f,1.0f,0.0f);		// Rotate The Triangle On The Y axis
    // draw a triangle (in smooth coloring mode)
    glBegin(GL_POLYGON);				// start drawing a polygon
    glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
    glVertex3f( 0.0f, 1.0f, 0.0f);		// Top
    glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
    glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
    glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
    glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
    glEnd();					// we're done with the polygon (smooth color interpolation)
    
    glLoadIdentity();				// make sure we're no longer rotated.
    glTranslatef(1.5f,0.0f, -6.0f);		// Move Right 3 Units, and back into the screen 6.0
    glTranslatef(0.0f,-1.0f, 0.0f);
    
    glRotatef(rquad,1.0f,0.0f,0.0f);		// Rotate The Quad On The X axis
    glTranslatef(0.0f,1.0f, 0.0f);
    // draw a square (quadrilateral)
    glColor3f(0.5f,0.5f,1.0f);			// set color to a blue shade.
    glBegin(GL_QUADS);				// start drawing a polygon (4 sided)
    glVertex3f(-1.0f, 1.0f, 0.0f);		// Top Left
    glVertex3f( 1.0f, 1.0f, 0.0f);		// Top Right
    glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
    glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
    glEnd();					// done with the polygon
    
    rtri+=5.0f;					// Increase The Rotation Variable For The Triangle
    rquad+=5.0f;					// Decrease The Rotation Variable For The Quad
    
    // swap the buffers to display, since double buffering is used.
    glutSwapBuffers();
}*/

/* The function called whenever a key is pressed. */

//void keyPressed(unsigned char key, int x, int y)
//{
    /* sleep to avoid thrashing this procedure */
    //usleep(100);
    
    /* If escape is pressed, kill everything. */
    //if (key == ESCAPE)
    //{
        /* shut down our window */
        //glutDestroyWindow(window);
        
        /* exit the program...normal termination. */
        //exit(0);           //TODO FIX
    //}
//}

/*** END OLD ***/

int main(int argc, char **argv)
{
    /* Initialize GLUT state - glut will take any command line arguments that pertain to it or
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
    glutInit(&argc, argv);
    
    /* Select type of Display mode:
     Double buffer
     RGBA color
     Alpha components supported
     Depth buffer */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    
    /* get a 640 x 480 window */
    glutInitWindowSize(640, 480);
    
    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(0, 0);
    
    /* Open a window */
    window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");
    
    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(&DrawGLScene);
    
    /* Go fullscreen.  This is as soon as possible. */
    //glutFullScreen();
    
    /* Even if there are no events, redraw our gl scene. */
    glutIdleFunc(&DrawGLScene);
    
    /* Register the function called when our window is resized. */
    glutReshapeFunc(&ReSizeGLScene);
    
    /* Register the function called when the keyboard is pressed. */
    glutKeyboardFunc(&keyPressed);
    
    /* Initialize our window. */
    InitGL(640, 480);
    
    /*** BEGIN RUBIK.C ***/
    
    /* Initialize rubik */
    rubik_init();
    
    /*** END RUBIK.C ***/
    
    /* Start Event Processing Engine */  
    glutMainLoop();  
    
    return 1;
}
