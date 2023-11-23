#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
static int Dance = 0, a = 20, b = 20, c = 0, d = 0, e=0, f=0, g=0, h=0;

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

//a= ����, b=������ c=�� �ȸ� d=���� �ȸ� e=�� ����� f= ���� ����� g=�� �߸� h=���� �߸�

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	glPopMatrix(); //��
	glPopMatrix(); //����
	glPushMatrix();
	glTranslatef(-0.1, 0.0, 0.0);
	glTranslatef(-0.20, 0.21, 0.0);
	Draw_L_Ball();  //���� �� �κ� ����
	glPushMatrix();
	glRotatef(a, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.22, 0.0);
	glTranslatef(0.0, 0.03, 0.0);
	Draw_L_UpperArm(); //���� �����
	glPushMatrix();
	glTranslatef(0.0, 0.15, 0.0);
	Draw_L_Ball();  //���� �� �κ� ����
	glPushMatrix();
	glRotatef(c, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.25, 0.0);
	glTranslatef(0.0, -0.05, 0.0);
	Draw_L_LowerArm();   //���� �ȸ�
	glPushMatrix();
	glTranslatef(0.0, -0.05, 0.0);
	glTranslatef(0.0, -0.2, 0.0);
	Draw_L_Hand();   //���� ��
	glPopMatrix(); //���� �ȸ�
	glPopMatrix();  //���� �ȸ����
	glPopMatrix();  //���� ���
	glPopMatrix();  //���� �������
	glPopMatrix(); //����
	glPushMatrix();
	glTranslatef(0.1, 0.0, 0.0);
	glTranslatef(0.20, 0.21, 0.0);
	Draw_R_Ball();  //������ �� �κ� ����
	glPushMatrix();
	glRotatef(-b, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.22, 0.0);
	glTranslatef(0.0, 0.03, 0.0);
	Draw_R_UpperArm(); //������ �����
	glPushMatrix();
	glTranslatef(0.0, 0.15, 0.0);
	Draw_R_Ball();  //������ �� �κ� ����
	glPushMatrix();
	glRotatef(d, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.25, 0.0);
	glTranslatef(0.0, -0.05, 0.0);
	Draw_R_LowerArm();   //������ �ȸ�
	glPushMatrix();
	glTranslatef(0.0, -0.05, 0.0);
	glTranslatef(0.0, -0.2, 0.0);
	Draw_R_Hand();   //������ ��
	glPopMatrix(); //������ �ȸ�
	glPopMatrix();  //������ �ȸ����
	glPopMatrix();  //������ ���
	glPopMatrix();  //������ �������
	glPopMatrix(); //����
	glPushMatrix();
	glTranslatef(-0.1, -0.0, 0.0);
	glTranslatef(-0.21, -0.2, 0.0);
	Draw_L_U_Ball();  //���� �ٸ� ���� ����
	glPushMatrix();
	glRotatef(e, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.5, 0.0);
	glTranslatef(0.0, 0.03, 0.0);
	Draw_L_UpperLeg();  //���� �����
	glPushMatrix();
	glTranslatef(0.0, 0.02, 0.0);
	glTranslatef(0.0, 0.18, 0.0);
	Draw_L_U_Ball();  //���� �ٸ� ���� ����
	glPushMatrix();
	glRotatef(g, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.22, 0.0);
	glTranslatef(0.0, -0.02, 0.0);
	Draw_L_LowerLeg();  //���� �ٸ�
	glPushMatrix();
	glTranslatef(0.0, -0.02, 0.0);
	glTranslatef(0.0, -0.13, 0.0);
	Draw_L_Foot();  //���� ��
	glPopMatrix(); //���� �ٸ�
	glPopMatrix();  //�ٸ� ����
	glPopMatrix();  //���� �����
	glPopMatrix(); //���� �ٸ����۰���
	glPopMatrix(); //����
	glTranslatef(0.1, -0.0, 0.0);
	glTranslatef(0.21, -0.2, 0.0);
	Draw_R_U_Ball();  //������ �ٸ� ���� ����
	glPushMatrix();
	glRotatef(f, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.5, 0.0);
	glTranslatef(0.0, 0.03, 0.0);
	Draw_R_UpperLeg();  //������ �����
	glPushMatrix();
	glTranslatef(0.0, 0.02, 0.0);
	glTranslatef(0.0, 0.18, 0.0);
	Draw_R_U_Ball();  //������ �ٸ� ���� ����
	glPushMatrix();
	glRotatef(h, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.22, 0.0);
	glTranslatef(0.0, -0.02, 0.0);
	Draw_R_LowerLeg();  //������ �ٸ�
	glPushMatrix();
	glTranslatef(0.0, -0.02, 0.0);
	glTranslatef(0.0, -0.13, 0.0);
	Draw_R_Foot();  //������ ��
	glPopMatrix(); //������ �ٸ�
	glPopMatrix();  //������ �ٸ� ����
	glPopMatrix();  //������ �����
	glPopMatrix(); //������ �ٸ� ���� ����
	glPopMatrix(); //����

	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
		//a= ����, b=������ c=�� �ȸ� d=���� �ȸ� e=�� ����� f= ���� ����� g=�� �߸� h=���� �߸�
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
		// 'd' Ű�� ������ Dance ������ 10�� ������Ű�� 360���� ���� �������� �����մϴ�.
		// �׸��� ȭ���� �ٽ� �׸����� �մϴ�.
	case 'd':
		Dance = (Dance + 10) % 360;
		glutPostRedisplay();
		break;
		// 'g' Ű�� ������ ���� ����� ���� ���� Ư�� ������ �����ϰ� ȭ���� �ٽ� �׸����� �մϴ�.
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
		
	
		// 'q' Ű�� ������ �� �������� �ʱⰪ���� �����ϰ� Dance ������ 0���� �ʱ�ȭ�� �� ȭ���� �ٽ� �׸����� �մϴ�.
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
	// ������ ũ�⸦ �����մϴ�. X������ 0.2, Y������ 1.0, Z������ 0.3�� ������ Ȯ���մϴ�.
	glScalef(0.2, 0.5, 0.3);
	// ������ ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(0.0, 0.0, 1.0);
	// ������ ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.3�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.3, 100, 100);
}

void Draw_Neck()
{
	// ���� ũ�⸦ �����մϴ�. X������ 2.0, Y������ -0.5, Z������ 1.0�� ������ Ȯ���մϴ�.
	glScalef(2.0, -0.5, 1.0);
	glColor3f(1.0, 0.87, 0.68);
	// ���� ���̾������� �� ���·� �׸��ϴ�.
   // �������� 0.04�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.04, 80, 80);
}

void Draw_L_Ball()
{
	// ���� �ո� �κ��� ũ�⸦ �����մϴ�. X������ 2.0, Y������ -0.5, Z������ 1.0�� ������ Ȯ���մϴ�.
	glScalef(2.0, -0.5, 1.0);
	// ���� �ո� �κ��� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(0.0, 0.0, 1.0);
	// ���� �ո� �κ��� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.04�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.04, 80, 80);
}

void Draw_Eyes() {
	// ù ��° ��
	glColor3f(0.0, 0.0, 0.0); // ���������� ����
	glPushMatrix();
	glTranslatef(-0.1, 0.1, 2.5); // ���� ��ġ ����
	glutSolidSphere(0.03, 20, 20);
	glPopMatrix();

	// �� ��° ��
	glPushMatrix();
	glTranslatef(0.1, 0.1, 2.5); // ���� ��ġ ����
	glutSolidSphere(0.03, 20, 20);
	glPopMatrix();
}

void Draw_Head() {
	glColor3f(1.0, 0.87, 0.68); // �Ӹ��� �⺻ ���� ����
	glutWireSphere(0.25, 90, 90); // �Ӹ� ��� �� ũ�� ����

	// �� �׸���
	glPushMatrix();
	
	Draw_Eyes(); // ������ �� �׸���
	glPopMatrix();

	glPushMatrix();
	
	Draw_Eyes(); // ���� �� �׸���
	glPopMatrix();

}


void Draw_L_UpperArm()
{
	// ���� ��� �� �κ��� ũ�⸦ �����մϴ�. X������ 0.3, Y������ 1.5, Z������ 0.3�� ������ Ȯ���մϴ�.
	glScalef(0.3, 1.5, 0.3);
	// ���� ��� �� �κ��� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(0.0, 0.0, 1.0);
	// ���� ��� �� �κ��� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.15�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.15, 80, 80);
}

void Draw_L_LowerArm()
{
	// ���� �ϴ� �� �κ�(�ȸ�)�� ũ�⸦ �����մϴ�. X������ 0.2, Y������ 1.5, Z������ 0.3�� ������ Ȯ���մϴ�.
	glScalef(0.2, 1.5, 0.3);
	// ���� �ϴ� �� �κ�(�ȸ�)�� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(0.0, 0.0, 1.0);
	// ���� �ϴ� �� �κ�(�ȸ�)�� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.2�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.2, 80, 80);
}

void Draw_L_Hand()
{
	// ���� ���� ũ�⸦ �����մϴ�. X������ 1.0, Y������ -0.5, Z������ 1.0�� ������ Ȯ���մϴ�.
	glScalef(4.0, -0.5, 4.0);
	// ���� ���� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(1.0, 0.87, 0.68);
	// ���� ���� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.1�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.1, 80, 80);
}

void Draw_R_Ball()
{
	// ������ �ո� �κ��� ũ�⸦ �����մϴ�. X������ 2.0, Y������ -0.5, Z������ 1.0�� ������ Ȯ���մϴ�.
	glScalef(2.0, -0.5, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	// ������ �ո� �κ��� ���̾������� �� ���·� �׸��ϴ�.
// �������� 0.04�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.04, 80, 80);
}

void Draw_R_UpperArm()
{
	// ������ ��� �� �κ��� ũ�⸦ �����մϴ�. X������ 0.3, Y������ 1.5, Z������ 0.3�� ������ Ȯ���մϴ�.
	glScalef(0.3, 1.5, 0.3);
	glColor3f(0.0, 0.0, 1.0);
	// ������ ��� �� �κ��� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.15�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.15, 80, 80);
}

void Draw_R_LowerArm()
{
	// ������ �ϴ� �� �κ�(�ȸ�)�� ũ�⸦ �����մϴ�. X������ 0.2, Y������ 1.5, Z������ 0.3�� ������ Ȯ���մϴ�.
	glScalef(0.2, 1.5, 0.3);
	glColor3f(0.0, 0.0, 1.0);
	// ������ �ϴ� �� �κ�(�ȸ�)�� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.2�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.2, 80, 80);
}

void Draw_R_Hand() {
	// ������ ���� ũ�⸦ �����մϴ�. X������ 1.0, Y������ -0.5, Z������ 1.0�� ������ Ȯ���մϴ�.
	glScalef(4.0, -0.5, 4.0);

	// ������ ���� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(1.0, 0.87, 0.68);

	// ������ ���� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.1�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.1, 80, 80);
}

void Draw_L_U_Ball() {
	// ���� ��� �ٸ��� ���� �κ��� ũ�⸦ �����մϴ�. X������ 2.0, Y������ -0.5, Z������ 1.0�� ������ Ȯ���մϴ�.
	glScalef(2.0, -0.5, 1.0);

	// ���� ��� �ٸ��� ���� �κ��� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(0.0, 0.0, 1.0);

	// ���� ��� �ٸ��� ���� �κ��� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.04�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.04, 80, 80);
}

void Draw_L_UpperLeg() {
	// ���� ����� �κ��� ũ�⸦ �����մϴ�. X������ 0.25, Y������ 2.5, Z������ 0.3�� ������ Ȯ���մϴ�.
	glScalef(0.25, 2.0, 0.3);

	// ���� ����� �κ��� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(0.0, 0.0, 1.0);

	// ���� ����� �κ��� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.2�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.2, 80, 80);
}

void Draw_L_LowerLeg() {
	// ���� �Ʒ��� �ٸ� �κ��� ũ�⸦ �����մϴ�. X������ 0.5, Y������ 1.5, Z������ 0.3�� ������ Ȯ���մϴ�.
	glScalef(0.5, 1.5, 0.3);

	// ���� �Ʒ��� �ٸ� �κ��� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(0.0, 0.0, 1.0);

	// ���� �Ʒ��� �ٸ� �κ��� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.15�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.15, 80, 80);
}

void Draw_L_Foot() {
	// ���� �� �κ��� ũ�⸦ �����մϴ�. X������ 3.0, Y������ 0.1, Z������ 0.3�� ������ Ȯ���մϴ�.
	glScalef(3.0, 0.4, 1.0);

	// ���� �� �κ��� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(1.0, 0.87, 0.68);

	// ���� �� �κ��� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.1�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.1, 80, 80);
}


void Draw_R_U_Ball() {
	// ������ �ٸ��� ���� �κ� ���� ũ�⸦ �����մϴ�. X������ 2.0, Y������ -0.5, Z������ 1.0�� ������ Ȯ���մϴ�.
	glScalef(2.0, -0.5, 1.0);

	// ������ �ٸ��� ���� �κ� ������ ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(0.0, 0.0, 1.0);

	// ������ �ٸ��� ���� �κ� ������ ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.04�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.04, 80, 80);
}


void Draw_R_UpperLeg() {
	// ������ ����� �κ��� ũ�⸦ �����մϴ�. X������ 0.25, Y������ 2.5, Z������ 0.3�� ������ Ȯ���մϴ�.
	glScalef(0.25, 2.0, 0.3);

	// ������ ����� �κ��� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(0.0, 0.0, 1.0);

	// ������ ����� �κ��� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.2�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.2, 80, 80);
}


void Draw_R_LowerLeg() {
	// ������ ���Ƹ� �κ��� ũ�⸦ �����մϴ�. X������ 0.5, Y������ 1.5, Z������ 0.3�� ������ Ȯ���մϴ�.
	glScalef(0.5, 1.5, 0.3);

	// ������ ���Ƹ� �κ��� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(0.0, 0.0, 1.0);

	// ������ ���Ƹ� �κ��� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.15�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.15, 80, 80);
}


void Draw_R_Foot() {
	// ������ �� �κ��� ũ�⸦ �����մϴ�. X������ 3.0, Y������ 0.1, Z������ 1.0�� ������ Ȯ���մϴ�.
	glScalef(3.0, 0.4, 1.0);

	// ������ �� �κ��� ������ �����մϴ�. �Ķ������� �����մϴ�.
	glColor3f(1.0, 0.87, 0.68);

	// ������ �� �κ��� ���̾������� �� ���·� �׸��ϴ�.
	// �������� 0.1�̸�, ���� �� ���ο� 20���� �����̽� �� ������ ���� ���� �׸��ϴ�.
	glutWireSphere(0.1, 80, 80);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 980);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("human");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}