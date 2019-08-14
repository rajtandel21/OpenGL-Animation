#include <stdio.h>
#include "glut.h"
#include <math.h>


int counter = 0;

int frame = 0;
int walkframe = 0;
int scalecounter = 0;
int character1[10][2];
int character2[10][2];
int character3[10][2];
int hand1[6][2];
int hand2[6][2];
int tweenPoly[10][2];
int tweenPoly2[6][2];
float proportion = 0.0;
float tx = 0.0;			//moving person
float ty = 0.0;
float rx = 0.0;			//moving road scene3
float ry = 0.0;
float sx = 0.9;			//scaling smartphone scene4 part1
float sy = 0.9;
float cx = 0.5;			//scaling crash scene 6
float cy = 0.5;
float mcx = 0.0;		//moving car1 scene5
float mcy = 0.0;
float mc2x = 0.0;		//moving car2 scene5
float mc2y = 0.0;
float theta = 0.0;
float theta2 = 0.0;		//rotating 3dcube scene1

GLfloat vertices[8][3] = {
	{250.0, 140.0, 0.0}, {350.0, 140.0, 0.0}, {350.0, 40.0, 0.0}, {250.0, 40.0, 0.0},
	{250.0, 140.0, 100.0}, {350.0, 140.0, 100.0}, {350.0, 40.0, 100.0}, {250.0, 40.0, 100.0}
};

GLfloat colors[8][3] = {
	{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
	{1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 0.5, 1.0}
};

void init3D(int w, int h) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 800.0, 0.0, 300.0, -500.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 300.0);
	

	character1[0][0] = 200;
	character1[0][1] = 150;
	character1[1][0] = 200;
	character1[1][1] = 100;
	character1[2][0] = 200;
	character1[2][1] = 100;
	character1[3][0] = 160;
	character1[3][1] = 40;
	character1[4][0] = 200;
	character1[4][1] = 100;
	character1[5][0] = 240;
	character1[5][1] = 40;
	character1[6][0] = 200;
	character1[6][1] = 150;
	character1[7][0] = 150;
	character1[7][1] = 100;
	character1[8][0] = 200;
	character1[8][1] = 150;
	character1[9][0] = 250;
	character1[9][1] = 100;

	character2[0][0] = 200;
	character2[0][1] = 150;
	character2[1][0] = 200;
	character2[1][1] = 100;
	character2[2][0] = 200;
	character2[2][1] = 100;
	character2[3][0] = 199;
	character2[3][1] = 40;
	character2[4][0] = 200;
	character2[4][1] = 100;
	character2[5][0] = 201;
	character2[5][1] = 40;
	character2[6][0] = 200;
	character2[6][1] = 150;
	character2[7][0] = 199;
	character2[7][1] = 100;
	character2[8][0] = 200;
	character2[8][1] = 150;
	character2[9][0] = 201;
	character2[9][1] = 100;

	character3[0][0] = 200;
	character3[0][1] = 150;
	character3[1][0] = 200;
	character3[1][1] = 100;
	character3[2][0] = 200;
	character3[2][1] = 150;
	character3[3][0] = 200;
	character3[3][1] = 100;
	character3[4][0] = 200;
	character3[4][1] = 150;
	character3[5][0] = 200;
	character3[5][1] = 100;
	character3[6][0] = 200;
	character3[6][1] = 100;
	character3[7][0] = 200;
	character3[7][1] = 40;
	character3[8][0] = 200;
	character3[8][1] = 100;
	character3[9][0] = 200;
	character3[9][1] = 40;

	hand1[0][0] = 500;
	hand1[0][1] = 300;
	hand1[1][0] = 500;
	hand1[1][1] = 0;
	hand1[2][0] = 500;
	hand1[2][1] = 250;
	hand1[3][0] = 400;
	hand1[3][1] = 170;
	hand1[4][0] = 400;
	hand1[4][1] = 170;
	hand1[5][0] = 300;
	hand1[5][1] = 300;

	hand2[0][0] = 500;
	hand2[0][1] = 500;
	hand2[1][0] = 500;
	hand2[1][1] = 0;
	hand2[2][0] = 500;
	hand2[2][1] = 250;
	hand2[3][0] = 400;
	hand2[3][1] = 170;
	hand2[4][0] = 400;
	hand2[4][1] = 170;
	hand2[5][0] = 310;
	hand2[5][1] = 120;
}

void circle(double radius, double xc, double yc) {
	int i;
	double angle = 2 * 3.1415 / 20;
	double circle_xy[40][2];

	circle_xy[0][0] = radius + xc;
	circle_xy[0][1] = yc;

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	for (i = 1; i < 20; i++) {
		circle_xy[i][0] = radius*cos(i*angle) + xc;
		circle_xy[i][1] = radius*sin(i*angle) + yc;

		glVertex2f(circle_xy[i - 1][0], circle_xy[i - 1][1]);
		glVertex2f(circle_xy[i][0], circle_xy[i][1]);
	}
	glEnd();
}

void circle2(double radius, double xc, double yc) {
	int i;
	double angle = 2 * 3.1415 / 20;
	double circle_xy[40][2];

	circle_xy[0][0] = radius + xc;
	circle_xy[0][1] = yc;

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	for (i = 1; i < 20; i++) {
		circle_xy[i][0] = radius*cos(i*angle) + xc;
		circle_xy[i][1] = radius*sin(i*angle) + yc;

		glVertex2f(circle_xy[i - 1][0], circle_xy[i - 1][1]);
		glVertex2f(circle_xy[i][0], circle_xy[i][1]);
	}
	glEnd();
}

void ground() {
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
	glVertex2d(0.0, 50.0);
	glVertex2d(800.0, 50.0);
	glVertex2d(800.0, 0.0);
	glVertex2d(0.0, 0.0);
	glEnd();
}

void road1() {
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
	glVertex2d(0.0, 50.0);
	glVertex2d(800.0, 50.0);
	glVertex2d(800.0, 0.0);
	glVertex2d(0.0, 0.0);
	glEnd();
}

void sky() {
	glColor3f(0.7, 0.7, 1.0);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
	glVertex2d(0.0, 50.0);
	glVertex2d(0.0, 300.0);
	glVertex2d(800.0, 300.0);
	glVertex2d(800.0, 0.0);
	glEnd();
}

void background4() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, 300.0);
	glVertex2d(800.0, 300.0);
	glVertex2d(800.0, 0.0);
	glEnd();
}

void background5() {
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);   //Grass
	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, 300.0);
	glVertex2d(800.0, 300.0);
	glVertex2d(800.0, 0.0);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);             //Road 1
	glVertex2d(0.0, 50.0);
	glVertex2d(0.0, 150.0);
	glVertex2d(800.0, 150.0);
	glVertex2d(800.0, 50.0);
	glEnd();

	glBegin(GL_POLYGON);             //Road 2
	glVertex2d(500.0, 0.0);
	glVertex2d(500.0, 300.0);
	glVertex2d(700.0, 300.0);
	glVertex2d(700.0, 0.0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);         //Road split 1
	glVertex2d(10.0, 95.0);
	glVertex2d(10.0, 105.0);
	glVertex2d(60.0, 105.0);
	glVertex2d(60.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(110.0, 95.0);
	glVertex2d(110.0, 105.0);
	glVertex2d(160.0, 105.0);
	glVertex2d(160.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(210.0, 95.0);
	glVertex2d(210.0, 105.0);
	glVertex2d(260.0, 105.0);
	glVertex2d(260.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(310.0, 95.0);
	glVertex2d(310.0, 105.0);
	glVertex2d(360.0, 105.0);
	glVertex2d(360.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(410.0, 95.0);
	glVertex2d(410.0, 105.0);
	glVertex2d(460.0, 105.0);
	glVertex2d(460.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(510.0, 95.0);
	glVertex2d(510.0, 105.0);
	glVertex2d(560.0, 105.0);
	glVertex2d(560.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(610.0, 95.0);
	glVertex2d(610.0, 105.0);
	glVertex2d(660.0, 105.0);
	glVertex2d(660.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(710.0, 95.0);
	glVertex2d(710.0, 105.0);
	glVertex2d(760.0, 105.0);
	glVertex2d(760.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);        //Road split 2
	glVertex2d(595.0, 300.0);
	glVertex2d(605.0, 300.0);
	glVertex2d(605.0, 250.0);
	glVertex2d(595.0, 250.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(595.0, 200.0);
	glVertex2d(605.0, 200.0);
	glVertex2d(605.0, 150.0);
	glVertex2d(595.0, 150.0);
	glEnd();
}

void car1() { //Scene 2 car
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	
	circle(35, 310, 75); //Car wheel 1
	glBegin(GL_LINES);
	glVertex2d(310, 110);
	glVertex2d(310, 40);
	glVertex2d(275, 75);
	glVertex2d(345, 75);
	glEnd();
	
	circle(35, 540, 75); //Car wheel 2
	glBegin(GL_LINES);
	glVertex2d(540, 110);
	glVertex2d(540, 40);
	glVertex2d(505, 75);
	glVertex2d(575, 75);
	glEnd();
	
	glBegin(GL_LINE_LOOP);  //Car body
	glVertex2d(270.0, 80.0);
	glVertex2d(240.0, 80.0);
	glVertex2d(240.0, 130.0);
	glVertex2d(300.0, 130.0);
	glVertex2d(320.0, 200.0);
	glVertex2d(500.0, 200.0);
	glVertex2d(550.0, 130.0);
	glVertex2d(610.0, 130.0);
	glVertex2d(610.0, 80.0);
	glVertex2d(580.0, 80.0);
	glVertex2d(565.0, 110.0);
	glVertex2d(515.0, 110.0);
	glVertex2d(500.0, 80.0);
	glVertex2d(350.0, 80.0);
	glVertex2d(335.0, 110.0);
	glVertex2d(285.0, 110.0);
	glEnd();
	
	glBegin(GL_LINE_LOOP);  //Car window
	glVertex2d(330.0, 190.0);
	glVertex2d(490.0, 190.0);
	glVertex2d(535.0, 130.0);
	glVertex2d(315.0, 130.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2d(405.0, 190.0);
	glVertex2d(415.0, 190.0);
	glVertex2d(415.0, 130.0);
	glVertex2d(405.0, 130.0);
	glEnd();
}

void car2() { //Scene 3 car
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);

	circle(35, 270, 75); //Car wheel 1
	
	circle(35, 500, 75); //Car wheel 2

	glBegin(GL_LINE_LOOP);  //Car body
	glVertex2d(230.0, 80.0);
	glVertex2d(200.0, 80.0);
	glVertex2d(200.0, 130.0);
	glVertex2d(260.0, 130.0);
	glVertex2d(280.0, 200.0);
	glVertex2d(460.0, 200.0);
	glVertex2d(510.0, 130.0);
	glVertex2d(570.0, 130.0);
	glVertex2d(570.0, 80.0);
	glVertex2d(540.0, 80.0);
	glVertex2d(525.0, 110.0);
	glVertex2d(475.0, 110.0);
	glVertex2d(460.0, 80.0);
	glVertex2d(310.0, 80.0);
	glVertex2d(295.0, 110.0);
	glVertex2d(245.0, 110.0);
	glEnd();

	circle(20, 400, 160); //Driver head
	glBegin(GL_LINES); //Driver body
	glVertex2d(400, 140);
	glVertex2d(400, 130);

	glVertex2d(400, 140);
	glVertex2d(430, 130);
	glEnd();

	glBegin(GL_LINE_LOOP);  //Car window
	glVertex2d(290.0, 190.0);
	glVertex2d(450.0, 190.0);
	glVertex2d(495.0, 130.0);
	glVertex2d(275.0, 130.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2d(365.0, 190.0);
	glVertex2d(375.0, 190.0);
	glVertex2d(375.0, 130.0);
	glVertex2d(365.0, 130.0);
	glEnd();
}

void scene5car1() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);		//Car body
	glVertex2d(20.0, 115.0);
	glVertex2d(20.0, 135.0);
	glVertex2d(70.0, 135.0);
	glVertex2d(70.0, 115.0);
	glEnd();

	glBegin(GL_POLYGON);		//Wheels 1
	glVertex2d(25.0, 110.0);
	glVertex2d(35.0, 110.0);
	glVertex2d(35.0, 140.0);
	glVertex2d(25.0, 140.0);
	glEnd();

	glBegin(GL_POLYGON);		//Wheels 2
	glVertex2d(65.0, 110.0);
	glVertex2d(55.0, 110.0);
	glVertex2d(55.0, 140.0);
	glVertex2d(65.0, 140.0);
	glEnd();
}

void scene5car2() {
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);		//Car body
	glVertex2d(615.0, 280.0);
	glVertex2d(635.0, 280.0);
	glVertex2d(635.0, 230.0);
	glVertex2d(615.0, 230.0);
	glEnd();

	glBegin(GL_POLYGON);		//Wheels 1
	glVertex2d(610.0, 275.0);
	glVertex2d(610.0, 265.0);
	glVertex2d(640.0, 265.0);
	glVertex2d(640.0, 275.0);
	glEnd();

	glBegin(GL_POLYGON);		//Wheels 2
	glVertex2d(610.0, 235.0);
	glVertex2d(610.0, 245.0);
	glVertex2d(640.0, 245.0);
	glVertex2d(640.0, 235.0);
	glEnd();
}

void wheelrim1() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINES); //wheel 1
	glVertex2d(270, 110);
	glVertex2d(270, 40);
	glVertex2d(235, 75);
	glVertex2d(305, 75);
	glEnd();
}

void wheelrim2() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINES); // wheel 2
	glVertex2d(500, 110);
	glVertex2d(500, 40);
	glVertex2d(465, 75);
	glVertex2d(535, 75);
	glEnd();
}

void roadsplit() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
	glVertex2d(10.0, 30.0);
	glVertex2d(110.0, 30.0);
	glVertex2d(110.0, 10.0);
	glVertex2d(10.0, 10.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(210.0, 30.0);
	glVertex2d(310.0, 30.0);
	glVertex2d(310.0, 10.0);
	glVertex2d(210.0, 10.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(410.0, 30.0);
	glVertex2d(510.0, 30.0);
	glVertex2d(510.0, 10.0);
	glVertex2d(410.0, 10.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(610.0, 30.0);
	glVertex2d(710.0, 30.0);
	glVertex2d(710.0, 10.0);
	glVertex2d(610.0, 10.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(810.0, 30.0);
	glVertex2d(910.0, 30.0);
	glVertex2d(910.0, 10.0);
	glVertex2d(810.0, 10.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(1010.0, 30.0);
	glVertex2d(1110.0, 30.0);
	glVertex2d(1110.0, 10.0);
	glVertex2d(1010.0, 10.0);
	glEnd();
}

void smartphone(){
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(375.0, 80.0);
	glVertex2d(375.0, 70.0);
	glVertex2d(310.0, 70.0);
	glVertex2d(310.0, 80.0);
	glEnd();

	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(260.0,50.0);
	glVertex2d(260.0,280.0);
	glVertex2d(430.0,280.0);
	glVertex2d(430.0,50.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(280.0, 100.0);
	glVertex2d(280.0, 250.0);
	glVertex2d(410.0, 250.0);
	glVertex2d(410.0, 100.0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(325.0, 150.0);
	glVertex2d(365.0, 150.0);
	glVertex2d(365.0, 130.0);
	glVertex2d(355.0, 130.0);
	glVertex2d(355.0, 140.0);
	glVertex2d(335.0, 140.0);
	glVertex2d(335.0, 130.0);
	glVertex2d(325.0, 130.0);
	glEnd();

}

void smartphone2() {
	//smaller phone for after scalling.
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(277.5, 40.0);
	glVertex2d(277.5, 35.0);
	glVertex2d(245.0, 35.0);
	glVertex2d(245.0, 40.0);
	glEnd();

	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(220.0, 25.0);
	glVertex2d(220.0, 140.0);
	glVertex2d(305.0, 140.0);
	glVertex2d(305.0, 25.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(230.0, 50.0);
	glVertex2d(230.0, 125.0);
	glVertex2d(295.0, 125.0);
	glVertex2d(295.0, 50.0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(252.5, 75.0);
	glVertex2d(272.5, 75.0);
	glVertex2d(272.5, 65.0);
	glVertex2d(267.5, 65.0);
	glVertex2d(267.5, 70.0);
	glVertex2d(257.5, 70.0);
	glVertex2d(257.5, 65.0);
	glVertex2d(252.5, 65.0);
	glEnd();
}

void tween(int source[10][2], int destination[10][2], int numPoints, double proportion, int tweenPoly[10][2]) {
	for (int p = 0; p < numPoints; p++) {
		double sourceX = source[p][0];
		double sourceY = source[p][1];

		double destinationX = destination[p][0];
		double destinationY = destination[p][1];

		double differenceX = (destinationX - sourceX);
		double differenceY = (destinationY - sourceY);

		double tweenX = sourceX + (differenceX*proportion);
		double tweenY = sourceY + (differenceY*proportion);

		tweenPoly[p][0] = int(tweenX);
		tweenPoly[p][1] = int(tweenY);
	}
}

void tween2(int source[6][2], int destination[6][2], int numPoints, double proportion, int tweenPoly2[6][2]) {
	for (int p = 0; p < numPoints; p++) {
		double sourceX = source[p][0];
		double sourceY = source[p][1];

		double destinationX = destination[p][0];
		double destinationY = destination[p][1];

		double differenceX = (destinationX - sourceX);
		double differenceY = (destinationY - sourceY);

		double tweenX = sourceX + (differenceX*proportion);
		double tweenY = sourceY + (differenceY*proportion);

		tweenPoly2[p][0] = int(tweenX);
		tweenPoly2[p][1] = int(tweenY);
	}
}

void renderSpaceBitmapString(float x, float y, int spacing, void *font, char *string) {
	char *c;
	int x1 = x;

	for (c = string; *c != '\0'; c++) {
		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);

		x1 = x1 + glutBitmapWidth(font, *c) + spacing;
	}
}

void movingp() {
	tx = tx + 5;           //moving person forward.
	ty = ty + 0;
	glutPostRedisplay();
}

void key1() {
	glColor3f(1.0, 1.0, 1.0);
	circle(30, 300, 240);

	glColor3f(0.0, 0.0, 0.0);
	circle(60, 300, 240);

	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(355.0, 260.0);
	glVertex2d(620.0, 260.0);
	glVertex2d(620.0, 220.0);
	glVertex2d(355.0, 220.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2d(600.0, 220.0);
	glVertex2d(590.0, 200.0);
	glVertex2d(580.0, 220.0);
	glVertex2d(570.0, 180.0);
	glVertex2d(560.0, 220.0);
	glVertex2d(550.0, 190.0);
	glVertex2d(540.0, 220.0);
	glVertex2d(530.0, 200.0);
	glVertex2d(520.0, 220.0);
	glVertex2d(510.0, 200.0);
	glVertex2d(500.0, 220.0);
	glEnd();

	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2d(300.0, 210.0);
	glVertex2d(300.0, 140.0);
	glEnd();
}

void clouds1() {
	glViewport(0, 200, 250, 100);
	circle2(50, 100, 200);
	circle2(100, 200, 200);

	glViewport(300, 200, 270, 100);
	circle2(50, 320, 200);
	circle2(100, 400, 200);
	circle2(50, 490, 200);

	glViewport(510, 200, 250, 100);
	circle2(50, 480, 200);
	circle2(100, 570, 200);
	circle2(100, 670, 200);
}

void rotater1() {		//moving roadsplit.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(270.0, 75.0, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
	glTranslatef(-270.0, -75.0, 0.0);
	wheelrim1();
	glPopMatrix();
	rx = rx - 2;
	ry = ry + 0;
	theta = theta - 3.14;
}

void rotater2() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(500.0, 75.0, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
	glTranslatef(-500.0, -75.0, 0.0);
	wheelrim2();
	glPopMatrix();
	rx = rx - 2;
	ry = ry + 0;
	theta = theta - 3.14;
}

void scalephone() { //make smartphone smaller.
	glPushMatrix();
	glScalef(sx, sy, 1.0);
	smartphone();
	glPopMatrix();
	sx = sx * 0.999;
	sy = sy * 0.999;
}

void ringring() {
	glColor3f(0.0, 0.0, 0.0);
	renderSpaceBitmapString(450, 200, 10, GLUT_BITMAP_HELVETICA_18, "RING");
	renderSpaceBitmapString(450, 150, 10, GLUT_BITMAP_HELVETICA_18, "RING");
}

void movecar1() {
	glPushMatrix();
	glTranslatef(mcx, mcy, 0.0);
	scene5car1();
	glPopMatrix();
	mcx = mcx + 10;
	mcy = mcy + 0;
}

void movecar2() {
	glPushMatrix();
	glTranslatef(mc2x, mc2y, 0.0);
	scene5car2();
	glPopMatrix();
	mc2x = mc2x + 0;
	mc2y = mc2y - 2;
}

void crashscene() {
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(400.0, 150.0, 0.0);
	glScalef(cx, cy, 1.0);
	glTranslatef(-400.0, -150.0, 0.0);

	glBegin(GL_POLYGON);
	glVertex2d(400.0, 280.0);
	glVertex2d(450.0, 220.0);
	glVertex2d(580.0, 240.0);
	glVertex2d(550.0, 170.0);
	glVertex2d(650.0, 130.0);
	glVertex2d(550.0, 90.0);
	glVertex2d(510.0, 20.0);
	glVertex2d(400.0, 70.0);
	glVertex2d(280.0, 50.0);
	glVertex2d(300.0, 110.0);
	glVertex2d(200.0, 170.0);
	glVertex2d(370.0, 200.0);
	glVertex2d(380.0, 250.0);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	renderSpaceBitmapString(350, 150, 10, GLUT_BITMAP_HELVETICA_18, "CRASH");

	glPopMatrix();
	cx = cx*1.01;
	cy = cy*1.01;
}

void message1() {
	glColor3f(0.0, 0.0, 0.0);
	renderSpaceBitmapString(250, 150, 10, GLUT_BITMAP_HELVETICA_18, "Leave the phone alone");
	renderSpaceBitmapString(250, 100, 10, GLUT_BITMAP_HELVETICA_18, "Pay attention to the road");
}

void walk4() {
	int i;
	glColor3f(0.0, 0.0, 0.0);
	circle(30, 200, 180);
	glBegin(GL_LINES);  //For a stick figure is might be good to do Lines instead. Points are not all connected.
	for (i = 0; i < 10; i++)
		glVertex2i(character1[i][0], character1[i][1]);
	glEnd();
}

void walk5() {
	int i;
	glColor3f(0.0, 0.0, 0.0);
	circle(30, 200, 180);
	glBegin(GL_LINES);
	for (i = 0; i < 10; i++)
		glVertex2i(character2[i][0], character2[i][1]);
	glEnd();
}

void walk2() {
	int i;
	glColor3f(0.0, 0.0, 0.0);
	circle(30, 200, 180);
	glBegin(GL_LINES);
	for (i = 0; i < 10; i++)
		glVertex2i(character3[i][0], character3[i][1]);
	glEnd();
}

void walk1() {
	int i;
	glColor3f(0.0, 0.0, 0.0);
	circle(30, 200, 180);
	glBegin(GL_LINES);
	for (i = 0; i < 10; i++)
		glVertex2i(tweenPoly[i][0], tweenPoly[i][1]);
	glEnd();
}

void walk3() {
	int i;
	glColor3f(0.0, 0.0, 0.0);
	circle(30, 200, 180);
	glBegin(GL_LINES);
	for (i = 0; i < 10; i++)
		glVertex2i(tweenPoly[i][0], tweenPoly[i][1]);
	glEnd();
}

void handmove1() {
	int i;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (i = 0; i < 6; i++)
		glVertex2i(tweenPoly2[i][0], tweenPoly2[i][1]);
	glEnd();
}

void handmove2() {
	int i;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (i = 0; i < 6; i++)
		glVertex2i(hand2[i][0], hand2[i][1]);
	glEnd();
}

void cubeface(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void cubecolor() {
	glColor3fv(colors[1]);
	cubeface(0, 3, 2, 1);
	glColor3fv(colors[2]);
	cubeface(2, 3, 7, 6);
	glColor3fv(colors[3]);
	cubeface(0, 4, 7, 3);
	glColor3fv(colors[4]);
	cubeface(1, 2, 6, 5);
	glColor3fv(colors[5]);
	cubeface(4, 5, 6, 7);
	glColor3fv(colors[6]);
	cubeface(0, 1, 5, 4);
}

void rotatecube() {
	theta2 += 10.0;
	if (theta2 > 360.0) theta2 -= 360.0;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(300.0, 140.0, 50.0);
	glRotatef(theta2, 0.0, 1.0, 0.0);
	glTranslatef(-300, -140, -50.0);
	cubecolor();
	glPopMatrix();
}

void main1() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	init();
	glDisable(GL_DEPTH_TEST);
}

void main2() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	init3D(800, 300);
	glEnable(GL_DEPTH_TEST);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	frame++;
	glLineWidth(1.0);
	if (frame == 1) main2();
	else if ((frame >= 1) && (frame < 50)) {			//Scene 1
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		key1();
		rotatecube();
	}
	else if (frame == 50) main1();
	else if ((frame >= 50) && (frame < 450)) {			//Scene 2
		glViewport(0, 0, 800, 300);
		sky();
		ground();
		car1();
		walkframe++;
		if ((walkframe >= 0) && (walkframe < 16)) {
			if (walkframe == 0) proportion = 0.0;
			glPushMatrix();
			glTranslatef(tx, ty, 0.0);
			tween(character1, character2, 10, proportion, tweenPoly);
			walk1();
			glPopMatrix();
			proportion = proportion + 0.05;
			if (proportion > 1.0) proportion = 0.0;
		}
		else if ((walkframe >= 16) && (walkframe < 22)) {
			if (walkframe == 16) proportion = 0.0;
			glPushMatrix();
			glTranslatef(tx, ty, 0.0);
			walk2();
			glPopMatrix();
		}
		else if ((walkframe >= 22) && (walkframe < 36)) {
			if (walkframe == 22) proportion = 0.0;
			glPushMatrix();
			glTranslatef(tx, ty, 0.0);
			tween(character2, character1, 10, proportion, tweenPoly);
			walk3();
			glPopMatrix();
			proportion = proportion + 0.05;
			if (proportion > 1.0) proportion = 0.0;
		}
		else if ((walkframe >= 36) && (walkframe < 40)) {
			if (walkframe == 36) proportion = 0.0;
			glPushMatrix();
			glTranslatef(tx, ty, 0.0);
			walk4();
			glPopMatrix();
			movingp();
		}
		else if (walkframe > 40) {
			walkframe = 0;
		}
		clouds1();
	}
	else if ((frame >= 450) && (frame < 560)) {			//Scene 3
		glViewport(0, 0, 800, 300);
		sky();
		road1();
		rotater1();
		rotater2();
		glPushMatrix();
		glTranslatef(rx, ry, 0.0);
		roadsplit();
		glPopMatrix();
		car2();
		clouds1();
	}
	else if ((frame >= 560) && (frame < 675)) {		 //Scene 4 Part 1
		glViewport(0, 0, 800, 300);
		background4();
		scalephone();
		ringring();
	}
	else if ((frame >= 675) && (frame < 725)) {		  //Scene 4 Part 2
		smartphone2();
		tween2(hand1, hand2, 6, proportion, tweenPoly2);
		handmove1();
		proportion = proportion + 0.01;
		if (proportion > 1.0) proportion = 0.0;
	}
	else if ((frame >= 725) && (frame < 780)) {		//Scene 5
		background5();
		movecar1();
		movecar2();
	}
	else if ((frame >= 780) && (frame < 840)) {		//Scene 6
		crashscene();
	}
	else if ((frame >= 840) && (frame < 900)) {		//Scene 7
		message1();
	}
	else if (frame > 900) {
		frame = 0;
		proportion = 0.0;
	}
	glFlush();
	glutSwapBuffers();
	printf("Frame number= %i\n", frame);
}

void Timer(int value) {
	if (value) glutPostRedisplay();
	glutTimerFunc(40, Timer, value);
}

void visibility(int state) {
	switch (state) {
	case GLUT_VISIBLE:
		Timer(1);
		break;
	case GLUT_NOT_VISIBLE:
		Timer(0);
		break;
	default:
		break;
	}
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Drive Safe Advert");
	init();
	glutDisplayFunc(display);
	glutVisibilityFunc(visibility);

	glutMainLoop();

	return 0;
}
