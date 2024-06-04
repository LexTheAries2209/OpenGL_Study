//
//  Print_Line.cpp
//  OpenGL_Study
//
//  Created by 吴坤城 on 3/18/24.
//

#include <GLUT/glut.h>

// 初始化OpenGL图形视图
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置背景颜色为黑色
}

// 绘制回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT);   // 清除屏幕
    glLoadIdentity();               // 重置当前指定的矩阵为单位矩阵
    
    // 绘制白色的线段
    glBegin(GL_LINES);              // 开始绘制线段
    glColor3f(1.0f, 1.0f, 1.0f);    // 设置线段颜色为白色
    glVertex2f(-0.5f, 0.0f);        // 线段起点
    glVertex2f(0.5f, 0.0f);         // 线段终点
    glEnd();                        // 结束绘制线段
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                          // 初始化GLUT
    glutCreateWindow("Print_Line");                 // 创建窗口
    glutInitWindowSize(500, 500);                   // 设置默认的初始窗口大小
    glutInitWindowPosition(50, 50);                 // 设置窗口的初始位置
    glutDisplayFunc(display);                       // 注册显示回调函数
    initGL();                                       // 进行一次性的设置
    glutMainLoop();                                 // 进入GLUT事件处理循环
    return 0;
}
