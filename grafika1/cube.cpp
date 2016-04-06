//
//  main.cpp
//  BaseOpenGL
//
//  Created by Chairuni Aulia Nusapati on 4/5/16.
//  Copyright © 2016 Chairuni Aulia Nusapati. All rights reserved.
//

#include <iostream>
//GLEW
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>


void hello_triangle(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear background
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0, .5);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-.5, -.5);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(.5, -.5);
    }
    glEnd();
}

void draw_square(GLfloat * a, GLfloat * b, GLfloat * c, GLfloat * d, GLfloat * color){
    
    glRotated(0.05, 1, 0, 0);
    glRotated(0.05, 0, 1, 0);
    glRotated(0.05, 0, 0, 1);
    //glTranslatef(0.001, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(color[0], color[1], color[2], color[3]);
        glVertex4f(a[0], a[1], a[2], a[3]);
        glColor4f(color[0], color[1], color[2], color[3]);
        glVertex4f(b[0], b[1], b[2], b[3]);
        glColor4f(color[0], color[1], color[2], color[3]);
        glVertex4f(d[0], d[1], d[2], d[3]);
        glColor4f(color[0], color[1], color[2], color[3]);
        glVertex4f(c[0], c[1], c[2], c[3]);
    }
    glEnd();
}

void colorful_cube(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear background
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    /*  Cube vertices */
    GLfloat vertA[4] = { 0.5, 0.5, 0.5, 1.0};
    GLfloat vertB[4] = {-0.5, 0.5, 0.5, 1.0};
    GLfloat vertC[4] = {-0.5,-0.5, 0.5, 1.0};
    GLfloat vertD[4] = { 0.5,-0.5, 0.5, 1.0};
    GLfloat vertE[4] = { 0.5, 0.5,-0.5, 1.0};
    GLfloat vertF[4] = {-0.5, 0.5,-0.5, 1.0};
    GLfloat vertG[4] = {-0.5,-0.5,-0.5, 1.0};
    GLfloat vertH[4] = { 0.5,-0.5,-0.5, 1.0};
    
    /*  Cube colors */
    GLfloat yellow[4]       = { 1.0, 1.0, 0.0, 1.0};
    GLfloat red[4]          = { 1.0, 0.0, 0.0, 1.0};
    GLfloat green[4]        = { 0.0, 1.0, 0.0, 1.0};
    GLfloat blue[4]         = { 0.0, 0.0, 1.0, 1.0};
    GLfloat turquoise[4]    = { 0.0, 1.0, 1.0, 1.0};
    GLfloat pink[4]         = { 1.0, 0.0, 1.0, 1.0};

    /* Draw Cubes */
    draw_square(vertA, vertB, vertC, vertD, yellow);
    draw_square(vertF, vertE, vertH, vertG, red);
    draw_square(vertE, vertA, vertD, vertH, green);
    draw_square(vertB, vertF, vertG, vertC, blue);
    draw_square(vertE, vertF, vertB, vertA, turquoise);
    draw_square(vertD, vertC, vertG, vertH, pink);
    
    
}

int main(int argc, const char * argv[]) {
    int choice;
    std::cout<<"Please Choose The Program You Want"<<std::endl;
    std::cout<<"1. Hello Triangle"<<std::endl;
    std::cin>>choice;
    
        GLFWwindow *win;
    
        if(!glfwInit()){
            return -1;
        }
    
        win = glfwCreateWindow(640, 480, "OpenGL Base Project", NULL, NULL);
        if(!win){
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
    
        if(!glewInit()){
            return -1;
        }
    
        glfwMakeContextCurrent(win);
    
        while(!glfwWindowShouldClose(win)){
            if(choice == 1){
                hello_triangle();
            }else if(choice == 2){
                colorful_cube();
            }
        
            glfwSwapBuffers(win);
            glfwPollEvents();
        }
    
        glfwTerminate();
        exit(EXIT_SUCCESS);
    
    return 0;
}
