//
//  diyizhouzuoye.cpp
//  OpenGL_Study
//
//  Created by 吴坤城 on 4/1/24.
//

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>
#include <ctime>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int currentScene = 0;

//绘制五角星
void drawStar() {
    const float pi = 3.1415926f;
    const float radius = 0.5f; // 星星的外圈半径
    const float innerRadius = radius * sin(18 * pi / 180) / sin(126 * pi / 180); // 星星的内圈半径
    
    glColor3f(1.0f, 1.0f, 1.0f); // 设置颜色为白色
    
    const float cx = 0.0f; // 星星的中心x坐标
    const float cy = 0.0f; // 星星的中心y坐标

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 5; ++i) {
        // 外部顶点
        float outerAngle = 2 * pi / 5 * i + pi / 2;
        glVertex2f(cx + radius * cos(outerAngle), cy + radius * sin(outerAngle));

        // 内部顶点
        float innerAngle = outerAngle + pi / 5;
        glVertex2f(cx + innerRadius * cos(innerAngle), cy + innerRadius * sin(innerAngle));
    }
    glEnd();
}

//绘制随机点
void drawRandomPoints(int count) {
    glPointSize(2); // 设置点的大小
    glColor3f(1.0f, 1.0f, 1.0f); // 设置点的颜色为白色
    glBegin(GL_POINTS);
    for (int i = 0; i < count; ++i) {
        float x = (2.0f * (float)rand() / RAND_MAX) - 1.0f;
        float y = (2.0f * (float)rand() / RAND_MAX) - 1.0f;
        glVertex2f(x, y);
    }
    glEnd();
}

//绘制不同颜色的三角形
void drawColoredTriangles() {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 5; ++i) { // 绘制五个三角形
        glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
        glVertex2f((2.0f * (float)rand() / RAND_MAX) - 1.0f, (2.0f * (float)rand() / RAND_MAX) - 1.0f);
        glVertex2f((2.0f * (float)rand() / RAND_MAX) - 1.0f, (2.0f * (float)rand() / RAND_MAX) - 1.0f);
        glVertex2f((2.0f * (float)rand() / RAND_MAX) - 1.0f, (2.0f * (float)rand() / RAND_MAX) - 1.0f);
    }
    glEnd();
}

//绘制正弦函数
void drawSineFunction() {
    const float pi = 3.1415926f;
    float amplitude = 0.5f;
    float frequency = 1.0f;
    glColor3f(1.0f, 1.0f, 1.0f); // 设置正弦函数的颜色为白色
    glBegin(GL_LINE_STRIP);
    for (float x = -1.0f; x < 1.0f; x += 0.01f) {
        glVertex2f(x, amplitude * sin(x * pi * frequency));
    }
    glEnd();
}

//循环切换窗口
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (currentScene) {
        case 0:
            drawStar();
            break;
        case 1:
            drawRandomPoints(100);
            break;
        case 2:
            drawColoredTriangles();
            break;
        case 3:
            drawSineFunction();
            break;
    }

    glFlush();
}

//回车切换 ESC退出
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 13:
            currentScene = (currentScene + 1) % 4;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(NULL))); //显式转换，忽略精度损失警告
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("使用回车键切换显示内容，使用ESC键退出");

    //调用四种函数
    glutDisplayFunc(display);
    //调用控制函数
    glutKeyboardFunc(keyboard);

    //初始化OpenGL
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutMainLoop();
    return 0;
}

