//
//  liulengzhui.cpp
//  OpenGL_Study
//
//  Created by 吴坤城 on 5/8/24.
//

#include <GLUT/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

float angle = 0.0; // 用于旋转的角度

void init() {
    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glClearColor(0.0, 0.0, 0.0, 1.0); // 设置背景颜色为黑色
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 设置为线框模式
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色和深度缓冲区
    glLoadIdentity(); // 重置视图

    // 设置视点
    gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 应用旋转
    glRotatef(angle, 0.0, 1.0, 0.0); // 绕Y轴旋转

    // 绘制六棱锥的基底
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0); // 中心点
    for(int i = 0; i <= 6; ++i) {
        float theta = 2 * PI * i / 6;
        glVertex3f(cos(theta), 0.0, sin(theta));
    }
    glEnd();

    // 绘制六棱锥的侧面
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < 6; ++i) {
        float theta1 = 2 * PI * i / 6;
        float theta2 = 2 * PI * (i + 1) / 6;
        glVertex3f(0.0, 1.5, 0.0); // 顶点
        glVertex3f(cos(theta1), 0.0, sin(theta1));
        glVertex3f(cos(theta2), 0.0, sin(theta2));
    }
    glEnd();

    glFlush(); // 确保命令被执行
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h); // 设置视口
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 10.0); // 设置透视投影
    glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
    angle += 2.0; // 增加旋转角度
    if (angle > 360.0) {
        angle -= 360.0; // 角度归一化
    }
    glutPostRedisplay(); // 请求重绘
    glutTimerFunc(1000/60, timer, v); // 设置定时器，约60Hz
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("旋转六棱锥");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0); // 初始化定时器
    glutMainLoop();
    return 0;
}
