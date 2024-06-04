//
//  chahu-light.cpp
//  OpenGL_Study
//
//  Created by 吴坤城 on 6/4/24.
//

#include <GLUT/glut.h>
#include <stdlib.h> // 引入stdlib.h以使用exit函数

int viewIndex = 0; // 当前视图方向的索引
bool isDiffuse = true; // 默认启用漫反射模式

void init() {
    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glClearColor(1.0, 1.0, 1.0, 1.0); // 设置背景颜色为黑色

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

void updateMaterial() {
    if (isDiffuse) {
        // 漫反射材质属性
        GLfloat mat_diffuse[] = { 0.58, 0.29, 0.0, 1.0 };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        // 减少镜面反射的强度
        GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    } else {
        // 镜面反射材质属性
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        // 减少漫反射的强度
        GLfloat mat_diffuse[] = { 0.1, 0.1, 0.1, 1.0 };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 根据当前视图索引设置视点
    switch (viewIndex) {
        case 0: // 前
            gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 1: // 后
            gluLookAt(0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 2: // 左
            gluLookAt(-5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 3: // 右
            gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 4: // 上
            gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
            break;
        case 5: // 下
            gluLookAt(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
            break;
    }

    updateMaterial(); // 更新材质属性

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
            viewIndex = (viewIndex + 1) % 6; // 循环切换视角
        } else if (button == GLUT_RIGHT_BUTTON) {
            isDiffuse = !isDiffuse; // 切换反射类型
        }
        glutPostRedisplay(); // 请求重绘
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC键退出
            exit(0);
            break;
        case '1': // 切换到漫反射模式
            isDiffuse = true;
            break;
        case '2': // 切换到镜面反射模式
            isDiffuse = false;
            break;
    }
    glutPostRedisplay(); // 请求重绘
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
