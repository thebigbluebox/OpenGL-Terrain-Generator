#include <stdio.h>
#include <iostream>
#include <time.h>
#include "Header.h"
#include "cameracontrolClass.h"
#include "faultgenClass.h"

cameracontrolClass camera(5,5,5,0,0,0);
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light_position2[] = { 1.0, 1.0, 1.0, 0.0 };
int lightnum = 0;
faultgenClass fault;
bool lighting = true;
int setting = 1;
bool block = true;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 27:
		exit(0);
		break;
	case 'r':
	case 'R':
		fault.fault(100);
		break;
	case 'e':
	case 'E':
		fault.changeFill();
		fault.draw();
		break;
	case '1':			//control camera rotation and angle
		setting = 1;
		printf("Mode Currently At: %d\n", setting);
		break;
	case '2':			//control camera lookat position
		setting = 2;
		printf("Mode Currently At: %d\n", setting);
		break;
	case '3':			
		setting = 3;	//control lighting position
		printf("Mode Currently At: %d\n", setting);
		break;
	case ' ':			//clears the terrain
		break;
	case 'x':
		fault.lightswitch();
		break;
	case 'l':
		if (lighting){
			lighting = false;
		}
		else{
			lighting = true;
		}
		break;
	case 'k':
		if (block){
			block = false;
		}
		else{
			block = true;
		}

	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	switch (key)
	{
	case GLUT_KEY_LEFT:
		switch (setting){
		case 1:
			camera.rotateLeft();
			break;
		case 2:
			camera.lookatleft();
			break;
		case 3:
			if (lightnum == 1){ light_position2[0] -= 0.2; }
			else{ light_position[0] -= 0.2; }
			
			break;
		}
		break;

	case GLUT_KEY_RIGHT:
		switch (setting){
		case 1:
			camera.rotateRight();
			break;
		case 2:
			camera.lookatright();
			break;
		case 3:
			if (lightnum == 1){ light_position2[0] += 0.2; }
			else{ light_position[0] += 0.2; }
			
			break;
		}
		break;

	case GLUT_KEY_UP:
		switch (setting){
		case 1:
			camera.moveForward();
			break;
		case 2:
			camera.lookatforward();
			break;
		case 3:
			if (lightnum == 1){ light_position2[2] += 0.2; }
			else{ light_position[2] += 0.2; }
			
			break;
		}
		break;

	case GLUT_KEY_DOWN:
		switch (setting){
		case 1:
			camera.moveBack();
			break;
		case 2:
			camera.lookatbackward();
			break;
		case 3:
			if (lightnum == 1){ light_position2[2] -= 0.2; }
			else{ light_position[2] -= 0.2; }
			
			break;
		}
		break;

	case GLUT_KEY_HOME:
		switch (setting){
		case 1:
			camera.angleUp();
			break;
		case 2:
			camera.lookatup();
			break;
		case 3:
			lightnum = 0;
			break;
		}
		break;

	case GLUT_KEY_END:
		switch (setting){
		case 1:
			camera.angleDown();
			break;
		case 2:
			camera.lookatdown();
			break;
		case 3:
			lightnum = 1;
			break;

		}
		break;
	}
	glutPostRedisplay();
}

void init(void)
{	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	if (block){
		glShadeModel(GL_FLAT);
	}
	else{
		glShadeModel(GL_SMOOTH);
	}
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);
	
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

}

void init2(void)
{
	int xcount = 0;
	int ycount = 0;
	int xstart, xend, zstart, zend;
	
	if (fault.getLen() % 2 == 0){
	xstart = 0 - (0.5)*fault.getLen();
	xend = (0.5)*fault.getLen();
	zstart = 0 - (0.5)*fault.getLen();
	zend = (0.5)*fault.getLen();
	}
	else{ //always truncates meaning add 1 to one area
		xstart = 0 - (0.5)*fault.getLen();
		xend = (0.5)*fault.getLen() + 1;
		zstart = 0 - (0.5)*fault.getLen();
		zend = (0.5)*fault.getLen() + 1;
	}
	gluOrtho2D(xstart, xend, zstart, zend);
	glPointSize(1);
}

//terrain map
void display2(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	fault.draw2d();
	glutPostRedisplay();
	glutSwapBuffers();
}


/* display function - GLUT display callback function
*		clears the screen, sets the camera position, draws the ground plane and movable box
*/
void display(void)
{
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	if (block){
		glShadeModel(GL_FLAT);
	}
	else{
		glShadeModel(GL_SMOOTH);
	}
	if (!lighting){
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
	}
	else{
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camera.x, camera.y, camera.z, camera.lx, camera.ly, camera.lz, 0, 1, 0);
	
	glColor3f(1, 1, 1);
	fault.draw();
	glutSwapBuffers();
}
void printhelp(void)
{
	printf("Key  | Function\n");
	printf("== == == == == == == == == =\n");
	printf("q    | Exit\n");//e r k l x
	printf("e    | Switch Between WireFrame and Filled\n");
	printf("r    | Generates 500 Fault\n");
	printf("k    | Switch Between GL_FLAT and GL_SMOOTH\n");
	printf("l    | Lighting On Off\n");
	printf("x    | Switch Between Vertex Shading and Flat Shading\n");
	printf("1    | Mode 1 Controls Camera\n");
	printf("2    | Mode 2 Controls Camera Look at Position\n");
	printf("3    | Mode 3 Controls Light\n");
	printf("Home | Moves Up Mode 3 Switch to light 1 controls\n");
	printf("End  | Moves Down Mode 3 Switch to light 2 controls\n");
	printf("up   | Move Forward\n");
	printf("down | Move Backward\n");
	printf("left | Mode1 Rotate Left Mode2 Move Left\n");
	printf("right | Mode1 Rotate Right Mode2 Move Right\n");
}
/* main function - program entry point */
int main(int argc, char** argv)
{
	printhelp();
	srand(time(NULL));			//random generator
	std::cout << "Input your side length:";
	GLint lens;
	std::cin >> lens;
	fault.setLens(lens);
	std::cout << "Set inital Run Iterations:";
	int iterate;
	std::cin >> iterate;
	fault.fault(iterate);

	//drawing main window
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 3");
	
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	
	init();

	glutInitWindowSize(lens*5, lens*5);
	glutCreateWindow("Terrain Map");
	glutPositionWindow(540, 40);
	glutDisplayFunc(display2);
	
	init2();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}