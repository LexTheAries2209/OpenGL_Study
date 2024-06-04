//
//  taiyangxi.cpp
//  OpenGL_Study
//
//  Created by 吴坤城 on 6/4/24.
//

//
//  taiyangxi.cpp
//  OpenGL_Study
//
//  Created by 吴坤城 on 6/4/24.
//

#include <GLUT/glut.h>
#include <cmath> // 引入数学库，用于计算椭圆轨道

// 定义旋转角度
static float year = 0.0, day = 0.0, moon = 0.0;

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 合并清除操作
   glEnable(GL_DEPTH_TEST); // 启动深度测试，用于隐藏被遮挡的部分

   // 绘制太阳
   glPushMatrix();
   glColor3f(1.0, 1.0, 0.0); // 黄色
   glutSolidSphere(1.0, 50, 40);   // 太阳，增加细分度以使球体更圆

   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);

   // 绘制地球
   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0); // 根据年份旋转，模拟公转
   // 使用sin和cos函数创建椭圆轨道，假设椭圆的长轴为2.0，短轴为1.5
   float earthX = 2.0 * cos(year * 3.14159 / 180);
   float earthZ = 1.5 * sin(year * 3.14159 / 180);
   glTranslatef(earthX, 0.0, earthZ); // 移动地球到椭圆轨道上的正确位置
   glColor3f(0.0, 0.0, 1.0); // 蓝色
   glutSolidSphere(0.2, 20, 16);    // 地球，增加细分度

   // 绘制月球
   glPushMatrix();
   glRotatef ((GLfloat) moon, 0.0, 1.0, 0.0);
   glTranslatef(0.5, 0.0, 0.0); // 月球相对于地球的位置
   glColor3f(0.5, 0.5, 0.5); // 灰色
   glutSolidSphere(0.05, 10, 8);    // 月球，增加细分度
   glPopMatrix();

   glPopMatrix();
   glPopMatrix();

   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void update(int value) {
   day += 5; // 地球自转速度，减慢了速度
   year += 2.5; // 地球公转速度，减慢了速度
   moon += 6.5; // 月球公转速度，减慢了速度

   // 确保角度不会无限增加
   if(day > 360) day -= 360;
   if(year > 360) year -= 360;
   if(moon > 360) moon -= 360;

   glutPostRedisplay();
   glutTimerFunc(16, update, 0); // 减少时间间隔至约60FPS（1000ms/60约等于16ms）
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27: // ESC 键的 ASCII 码是 27
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard); // 注册键盘回调函数
   glutTimerFunc(16, update, 0); // 设置第一次更新的定时器为更高的帧率
   glutMainLoop();
   return 0;
}
