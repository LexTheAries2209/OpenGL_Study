//
//  chahu.cpp
//  OpenGL_Study
//
//  Created by 吴坤城 on 5/8/24.
//

#include <GLUT/glut.h>
#include <stdlib.h> // 引入stdlib.h以使用exit函数

int viewIndex = 0; // 当前视图方向的索引
bool depthEnabled = true; // 深度测试是否启用

void init() {
    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glClearColor(0.0, 0.0, 0.0, 1.0); // 设置背景颜色为黑色

    // 设置光照
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 5.0, 5.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 根据当前视图索引设置视点
    switch (viewIndex) {
        case 0: // 正面
            gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 1: // 后面
            gluLookAt(0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 2: // 左侧
            gluLookAt(-5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 3: // 右侧
            gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 4: // 顶部
            gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
            break;
        case 5: // 底部
            gluLookAt(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
            break;
    }

    // 设置材质颜色为紫砂壶的颜色
    GLfloat mat_ambient[] = { 0.58, 0.29, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.58, 0.29, 0.0, 1.0 };
    GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidTeapot(1.0); // 绘制实心茶壶
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            viewIndex = (viewIndex + 1) % 6; // 更新视图索引
        } else if (button == GLUT_RIGHT_BUTTON) {
            depthEnabled = !depthEnabled; // 切换深度测试开关
            if (depthEnabled) {
                glEnable(GL_DEPTH_TEST);
            } else {
                glDisable(GL_DEPTH_TEST);
            }
        }
        glutPostRedisplay(); // 请求重绘
    }
}

// 键盘事件处理函数
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC键的ASCII码是27
            exit(0); // 退出程序
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("茶壶");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard); // 注册键盘事件处理函数
    glutMainLoop();
    return 0;
}
