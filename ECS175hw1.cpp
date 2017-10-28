//
//  main.cpp
//  ECS175Assigment1
//
//  Created by Lisadapu on 1/11/16.
//  Copyright © 2016 Lisadapu. All rights reserved.
//
#include <GL/glut.h>  // for csif
#include <GL/glu.h>
//#include <OpenGL/gl.h> // for Xcode
//#include <OpenGL/glu.h>
//#include <GLUT/glut.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

char *pixel;
int width = 400, length = 400;

void init (void)
{
    glClearColor (1.0, 1.0, 0.0, 1.0);  // Set display-window color to white.
    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void setPixel(char *PB, int x, int y, int r, int g, int b)
{
    PB[3*(y*width+x)+0] = r;
    PB[3*(y*width+x)+1] = g;
    PB[3*(y*width+x)+2] = b;
    glRasterPos2i(x, y);
    glDrawPixels(5, 5, GL_RGB, GL_UNSIGNED_INT, PB);
}

void lineBar(void){
    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.
    
    int x0=0, y0=0, xEnd=0, yEnd=0;
    for(int i=0;i<4;i++){
        if(i==0)
            x0 = 35, y0 = 40, xEnd = 85,yEnd = 100;
        else if(i==1)
            x0 = 35, y0 = 100, xEnd = 85,yEnd = 40;
        else if(i==2)
            x0 = 105, y0 = 40, xEnd = 105,yEnd = 100;
        else if(i==3)
            x0 = 105, y0 = 40, xEnd = 155,yEnd = 40;
        
        int dx = abs(xEnd - x0);
        int dy = abs(yEnd - y0);
        int x,y;
        int twoDy = 2 * dy;
        int twoDx = 2 * dx;
        int twoDyMiDx = 2 * (dy - dx);
        int twoDxMiDy = 2 * (dx - dy);
        int p = twoDy - dx;
        int m;
        int iDy = (yEnd - y0) > 0 ? 1:-1;
        
        if(dy == 0)
            m = 0;
        else if(dx < dy){
            if(iDy > 0)   // angle > 45
                m = 2;
            else          // angle < -45
                m = -2;
        }
        else if(dx == dy){
            if(iDy>0)   // angle = 45
                m = 1;
            else        // angle = -45
               m = -1;
        }
        else if(dy < dx){
            if(iDy>0)   // 0 < angle < 45
                m = 0.5;
            else        // -45 < angle < 0
                m = -0.5;
        }
        
        if(x0 > xEnd) // to know which point to use to start the line
        {
            x = xEnd;
            y = yEnd;
            xEnd = x0;
        }
        else{
            x = x0;
            y = y0;
        }
        setPixel(pixel, x, y, 255, 0, 10);

        //==================== |m| = 1, angle = 45====================
        if(abs(m) == 1){
            while(x < xEnd) // to decide which pixel should start at
            {
                x++;
                y++;
                setPixel(pixel,x, y, 0, 200, 50);
            }
        }
        //==================== m < -1, angle < -45====================
        else if(m < -1)
        {
            while(y > yEnd) // to decide which pixel should start at
            {
                x++;
                if(p < 0)   //p = 2*dy - dx,
                    p += twoDy; //p = p + twoDy
                else
                {
                    y--;
                    p += twoDyMiDx; //p=p+t
                }
                setPixel(pixel,x, y, 255, 0, 0); // "\"
            }
        }
        //==================== -1 < m < 0, -45 < angle < 0====================
        else if(m < 0)
        {
            while(x < xEnd)
            {
                x++;
                if(p < 0)   //p = 2*dy - dx,
                {
                    p += twoDy; //p = p + twoDy
                }
                else
                {
                    y++;
                    p += twoDyMiDx; //p=p+t
                }
                setPixel(pixel,x, y, 0, 100, 200);
            }
        }
        //==================== m = 0, angle = 0====================
        else if(m == 0){
            while(x < xEnd) // to decide which pixel should start at
            {
                x++;
                if(p < 0)   //p = 2*dx - dy,
                    p += twoDx; //p = p + 2dx
                else
                {
                    p += twoDxMiDy; // p = p + 2(dx-dy)
                }
                setPixel(pixel,x, y, 100, 0, 200);//"_"
            }
        }
        //==================== 0 < m < 1, 0 < angle < 45====================
        else if(m < 1){
            while(y < yEnd) // to decide which pixel should start at
            {
                y--;
                if(p < 0)   //p = 2*dx - dy,
                    p += twoDx; //p = p + 2dx
                else
                {
                    x++;
                    p += twoDxMiDy; // p = p + 2(dx-dy)
                }
                setPixel(pixel,x, y, 0, 0, 0);
            }
        }
        //==================== m > 1, angle > 45====================
        else if(m > 1){
            while(y < yEnd) // to decide which pixel should start at
            {
                y++;
                if(p < 0)   //p = 2*dx - dy,
                    p += twoDx; //p = p + 2dx
                else
                {
                    x++;
                    p += twoDxMiDy; // p = p + 2(dx-dy)
                }
                setPixel(pixel,x, y,200,200,200); // "/", "|"
            }
        }
        glFlush ( );
    }
}

int main(int argc,char** argv)
{
    pixel = new char[3*width*length];
    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (200, 200);   // Set top-left display-window position.
    glutInitWindowSize (width, length);      // Set display-window width and height.
    glutCreateWindow ("ECS 175 Assigtment 1"); // Create display window.
    init ( );                            // Execute initialization procedure.
    glutDisplayFunc (lineBar);       // Send graphics to display window.
    glutMainLoop ( );                    // Display everything and wait.
    return 0;
}
