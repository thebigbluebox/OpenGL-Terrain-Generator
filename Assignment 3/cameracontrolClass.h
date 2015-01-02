#include "Header.h"
#include <math.h>
using namespace std;
class cameracontrolClass{
public:
	cameracontrolClass(void);

	cameracontrolClass(
		GLdouble x1,
		GLdouble y1,
		GLdouble z1,
		GLdouble lx1,
		GLdouble ly1,
		GLdouble lz1
		);

	void setlookAt(GLdouble x, GLdouble y, GLdouble z);

	void setcam(GLdouble x, GLdouble y, GLdouble z);

	void rotateLeft(void);

	void rotateRight(void);

	void moveBack(void);

	void moveForward(void);

	void angleUp(void);

	void angleDown(void);

	void lookatup(void);

	void lookatdown(void);

	void lookatleft(void);

	void lookatright(void);

	void lookatforward(void);
	
	void lookatbackward(void);

	GLdouble lx, ly, lz, x, y, z, r; //x is camera coord and lx is lookat coord
};
