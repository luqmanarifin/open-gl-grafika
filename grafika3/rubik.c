//
// Source : Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
// Visit me at www.demonews.com/hosted/nehe 
// (email Richard Campbell at ulmont@bellsouth.net)
//
// Modified by Luqman A. Siswanto
// Institut Teknologi Bandung
// email me at l.arifin.siswanto@gmail.com
// Rubik 3D OpenGL Simulator

#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h>     // Header File For sleeping.
#include <cstdio>
#include <stack>

#include "rubik.h"

using namespace std;

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int window; 

/* rotation angle for the triangle. */
float rtri = 0.0f;

/* rotation angle for the quadrilateral. */
float rquad = 0.0f;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)          // We call this right after our OpenGL window is created.
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // This Will Clear The Background Color To Black
  glClearDepth(1.0);        // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);       // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);      // Enables Depth Testing
  glShadeModel(GL_SMOOTH);      // Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();       // Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f); // Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)        // Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);    // Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}


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
    exit(0);                   
  } 
}

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
  window = glutCreateWindow("Luqman's Rubik 3D OpenGL");  

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
  
  /* Initialize rubik */
  rubik_init();

  /* Start Event Processing Engine */  
  glutMainLoop();  

  return 1;
}
