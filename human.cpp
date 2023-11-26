#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
static int Dance = 0, a = 20, b = 20, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;

void Draw_Body();
void Draw_Neck();
void Draw_Head();
void Draw_L_Ball();
void Draw_L_UpperArm();
void Draw_L_LowerArm();
void Draw_L_Hand();
void Draw_R_Ball();
void Draw_R_UpperArm();
void Draw_R_LowerArm();
void Draw_R_Hand();
void Draw_L_U_Ball();
void Draw_L_UpperLeg();
void Draw_L_LowerLeg();
void Draw_L_Foot();
void Draw_R_U_Ball();
void Draw_R_UpperLeg();
void Draw_R_LowerLeg();
void Draw_R_Foot();
void drawFilledCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks);
//a= 왼팔, b=오른팔 c=왼 팔목 d=오른 팔목 e=왼 허벅지 f= 오른 허벅지 g=왼 발목 h=오른 발목

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)Dance, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.31, 0.0);
	Draw_Body();
	glPushMatrix();
	glTranslatef(0.0, 0.02, 0.0);
	glTranslatef(0.0, 0.3, 0.0);
	Draw_Neck();
	glPushMatrix();
	glTranslatef(0.0, -0.19, 0.0);
	glTranslatef(0.0, -0.05, 0.0);
	Draw_Head();
	glPopMatrix(); //목
	glPopMatrix(); //몸통
	glPushMatrix();
	glTranslatef(-0.1, 0.0, 0.0);
	glTranslatef(-0.20, 0.21, 0.0);
	Draw_L_Ball();  //왼쪽 팔 부분 시작
	glPushMatrix();
	glRotatef(a, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.22, 0.0);
	glTranslatef(0.0, 0.03, 0.0);
	Draw_L_UpperArm(); //왼쪽 어깨쪽
	glPushMatrix();
	glTranslatef(0.0, 0.15, 0.0);
	Draw_L_Ball();  //왼쪽 팔 부분 시작
	glPushMatrix();
	glRotatef(c, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.25, 0.0);
	glTranslatef(0.0, -0.05, 0.0);
	Draw_L_LowerArm();   //왼쪽 팔목
	glPushMatrix();
	glTranslatef(0.0, -0.05, 0.0);
	glTranslatef(0.0, -0.2, 0.0);
	Draw_L_Hand();   //왼쪽 손
	glPopMatrix(); //왼쪽 팔목
	glPopMatrix();  //왼쪽 팔목관절
	glPopMatrix();  //왼쪽 어깨
	glPopMatrix();  //왼쪽 어깨관절
	glPopMatrix(); //몸통
	glPushMatrix();
	glTranslatef(0.1, 0.0, 0.0);
	glTranslatef(0.20, 0.21, 0.0);
	Draw_R_Ball();  //오른쪽 팔 부분 시작
	glPushMatrix();
	glRotatef(-b, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.22, 0.0);
	glTranslatef(0.0, 0.03, 0.0);
	Draw_R_UpperArm(); //오른쪽 어깨쪽
	glPushMatrix();
	glTranslatef(0.0, 0.15, 0.0);
	Draw_R_Ball();  //오른쪽 팔 부분 시작
	glPushMatrix();
	glRotatef(d, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.25, 0.0);
	glTranslatef(0.0, -0.05, 0.0);
	Draw_R_LowerArm();   //오른쪽 팔목
	glPushMatrix();
	glTranslatef(0.0, -0.05, 0.0);
	glTranslatef(0.0, -0.2, 0.0);
	Draw_R_Hand();   //오른쪽 손
	glPopMatrix(); //오른쪽 팔목
	glPopMatrix();  //오른쪽 팔목관절
	glPopMatrix();  //오른쪽 어깨
	glPopMatrix();  //오른쪽 어깨관절
	glPopMatrix(); //몸통
	glPushMatrix();
	glTranslatef(-0.1, -0.0, 0.0);
	glTranslatef(-0.21, -0.2, 0.0);
	Draw_L_U_Ball();  //왼쪽 다리 시작 관절
	glPushMatrix();
	glRotatef(e, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.5, 0.0);
	glTranslatef(0.0, 0.03, 0.0);
	Draw_L_UpperLeg();  //왼쪽 허벅지
	glPushMatrix();
	glTranslatef(0.0, 0.02, 0.0);
	glTranslatef(0.0, 0.18, 0.0);
	Draw_L_U_Ball();  //왼쪽 다리 시작 관절
	glPushMatrix();
	glRotatef(g, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.22, 0.0);
	glTranslatef(0.0, -0.02, 0.0);
	Draw_L_LowerLeg();  //왼쪽 다리
	glPushMatrix();
	glTranslatef(0.0, -0.02, 0.0);
	glTranslatef(0.0, -0.13, 0.0);
	Draw_L_Foot();  //왼쪽 발
	glPopMatrix(); //왼쪽 다리
	glPopMatrix();  //다리 관절
	glPopMatrix();  //왼쪽 허벅지
	glPopMatrix(); //왼쪽 다리시작관절
	glPopMatrix(); //몸통
	glTranslatef(0.1, -0.0, 0.0);
	glTranslatef(0.21, -0.2, 0.0);
	Draw_R_U_Ball();  //오른쪽 다리 시작 관절
	glPushMatrix();
	glRotatef(f, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.5, 0.0);
	glTranslatef(0.0, 0.03, 0.0);
	Draw_R_UpperLeg();  //오른쪽 허벅지
	glPushMatrix();
	glTranslatef(0.0, 0.02, 0.0);
	glTranslatef(0.0, 0.18, 0.0);
	Draw_R_U_Ball();  //오른쪽 다리 시작 관절
	glPushMatrix();
	glRotatef(h, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.22, 0.0);
	glTranslatef(0.0, -0.02, 0.0);
	Draw_R_LowerLeg();  //오른쪽 다리
	glPushMatrix();
	glTranslatef(0.0, -0.02, 0.0);
	glTranslatef(0.0, -0.13, 0.0);
	Draw_R_Foot();  //오른쪽 발
	glPopMatrix(); //오른쪽 다리
	glPopMatrix();  //오른쪽 다리 관절
	glPopMatrix();  //오른쪽 허벅지
	glPopMatrix(); //오른쪽 다리 시작 관절
	glPopMatrix(); //몸통

	glColor3f(1.0, 1.0, 1.0);  // 흰색
	drawFilledCylinder(2.0, 0.2, 20, 10);

	// 두 번째 원기둥
	glColor3f(1.0, 1.0, 1.0);  // 흰색
	glTranslatef(0.0, 0.0, 0.2);
	drawFilledCylinder(2.5, 0.4, 20, 10);
	glPopMatrix();

	glutSwapBuffers();
}

void drawFilledCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks) {
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, radius, radius, height, slices, stacks);
	gluDeleteQuadric(quadric);
}


void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
		//a= 왼팔, b=오른팔 c=왼 팔목 d=오른 팔목 e=왼 허벅지 f= 오른 허벅지 g=왼 발목 h=오른 발목
	case 'a':
		a = 90;
		b = 90;
		c = -90;
		d = -90;
		Dance = 0;
		glutPostRedisplay();
		break;
	case 'b':
		a = 90;
		b = 90;
		c = 90;
		d = 90;
		Dance = 0;
		glutPostRedisplay();
		break;
	case 'c':
		e = 40;
		f = -40;
		g = 80;
		h = -80;
		Dance = 0;
		glutPostRedisplay();
		break;
		// 'd' 키를 누르면 Dance 변수를 10씩 증가시키고 360으로 나눈 나머지를 대입합니다.
		// 그리고 화면을 다시 그리도록 합니다.
	case 'd':
		Dance = (Dance + 10) % 360;
		glutPostRedisplay();
		break;
		// 'g' 키를 누르면 왼쪽 어깨와 왼쪽 팔을 특정 각도로 설정하고 화면을 다시 그리도록 합니다.
	case 'g':
		a = 90;
		b = 90;
		glutPostRedisplay();
		break;
	case 'e':
		a = 180;
		b = 180;
		glutPostRedisplay();
		break;


		// 'q' 키를 누르면 각 변수들을 초기값으로 설정하고 Dance 변수도 0으로 초기화한 후 화면을 다시 그리도록 합니다.
	case 'q':
		a = 20;
		b = 20;
		c = 0;
		d = 0;
		e = 0;
		f = 0;
		h = 0;
		g = 0;
		Dance = 0;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}

void Draw_Body()
{
	// 몸통의 크기를 조절합니다. X축으로 0.2, Y축으로 1.0, Z축으로 0.3의 비율로 확대합니다.
	glScalef(0.2, 0.5, 0.3);
	// 몸통의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(0.0, 0.0, 1.0);
	// 몸통을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.3이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.3, 100, 100);
}

void Draw_Neck()
{
	// 목의 크기를 조절합니다. X축으로 2.0, Y축으로 -0.5, Z축으로 1.0의 비율로 확대합니다.
	glScalef(2.0, -0.5, 1.0);
	glColor3f(1.0, 0.87, 0.68);
	// 목을 와이어프레임 구 형태로 그립니다.
   // 반지름이 0.04이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.04, 80, 80);
}

void Draw_L_Ball()
{
	// 왼쪽 손목 부분의 크기를 조절합니다. X축으로 2.0, Y축으로 -0.5, Z축으로 1.0의 비율로 확대합니다.
	glScalef(2.0, -0.5, 1.0);
	// 왼쪽 손목 부분의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(0.0, 0.0, 1.0);
	// 왼쪽 손목 부분을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.04이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.04, 80, 80);
}

void Draw_Eyes() {
	// 첫 번째 눈
	glColor3f(0.0, 0.0, 0.0); // 검정색으로 설정
	glPushMatrix();
	glTranslatef(-0.1, 0.1, 2.5); // 눈의 위치 조절
	glutSolidSphere(0.03, 20, 20);
	glPopMatrix();

	// 두 번째 눈
	glPushMatrix();
	glTranslatef(0.1, 0.1, 2.5); // 눈의 위치 조절
	glutSolidSphere(0.03, 20, 20);
	glPopMatrix();
}

void Draw_Head() {
	glColor3f(1.0, 0.87, 0.68); // 머리의 기본 색상 설정
	glutWireSphere(0.25, 90, 90); // 머리 모양 및 크기 설정

	// 눈 그리기
	glPushMatrix();

	Draw_Eyes(); // 오른쪽 눈 그리기
	glPopMatrix();

	glPushMatrix();

	Draw_Eyes(); // 왼쪽 눈 그리기
	glPopMatrix();

}


void Draw_L_UpperArm()
{
	// 왼쪽 상단 팔 부분의 크기를 조절합니다. X축으로 0.3, Y축으로 1.5, Z축으로 0.3의 비율로 확대합니다.
	glScalef(0.3, 1.5, 0.3);
	// 왼쪽 상단 팔 부분의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(0.0, 0.0, 1.0);
	// 왼쪽 상단 팔 부분을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.15이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.15, 80, 80);
}

void Draw_L_LowerArm()
{
	// 왼쪽 하단 팔 부분(팔목)의 크기를 조절합니다. X축으로 0.2, Y축으로 1.5, Z축으로 0.3의 비율로 확대합니다.
	glScalef(0.2, 1.5, 0.3);
	// 왼쪽 하단 팔 부분(팔목)의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(0.0, 0.0, 1.0);
	// 왼쪽 하단 팔 부분(팔목)을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.2이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.2, 80, 80);
}

void Draw_L_Hand()
{
	// 왼쪽 손의 크기를 조절합니다. X축으로 1.0, Y축으로 -0.5, Z축으로 1.0의 비율로 확대합니다.
	glScalef(4.0, -0.5, 4.0);
	// 왼쪽 손의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(1.0, 0.87, 0.68);
	// 왼쪽 손을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.1이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.1, 80, 80);
}

void Draw_R_Ball()
{
	// 오른쪽 손목 부분의 크기를 조절합니다. X축으로 2.0, Y축으로 -0.5, Z축으로 1.0의 비율로 확대합니다.
	glScalef(2.0, -0.5, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	// 오른쪽 손목 부분을 와이어프레임 구 형태로 그립니다.
// 반지름이 0.04이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.04, 80, 80);
}

void Draw_R_UpperArm()
{
	// 오른쪽 상단 팔 부분의 크기를 조절합니다. X축으로 0.3, Y축으로 1.5, Z축으로 0.3의 비율로 확대합니다.
	glScalef(0.3, 1.5, 0.3);
	glColor3f(0.0, 0.0, 1.0);
	// 오른쪽 상단 팔 부분을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.15이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.15, 80, 80);
}

void Draw_R_LowerArm()
{
	// 오른쪽 하단 팔 부분(팔목)의 크기를 조절합니다. X축으로 0.2, Y축으로 1.5, Z축으로 0.3의 비율로 확대합니다.
	glScalef(0.2, 1.5, 0.3);
	glColor3f(0.0, 0.0, 1.0);
	// 오른쪽 하단 팔 부분(팔목)을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.2이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.2, 80, 80);
}

void Draw_R_Hand() {
	// 오른쪽 손의 크기를 조절합니다. X축으로 1.0, Y축으로 -0.5, Z축으로 1.0의 비율로 확대합니다.
	glScalef(4.0, -0.5, 4.0);

	// 오른쪽 손의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(1.0, 0.87, 0.68);

	// 오른쪽 손을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.1이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.1, 80, 80);
}

void Draw_L_U_Ball() {
	// 왼쪽 상단 다리의 시작 부분의 크기를 조절합니다. X축으로 2.0, Y축으로 -0.5, Z축으로 1.0의 비율로 확대합니다.
	glScalef(2.0, -0.5, 1.0);

	// 왼쪽 상단 다리의 시작 부분의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(0.0, 0.0, 1.0);

	// 왼쪽 상단 다리의 시작 부분을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.04이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.04, 80, 80);
}

void Draw_L_UpperLeg() {
	// 왼쪽 허벅지 부분의 크기를 조절합니다. X축으로 0.25, Y축으로 2.5, Z축으로 0.3의 비율로 확대합니다.
	glScalef(0.25, 2.0, 0.3);

	// 왼쪽 허벅지 부분의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(0.0, 0.0, 1.0);

	// 왼쪽 허벅지 부분을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.2이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.2, 80, 80);
}

void Draw_L_LowerLeg() {
	// 왼쪽 아래쪽 다리 부분의 크기를 조절합니다. X축으로 0.5, Y축으로 1.5, Z축으로 0.3의 비율로 확대합니다.
	glScalef(0.5, 1.5, 0.3);

	// 왼쪽 아래쪽 다리 부분의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(0.0, 0.0, 1.0);

	// 왼쪽 아래쪽 다리 부분을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.15이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.15, 80, 80);
}

void Draw_L_Foot() {
	// 왼쪽 발 부분의 크기를 조절합니다. X축으로 3.0, Y축으로 0.1, Z축으로 0.3의 비율로 확대합니다.
	glScalef(3.0, 0.4, 1.0);

	// 왼쪽 발 부분의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(1.0, 0.87, 0.68);

	// 왼쪽 발 부분을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.1이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.1, 80, 80);
}


void Draw_R_U_Ball() {
	// 오른쪽 다리의 시작 부분 관절 크기를 조절합니다. X축으로 2.0, Y축으로 -0.5, Z축으로 1.0의 비율로 확대합니다.
	glScalef(2.0, -0.5, 1.0);

	// 오른쪽 다리의 시작 부분 관절의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(0.0, 0.0, 1.0);

	// 오른쪽 다리의 시작 부분 관절을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.04이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.04, 80, 80);
}


void Draw_R_UpperLeg() {
	// 오른쪽 허벅지 부분의 크기를 조절합니다. X축으로 0.25, Y축으로 2.5, Z축으로 0.3의 비율로 확대합니다.
	glScalef(0.25, 2.0, 0.3);

	// 오른쪽 허벅지 부분의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(0.0, 0.0, 1.0);

	// 오른쪽 허벅지 부분을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.2이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.2, 80, 80);
}


void Draw_R_LowerLeg() {
	// 오른쪽 종아리 부분의 크기를 조절합니다. X축으로 0.5, Y축으로 1.5, Z축으로 0.3의 비율로 확대합니다.
	glScalef(0.5, 1.5, 0.3);

	// 오른쪽 종아리 부분의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(0.0, 0.0, 1.0);

	// 오른쪽 종아리 부분을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.15이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.15, 80, 80);
}


void Draw_R_Foot() {
	// 오른쪽 발 부분의 크기를 조절합니다. X축으로 3.0, Y축으로 0.1, Z축으로 1.0의 비율로 확대합니다.
	glScalef(3.0, 0.4, 1.0);

	// 오른쪽 발 부분의 색상을 설정합니다. 파란색으로 설정합니다.
	glColor3f(1.0, 0.87, 0.68);

	// 오른쪽 발 부분을 와이어프레임 구 형태로 그립니다.
	// 반지름이 0.1이며, 가로 및 세로에 20개의 슬라이스 및 스택을 가진 구를 그립니다.
	glutWireSphere(0.1, 80, 80);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 980);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("human");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 0.1, 100.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}
