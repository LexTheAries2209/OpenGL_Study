//
//  yongsizhongfangfahuaxian.cpp
//  OpenGL_Study
//
//  Created by 吴坤城 on 3/23/24.
//

#include <GLUT/glut.h>
#include <cmath>
#include <iostream>

// DDA算法
void drawLineDDA(int x0, int y0, int x1, int y1) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = x0;
    float y = y0;
    
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

// Bresenham算法
void drawLineBresenham(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
    glEnd();
}

// 中点画线法
void drawLineMidpoint(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
    glEnd();
}

// 逐点比较法
void drawLinePointByPoint(int x0, int y0, int x1, int y1) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    float y = y0;
    
    glBegin(GL_POINTS);
    for (int x = x0; x <= x1; x++) {
        glVertex2i(x, round(y));
        y += dy / dx;
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 设置直线颜色为白色
    glColor3f(1.0, 1.0, 1.0);

    // 调用DDA算法绘制第一条平行线
    drawLineDDA(10, 50, 200, 50);

    // 调用Bresenham算法绘制第二条平行线
    drawLineBresenham(10, 100, 200, 100);

    // 调用中点画线法绘制第三条平行线
    drawLineMidpoint(10, 150, 200, 150);

    // 调用逐点比较法绘制第四条平行线
    drawLinePointByPoint(10, 200, 200, 200);

    glFlush();
}

void init() {
    // 设置背景颜色为黑色
    glClearColor(0.0, 0.0, 0.0, 1.0);
    // 初始化视图为2D
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 300, 0.0, 300);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Parallel Lines");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
