#include "Header.h"
#include "triple.h"
#include <vector>
#include <math.h>
using namespace std;

class faultgenClass{
public:
	faultgenClass(void);

	faultgenClass(
		GLint lens, 
		GLdouble x, 
		GLdouble y,
		GLdouble z);

	void setLens(GLint lens);

	void setCoord(GLdouble x, GLdouble y, GLdouble z);

	//generates faults
	void fault(int iterations);

	//changes from wireframe to filled
	void changeFill(void);

	//draws the terrain
	void draw(void);

	void draw2d(void);

	//changes vertex color given the height and in reference to max height
	void heightColor(GLdouble height);

	//finds max and min values
	void maxminHeight(void);	

	//makes sure the plane isn't constantly rising
	void heightreadjust(void);

	//enables calculation for normals and sets all lighting
	void lightswitch(void);

	void normalCalculation(void);

	void vertextnormCalculation(void);

	triple crossproduct(triple a, triple b);

	triple normalize(triple a);

	int getLen(void);

private:
	vector<vector <GLdouble> > heightmap;
	vector<vector <triple> > surfacenormal;
	vector<vector <triple> > vertexnormal;

	int length;

	bool wireframe = true;

	bool lighting = true; //true for groald shading false for vertex shading

	GLdouble x, y, z, max = 0, min;
};
