/*
#include <iostream>
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <math.h>
using namespace std;
#define PI 3.1415926535898 // Defining Pi
#define Cos(t) cos(PI/180*(t))
#define Sin(t) sin(PI/180*(t))

double dim = 15.0;
int toggleMode = 0;
int totalFaces = 1;
int cx = 10, cy = 0, cz = 10;
int view = 0;
float angle;
int rot1 = 0, rot2 = 0, rot3 = 0;
int th=0, ph=0;
int fov = 55; //field of view
int asp = 1; // aspect ratio
int toggleView = 1;

struct Faces
{
	//each face can have a maximum of 100 verices
	int xVertices[100];
	int yVertices[100];
	int zVertices[100];
	float r = 1, g = 1, b = 1;
	int state = 0;
	int vertexCount = 0;
}; Faces F[100]; //Solid can have a maximum of 100 Faces

bool checkLoop(int x1, int x2, int y1, int y2, int z1, int z2) {
	//cout << "Y1";
	if (x1 == x2) {
		//cout << "Y2";
		if (y1 == y2) {
			//cout << "Y3";
			if (z1 == z2) {
		//		cout << "Y4";
				return true;
			}
		}
	}
	
	//	cout << "Y5";
		return false; 
}

void addFace() {
	Faces temp = F[totalFaces];
	int count = temp.vertexCount;
	
//	cout << "\n";
//	cout << "Total Faces: ";
//	cout << totalFaces;
//	cout << "      Vertex Count: ";
//	cout << count;
//	cout << "      First X: ";
//	cout << temp.xVertices[0];
//	cout << "      First Y: ";
//	cout << temp.yVertices[0];
//	cout << "      First Z: ";
//	cout << temp.zVertices[0];

//-------------------------------------------------------------------------------------

	if (checkLoop(cx, temp.xVertices[0], cy, temp.yVertices[0], cz, temp.zVertices[0])) { 
		totalFaces += 1;
		cout << "face completed!";
		return;
	}
	else {
		temp.xVertices[count] = cx;
		//cout << "      Current X: ";
		//cout << temp.xVertices[count];

		temp.yVertices[count] = cy;
		//cout << "      Current Y: ";
		//cout << temp.yVertices[count];

		temp.zVertices[count] = cz;
		//cout << "      Current Z: ";
		//cout << temp.zVertices[count];
		count += 1;
		temp.vertexCount = count;
	}
	F[totalFaces] = temp;
}

void selView(int x)
{
	if (x == 1) { glBegin(GL_LINE_LOOP); }
	else { glBegin(GL_POLYGON); }
}

void drawFaces()
{
	int i;
	for (i = 1; i < totalFaces + 1 ; i++)
	{
		selView(view);
		Faces temp = F[i];
		glColor3f(temp.r, temp.g, temp.b);
		for (int i = 0; i < temp.vertexCount; i++) {
			glVertex3f(temp.xVertices[i], temp.yVertices[i], temp.zVertices[i]);
		}
		glEnd();
	}
}

void theCube()
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(cx, cy, cz);
	glutSolidCube(0.4);
	glPopMatrix();
}

void drawGrid()
{
	int i;
	for (i = 0; i < 30; i++)
	{
		glPushMatrix();
		if (i < 15) { glTranslatef(0, 0, i); }
		if (i >= 15) { glTranslatef(i - 15, 0, 0); glRotatef(-90, 0, 1, 0); }

		glBegin(GL_LINES);
		glColor3f(1, 1, 1); glLineWidth(1);
		glVertex3f(0, -0.01, 0); glVertex3f(14, -0.01, 0);
		glEnd();
		glPopMatrix();
	}
}

void drawTopView() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(cx, cy, cz);
	glutSolidCube(0.4);
	glPopMatrix();
}
void drawFrontView() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(cx, cy, cz);
	glutSolidCube(0.4);
	glPopMatrix();
}
void drawSideView() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(cx, cy, cz);
	glutSolidCube(0.4);
	glPopMatrix();
}

void rotGrid(int x, int y, int z)
{
	glTranslatef(x, y, z);
}

void project() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (toggleMode) {
		//Perspective
		gluPerspective(fov, asp, dim / 4, 4 * dim);
	}
	else {
		//Orthographic
		glOrtho(-dim * asp, +dim * asp, -dim, +dim, -dim, +dim);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	if (toggleMode) {
		double Ex = -2 * dim*Sin(th)*Cos(ph);
		double Ey = +2 * dim*Sin(ph);
		double Ez = +2 * dim*Cos(th)*Cos(ph);

		gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
	}
	else {
		glRotatef(ph, 1, 0, 0);
		glRotatef(th, 0, 1, 0);
	}
	
	rotGrid(rot1, rot2, rot3);
	if (toggleView == 1){
		drawGrid();
		drawFaces();
		theCube();
	}

	if (toggleView == 2) {
		drawTopView();
		
	}
	if (toggleView == 3) {
		drawFrontView();
	}
	if (toggleView == 4) {
		drawSideView();
	}

	
	glFlush();
	glutSwapBuffers();
}

void reshape(int width, int height) {
	asp = (height>0) ? (double)width / height : 1;
	glViewport(0, 0, width, height);
	project();
}

//------------------------------------------------------------------------------//
void getFrontView()
{
	dim = 15.0;
	toggleMode = 0;
	cx = 10, cy = 0, cz = 10;	
	rot1 = -7, rot2 = -3, rot3 = -7;
	th = 0, ph = 0;
	fov = 55; //field of view
	asp = 1; // aspect ratio

}

void getLeftSideView()
{
	dim = 15.0;
	toggleMode = 0;
	cx = 10, cy = 0, cz = 10;
	rot1 = -2, rot2 = 1, rot3 = -7;
	th = -90, ph = 0;
	fov = 55; //field of view
	asp = 1; // aspect ratio

}

void getTopView()
{
	dim = 15.0;
	toggleMode = 0;
	cx = 10, cy = 0, cz = 10;
	rot1 = -7, rot2 = 0, rot3 = -5;
	th = 0, ph = 90;
	fov = 55; //field of view
	asp = 1; // aspect ratio
}

void resetView()
{

	dim = 15.0;
	toggleMode = 0;
	int cx = 10, cy = 0, cz = 10;
	view = 0;
	
	rot1 = -9, rot2 = 3, rot3 = 0;
	th = 35, ph = 40;
	fov = 55; //field of view
	asp = 1; // aspect ratio
	
}


void changeAngle()
{
	int i;
	cout << "angle: ";
	cin >> i;
	angle = i;
}

void prValues()
{
	cout << th;
	cout << "    ";
	cout << ph;
	cout << "    ";
	cout << rot1;
	cout << "    ";
	cout << rot2;
	cout << "    ";
	cout << rot3;
	cout << "   \n ";
}
//------------------------------------------------------------------------------//

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'w') { cz -= 1; } if (key == 's') { cz += 1; }
	if (key == 'a') { cx -= 1; } if (key == 'd') { cx += 1; }
	if (key == 'z') { cy -= 1; } if (key == 'q') { cy += 1; }

	if (key == 'D') { rot1 -= 1; } if (key == 'A') { rot1 += 1; }
	if (key == 'W') { rot2 -= 1; } if (key == 'S') { rot2 += 1; }
	if (key == 'Z') { rot3 -= 1; } if (key == 'Q') { rot3 += 1; }
	if (key == '+') { dim -= 1.00; } if (key == '-') { dim += 1.00; }

	if (key == ' ') { addFace(); }

	if (key == 'F') { getFrontView(); }
	if (key == 'G') { getLeftSideView(); }
	if (key == 'T') { getTopView(); }
	if (key == 'f') { toggleView = 2; }
	if (key == 'g') { toggleView = 3; }
	if (key == 't') { toggleView = 4; }

	if (key == 'm')toggleMode = 1 - toggleMode;
	if (key == '~') { resetView(); }
	//	if (key == ')') { changeAngle(); }
	if (key == '@') { prValues(); }

	//	if (key == 'I') { rot1 = 1; rot2 = 0; rot3 = 0; }
	//	if (key == 'O') { rot1 = 0; rot2 = 1; rot3 = 0; }
	//	if (key == 'P') { rot1 = 0; rot2 = 0; rot3 = 1; }


	if (key == '1') { F[totalFaces].r = 1; F[totalFaces].g = 0; F[totalFaces].b = 0; }
	if (key == '2') { F[totalFaces].r = 0; F[totalFaces].g = 1; F[totalFaces].b = 0; }
	if (key == '3') { F[totalFaces].r = 0; F[totalFaces].g = 0; F[totalFaces].b = 1; }
	if (key == '4') { F[totalFaces].r = 1; F[totalFaces].g = 1; F[totalFaces].b = 0; }
	if (key == '5') { F[totalFaces].r = 1; F[totalFaces].g = 0; F[totalFaces].b = 1; }
	if (key == '6') { F[totalFaces].r = 0; F[totalFaces].g = 1; F[totalFaces].b = 1; }
	if (key == '0') { F[totalFaces].r = 1; F[totalFaces].g = 1; F[totalFaces].b = 1; }

	if (key == '7') { view = 0; } if (key == '9') { view = 1; }


	project();
	glutPostRedisplay();
}

void windowSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) th -= 5;
	else if (key == GLUT_KEY_LEFT) th += 5;
	else if (key == GLUT_KEY_UP) ph += 5;
	else if (key == GLUT_KEY_DOWN) ph -= 5;

	th %= 360;
	ph %= 360;

	project();
	glutPostRedisplay();

}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 1.0f, 0.1f, 1000);
	//glOrtho(0.01f, 1000, 0.01f, 1000, 0.01f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);

}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(1280, 1280);
	glutCreateWindow("saffssa");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(windowSpecial);

	
	glutMainLoop();
	return 0;
}

*/