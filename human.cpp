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
#define RB_HEAD_SIDE 70.0f		//로봇 머리 크기.
#define RB_JOINT_GAP 20.0f		//로봇 관절 틈 크기.
#define RB_LEG_LENGTH 120.0f	//로봇 다리 길이.
#define RB_ARM_LENGTH 140.0f	//로봇 팔 길이.
#define VIEW_SIZE 700.0f	

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

	glClearColor(1.0, 1.0, 1.0, 0.0); // 배경 흰색.

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
	glutSolidSphere(8.0, 80, 80); // 얼굴 그리기.

}

void drawBoard() { // 땅그리기.

	glBegin(GL_TRIANGLE_FAN); //오른쪽 뒤 원 그리기.


	glColor3f(0.8f, 0.8f, 0.8f); //밝은 회색
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, -278, 0.0f); //오른쪽 뒤 원 중점.
	float angle;
	for (angle = 0.0f; angle < (2.0f * 3.14159); angle += (3.14159 / 360.0f)) {

		glVertex3f((500 * cos(angle)), -278.0f, (500 * sin(angle)));
	}
	glEnd();

}

void robot_Display() {  // 디스플레이 콜백함수.

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); // 모델뷰 매트릭스 초기화.
	glLoadIdentity();

	gluLookAt(50, 40, 80, 0, 0, 0, 0, 1, 0); // 카메라 셋팅.
	drawBoard();

	glRotatef(center_Y, 0, 1, 0);
	glPushMatrix();



	drawBody(); // 몸통.
	glPopMatrix();
	glPushMatrix();

	drawHead();	// 머리.
	glPopMatrix();
	glPushMatrix();

	drawLeg();	// 다리.
	glPopMatrix();
	glPushMatrix();

	drawArm();  // 팔.

	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers(); //스왑 버퍼.

}

void timerFunction(int value) { //애니매이션 처리를 위한 timefunc콜백 함수.

	time = time + 0.1047;//시간 증가변수.

	static float step = 10;

	if (step <= 21) { //다리가 발로 땅을 찰때는 로봇이 앞으로 빠르게 전진.
		center_Y -= 0.65;
		step++;
	}
	else if (21 < step) { //땅을 차는 다리가 바뀌는 시점은 약간 주춤.
		center_Y -= 0.04;
		step++;
		if (step >= 30) step = 0;
	}

	head_Y = sin(time) * 5; //머리는 5도 각도로 흔들림.
	body_Y = sin(time) * 10; //몸통은 10도 각도로 흔들림.

	left_arm_X = sin(time) * 20;//왼팔은 20도 각도로.
	right_arm_X = -left_arm_X;//오른팔은 왼팔 반대로 20도 각도.

	right_up_leg_X = sin(time) * 20;//오른다리는 왼팔과 같은 각도로.
	left_up_leg_X = -right_up_leg_X;//왼다리는 오른팔과 같은 각도로.

	right_down_leg_X = abs(right_up_leg_X / 1.2f);//오른무릎은 다리 각도를 1.2로 나눈 절대각도.
	left_down_leg_X = abs(left_up_leg_X / 1.2f);//왼무릎은 다리 각도를 1.2로 나눈 절대각도.

	glutPostRedisplay();//다시 그리기.

	glutTimerFunc(22, timerFunction, 1); //다음 타이머 설정.

}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //더블 버퍼 컬러 모드.
	glutInitWindowSize(1280, 980); 
	glutInitWindowPosition(0, 0); 
	glutCreateWindow("히언이와 으나의 가요 톱 파이부"); 
	//glutTimerFunc(1000, timerFunction, 1);//타이머 설정.
	glutDisplayFunc(robot_Display);
	glInit();
	glutMainLoop();
}
