#include <GL/glut.h>
#include <GL/glu.h>

GLfloat lightPosition[] = { 0, 8, 0 };  // 빛의 위치를 변경

void drawFilledCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks) {
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluCylinder(quadric, radius, radius, height, slices, stacks);
    gluDeleteQuadric(quadric);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glColor3f(1.0, 1.0, 1.0);  // 흰색
    drawFilledCylinder(2.0, 0.2, 20, 10);

    // 두 번째 원기둥
    glColor3f(1.0, 1.0, 1.0);  // 흰색
    glTranslatef(0.0, 0.0, 0.2);
    drawFilledCylinder(2.5, 0.4, 20, 10);
    glPopMatrix();

    glutSwapBuffers();
}




void init() {

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 4.0 / 3.0, 1.0, 15.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 7, 0, 0, 5, 0, 0, 0, -1);  // 시야를 위로 조금 올림

    // 조명의 파라미터 설정
    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat yellow[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat cyan[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 3.0, 4.0, 2.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);

    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(120, 60);
    glutInitWindowSize(1280, 980);
    glutCreateWindow("가요톱5");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    init();
    glutMainLoop();

    return 0;
}