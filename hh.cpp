#include <windows.h>
#include <gl/GL.H>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include <cmath>

#define CUBE_SIDE 10.0f			//�ҽ� ť�� ũ��.(ũ��=�Ѻ��� ����)
#define RB_AXIS_X 0.0f		//�κ��� �߽� ��ǥ x.
#define RB_AXIS_Y 0.0f		//�κ��� �߽� ��ǥ y.
#define RB_BODY_SIDE 120.0f		//�κ� ���� ũ��.
#define RB_HEAD_SIDE 35.0f		//�κ� �Ӹ� ũ��.
#define RB_JOINT_GAP 20.0f		//�κ� ���� ƴ ũ��.
#define RB_LEG_LENGTH 120.0f	//�κ� �ٸ� ����.
#define RB_ARM_LENGTH 140.0f	//�κ� �� ����.
#define VIEW_SIZE 600.0f	

static double time = 0;		//time ����.
GLfloat center_Y = 0.0f;		//ȭ�� �߽� y�� angle����.
GLfloat left_arm_X = 0.0f;	//�� �� X�� angle.
GLfloat right_arm_X = 0.0f;	//���� �� X�� angle.
GLfloat left_up_leg_X = 0.0f;	//�� �ٸ� ���� X��.
GLfloat right_up_leg_X = 0.0f;//���� �ٸ� ���� X��.
GLfloat left_down_leg_X = 0.0f;//�� ���� ����.
GLfloat right_down_leg_X = 0.0f;//���� ���� ����.
GLfloat body_Y = 0.0f;//���߽� ��.
GLfloat head_Y = 0.0f;//�Ӹ��߽� ��.


void glInit(void) {	// GL�ʱ�ȭ �Լ�.

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);

	GLfloat ambientLight[] = { 0.3f,0.3f,0.3f,1.0f };
	GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat position[] = { 400.0f,300.0f,700.0f,1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glClearColor(0.0, 0.0, 0.0, 0.0); // ��� ���.

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-VIEW_SIZE, VIEW_SIZE, -VIEW_SIZE, VIEW_SIZE, -VIEW_SIZE, VIEW_SIZE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

//void drawFilledCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks) {
//    GLUquadricObj* quadric = gluNewQuadric();
//    gluQuadricDrawStyle(quadric, GLU_FILL);
//    gluCylinder(quadric, radius, radius, height, slices, stacks);
//    gluDeleteQuadric(quadric);
//}


void drawArm() { //�ȱ׸���.

	glTranslatef(RB_BODY_SIDE / 2.0f + RB_JOINT_GAP, RB_BODY_SIDE * 0.9, 0.0f);
	//drawAxis(50.0f);
	glRotatef(15, 0, 0, 1);	// �� ���� �߽����� �� ���� ���� ������.
	glRotatef(left_arm_X, 1, 0, 0);   //�� ����.
	glRotatef(-30, 0, 1, 0);

	glScalef(RB_ARM_LENGTH / 4.0 / CUBE_SIDE, RB_ARM_LENGTH / CUBE_SIDE, RB_ARM_LENGTH / 4.0 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE); // ���� �׸���.

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-(RB_BODY_SIDE / 2.0f + RB_JOINT_GAP), RB_BODY_SIDE * 0.9, 0.0f);
	//drawAxis(50.0f);
	glRotatef(-15, 0, 0, 1);  // �� ���� �߽����� �� ���� ���� ������.
	glRotatef(right_arm_X, 1, 0, 0);	//�� ����.
	glRotatef(30, 0, 1, 0);

	glScalef(RB_ARM_LENGTH / 4.0 / CUBE_SIDE, RB_ARM_LENGTH / CUBE_SIDE, RB_ARM_LENGTH / 4.0 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE); // ������ �׸���.

}

void drawLeg() {	//�ٸ� �׸���.

	glTranslatef(RB_BODY_SIDE / 4.0f, -RB_JOINT_GAP, 0.0f);  //�� �ٸ� �߽�.
	//drawAxis(50.0f);
	glRotatef(2, 0, 0, 1);		// ����� �ٸ� ����.
	glRotatef(left_up_leg_X, 1, 0, 0); //�ٸ� ����.
	glScalef(RB_LEG_LENGTH / 2.5 / CUBE_SIDE, RB_LEG_LENGTH / CUBE_SIDE, RB_LEG_LENGTH / 2.5 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE);	//���� �ٸ� �������� �׸���.

	glScalef(CUBE_SIDE * 2.5 / RB_LEG_LENGTH, CUBE_SIDE / RB_LEG_LENGTH, CUBE_SIDE * 2.5 / RB_LEG_LENGTH);
	// ������ ���� ����.

	glTranslatef(0.0f, -RB_LEG_LENGTH / 2.0f - RB_JOINT_GAP, 0.0f); // �� �ٸ� �߽�.
	//drawAxis(50.0f);
	glRotatef(left_down_leg_X, 1, 0, 0);// ���� ����. ���� ����.
	glScalef(RB_LEG_LENGTH / 2.5 / CUBE_SIDE, RB_LEG_LENGTH / CUBE_SIDE, RB_LEG_LENGTH / 2.5 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE);	//���� �ٸ� ������ �׸���.

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-RB_BODY_SIDE / 4.0f, -RB_JOINT_GAP, 0.0f);  //�� �ٸ� �߽�.
	//drawAxis(50.0f);
	glRotatef(-2, 0, 0, 1);		// ����� �ٸ� ����.
	glRotatef(right_up_leg_X, 1, 0, 0);//�ٸ� ����.
	glScalef(RB_LEG_LENGTH / 2.5 / CUBE_SIDE, RB_LEG_LENGTH / CUBE_SIDE, RB_LEG_LENGTH / 2.5 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE);	//������ �ٸ� �������� �׸���.

	glScalef(CUBE_SIDE * 2.5 / RB_LEG_LENGTH, CUBE_SIDE / RB_LEG_LENGTH, CUBE_SIDE * 2.5 / RB_LEG_LENGTH);
	//������ ���� ����.
	glTranslatef(0.0f, -RB_LEG_LENGTH / 2.0f - RB_JOINT_GAP, 0.0f); // �� �ٸ� �߽�.
	//drawAxis(50.0f);
	glRotatef(right_down_leg_X, 1, 0, 0);// ���� ����. ���� ����.
	glScalef(RB_LEG_LENGTH / 2.5 / CUBE_SIDE, RB_LEG_LENGTH / CUBE_SIDE, RB_LEG_LENGTH / 2.5 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE);	//���� �ٸ� ������ �׸���.

}

void drawBody() { //���� �׸���.

	glTranslatef(RB_AXIS_X, RB_AXIS_Y, 0.0f); // �κ� �߽�.
	//drawAxis(80.0f);	//�κ� �߽� �� �׸���.
	glRotatef(0, 0, 1, 0); //�κ��� ������ �ޱ�.
	glPushMatrix(); //�κ��� �� ������ �׸��� �߽��� �Ǵ� ��Ʈ���� Ǫ��.

	glScalef(RB_BODY_SIDE / CUBE_SIDE, RB_BODY_SIDE / CUBE_SIDE, RB_BODY_SIDE / CUBE_SIDE);
	glColor3f(1.0, 0.7, 0.8);
	glTranslatef(0.0f, CUBE_SIDE / 2, 0.0f);
	glRotatef(body_Y, 0, 1, 0);	//���� ����.
	glutSolidCube(CUBE_SIDE);  // ����׸���.

}

void drawHead() { //�Ӹ� �׸���.

	glTranslatef(0.0f, RB_BODY_SIDE + RB_JOINT_GAP + (RB_HEAD_SIDE / 2.0f), 0.0f); // �� �߽�.
	//drawAxis(80.0f);
	glRotatef(head_Y, 0, 1, 0);//�� ������.
	glScalef(RB_HEAD_SIDE / CUBE_SIDE, RB_HEAD_SIDE / CUBE_SIDE, RB_HEAD_SIDE / CUBE_SIDE);
	glutSolidSphere(RB_HEAD_SIDE / 2.0, 50, 50);  // �� �׸���.
}


void drawCone(GLfloat radius, GLfloat height, GLint slices, GLint stacks) {
	GLUquadric* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, radius, 0.0, height, slices, stacks);
	gluDeleteQuadric(quadric);
}


void drawBoard() {
	glPushMatrix();

	glColor4f(0.8f, 0.8f, 0.8f, 0.5f); // Light gray 

	// Define the vertices of the rectangle with increased vertical length
	glBegin(GL_QUADS);
	glVertex3f(-1200.0f, -400.0f, -250.0f); // Bottom-left
	glVertex3f(1200.0f, -400.0f, -250.0f);  // Bottom-right
	glVertex3f(1200.0f, -400.0f, 250.0f);   // Top-right
	glVertex3f(-1200.0f, -400.0f, 250.0f);  // Top-left
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0f, 0.0f, 1.0f, 0.25f); //�Ķ���
	glTranslatef(0.0f, 300.0f,  0.0f);
	glRotatef(-135, 1, 0, 0); // ������ ���� ���ϵ��� ȸ��
	drawCone(100.0, 500.0, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 0.65f, 0.0f, 0.25f); //�����
	glTranslatef(-300.0f, 250.0f, 0.0f); 
	glRotatef(-135, 1, 1 , 0); // ������ ���� ���ϵ��� ȸ��
	drawCone(100.0, 1000.0, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 0.0f, 0.0f, 0.25f); //������
	glTranslatef(300.0f, 250.0f, 0.0f);
	glRotatef(-135, 1, -1, 0); // ������ ���� ���ϵ��� ȸ��
	drawCone(100.0, 1000.0, 50, 50);
	glPopMatrix();

}

void draw3DText(const char* text, GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(1.0f, 1.0f, 1.0f);
	glColor3f(1.0, 1.0, 1.0);

	for (const char* c = text; *c != '\0'; ++c) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
	}

	glPopMatrix();
}


void robot_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 100, 200, 0, 0, 0, 0, 1, 0);

	drawBoard();

	glLoadIdentity();
	gluLookAt(0, 100, 300, 0, 0, 0, 0, 1, 0);
	glRotatef(center_Y, 0, 1, 0);

	glPushMatrix();


	glTranslatef(0.0f, -50.0f, 0.0f);

	drawBody(); // ����.
	glPopMatrix();
    glPushMatrix();

	drawHead();  // �Ӹ�.
	glPopMatrix();
	glPushMatrix();

	drawLeg();  // �ٸ�.
	glPopMatrix();
	glPushMatrix();

	drawArm();  // ��
    glPopMatrix();
	glPushMatrix();

	draw3DText("Top", -RB_BODY_SIDE / 2.0f - 400.0f, RB_BODY_SIDE * 0.9f, 0.0f);
	draw3DText("3", RB_BODY_SIDE / 2.0f + 200.0f, RB_BODY_SIDE * 0.9f, 0.0f);

	glPushMatrix();


	glutSwapBuffers();  // ���� ����.
}

void timerFunction(int value) {
	int elapsedMilliseconds = glutGet(GLUT_ELAPSED_TIME);
	int elapsedSeconds = (elapsedMilliseconds / 1000) % 60;

	time = elapsedMilliseconds / 1000.0;


	if (elapsedSeconds < 10) {
		// First 10 seconds: Wave arms
		left_arm_X = 60 * sin(6 * time);
		right_arm_X = -left_arm_X;
	}
	else if (elapsedSeconds < 20) {
		// Next 10 seconds: Move legs
		right_up_leg_X = 60 * sin(4 * time);
		left_up_leg_X = -right_up_leg_X;
		right_down_leg_X = 40 * sin(4 * time);
		left_down_leg_X = -40 * sin(4 * time);


		left_arm_X = 0;
		right_arm_X = 0;
	}
	else {

		left_arm_X = 0;
		right_arm_X = 0;
		right_up_leg_X = 0;
		left_up_leg_X = 0;
		right_down_leg_X = 0;
		left_down_leg_X = 0;
	}

	glutPostRedisplay();

	glutTimerFunc(500, timerFunction, 1);
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //���� ���� �÷� ���.
	glutInitWindowSize(1200, 980);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("�����̿� ������ ���� �� ���̺�");
	glutTimerFunc(1000, timerFunction, 1);//Ÿ�̸� ����.
	glutDisplayFunc(robot_Display);
	glInit();
	glutMainLoop();
}