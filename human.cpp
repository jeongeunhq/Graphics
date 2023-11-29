#include <windows.h>
#include <gl/GL.H>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include <cmath>

#define CUBE_SIDE 10.0f			//소스 큐브 크기.(크기=한변의 길이)
#define RB_AXIS_X 0.0f		//로봇의 중심 좌표 x.
#define RB_AXIS_Y 0.0f		//로봇의 중심 좌표 y.
#define RB_BODY_SIDE 120.0f		//로봇 몸통 크기.
#define RB_HEAD_SIDE 35.0f		//로봇 머리 크기.
#define RB_JOINT_GAP 20.0f		//로봇 관절 틈 크기.
#define RB_LEG_LENGTH 120.0f	//로봇 다리 길이.
#define RB_ARM_LENGTH 140.0f	//로봇 팔 길이.
#define VIEW_SIZE 600.0f	

static double time = 0;		//time 변수.
GLfloat center_Y = 0.0f;		//화면 중심 y축 angle변수.
GLfloat left_arm_X = 0.0f;	//왼 팔 X축 angle.
GLfloat right_arm_X = 0.0f;	//오른 팔 X축 angle.
GLfloat left_up_leg_X = 0.0f;	//왼 다리 관절 X축.
GLfloat right_up_leg_X = 0.0f;//오른 다리 관절 X축.
GLfloat left_down_leg_X = 0.0f;//왼 무릎 관절.
GLfloat right_down_leg_X = 0.0f;//오른 무릎 관절.
GLfloat body_Y = 0.0f;//몸중심 축.
GLfloat head_Y = 0.0f;//머리중심 축.


void glInit(void) {	// GL초기화 함수.

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

	glClearColor(0.0, 0.0, 0.0, 0.0); // 배경 흰색.

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-VIEW_SIZE, VIEW_SIZE, -VIEW_SIZE, VIEW_SIZE, -VIEW_SIZE, VIEW_SIZE);

}


void drawArm() { //팔그리기.

	glTranslatef(RB_BODY_SIDE / 2.0f + RB_JOINT_GAP, RB_BODY_SIDE * 0.9, 0.0f);
	//drawAxis(50.0f);
	glRotatef(15, 0, 0, 1);	// 팔 축을 중심으로 한 팔의 현재 움직임.
	glRotatef(left_arm_X, 1, 0, 0);   //팔 흔들기.
	glRotatef(-30, 0, 1, 0);

	glScalef(RB_ARM_LENGTH / 4.0 / CUBE_SIDE, RB_ARM_LENGTH / CUBE_SIDE, RB_ARM_LENGTH / 4.0 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE); // 왼팔 그리기.

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-(RB_BODY_SIDE / 2.0f + RB_JOINT_GAP), RB_BODY_SIDE * 0.9, 0.0f);
	//drawAxis(50.0f);
	glRotatef(-15, 0, 0, 1);  // 팔 축을 중심으로 한 팔의 현재 움직임.
	glRotatef(right_arm_X, 1, 0, 0);	//팔 흔들기.
	glRotatef(30, 0, 1, 0);

	glScalef(RB_ARM_LENGTH / 4.0 / CUBE_SIDE, RB_ARM_LENGTH / CUBE_SIDE, RB_ARM_LENGTH / 4.0 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE); // 오른팔 그리기.

}

void drawLeg() {	//다리 그리기.

	glTranslatef(RB_BODY_SIDE / 4.0f, -RB_JOINT_GAP, 0.0f);  //윗 다리 중심.
	//drawAxis(50.0f);
	glRotatef(2, 0, 0, 1);		// 몸통과 다리 각도.
	glRotatef(left_up_leg_X, 1, 0, 0); //다리 흔들기.
	glScalef(RB_LEG_LENGTH / 2.5 / CUBE_SIDE, RB_LEG_LENGTH / CUBE_SIDE, RB_LEG_LENGTH / 2.5 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE);	//왼쪽 다리 무릎까지 그리기.

	glScalef(CUBE_SIDE * 2.5 / RB_LEG_LENGTH, CUBE_SIDE / RB_LEG_LENGTH, CUBE_SIDE * 2.5 / RB_LEG_LENGTH);
	// 스케일 원상 복구.

	glTranslatef(0.0f, -RB_LEG_LENGTH / 2.0f - RB_JOINT_GAP, 0.0f); // 밑 다리 중심.
	//drawAxis(50.0f);
	glRotatef(left_down_leg_X, 1, 0, 0);// 무릎 각도. 무릎 흔들기.
	glScalef(RB_LEG_LENGTH / 2.5 / CUBE_SIDE, RB_LEG_LENGTH / CUBE_SIDE, RB_LEG_LENGTH / 2.5 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE);	//왼쪽 다리 끝까지 그리기.

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-RB_BODY_SIDE / 4.0f, -RB_JOINT_GAP, 0.0f);  //윗 다리 중심.
	//drawAxis(50.0f);
	glRotatef(-2, 0, 0, 1);		// 몸통과 다리 각도.
	glRotatef(right_up_leg_X, 1, 0, 0);//다리 흔들기.
	glScalef(RB_LEG_LENGTH / 2.5 / CUBE_SIDE, RB_LEG_LENGTH / CUBE_SIDE, RB_LEG_LENGTH / 2.5 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE);	//오른쪽 다리 무릎까지 그리기.

	glScalef(CUBE_SIDE * 2.5 / RB_LEG_LENGTH, CUBE_SIDE / RB_LEG_LENGTH, CUBE_SIDE * 2.5 / RB_LEG_LENGTH);
	//스케일 원상 복구.
	glTranslatef(0.0f, -RB_LEG_LENGTH / 2.0f - RB_JOINT_GAP, 0.0f); // 밑 다리 중심.
	//drawAxis(50.0f);
	glRotatef(right_down_leg_X, 1, 0, 0);// 무릎 각도. 무릎 흔들기.
	glScalef(RB_LEG_LENGTH / 2.5 / CUBE_SIDE, RB_LEG_LENGTH / CUBE_SIDE, RB_LEG_LENGTH / 2.5 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE);	//왼쪽 다리 끝까지 그리기.

}

void drawBody() { //몸통 그리기.

	glTranslatef(RB_AXIS_X, RB_AXIS_Y, 0.0f); // 로봇 중심.
	//drawAxis(80.0f);	//로봇 중심 축 그리기.
	glRotatef(0, 0, 1, 0); //로봇을 돌리는 앵글.
	glPushMatrix(); //로봇의 각 부위를 그릴때 중심이 되는 매트릭스 푸싱.

	glScalef(RB_BODY_SIDE / CUBE_SIDE, RB_BODY_SIDE / CUBE_SIDE, RB_BODY_SIDE / CUBE_SIDE);
	glColor3f(1.0, 0.7, 0.8);
	glTranslatef(0.0f, CUBE_SIDE / 2, 0.0f);
	glRotatef(body_Y, 0, 1, 0);	//몸통 흔들기.
	glutSolidCube(CUBE_SIDE);  // 몸통그리기.

}

void drawHead() { //머리 그리기.

	glTranslatef(0.0f, RB_BODY_SIDE + RB_JOINT_GAP + (RB_HEAD_SIDE / 2.0f), 0.0f); // 얼굴 중심.
	//drawAxis(80.0f);
	glRotatef(head_Y, 0, 1, 0);//얼굴 움직임.
	glScalef(RB_HEAD_SIDE / CUBE_SIDE, RB_HEAD_SIDE / CUBE_SIDE, RB_HEAD_SIDE / CUBE_SIDE);
	glutSolidSphere(RB_HEAD_SIDE / 2.0, 50, 50);  // 얼굴 그리기.

}

void drawBoard() {
	glPushMatrix();

	glColor3f(0.8f, 0.8f, 0.8f); // Light gray color

	// Define the vertices of the rectangle with increased vertical length
	glBegin(GL_QUADS);
	glVertex3f(-1200.0f, -400.0f, -250.0f); // Bottom-left
	glVertex3f(1200.0f, -400.0f, -250.0f);  // Bottom-right
	glVertex3f(1200.0f, -400.0f, 250.0f);   // Top-right
	glVertex3f(-1200.0f, -400.0f, 250.0f);  // Top-left
	glEnd();

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

	drawBody(); // 몸통.
	glPopMatrix();
	glPushMatrix();

	drawHead();  // 머리.
	glPopMatrix();
	glPushMatrix();

	drawLeg();  // 다리.
	glPopMatrix();
	glPushMatrix();

	drawArm();  // 팔.

	glPopMatrix();
	glutSwapBuffers();  // 스왑 버퍼.
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //더블 버퍼 컬러 모드.
	glutInitWindowSize(1200, 980);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("히언이와 으나의 가요 톱 파이부");
	glutTimerFunc(1000, timerFunction, 1);//타이머 설정.
	glutDisplayFunc(robot_Display);
	glInit();
	glutMainLoop();
}
