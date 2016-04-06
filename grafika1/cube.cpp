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

void colorful_cube(char color_scheme){
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
    
    
    if(color_scheme == 'r'){
        
        /*  Cube colors */
        GLfloat shade1[4]       = { (GLfloat) 230/255, (GLfloat) 0/255, (GLfloat) 0/255, 1.0};
        GLfloat shade2[4]       = { (GLfloat) 229/255, (GLfloat) 38/255, (GLfloat) 23/255, 1.0};
        GLfloat shade3[4]       = { (GLfloat) 228/255, (GLfloat) 63/255, (GLfloat) 41/255, 1.0};
        GLfloat shade4[4]       = { (GLfloat) 228/255, (GLfloat) 86/255, (GLfloat) 60/255, 1.0};
        GLfloat shade5[4]       = { (GLfloat) 227/255, (GLfloat) 111/255, (GLfloat) 83/255, 1.0};
        GLfloat shade6[4]       = { (GLfloat) 227/255, (GLfloat) 135/255, (GLfloat) 108/255, 1.0};
        
        /* Draw Cubes */
        draw_square(vertA, vertB, vertC, vertD, shade1);
        draw_square(vertF, vertE, vertH, vertG, shade6);
        draw_square(vertE, vertA, vertD, vertH, shade2);
        draw_square(vertB, vertF, vertG, vertC, shade5);
        draw_square(vertE, vertF, vertB, vertA, shade3);
        draw_square(vertD, vertC, vertG, vertH, shade4);
        
    } else if(color_scheme == 'g'){
        
        GLfloat shade1[4]       = { (GLfloat) 0/255, (GLfloat) 230/255, (GLfloat) 0/255, 1.0};
        GLfloat shade2[4]       = { (GLfloat) 38/255, (GLfloat) 229/255, (GLfloat) 23/255, 1.0};
        GLfloat shade3[4]       = { (GLfloat) 63/255, (GLfloat) 228/255, (GLfloat) 41/255, 1.0};
        GLfloat shade4[4]       = { (GLfloat) 86/255, (GLfloat) 228/255, (GLfloat) 60/255, 1.0};
        GLfloat shade5[4]       = { (GLfloat) 111/255, (GLfloat) 227/255, (GLfloat) 83/255, 1.0};
        GLfloat shade6[4]       = { (GLfloat) 135/255, (GLfloat) 227/255, (GLfloat) 108/255, 1.0};
        
        /* Draw Cubes */
        draw_square(vertA, vertB, vertC, vertD, shade1);
        draw_square(vertF, vertE, vertH, vertG, shade6);
        draw_square(vertE, vertA, vertD, vertH, shade2);
        draw_square(vertB, vertF, vertG, vertC, shade5);
        draw_square(vertE, vertF, vertB, vertA, shade3);
        draw_square(vertD, vertC, vertG, vertH, shade4);
        
    } else if(color_scheme == 'b'){
        
        GLfloat shade1[4]       = { (GLfloat) 0.0, (GLfloat) 0/255, (GLfloat) 230/255, 1.0};
        GLfloat shade2[4]       = { (GLfloat) 0.0, (GLfloat) 38/255, (GLfloat) 229/255, 1.0};
        GLfloat shade3[4]       = { (GLfloat) 0.0, (GLfloat) 63/255, (GLfloat) 228/255, 1.0};
        GLfloat shade4[4]       = { (GLfloat) 0.0, (GLfloat) 86/255, (GLfloat) 228/255, 1.0};
        GLfloat shade5[4]       = { (GLfloat) 0.0, (GLfloat) 111/255, (GLfloat) 227/255, 1.0};
        GLfloat shade6[4]       = { (GLfloat) 0.0, (GLfloat) 135/255, (GLfloat) 227/255, 1.0};
        
        /* Draw Cubes */
        draw_square(vertA, vertB, vertC, vertD, shade1);
        draw_square(vertF, vertE, vertH, vertG, shade6);
        draw_square(vertE, vertA, vertD, vertH, shade2);
        draw_square(vertB, vertF, vertG, vertC, shade5);
        draw_square(vertE, vertF, vertB, vertA, shade3);
        draw_square(vertD, vertC, vertG, vertH, shade4);
        
    }
    
}

int main(int argc, const char * argv[]) {
    int choice;
    char color_scheme = '\0';
    std::cout<<"Please Choose The Program You Want"<<std::endl;
    std::cout<<"1. Hello Triangle"<<std::endl;
    std::cout<<"2. Colorful Cube"<<std::endl;
    std::cin>>choice;
    if(choice == 2){
        std::cout<<"Choose your scheme (r/g/b)"<<std::endl;
        std::cin>>color_scheme;
    }
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
                colorful_cube(color_scheme);
            }
        
            glfwSwapBuffers(win);
            glfwPollEvents();
        }
    
        glfwTerminate();
        exit(EXIT_SUCCESS);
    
    return 0;
}
