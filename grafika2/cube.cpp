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

/* tugas 1 */
void hello_triangle(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear background
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    
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

/* tugas 2a */
void draw_square(GLfloat * a, GLfloat * b, GLfloat * c, GLfloat * d, GLfloat * color){
    
    glRotated(0.05, 1, 0, 0);
    glRotated(0.05, 0, 1, 0);
    glRotated(0.05, 0, 0, 1);
    glBegin(GL_TRIANGLE_STRIP);
    {
        glColor4f(color[0], color[1], color[2], color[3]);
        glVertex4f(a[0], a[1], a[2], a[3]);
        glVertex4f(b[0], b[1], b[2], b[3]);
        glVertex4f(d[0], d[1], d[2], d[3]);
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

/* tugas 2b */
void serpienski_triangle_recursive_points(GLfloat * a, GLfloat * b, GLfloat * c, int num_iterative){
    
    
    if(num_iterative > 0){
        num_iterative--;
        glBegin(GL_LINE_LOOP);
        {
            glVertex4f(a[0], a[1], a[2], a[3]);
            glVertex4f(b[0], b[1], b[2], b[3]);
            glVertex4f(c[0], c[1], c[2], c[3]);
        }
        glEnd();
        
        if(num_iterative > 0){
            GLfloat vertAB[4] = { (GLfloat) (a[0]+b[0])/2, (GLfloat) (a[1]+b[1])/2, a[2], a[3]};
            GLfloat vertBC[4] = { (GLfloat) (b[0]+c[0])/2, (GLfloat) (b[1]+c[1])/2, b[2], b[3]};
            GLfloat vertCA[4] = { (GLfloat) (c[0]+a[0])/2, (GLfloat) (c[1]+a[1])/2, c[2], c[3]};
            
            serpienski_triangle_recursive_points(a, vertAB, vertCA, num_iterative);
            serpienski_triangle_recursive_points(vertAB, b, vertBC, num_iterative);
            serpienski_triangle_recursive_points(vertCA, vertBC, c, num_iterative);
        }
        
    }
    
}

void serpienski_triangle_points(int num_iterative){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear background
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST); do not uncomment
    
    /*  Triangle vertices */
    GLfloat vertA[4] = { 0.0, 0.5, 0.0, 1.0};
    GLfloat vertB[4] = {-0.5,-0.5, 0.0, 1.0};
    GLfloat vertC[4] = { 0.5,-0.5, 0.0, 1.0};
    
    serpienski_triangle_recursive_points(vertA, vertB, vertC, num_iterative);
}

/* tugas 2c */
void serpienski_triangle_recursive(GLfloat * a, GLfloat * b, GLfloat * c, GLfloat * color, int num_iterative, int count){
    
    
    if(count < num_iterative){
        count++;
        glBegin(GL_TRIANGLES);
        {
            glColor4f(color[0], color[1], color[2], color[3]);
            glVertex4f(a[0], a[1], a[2], a[3]);
            glVertex4f(b[0], b[1], b[2], b[3]);
            glVertex4f(c[0], c[1], c[2], c[3]);
            
        }
        glEnd();
        
        if (count < num_iterative){
        
            GLfloat vertAB[4] = { (GLfloat) (a[0]+b[0])/2, (GLfloat) (a[1]+b[1])/2, a[2], a[3]};
            GLfloat vertBC[4] = { (GLfloat) (b[0]+c[0])/2, (GLfloat) (b[1]+c[1])/2, b[2], b[3]};
            GLfloat vertCA[4] = { (GLfloat) (c[0]+a[0])/2, (GLfloat) (c[1]+a[1])/2, c[2], c[3]};
            
            GLfloat shade[4] = {
                (GLfloat) (color[0] - (GLfloat) 1/num_iterative),
                (GLfloat) (color[1] - (GLfloat) 1/num_iterative),
                (GLfloat) (color[2] - (GLfloat) 1/num_iterative),
                1.0};
            
            serpienski_triangle_recursive(a, vertAB, vertCA, shade, num_iterative, count);
            serpienski_triangle_recursive(vertAB, b, vertBC, shade, num_iterative, count);
            serpienski_triangle_recursive(vertCA, vertBC, c, shade, num_iterative, count);
            
        }
        
    }
    
}

void serpienski_triangle(int num_iterative){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear background
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST); do not uncomment
    
    /*  Triangle vertices */
    GLfloat vertA[4] = { 0.0, 0.5, 0.0, 1.0};
    GLfloat vertB[4] = {-0.5,-0.5, 0.0, 1.0};
    GLfloat vertC[4] = { 0.5,-0.5, 0.0, 1.0};
    
    /* Triangle color */
    GLfloat shade[4]       = { 1, 1, 1, 1.0};
    
    serpienski_triangle_recursive(vertA, vertB, vertC, shade, num_iterative, 0);
}


int main(int argc, const char * argv[]) {
    int choice;
    char color_scheme = '\0';
    int num_iterative = 0;
    std::cout<<"Please Choose The Program You Want"<<std::endl;
    std::cout<<"1. Hello Triangle"<<std::endl;
    std::cout<<"2. Colorful Cube"<<std::endl;
    std::cout<<"3. Serpienski Triangle Points"<<std::endl;
    std::cout<<"4. Serpienski Triangle"<<std::endl;
    std::cin>>choice;
    if(choice == 2){
        std::cout<<"Choose your scheme (r/g/b)"<<std::endl;
        std::cin>>color_scheme;
    }else if(choice == 3 || choice == 4){
        std::cout<<"How many iteratives?"<<std::endl;
        std::cin>>num_iterative;
    }
    
        GLFWwindow *win;
    
        if(!glfwInit()){
            return -1;
        }
    
        win = glfwCreateWindow(640, 480, "Tugas Grafika ", NULL, NULL);
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
            }else if(choice == 3){
                serpienski_triangle_points(num_iterative);
            }else if(choice == 4){
                serpienski_triangle(num_iterative);
            }
            glfwSwapBuffers(win);
            glfwPollEvents();
        }
        glfwTerminate();
        exit(EXIT_SUCCESS);
    
    return 0;
}
