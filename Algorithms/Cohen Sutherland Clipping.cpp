#include <stdio.h>
#include <GL\glut.h>

typedef unsigned int outcode;
enum { TOP = 0x1, BOTTOM = 0x2, RIGHT = 0x4, LEFT = 0x8 };

double x0, x1, y0, y1, xMin, xMax, yMin, yMax;

void drawClipRectangle()
{
	glColor3f(1.0, 0.0, 0.0); //Red Clipped Window
	glPointSize(4.0);

	glBegin(GL_LINE_LOOP);
	glVertex2d(xMin, yMin);
	glVertex2d(xMin, yMax);
	glVertex2d(xMax, yMax);
	glVertex2d(xMax, yMin);
	glEnd();
}

outcode outcodeComputation(double x, double y) //Getting the bitcode of point
{
	outcode code = 0;

	if (y > yMax)
		code |= TOP;
	else if (y < yMin)
		code |= BOTTOM;

	if (x > xMax)
		code |= RIGHT;
	else if (x < xMin)
		code |= LEFT;

	return code;
}

void CohenSutherlandClipAndDraw()
{
	outcode outcode0, outcode1, outcodeOut;
	bool accept = false, done = false;

	//Gathering the bit code of two points
	outcode0 = outcodeComputation(x0, y0);
	outcode1 = outcodeComputation(x1, y1);
	
	do
	{
		//Trivally accept, both of the points are situated inside clipped rectangle
		if (!(outcode0 | outcode1)) 
		{
			accept = true;
			done = true;
		}
		//Trivally reject, both of the points are situated outside clipped rectangle
		else if (outcode0 & outcode1)
		{
			done = true;
		}
		//Logically	TRUE so line can be clipped
		else
		{
			double x, y;
			//It picks out the point(s) which lies outside
			outcodeOut = outcode0 ? outcode0 : outcode1;

			if (outcodeOut & TOP) //Top region is to be clipped
			{
				x = x0 + (x1 - x0) * (yMax - y0) / (y1 - y0); //x's value will be changed by eqn
				y = yMax;
			}
			else if (outcodeOut & BOTTOM) //BOTTOM region is to be clipped
			{
				x = x0 + (x1 - x0) * (yMin - y0) / (y1 - y0); //x's value will be changed by eqn
				y = yMin;
			}
			else if (outcodeOut & RIGHT) //Right region is to be clipped
			{
				y = y0 + (y1 - y0) * (xMax - x0) / (x1 - x0); //y's value will be changed by eqn
				x = xMax;
			}
			else //Right region is to be clipped
			{
				y = y0 + (y1 - y0) * (xMin - x0) / (x1 - x0); //y's value will be changed by eqn
				x = xMin;
			}

			if (outcodeOut == outcode0)
			{ //Initial Points are changed and bitcode is again checked
				x0 = x;
				y0 = y;
				outcode0 = outcodeComputation(x0, y0);
			}
			else
			{ //Initial Points are changed and bitcode is again checked
				x1 = x;
				y1 = y;
				outcode1 = outcodeComputation(x1, y1);
			}
		}
	} while (done == false);

	if (accept)	//Line to be drwan from x0, y0 (either changed or initial value)
		//till x1, y1 (either changed or initial value)
	{
		glColor3f(0.0, 0.0, 0.0);
		glPointSize(2.0);

		glBegin(GL_LINES);
		glVertex2d(x0, y0);
		glVertex2d(x1, y1);
		glEnd();

		/*printf("x0 = %lf, y0 = %lf\n", x0, y0);
		printf("x1 = %lf, y1 = %lf\n", x1, y1);*/
	}
}

void ClippingOperation()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);

	drawClipRectangle(); //Drawing the clipped rectangle

	CohenSutherlandClipAndDraw(); //Algorithm for clipping the line

	glFlush();
}

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//clears the window, by overwriting it with the background color.
	//glClearColor(Red, Green, Blue, Alpha).

	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION); //used to specify/ handle current matrix

	glLoadIdentity(); //initializing to identity
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); //initializing GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //setting up its frame buffer
	glutInitWindowSize(640, 480); //width & height of the graphical window
	glutInitWindowPosition(0, 0); //location of the upper left corner of the graphical window
	glutCreateWindow("Line CLipping"); //Creates the graphical window, titled within the brackets

	printf("Enter Minimum window co-ordinates:- ");
	scanf("%lf %lf", &xMin, &yMin);
	printf("Enter Maximum window co-ordinates:- ");
	scanf("%lf %lf", &xMax, &yMax);
	printf("Enter co-ordinates of first point of line:- ");
	scanf("%lf %lf", &x0, &y0);
	printf("Enter co-ordinates of last point of line:- ");
	scanf("%lf %lf", &x1, &y1);

	glutDisplayFunc(ClippingOperation);
	myInit();
	glutMainLoop();
}