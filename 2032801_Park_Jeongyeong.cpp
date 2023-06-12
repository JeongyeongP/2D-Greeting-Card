#define FREEGLUT_STATIC
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>

typedef struct { GLfloat x, y; } point;
point p0 = { 0,0 };
float t = 0.0;
float r_a = 0.0;
float s = 0.0;

GLfloat step = 10; // declare incremental step
int time_interval = 800; // declare refresh interval in ms
void when_in_mainloop()
{ // idle callback function
	glutPostRedisplay(); // force OpenGL to redraw the current window
}
void OnTimer(int value)
{	
	//for p0.x
	p0.x += step;
	if (p0.x > 220)
		p0.x = 0;
	else if (p0.x <= 0)
		p0.x = 110;
	//for p0.y
	p0.y += step;
	if (p0.y > 120)
		p0.y = 0;
	else if (p0.y < 0)
		p0.y = 40;
	
	when_in_mainloop();
	glutTimerFunc(time_interval, OnTimer, 1);
}

bool flag1, flag2;
void mouse_input(int button, int state, int x, int y) {
	//Left button
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (flag1 == false)
			flag1 = true;
		else
			flag1 = false;
	}
	//Right button
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		if (flag2 == false)
			flag2 = true;
		else
			flag2 = false;
	}
}

void keyboard_input(unsigned char key, int x, int y) {

	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 'c' || key == 'C') // change direction of movement
		step = -step;
	else if (key == 's' || key == 'S') // stop movement
		step = 0;
	else if (key == 'r' || key == 'R') // reset step (resume movement)
		step = 10;
}

double spin;
void Spin(int value) {
	spin = spin + step;
	if (spin > 50)
		spin = spin - 50;
	else if (spin <= -30) //in order not to invade the ground part
		spin = spin + 80;
	when_in_mainloop();
	glutTimerFunc(time_interval, Spin, 1);
}
void star(void) {

	glColor3f(1, 0.843, 0);
	glPushMatrix();
	glScalef(0.5, 0.5, 0);
	glRotatef(spin, 0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(110, 320);
	glVertex2f(130, 300);
	glVertex2f(120, 330);
	glVertex2f(140, 340);
	glVertex2f(118, 340);
	glVertex2f(110, 360);
	glVertex2f(102, 340);
	glVertex2f(80, 340);
	glVertex2f(100, 330);
	glVertex2f(90, 300);
	glEnd();
	glPopMatrix();

}

void moon(double a, double b) {

	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		double angle = i * 3.141592 / 180;
		double x = 30 * cos(angle);
		double y = 30 * sin(angle);
		glVertex2f(x + a, y + b);
	}
	glEnd();
	
}

void circle_Tree(double a, double b, double r) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		double angle = i * 3.141592 / 180;
		double x = r * cos(angle);
		double y = r * sin(angle);

		glVertex2f(x + a, y + b);
	}
	glEnd();
}

void Tree(void) {
	glColor3f(0.63, 0.32, 0.18);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glVertex2f(780, 20);
	glVertex2f(800, 20);
	glVertex2f(790, 80);
	glEnd();
	//Leaves
	glColor3f(0, 0.39, 0);
	circle_Tree(790, 100, 15);
	glColor3f(0, 0.50, 0);
	circle_Tree(780, 80, 15);
	glColor3f(0.13, 0.55, 0.13);
	circle_Tree(800, 80, 15);
	glColor3f(0.18, 0.55, 0.34);
	circle_Tree(770, 60, 15);
	glColor3f(0.235, 0.70, 0.44);
	circle_Tree(790, 60, 15);
	glColor3f(0.60, 0.80, 0.20);
	circle_Tree(810, 60, 15);
}

void circle_Cloud(double a, double b) {

	double c_r = 20;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		double angle = i * 3.141592 / 180;
		double x = c_r * cos(angle);
		double y = c_r * sin(angle);

		glVertex2f(x + a + p0.x, y + b);
	}
	glEnd();
}

void circle_Ballon(double a, double b) {
	glBegin(GL_POLYGON);
	double r = 20;
	for (int i = 0; i < 360; i++)
	{
		double angle = i * 3.141592 / 180;
		double x = r * cos(angle);
		double y = r * sin(angle);
		glVertex2f(x + a, y + b + p0.y);
	}
	glEnd();
}

void circle_Heart(double a, double b) {
	glBegin(GL_POLYGON);
	double r = 10;
	for (int i = 0; i <= 180; i++) {
		double angle = i * 3.141592 / 180;
		double x = r * cos(angle);
		double y = r * sin(angle);
		glVertex2f(x + a, y + b);
	}
	glEnd();
}

void text(double a, double b, double c, double d) {
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex2f(a, b);
	glVertex2f(c, d);
	glEnd();
}

void full_text(void) {
	//text 15th anniversary
	//1
	text(85, 120, 85, 80);
	//5
	glBegin(GL_LINE_STRIP);
	glVertex2f(115, 120);
	glVertex2f(95, 120);
	glVertex2f(95, 100);
	glVertex2f(115, 100);
	glVertex2f(115, 80);
	glVertex2f(95, 80);
	glEnd();
	//th
	text(125, 120, 125, 135);
	text(120, 130, 130, 130);
	text(131, 135, 131, 120);
	text(131, 128, 136, 128);
	text(136, 128, 136, 128);
	text(136, 128, 136, 120);
	//A
	text(160, 80, 160, 120);
	text(160, 120, 180, 120);
	text(180, 80, 180, 120);
	text(160, 100, 180, 100);
	//NN
	text(190, 80, 190, 120);
	text(190, 120, 210, 80);
	text(210, 80, 210, 120);
	text(220, 80, 220, 120);
	text(220, 120, 240, 80);
	text(240, 80, 240, 120);
	//I
	text(250, 120, 270, 120);
	text(260, 80, 260, 120);
	text(250, 80, 270, 80);
	//V
	text(280, 120, 290, 80);
	text(300, 120, 290, 80);
	//E
	text(310, 120, 330, 120);
	text(310, 80, 310, 120);
	text(310, 100, 330, 100);
	text(310, 80, 330, 80);
	//R
	text(340, 80, 340, 120);
	text(340, 120, 360, 120);
	text(360, 120, 360, 100);
	text(340, 100, 360, 100);
	text(340, 100, 360, 80);
	//S
	glBegin(GL_LINE_STRIP);
	glVertex2f(390, 120);
	glVertex2f(370, 120);
	glVertex2f(370, 100);
	glVertex2f(390, 100);
	glVertex2f(390, 80);
	glVertex2f(370, 80);
	glEnd();
	//A
	text(400, 80, 400, 120);
	text(400, 120, 420, 120);
	text(420, 80, 420, 120);
	text(400, 100, 420, 100);
	//R
	text(430, 80, 430, 120);
	text(430, 120, 450, 120);
	text(450, 120, 450, 100);
	text(430, 100, 450, 100);
	text(430, 100, 450, 80);
	//Y
	text(460, 120, 470, 100);
	text(480, 120, 470, 100);
	text(470, 100, 470, 80);
	//heart
	glColor3f(0.863, 0.078, 0.235);
	circle_Heart(500, 110);
	circle_Heart(520, 110);
	glBegin(GL_TRIANGLES);
	glVertex2f(490, 110);
	glVertex2f(530, 110);
	glVertex2f(510, 80);
	glEnd();
}

void celebration(void) {
	//text Congratualtion
	glColor3f(0.294, 0, 0.510);
	//c
	text(-980, -240, -940, -240);
	text(-980, -240, -980, -320);
	text(-980, -320, -940, -320);
	//o
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex2f(-920, -240);
	glVertex2f(-920, -320);
	glVertex2f(-880, -320);
	glVertex2f(-880, -240);
	glEnd();
	//n
	text(-860, -240, -860, -320);
	text(-860, -240, -820, -320);
	text(-820, -240, -820, -320);
	//g
	text(-760, -240, -800, -240);
	text(-800, -240, -800, -320);
	text(-800, -320, -760, -320);
	text(-760, -320, -760, -300);
	text(-760, -300, -780, -300);
	//r
	glBegin(GL_POLYGON);
	glVertex2f(-740, -240);
	glVertex2f(-740, -260);
	glVertex2f(-700, -260);
	glVertex2f(-700, -240);
	glEnd();
	text(-740, -260, -740, -320);
	text(-740, -260, -700, -320);
	//a
	glBegin(GL_POLYGON);
	glVertex2f(-680, -240);
	glVertex2f(-680, -260);
	glVertex2f(-640, -260);
	glVertex2f(-640, -240);
	glEnd();
	text(-680, -260, -680, -320);
	text(-640, -260, -640, -320);
	//t
	text(-620, -240, -580, -240);
	text(-600, -240, -600, -320);
	//s
	glBegin(GL_LINE_STRIP);
	glVertex2f(-520, -240);
	glVertex2f(-560, -240);
	glVertex2f(-560, -260);
	glVertex2f(-520, -260);
	glVertex2f(-520, -320);
	glVertex2f(-560, -320);
	glEnd();
	//!
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(-500, -240);
	glVertex2f(-500, -300);
	glVertex2f(-490, -300);
	glVertex2f(-490, -240);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-500, -310);
	glVertex2f(-500, -320);
	glVertex2f(-490, -320);
	glVertex2f(-490, -310);
	glEnd();
	//x
	text(-440, -240, -400, -320);
	text(-400, -240, -440, -320);
	//j
	glBegin(GL_LINE_STRIP);
	glVertex2f(-380, -240);
	glVertex2f(-340, -240);
	glVertex2f(-360, -240);
	glVertex2f(-360, -320);
	glVertex2f(-380, -320);
	glEnd();
	//t
	glBegin(GL_LINE_STRIP);
	glVertex2f(-320, -240);
	glVertex2f(-280, -240);
	glVertex2f(-300, -240);
	glVertex2f(-300, -320);
	glEnd();
	//l
	glBegin(GL_LINE_STRIP);
	glVertex2f(-260, -240);
	glVertex2f(-260, -320);
	glVertex2f(-220, -320);
	glEnd();
	//u
	glBegin(GL_LINE_STRIP);
	glVertex2f(-200, -240);
	glVertex2f(-200, -320);
	glVertex2f(-160, -320);
	glVertex2f(-160, -240);
	glEnd();
	//smile
	glColor3f(1, 0.647, 0);
	glBegin(GL_POLYGON);
	glVertex2f(-110, -250);
	glVertex2f(-100, -250);
	glVertex2f(-100, -270);
	glVertex2f(-110, -270);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-70, -250);
	glVertex2f(-80, -250);
	glVertex2f(-80, -270);
	glVertex2f(-70, -270);
	glEnd();
	glBegin(GL_POLYGON);
	double ra = 40;
	for (int i = 0; i <= 180; i++)
	{
		double angle = i * 3.141592 / -180;
		double x = ra * cos(angle);
		double y = ra * sin(angle);
		glVertex2f(x - 90, y - 280);
	}
	glEnd();
	glColor3f(0.96, 1, 1);
	glBegin(GL_POLYGON);
	ra = 30;
	for (int i = 0; i <= 180; i++)
	{
		double angle = i * 3.141592 / -180;
		double x = ra * cos(angle);
		double y = ra * sin(angle);
		glVertex2f(x - 90, y - 280);
	}
	glEnd();
	//Decoration Sine Waves
	glPointSize(2);
	glColor3f(0.416, 0.353, 0.804);
	float x, y;
	int i;
	for (i = 0; i > -1000; i = i - 5)
	{
		x = (float)i;
		y = 20 * sin(2 * (i * (3.141592 / 180))- p0.x) - 400;
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
	for (i = 0; i > -1000; i = i - 5)
	{
		x = (float)i;
		y = 20 * sin(2 * (i * (3.141592 / 180)) - p0.x) - 150;
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();

	}
}
void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (flag2 == false) {
		gluOrtho2D(0, 1000, 0, 600); //sets up a 2d orthographic viewing region for day version
	}
	else if (flag2 == true) {
		gluOrtho2D(-1000, 0, -600, 0); //for night version
	}
	glClearColor(0.96, 1, 1, 0); //pale skyBlue value should be 0-1 rgb value/255
	glClear(GL_COLOR_BUFFER_BIT);

	//sky
	glColor3f(0.910, 0.957, 1);
	glBegin(GL_POLYGON);
	glVertex2f(0, 220);
	glVertex2f(0, 600);
	glVertex2f(1000, 600);
	glVertex2f(1000, 220);
	glEnd();

	//Balloons_1
	glLineWidth(1);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(920, 580 + p0.y);
	glVertex2f(920, 540 + p0.y);
	glEnd();
	//circle
	glColor3f(0.251, 0.878, 0.816);
	circle_Ballon(920, 580);
	//balloon bottom
	glBegin(GL_TRIANGLES);
	glVertex2f(920, 565 + p0.y);
	glVertex2f(916, 555 + p0.y);
	glVertex2f(924, 555 + p0.y);
	glEnd();

	//Balloons_2
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(700, 520 + p0.y);
	glVertex2f(700, 480 + p0.y);
	glEnd();
	//circle
	glColor3f(0.941, 0.902, 0.549);
	circle_Ballon(700, 520);
	glBegin(GL_TRIANGLES);
	glVertex2f(700, 505 + p0.y);
	glVertex2f(696, 495 + p0.y);
	glVertex2f(704, 495 + p0.y);
	glEnd();

	//Balloons_3
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(200, 580 + p0.y);
	glVertex2f(200, 540 + p0.y);
	glEnd();
	//circle
	glColor3f(0.847, 0.749, 0.847);
	circle_Ballon(200, 580);
	glBegin(GL_TRIANGLES);
	glVertex2f(200, 565 + p0.y);
	glVertex2f(196, 555 + p0.y);
	glVertex2f(204, 555 + p0.y);
	glEnd();

	//Balloons_4
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(20, 540 + p0.y);
	glVertex2f(20, 500 + p0.y);
	glEnd();
	//circle
	glColor3f(0.545, 0, 0.545);
	circle_Ballon(20, 540);
	glBegin(GL_TRIANGLES);
	glVertex2f(20, 525 + p0.y);
	glVertex2f(16, 515 + p0.y);
	glVertex2f(24, 515 + p0.y);
	glEnd();

	//Cloud1
	glColor3f(0.690, 0.878, 0.902);
	circle_Cloud(100, 400);
	circle_Cloud(80, 420);
	circle_Cloud(100, 440);
	circle_Cloud(130, 400);
	circle_Cloud(130, 440);
	circle_Cloud(150, 420);
	circle_Cloud(120, 420);

	//Cloud2
	glColor3f(0.690, 0.878, 0.902);
	circle_Cloud(800, 360);
	circle_Cloud(780, 380);
	circle_Cloud(800, 400);
	circle_Cloud(830, 360);
	circle_Cloud(830, 400);
	circle_Cloud(850, 380);
	circle_Cloud(820, 380);

	//text
	//15th Anniversary
	glColor3f(0, 0, 0);
	full_text();

	//Night View*********
	if (flag1 == true) {
		//Dark sky
		glColor3f(0.098, 0.098, 0.439);
		glBegin(GL_POLYGON);
		glVertex2f(0, 220);
		glVertex2f(0, 600);
		glVertex2f(1000, 600);
		glVertex2f(1000, 220);
		glEnd();
		//Dark ground
		glColor3f(0.333, 0.420, 0.184);
		glColor3f(0, 0.255, 0);
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(0, 200);
		glVertex2f(1000, 200);
		glVertex2f(1000, 0);
		glEnd();
		//text
		//15th anniversary
		glColor3f(1, 1, 1);
		full_text();
		//moon
		glColor3f(1, 0.843, 0);
		moon(900, 560);
		glColor3f(0.098, 0.098, 0.439);
		moon(880, 560);
		//star1
		glPushMatrix();
		glTranslatef(100, 250, 0);
		star();
		glPopMatrix();
		//star2
		glPushMatrix();
		glTranslatef(680, 230, 0);
		star();
		glPopMatrix();
		//star3
		glPushMatrix();
		glTranslatef(820, 100, 0);
		star();
		glPopMatrix();
		//star4
		glPushMatrix();
		glTranslatef(360, 430, 0);
		star();
		glPopMatrix();
		//star5
		glPushMatrix();
		glTranslatef(-50, 360, 0);
		star();
		glPopMatrix();
		//star6
		glPushMatrix();
		glTranslatef(900, 290, 0);
		star();
		glPopMatrix();
	} 

	//base of the building fill colour
	glColor3f(0.827, 0.827, 0.827);
	glBegin(GL_POLYGON);
	glVertex2f(0, 200);
	glVertex2f(0, 220);
	glVertex2f(1000, 220);
	glVertex2f(1000, 200);
	glEnd();

	//base_upper part_line
	glColor3f(0.412, 0.412, 0.412);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(0, 220);
	glVertex2f(1000, 220);
	glEnd();

	//base_lower part_line
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(0, 200);
	glVertex2f(1000, 200);
	glEnd();

	//base centre line
	glBegin(GL_LINES);
	glVertex2f(400, 200);
	glVertex2f(400, 220);
	glEnd();

	//Central building background fill
	glColor3f(0.827, 0.827, 0.827);
	glBegin(GL_POLYGON);
	glVertex2f(260, 220);
	glVertex2f(260, 450);
	glVertex2f(400, 540);
	glVertex2f(640, 470);
	glVertex2f(640, 220);
	glEnd();

	//block1 stripe
	double x0, y0_1, y0_2;
	glColor3f(0.498, 0.502, 0.565);
	glBegin(GL_LINES);
	for (int i = 280; i > 190; i = i - 5) {
		y0_1 = 0.64286 * 260 + i;
		x0 = (i + 2684.2) / 9.57114;
		y0_2 = (0.64286 * x0) + i;
		glVertex2f(260, y0_1);
		glVertex2f(x0, y0_2);
	}
	glEnd();

	//block2 stripe
	glBegin(GL_LINES);
	for (int i = 280; i > 122; i = i - 5) {
		y0_1 = 0.64286 * 340 + i;
		y0_2 = 0.64286 * 400 + i;
		glVertex2f(340, y0_1);
		glVertex2f(400, y0_2);
	}
	glEnd();

	//block3 stripe
	glBegin(GL_LINES);
	for (int i = 188; i > 95; i = i - 5) {
		y0_1 = 0.5 * 260 + i;
		x0 = (475.0 - i) / 0.95;
		y0_2 = (0.5 * x0) + i;
		glVertex2f(260, y0_1);
		glVertex2f(x0, y0_2);
	}
	glEnd();

	double a = 0;
	glBegin(GL_LINES);
	for (double i = 290; i > 230; i = i - 8) {
		glVertex2f(260, 225 - a);
		glVertex2f(400, i);
		a = a + 0.80;
	}
	glEnd();

	//block4 stripe
	glBegin(GL_LINES);
	for (int i = 654; i > 500; i = i - 5) {
		y0_1 = -0.2917 * 400 + i;
		y0_2 = -0.2917 * 640 + i;
		glVertex2f(400, y0_1);
		glVertex2f(640, y0_2);
	}
	glEnd();

	//block5 stripe
	glBegin(GL_LINES);
	for (int i = 295; i > 230; i = i - 5) {
		glVertex2f(400, i);
		glVertex2f(420, i);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 375; i > 335; i = i - 5) {
		y0_1 = (-0.1 * 640) + i;
		x0 = (i - 190.0) / 0.35;
		y0_2 = (-0.1 * x0) + i;
		glVertex2f(640, y0_1);
		glVertex2f(x0, y0_2);
	}
	glEnd();

	glBegin(GL_LINES);
	int b = 0;
	for (int i = 295; i > 230; i = i - 5) {
		glVertex2f(420, i);
		glVertex2f(640, 270 - b);
		b = b + 4;
	}
	glEnd();

	//block top cover
	glColor3f(0.690, 0.769, 0.871);
	glBegin(GL_POLYGON);
	glVertex2f(500, 510.83);
	glVertex2f(500, 465);
	glVertex2f(470, 470);
	glVertex2f(460, 522.5);
	glEnd();

	//block middle cover
	glBegin(GL_POLYGON);
	glVertex2f(400, 295);
	glVertex2f(420, 295);
	glVertex2f(520, 355);
	glVertex2f(400, 375);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(420, 295);
	glVertex2f(520, 355);
	glVertex2f(540, 325);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(520, 355);
	glVertex2f(540, 325);
	glVertex2f(620, 340);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(545, 430);
	glVertex2f(520, 355);
	glVertex2f(620, 340);
	glVertex2f(600, 420);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(620, 340);
	glVertex2f(540, 325);
	glVertex2f(640, 315);
	glVertex2f(640, 335);
	glEnd();

	//block side cover
	glBegin(GL_POLYGON);
	glVertex2f(310, 482.14);
	glVertex2f(340, 501.43);
	glVertex2f(340, 340);
	glVertex2f(300, 380);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(260, 360);
	glVertex2f(260, 320);
	glVertex2f(300, 340);
	glVertex2f(300, 380);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(300, 380);
	glVertex2f(340, 340);
	glVertex2f(300, 340);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(300, 340);
	glVertex2f(340, 340);
	glVertex2f(400, 295);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(340, 340);
	glVertex2f(400, 375);
	glVertex2f(400, 295);
	glEnd();

	//Bulding Edges
	//block1
	glColor3f(0.412, 0.412, 0.412);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex2f(260, 450);
	glVertex2f(260, 360);
	glVertex2f(300, 380);
	glVertex2f(310, 482.14);
	glEnd();

	//block2
	glBegin(GL_POLYGON);
	glVertex2f(400, 540);
	glVertex2f(400, 375);
	glVertex2f(340, 340);
	glVertex2f(340, 501.43);
	glEnd();

	//block3
	glBegin(GL_POLYGON);
	glVertex2f(260, 320);
	glVertex2f(260, 220);
	glVertex2f(400, 220);
	glVertex2f(400, 295);
	glVertex2f(300, 340);
	glEnd();

	//block4
	glBegin(GL_POLYGON);
	glVertex2f(400, 540);
	glVertex2f(400, 375);
	glVertex2f(520, 355);
	glVertex2f(545, 430);
	glVertex2f(600, 420);
	glVertex2f(620, 340);
	glVertex2f(640, 335);
	glVertex2f(640, 470);
	glVertex2f(500, 510.83);
	glVertex2f(500, 465);
	glVertex2f(470, 470);
	glVertex2f(460, 522.5);
	glEnd();

	//block5
	glBegin(GL_POLYGON);
	glVertex2f(400, 295);
	glVertex2f(400, 220);
	glVertex2f(640, 220);
	glVertex2f(640, 315);
	glVertex2f(540, 325);
	glVertex2f(420, 295);
	glEnd();

	//Building's Centre Line
	glColor3f(0.412, 0.412, 0.412);
	glBegin(GL_LINES);
	glVertex2f(400, 540);
	glVertex2f(400, 220);
	glEnd();

	//Rode
	glColor3f(0.827, 0.827, 0.827);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(580, 199);
	glVertex2f(620, 199);
	glVertex2f(980, 0);
	glVertex2f(840, 0);
	glEnd();

	//Left Side Tree
	//Left_Tree1
	Tree();
	//Left_Tree2
	glPushMatrix();
	glScalef(0.9, 0.9, 0);
	glTranslatef(-17, 63, 0);
	Tree();
	glPopMatrix();
	//Left_Tree3
	glPushMatrix();
	glScalef(0.8, 0.8, 0);
	glTranslatef(-3, 128, 0);
	Tree();
	glPopMatrix();
	//Righ_Tree4
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(40, 210, 0);
	Tree();
	glPopMatrix();

	//Right Side Tree
	//Right_Tree1
	glPushMatrix();
	glTranslatef(180, 0, 0);
	Tree();
	glPopMatrix();
	//Right_Tree2
	glPushMatrix();
	glScalef(0.9, 0.9, 0);
	glTranslatef(-17, 63, 0);
	glTranslatef(180, 0, 0);
	Tree();
	glPopMatrix();
	//Right_Tree3
	glPushMatrix();
	glScalef(0.8, 0.8, 0);
	glTranslatef(-3, 128, 0);
	glTranslatef(180, 0, 0);
	Tree();
	glPopMatrix();
	//Righ_Tree4
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(200, 212, 0);
	Tree();
	glPopMatrix();

	//Celebration Message display
	celebration();
	
	glutSwapBuffers();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 60);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("Greeting Card");
	glutDisplayFunc(display);
	//Interaction
	glutIdleFunc(when_in_mainloop);
	glutTimerFunc(time_interval, OnTimer, 1);
	glutTimerFunc(time_interval, Spin, 1);
	glutKeyboardFunc(keyboard_input);
	glutMouseFunc(mouse_input);
	glutMainLoop();

}