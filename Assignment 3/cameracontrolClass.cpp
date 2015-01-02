#include "cameracontrolClass.h"
GLdouble a;

cameracontrolClass::cameracontrolClass(void){
	GLdouble r1 = 2;
	lx = 0.0;
	ly = 0.0;
	lz = 0.0;
	x = sqrt(r1);
	y = sqrt(r1);
	z = sqrt(r1);
	r = 1;
}

cameracontrolClass::cameracontrolClass(
	GLdouble x1,
	GLdouble y1,
	GLdouble z1,
	GLdouble lx1,
	GLdouble ly1,
	GLdouble lz1
	){
	x = x1;
	y = y1;
	z = z1;
	lx = lx1;
	ly = ly1;
	lz = lz1;
	r = sqrt(pow(x, 2) + pow(z, 2));
	a = 90 - tan(x / z);
}

void cameracontrolClass::setlookAt(GLdouble x, GLdouble y, GLdouble z){
	lx = x;
	ly = y;
	lz = z;
}

void cameracontrolClass::setcam(GLdouble x1, GLdouble y1, GLdouble z1){
	x = x1;
	y = y1;
	z = z1;
}

void cameracontrolClass::rotateLeft(void){
	a += 0.05;
	x = lx + r * cos(a);
	z = lz + r * sin(a);
}
void cameracontrolClass::rotateRight(void){
	a -= 0.05;
	x = lx + r * cos(a);
	z = lz + r * sin(a);
}

void cameracontrolClass::moveForward(void){
	if (!(r - 0.4 <= 0)){
		GLdouble ratio = (r - 0.4) / r;
		r -= 0.4;
		x *= ratio;
		z *= ratio;
	}
}

void cameracontrolClass::moveBack(void){
	GLdouble ratio = (r + 0.4) / r;
	r += 0.4;
	x *= ratio;
	z *= ratio;
}

void cameracontrolClass::angleDown(void){
	y -= 0.5;

}
void cameracontrolClass::angleUp(void){
	y += 0.5;
}

void cameracontrolClass::lookatup(void){
	ly += 0.2;
}

void cameracontrolClass::lookatdown(void){
	ly -= 0.2;
}

void cameracontrolClass::lookatleft(void){
	lx -= 0.2;
}

void cameracontrolClass::lookatright(void){
	lx += 0.2;
}

void cameracontrolClass::lookatforward(void){
	lz += 0.2;
}

void cameracontrolClass::lookatbackward(void){
	lz -= 0.2;
}