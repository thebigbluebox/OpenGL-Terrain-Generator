#include "faultgenClass.h"


faultgenClass::faultgenClass(void){
	length = 0;
	x = 0;
	y = 0;
	z = 0;
};

faultgenClass::faultgenClass(GLint lens, GLdouble x1, GLdouble y1, GLdouble z1){
	length = lens;
	x = x1;
	y = y1;
	z = z1;
	heightmap.resize(length);
	for (int x = 0; x < length+1; x++){
		heightmap[x].resize(length);
	}
	surfacenormal.resize(length);
	for (int x = 0; x < length; x++){
		surfacenormal[x].resize(length);
	}
	vertexnormal.resize(length);
	for (int x = 0; x < length; x++){
		vertexnormal[x].resize(length);
	}
}

void faultgenClass::setLens(GLint lens1){
	length = lens1;
	heightmap.resize(length);
	for (int x = 0; x < length; x++){
		heightmap[x].resize(length);
	}
	surfacenormal.resize(length);
	for (int x = 0; x < length; x++){
		surfacenormal[x].resize(length);
	}
	vertexnormal.resize(length);
	for (int x = 0; x < length; x++){
		vertexnormal[x].resize(length);
	}
}

void faultgenClass::setCoord(GLdouble x1, GLdouble y1, GLdouble z1){
	x = x1;
	y = y1;
	z = z1;
}

void faultgenClass::changeFill(void){
	if (wireframe == true){
		wireframe = false;
	}
	else{
		wireframe = true;
	}
}

void faultgenClass::maxminHeight(void){
	min = heightmap[0][0]; //sets baseline for comparison
	for (int x = 0; x < length; x++){
		for (int y = 0; y < length; y++){
			if (heightmap[x][y] > max){
				max = heightmap[x][y];
			}
			if (heightmap[x][y] < min){
				min = heightmap[x][y];
			}
		}
	}
}

void faultgenClass::heightreadjust(void){
	if (min > 0){
		for (int x = 0; x < length; x++){
			for (int y = 0; y < length; y++){
				heightmap[x][y] -= min;
			}
		}
	}
}

void faultgenClass::heightColor(GLdouble height){
	GLfloat mat_ambient[] = {1,1,1,1};
	GLfloat mat_diffuse[] = { 0.78, 0.57, 0.11, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 70 };

	if (height > max){
		glColor3f(1, 1, 1);
	}
	if (height > max*0.75 && height < max){
		glColor3f(0.14509, 0.0549, 0);
	}
	if (height > max*0.5 && height < max*0.75){
		glColor3f(0.349019, 0.13333, 0.007);
	}
	if (height > max*0.25 && height < max*0.5){
		glColor3f(0.149019, 0.45098, 0.007);
	}
	if (height < 0){
		glColor3f(0.019607843, 0.58823, 0.83137);
	}
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void faultgenClass::fault(int iterations){
	for (int it = 0; it < iterations; it++){
		heightreadjust();
		maxminHeight();
		GLint v = rand();
		GLdouble a = sin(v);
		GLdouble b = cos(v);
		GLdouble d = sqrt(2 * length*length);

		GLdouble c = ((float)rand() / RAND_MAX) * d - d / 2;

		for (int x = 0; x < length; x++){
			for (int y = 0; y < length; y++){
				if ((a*x + b*y - c) > 0){
					heightmap[x][y] += 0.1;
				}
				else{
					heightmap[x][y] -= 0.1;
				}
			}
		}
	}
}


/*void faultgenClass::fault(int iterations){
	heightreadjust();
	maxminHeight();
	for (int i = 0; i < iterations; i++){
		int rx = rand() % length;
		int ry = rand() % length;
		GLdouble a = ((GLdouble)rand() / (RAND_MAX))*0.3;
		//extra random fault algorithm
		int b = rand() % 3;
		for (int x = 0; x < length; x++){
			for (int y = 0; y < length; y++){
				if(b == 0){
					if (x > rx && y > ry){
						heightmap[x][y] -= a;
					}
					else{
						heightmap[x][y] += a;
					}
				}
				if(b == 1){	
					if (x < rx && y < ry){
						heightmap[x][y] -= a;
					}
					else{
						heightmap[x][y] += a;
					}
				}
				if (b == 2){
					if (x > rx && y < ry){
						heightmap[x][y] -= a;
					}
					else{
						heightmap[x][y] += a;
					}
				}
				if (b == 3){
					if (x < rx && y > ry){
						heightmap[x][y] -= a;
					}
					else{
						heightmap[x][y] += a;
					}
				}
			}
		}
	}
}*/


void faultgenClass::lightswitch(void){
	if (lighting == true){
		lighting = false;
	}
	else{
		lighting = true;
	}
}

void faultgenClass::draw(void){
	normalCalculation();
	vertextnormCalculation();

	int xcount = 0;
	int ycount = 0;
	int xstart, xend, zstart, zend;
	
	if (length % 2 == 0){
		xstart = x - (0.5)*length;
		xend = x + (0.5)*length;
		zstart = z - (0.5)*length;
		zend = z + (0.5)*length;
	}
	else{ //always truncates meaning add 1 to one area
		xstart = x - (0.5)*length;
		xend = x + (0.5)*length + 1;
		zstart = y - (0.5)*length;
		zend = y + (0.5)*length + 1;
	}
	
	//changes between the wireframe and fill
	if (wireframe){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//drawing base out line of grid
	glBegin(GL_QUADS);
	glColor3f(0.019607843, 0.58823, 0.83137);
		glVertex3d(xstart*0.5, 0, zstart*0.5);
		glColor3f(0.019607843, 0.58823, 0.83137);
		glVertex3d(xstart*0.5, 0, zend*0.5);
		glColor3f(0.019607843, 0.58823, 0.83137);
		glVertex3d(xend*0.5, 0, zend*0.5);
		glColor3f(0.019607843, 0.58823, 0.83137);
		glVertex3d(xend*0.5, 0, zstart*0.5);
	glEnd();

	//begin drawing whole scene
	for (int i = xstart; i < xend-1; i++){
		//reseting y index after iteration
		ycount = 0;
		for (int i2 = zstart; i2 < zend-1; i2++){
			
			GLdouble x1 = i*0.5; //x2 is the same
			GLdouble x3 = (i+1)*0.5; //x4 is the same
			GLdouble y1 = heightmap[xcount][ycount];
			GLdouble y2 = heightmap[xcount][ycount + 1];
			GLdouble y3 = heightmap[xcount + 1][ycount + 1];
			GLdouble y4 = heightmap[xcount + 1][ycount];
			GLdouble z1 = i2*0.5;		//x4 is the same
			GLdouble z2 = (i2+1)*0.5; // x3 is th e same
			
			if (lighting){
				triple temp = surfacenormal[xcount][ycount];
				glNormal3d(temp.x, temp.y, temp.z);

				glBegin(GL_QUADS);
				heightColor(y1);
				glVertex3d(x1, y1, z1);

				heightColor(y2);
				glVertex3d(x1, y2, z2);

				heightColor(y3);
				glVertex3d(x3, y3, z2);

				heightColor(y4);
				glVertex3d(x3, y4, z1);
				glEnd();
			}
			else{
				triple temp = vertexnormal[xcount][ycount];
				glNormal3d(temp.x, temp.y, temp.z);

				glBegin(GL_QUADS);
				heightColor(y1);
				glVertex3d(x1, y1, z1);

				temp = vertexnormal[xcount][ycount+1];
				glNormal3d(temp.x, temp.y, temp.z);
				heightColor(y2);
				glVertex3d(x1, y2, z2);

				temp = vertexnormal[xcount+1][ycount + 1];
				glNormal3d(temp.x, temp.y, temp.z);
				heightColor(y3);
				glVertex3d(x3, y3, z2);

				temp = vertexnormal[xcount + 1][ycount];
				glNormal3d(temp.x, temp.y, temp.z);
				heightColor(y4);
				glVertex3d(x3, y4, z1);
				glEnd();
			}
			//increases y index in the height map
			ycount++;
			}
		//increases x index in the height map
		xcount++;
		}
}

void faultgenClass::draw2d(void){
	//normalCalculation();
	//vertextnormCalculation();

	int xcount = 0;
	int ycount = 0;
	int xstart, xend, zstart, zend;

	if (length % 2 == 0){
		xstart = 0 - (0.5)*length;
		xend = (0.5)*length;
		zstart = 0- (0.5)*length;
		zend = (0.5)*length;
	}
	else{ //always truncates meaning add 1 to one area
		xstart = 0 - (0.5)*length;
		xend = (0.5)*length + 1;
		zstart = 0 - (0.5)*length;
		zend = (0.5)*length + 1;
	}

	//drawing base out line of grid
	/*glBegin(GL_QUADS);
	glColor3f(0.019607843, 0.58823, 0.83137);
	glVertex3d(xstart*0.5, 0, zstart*0.5);
	glColor3f(0.019607843, 0.58823, 0.83137);
	glVertex3d(xstart*0.5, 0, zend*0.5);
	glColor3f(0.019607843, 0.58823, 0.83137);
	glVertex3d(xend*0.5, 0, zend*0.5);
	glColor3f(0.019607843, 0.58823, 0.83137);
	glVertex3d(xend*0.5, 0, zstart*0.5);
	glEnd();
*/
	//begin drawing whole scene
	for (int i = xstart; i < xend - 1; i++){
		//reseting y index after iteration
		ycount = 0;
		for (int i2 = zstart; i2 < zend - 1; i2++){

			//GLdouble x1 = i*0.5; //x2 is the same
			//GLdouble x3 = (i + 1)*0.5; //x4 is the same
			//GLdouble y1 = heightmap[xcount][ycount];
			//GLdouble y2 = heightmap[xcount][ycount + 1];
			//GLdouble y3 = heightmap[xcount + 1][ycount + 1];
			//GLdouble y4 = heightmap[xcount + 1][ycount];
			//GLdouble z1 = i2*0.5;		//x4 is the same
			//GLdouble z2 = (i2 + 1)*0.5; // x3 is th e same

			
				triple temp = surfacenormal[xcount][ycount];
				//glNormal3d(temp.x, temp.y, temp.z);

				glPointSize(5);
				glBegin(GL_POINTS);
				heightColor(heightmap[xcount][ycount]);
				glVertex2d(i, i2);

				//heightColor(y2);
				//glVertex2d(x1,z2);

				//heightColor(y3);
				//glVertex2d(x3,z2);

				//heightColor(y4);
				//glVertex2d(x3,z1);
				glEnd();
			
			//increases y index in the height map
			ycount++;
		}
		//increases x index in the height map
		xcount++;
	}
}

	void faultgenClass::normalCalculation(void){
		for (int i = 0; i < length-1; i++){
			for (int i2 = 0; i2 < length-1; i2++){
				triple a;
				triple b;
				triple c;
				triple d;

				a.x = i;
				a.y = heightmap[i][i2];
				a.z = i2;

				b.x = i;
				b.y = heightmap[i][i2 + 1];
				b.z = i2 + 1;

				c.x = i + 1;
				c.y = heightmap[i + 1][i2 + 1];
				c.z = i2 + 1;

				d.x = i + 1;
				d.y = heightmap[i + 1][i2];
				d.z = i2;

				//create the vectors we need for averaging

				triple na;
				triple nb;
				triple nc;
				triple nd;

				na.x = b.x - a.x;
				na.y = b.y - a.y;
				na.z = b.z - a.z;

				nb.x = c.x - b.x;
				nb.y = c.y - b.y;
				nb.z = c.z - b.z;

				nc.x = c.x - d.x;
				nc.y = c.y - d.y;
				nc.z = c.z - d.z;

				nd.x = d.x - a.x;
				nd.y = d.y - a.y;
				nd.z = d.z - a.z;


				triple n1 = crossproduct(na, nd);
				triple n2 = crossproduct(na, nb);
				triple n3 = crossproduct(nc, nb);
				triple n4 = crossproduct(nc, nd);

				triple n;
				n.x = (n1.x + n2.x + n3.x + n4.x) / 4;
				n.y = (n1.y + n2.y + n3.y + n4.y) / 4;
				n.z = (n1.z + n2.z + n3.z + n4.z) / 4;

				n = normalize(n);

				surfacenormal[i][i2] = n; //where it will be saved to
			}
		}
	}

	void faultgenClass::vertextnormCalculation(void){
		for (int i = 1; i < length - 1; i++){
			for (int i2 = 1; i2 < length - 1; i2++){
				triple a;
				triple b;
				triple c;
				triple d;
				triple current;
				
				current.x = i;
				current.y = heightmap[i][i2];
				current.z = i2;

				a.x = i - 1 - current.x;
				a.y = heightmap[i-1][i2] - current.y;
				a.z = i2 - current.z;

				b.x = i - current.x;
				b.y = heightmap[i][i2 - 1] - current.y;
				a.z = i2 - 1 - current.z;

				c.x = i + 1 - current.x;
				c.y = heightmap[i + 1][i2] - current.y;
				c.z = i2 - current.z;

				d.x = i - current.x;
				d.y = heightmap[i][i2+1] - current.y;
				d.z = i2 + 1 - current.z;

				triple n1 = crossproduct(a, b);
				triple n2 = crossproduct(b, c);
				triple n3 = crossproduct(c, d);
				triple n4 = crossproduct(d, a);

				triple n;
				n.x = (n1.x + n2.x + n3.x + n4.x) / 4;
				n.y = -1*(n1.y + n2.y + n3.y + n4.y) / 4;
				n.z = (n1.z + n2.z + n3.z + n4.z) / 4;

				n = normalize(n);

				vertexnormal[i][i2] = n; //where it will be saved to
			}
		}
	}

	triple faultgenClass::crossproduct(triple a, triple b){
		triple normal;
		normal.x = a.y*b.z - a.z*b.y;
		normal.y = a.z*b.x - a.x*b.z;
		normal.z = a.x*b.y - a.y*b.x;
		return normal;
	}

	triple faultgenClass::normalize(triple a){
		triple normal;
		GLdouble mag = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
		normal.x = a.x / mag;
		normal.y = a.y / mag;
		normal.z = a.z / mag;
		return normal;
	}

	int faultgenClass::getLen(void){
		return length;
	}