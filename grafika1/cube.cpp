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

void draw_square(float ax, float ay, float az, float aw,
                 float bx, float by, float bz, float bw,
                 float cx, float cy, float cz, float cw,
                 float dx, float dy, float dz, float dw,
                 float color_r, float color_g, float color_b, float color_a){
    
    //glTranslatef(0.01, 0, 0);
    glRotated(0.1, 1, 0, 0);
    glRotated(0.1, 0, 1, 0);
    glRotated(0.1, 0, 0, 1);
    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(color_r, color_g, color_b, color_a);
        glVertex4f(ax, ay, az, aw);
        glColor4f(color_r, color_g, color_b, color_a);
        glVertex4f(bx, by, bz, bw);
        glColor4f(color_r, color_g, color_b, color_a);
        glVertex4f(dx, dy, dz, dw);
        glColor4f(color_r, color_g, color_b, color_a);
        glVertex4f(cx, cy, cz, cw);
    }
    glEnd();
    
}

void colorful_cube(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear background
    glClear(GL_COLOR_BUFFER_BIT);
    
    float vertex_positions[] = {
        -0.5,   -0.5,   0.5,    1.0,
        -0.5,   0.5,    0.5,    1.0,
        0.5,    0.5,    0.5,    1.0,
        0.5,    -0.5,   0.5,    1.0,
        -0.5,   -0.5,   -0.5,   1.0,
        -0.5,   0.5,    -0.5,   1.0,
        0.5,    0.5,    -0.5,   1.0,
        0.5,    -0.5,   -0.5,   1.0
    };
    
    float vertex_colors[] = {
        1.0,  0.0,  0.0,  1.0, //red
        1.0,  1.0,  0.0,  1.0, //yellow
        0.0,  1.0,  0.0,  1.0, //green
        0.0,  0.0,  1.0,  1.0, //blue
        1.0,  0.0,  1.0,  1.0, //magenta
        0.0,  1.0,  1.0,  1.0 //cyan
    };

    //draw squares
    draw_square( //0
        vertex_positions[1*4 + 0], vertex_positions[1*4 + 1], vertex_positions[1*4 + 2], vertex_positions[1*4 + 3],
        vertex_positions[0*4 + 0], vertex_positions[0*4 + 1], vertex_positions[0*4 + 2], vertex_positions[0*4 + 3],
        vertex_positions[3*4 + 0], vertex_positions[3*4 + 1], vertex_positions[3*4 + 2], vertex_positions[3*4 + 3],
        vertex_positions[2*4 + 0], vertex_positions[2*4 + 1], vertex_positions[2*4 + 2], vertex_positions[2*4 + 3],
        vertex_colors[0*4 + 0], vertex_colors[0*4 + 1], vertex_colors[0*4 + 2], vertex_colors[0*4 + 3]
    );
    draw_square( //1
        vertex_positions[2*4 + 0], vertex_positions[2*4 + 1], vertex_positions[2*4 + 2], vertex_positions[2*4 + 3],
        vertex_positions[3*4 + 0], vertex_positions[3*4 + 1], vertex_positions[3*4 + 2], vertex_positions[3*4 + 3],
        vertex_positions[7*4 + 0], vertex_positions[7*4 + 1], vertex_positions[7*4 + 2], vertex_positions[7*4 + 3],
        vertex_positions[6*4 + 0], vertex_positions[6*4 + 1], vertex_positions[6*4 + 2], vertex_positions[6*4 + 3],
        vertex_colors[1*4 + 0], vertex_colors[1*4 + 1], vertex_colors[1*4 + 2], vertex_colors[1*4 + 3]
    );
    draw_square( //2
        vertex_positions[3*4 + 0], vertex_positions[3*4 + 1], vertex_positions[3*4 + 2], vertex_positions[3*4 + 3],
        vertex_positions[0*4 + 0], vertex_positions[0*4 + 1], vertex_positions[0*4 + 2], vertex_positions[0*4 + 3],
        vertex_positions[4*4 + 0], vertex_positions[4*4 + 1], vertex_positions[4*4 + 2], vertex_positions[4*4 + 3],
        vertex_positions[7*4 + 0], vertex_positions[7*4 + 1], vertex_positions[7*4 + 2], vertex_positions[7*4 + 3],
        vertex_colors[2*4 + 0], vertex_colors[2*4 + 1], vertex_colors[2*4 + 2], vertex_colors[2*4 + 3]
    );
    draw_square( //3
        vertex_positions[6*4 + 0], vertex_positions[6*4 + 1], vertex_positions[6*4 + 2], vertex_positions[6*4 + 3],
        vertex_positions[5*4 + 0], vertex_positions[5*4 + 1], vertex_positions[5*4 + 2], vertex_positions[5*4 + 3],
        vertex_positions[1*4 + 0], vertex_positions[1*4 + 1], vertex_positions[1*4 + 2], vertex_positions[1*4 + 3],
        vertex_positions[2*4 + 0], vertex_positions[2*4 + 1], vertex_positions[2*4 + 2], vertex_positions[2*4 + 3],
        vertex_colors[3*4 + 0], vertex_colors[3*4 + 1], vertex_colors[3*4 + 2], vertex_colors[3*4 + 3]
    );
    draw_square( //4
        vertex_positions[4*4 + 0], vertex_positions[4*4 + 1], vertex_positions[4*4 + 2], vertex_positions[4*4 + 3],
        vertex_positions[5*4 + 0], vertex_positions[5*4 + 1], vertex_positions[5*4 + 2], vertex_positions[5*4 + 3],
        vertex_positions[6*4 + 0], vertex_positions[6*4 + 1], vertex_positions[6*4 + 2], vertex_positions[6*4 + 3],
        vertex_positions[7*4 + 0], vertex_positions[7*4 + 1], vertex_positions[7*4 + 2], vertex_positions[7*4 + 3],
        vertex_colors[4*4 + 0], vertex_colors[4*4 + 1], vertex_colors[4*4 + 2], vertex_colors[4*4 + 3]
    );
    draw_square( //5
        vertex_positions[5*4 + 0], vertex_positions[5*4 + 1], vertex_positions[5*4 + 2], vertex_positions[5*4 + 3],
        vertex_positions[4*4 + 0], vertex_positions[4*4 + 1], vertex_positions[4*4 + 2], vertex_positions[4*4 + 3],
        vertex_positions[0*4 + 0], vertex_positions[0*4 + 1], vertex_positions[0*4 + 2], vertex_positions[0*4 + 3],
        vertex_positions[1*4 + 0], vertex_positions[1*4 + 1], vertex_positions[1*4 + 2], vertex_positions[1*4 + 3],
        vertex_colors[5*4 + 0], vertex_colors[5*4 + 1], vertex_colors[5*4 + 2], vertex_colors[5*4 + 3]
    );

    
    
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
