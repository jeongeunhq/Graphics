#include <windows.h>
#include <gl/GL.H>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include <cmath>
#include <mmsystem.h>;
#pragma comment(lib, "winmm.lib")
#define CUBE_SIDE 10.0f			//소스 큐브 크기.(크기=한변의 길이)
#define RB_AXIS_X 0.0f		//로봇의 중심 좌표 x.
#define RB_AXIS_Y 0.0f		//로봇의 중심 좌표 y.
#define RB_BODY_SIDE 120.0f		//로봇 몸통 크기.
#define RB_HEAD_SIDE 80.0f		//로봇 머리 크기.
#define RB_JOINT_GAP 10.0f		//로봇 관절 틈 크기.
#define RB_LEG_LENGTH 120.0f	//로봇 다리 길이.
#define RB_ARM_LENGTH 140.0f	//로봇 팔 길이.
#define VIEW_SIZE 600.0f	
#define SOUND_FILE_NAME  "../가요톱빠이부.wav"
;
static double time = 0;		//time 변수.

GLfloat center_Y = 0.0f;		//화면 중심 y축 angle변수.
GLfloat left_arm_X = 0.0f;	//왼 팔 X축 angle.
GLfloat right_arm_X = 0.0f;	//오른 팔 X축 angle.
GLfloat left_arm_Y = 0.0f;	//왼 팔 X축 angle.
GLfloat right_arm_Y = 0.0f;
GLfloat left_up_leg_X = 0.0f;	//왼 다리 관절 X축.
GLfloat right_up_leg_X = 0.0f;//오른 다리 관절 X축.
GLfloat left_down_leg_X = 0.0f;//왼 무릎 관절.
GLfloat right_down_leg_X = 0.0f;//오른 무릎 관절.
GLfloat body_Y = 0.0f;//몸중심 축.
GLfloat head_Y = 0.0f;//머리중심 축.
GLfloat head_X = 0.0f;

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

struct Snowflake {
	float x, y, z;   // 눈송이의 위치
	float speed;     // 눈송이의 속도
};

const int NUM_SNOWFLAKES = 100; // 눈송이의 개수
Snowflake snowflakes[NUM_SNOWFLAKES]; // 눈송이 배열

void initSnowflakes() {
	for (int i = 0; i < NUM_SNOWFLAKES; ++i) {
		snowflakes[i].x = static_cast<float>(rand() % 1200);  // x 좌표는 0부터 1200 사이의 랜덤 값
		snowflakes[i].y = static_cast<float>(rand() % 980);  // y 좌표는 0부터 980 사이의 랜덤 값
		snowflakes[i].z = static_cast<float>(rand() % 100);  // z 좌표는 0부터 100 사이의 랜덤 값
		snowflakes[i].speed = static_cast<float>(rand() % 8 + 4); // 눈송이의 속도는 1부터 5까지의 랜덤 값
	}
}

void drawSnowflakes() {
	glColor3f(1.0, 1.0, 1.0); // 눈송이의 색상 (흰색)
	glPointSize(5.0); // 눈송이의 크기

	for (int i = 0; i < NUM_SNOWFLAKES; ++i) {
		glBegin(GL_POLYGON);
		for (int j = 0; j < 360; j += 60) { // 6개의 점을 이용하여 동그란 모양을 만듦
			float angle = static_cast<float>(j) * 3.1415926535 / 180.0;
			float radius = 4.0; // 동그란 모양의 반지름
			float x = snowflakes[i].x + radius * cos(angle);
			float y = snowflakes[i].y + radius * sin(angle);
			glVertex3f(x, y, snowflakes[i].z);
		}
		glEnd();
	}
}


void updateSnowflakes() {
	for (int i = 0; i < NUM_SNOWFLAKES; ++i) {
		snowflakes[i].y -= snowflakes[i].speed; // 눈송이를 아래로 움직임
		snowflakes[i].x -= 2.5; // 각 눈송이를 왼쪽으로 0.5씩 움직임
	
	}
}

void drawCone(GLfloat radius, GLfloat height, GLint slices, GLint stacks) {
	GLUquadric* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, radius, 0.0, height, slices, stacks);
	gluDeleteQuadric(quadric);
}

void drawArm() { //팔그리기.
	glColor3f(1.0, 0.7, 0.8);
	glTranslatef(RB_BODY_SIDE / 2.0f + RB_JOINT_GAP, RB_BODY_SIDE * 0.9, 0.0f);
	//drawAxis(50.0f);
	glRotatef(15, 0, 0, 1);	// 팔 축을 중심으로 한 팔의 현재 움직임.
	glRotatef(left_arm_X, 1, left_arm_Y, 0);   //팔 흔들기.
	glRotatef(-30, 0, 1, 0);

	glScalef(RB_ARM_LENGTH / 4.0 / CUBE_SIDE, RB_ARM_LENGTH / CUBE_SIDE, RB_ARM_LENGTH / 4.0 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE); // 왼팔 그리기.

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-(RB_BODY_SIDE / 2.0f + RB_JOINT_GAP), RB_BODY_SIDE * 0.9, 0.0f);
	//drawAxis(50.0f);
	glRotatef(-15, 0, 0, 1);  // 팔 축을 중심으로 한 팔의 현재 움직임.
	glRotatef(right_arm_X,1, right_arm_Y, 0);	//팔 흔들기.
	glRotatef(30, 0, 1, 0);

	glScalef(RB_ARM_LENGTH / 4.0 / CUBE_SIDE, RB_ARM_LENGTH / CUBE_SIDE, RB_ARM_LENGTH / 4.0 / CUBE_SIDE);
	glTranslatef(0.0f, -CUBE_SIDE / 2.0f, 0.0f);
	glutSolidCube(CUBE_SIDE); // 오른팔 그리기.

}

void drawLeg() {	//다리 그리기.
	glColor3f(1.0, 0.7, 0.8);
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
	
	glTranslatef(0.0f, RB_BODY_SIDE  + (RB_HEAD_SIDE / 2.0f), 0.0f); // 얼굴 중심.
	glRotatef(head_Y, 0, 1, 0);//얼굴 움직임.
	glScalef(RB_HEAD_SIDE / CUBE_SIDE, RB_HEAD_SIDE / CUBE_SIDE, RB_HEAD_SIDE / CUBE_SIDE);
	glColor3f(1.0, 0.7, 0.8);
	glutSolidCube(CUBE_SIDE); // 얼굴 그리기.
	

	glPushMatrix();

	//모자
	
	glColor4f(1.0f, 0.0f, 0.0f, 0.25f); //빨간색
	glTranslatef(0.0f, RB_HEAD_SIDE / 15.0f, 0.0f);
	glRotatef(-90, 8, 0, 0); // 원뿔을 위로 향하도록 회전
	drawCone(5.0,10.0, 50, 50);
	glTranslatef(0.0f, RB_HEAD_SIDE / 5.0f, 5.0f); // 원뿔의 꼭대기에서 내려온 위치로 이동
	glColor3f(1.0, 1.0, 1.0); // 하얀색
	glutSolidSphere(1.5, 20, 20);

	glPopMatrix();
}



void drawBoard() {
	glPushMatrix();

	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

	
	glBegin(GL_QUADS);
	glVertex3f(-1200.0f, -400.0f, -250.0f); 
	glVertex3f(1200.0f, -400.0f, -250.0f);  
	glVertex3f(1200.0f, -400.0f, 250.0f);  
	glVertex3f(-1200.0f, -400.0f, 250.0f);  
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //노란색
	glTranslatef(0.0f, 400.0f, 0.0f);
	glRotatef(-135, 1, 0, 0); // 원뿔을 위로 향하도록 회전
	drawCone(100.0, 400.0, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 0.0f, 0.0f, 0.25f); //빨간색
	glTranslatef(-300.0f, 350.0f, 0.0f);
	glRotatef(-135, 1, 1, 0); // 원뿔을 위로 향하도록 회전
	drawCone(100.0, 700.0, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0f, 0.5f, 0.0f, 1.0f);  // 초록색
	glTranslatef(300.0f, 350.0f, 0.0f);
	glRotatef(-135, 1, -1, 0); // 원뿔을 위로 향하도록 회전
	drawCone(100.0, 700.0, 50, 50);
	glPopMatrix();

}

void draw3DText(const char* text, GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(0.5f, 0.5f, 0.5f);
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
	glPushMatrix();

	draw3DText("Merry", -RB_BODY_SIDE / 2.0f - 400.0f, RB_BODY_SIDE * 0.1f, 0.0f);
	draw3DText("Christmas", RB_BODY_SIDE / 2.0f + 60.0f, RB_BODY_SIDE * 0.1f, 0.0f);

	drawSnowflakes();

	glPushMatrix();
	glutSwapBuffers();  // 스왑 버퍼.
}


void timerFunction(int value) {

	int elapsedMilliseconds = glutGet(GLUT_ELAPSED_TIME);
	int elapsedSeconds = (elapsedMilliseconds / 1000) % 60;  

	time = elapsedMilliseconds / 2000.0; 

	updateSnowflakes();
	glutPostRedisplay(); // 화면을 다시 그리도록 요청
	
	if (elapsedSeconds <= 5) {
		head_X= 10 * sin(12 * time);
		left_arm_X = 180 * sin(12 * time);
		right_arm_X = -180 * sin(12 * time);
	}
	else if (elapsedSeconds > 5&&elapsedSeconds <= 10) {
		
		right_up_leg_X = 60 * sin(12 * time);
		//left_up_leg_X = -right_up_leg_X;
		right_down_leg_X = 40 * sin(12 * time);
		//left_down_leg_X = -40 * sin(12 * time);
		body_Y = 10 * sin(12 * time);
		head_Y= 10 * sin(12 * time);
        left_arm_X = 180 * sin(12 * time);
		right_arm_X = 0;
	}
	else if (elapsedSeconds > 10&&elapsedSeconds <= 15) {
		
		right_up_leg_X = 0;
		left_up_leg_X = -50 * sin(12 * time);
		right_down_leg_X = 0;
		left_down_leg_X = -30 * sin(12 * time);
		body_Y = 20 * sin(12 * time);
		head_Y = 20 * sin(12 * time);
		head_X = 0;
		left_arm_X = 180 * sin(12 * time);
		right_arm_X = 180 * sin(12 * time);
	}
	else if (elapsedSeconds > 15 && elapsedSeconds <= 20) {

		right_up_leg_X = 0;
		left_up_leg_X = -50 * sin(12 * time);
		right_down_leg_X = 0;
		left_down_leg_X = -30 * sin(12 * time);
		body_Y = 20 * sin(12 * time);
		head_Y = 20 * sin(12 * time);
		head_X = 0;
		left_arm_X = 180 * sin(12 * time);
		right_arm_X = 180 * sin(12 * time);
	}
	else if (elapsedSeconds > 20 && elapsedSeconds <= 25) {

		right_up_leg_X = 50 * sin(12 * time);
		left_up_leg_X = -50 * sin(12 * time);
		right_down_leg_X = 0;
		left_down_leg_X = -30 * sin(12 * time);
		body_Y = 0;
		head_Y = 0;
		left_arm_X = 180 * sin(12 * time);
		right_arm_X = 180 * sin(12 * time);
	}
	else if (elapsedSeconds > 25 && elapsedSeconds <= 30) {

		right_up_leg_X = 50 * sin(12 * time);
		left_up_leg_X = -50 * sin(12 * time);
		right_down_leg_X = 30 * sin(12 * time);
		left_down_leg_X = -30 * sin(12 * time);
		body_Y = 0;
		head_Y = 0;
		left_arm_X = 70 * sin(6 * time);
		right_arm_X = -70 * sin(6 * time);
	}
	else if (elapsedSeconds > 30 && elapsedSeconds <= 40) {

		right_up_leg_X = 50 * sin(12 * time);
		left_up_leg_X = 0;
		right_down_leg_X = 30 * sin(12 * time);
		left_down_leg_X = 0;
		body_Y = -20 * sin(12 * time);
		head_Y = 20 * sin(12 * time);
		left_arm_Y = 90 * sin(6 * time);
		right_arm_Y = 90 * sin(6 * time);
	}
	else if (elapsedSeconds > 40 && elapsedSeconds <= 45) {

		right_up_leg_X = 0;
		left_up_leg_X = 0;
		right_down_leg_X = 0;
		left_down_leg_X = 0;
		body_Y = 0;
		head_X = 20 * sin(12 * time);
		left_arm_Y = 90 * sin(6 * time);
		right_arm_Y = 90 * sin(6 * time);
	}
	else if (elapsedSeconds > 45 && elapsedSeconds <= 50) {

		right_up_leg_X = 0;
		left_up_leg_X = 0;
		right_down_leg_X = 0;
		left_down_leg_X = 0;
		body_Y = 0;
		head_X = 20 * sin(12 * time);
		left_arm_X = 90 * sin(6 * time);
		left_arm_Y =0;
		right_arm_X = 90 * sin(6 * time);
		right_arm_Y = 0;
	}
	else if (elapsedSeconds > 50 && elapsedSeconds <= 55) {
		right_up_leg_X = 0;
		left_up_leg_X = 0;
		right_down_leg_X = 0;
		left_down_leg_X = 0;
		body_Y = 30 * sin(12 * time);
		head_X = 20 * sin(12 * time);
		left_arm_X = 90 * sin(6 * time);
		left_arm_Y = 0;
		right_arm_X = 90 * sin(6 * time);
		right_arm_Y = 0;
	}
	else if (elapsedSeconds > 55 && elapsedSeconds <= 60) {
		right_up_leg_X = 30;
		left_up_leg_X = 30;
		right_down_leg_X = -30;
		left_down_leg_X = -30;
		//body_Y = 30 * sin(12 * time);
		head_X = 20 * sin(12 * time);
		left_arm_X = 90 * sin(6 * time);
		left_arm_Y = 0;
		right_arm_X = 90 * sin(6 * time);
		right_arm_Y = 0;
		}
	else {
		
		left_arm_X = 0;
		right_arm_X = 0;
		right_up_leg_X = 0;
		left_up_leg_X = 0;
		right_down_leg_X = 0;
		left_down_leg_X = 0;
		body_Y = 0;
		head_Y = 0;
	}

	glutPostRedisplay(); 

	glutTimerFunc(500, timerFunction, 1);
	
}


void main(int argc, char** argv) {
	initSnowflakes();
	PlaySound(TEXT("가요톱쓰리.wav"), 0, SND_FILENAME | SND_ASYNC);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //더블 버퍼 컬러 모드.
	glutInitWindowSize(1200, 980);
	glutInitWindowPosition(90, 90);
	glutCreateWindow("히언이와 으나의 캐롤 메들리><");
	glutTimerFunc(1000, timerFunction, 1);//타이머 설정.
	glutDisplayFunc(robot_Display);
	glInit();
	glutMainLoop();
}
