#include <stdio.h>
#include <gl\glut.h>

int xi, yi, x, y, d, R, b, a, fx, fy;
void DrawPoint(int x, int y)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0); //B
	glBegin(GL_POINTS);
	glPointSize(5.0);
	
	glVertex2i(x, y);
	glEnd();
}

void DrawingPointsTillY() //Responsible while the slope is NOT 1 or 2nd Region
{
	d = ((b * b) * ((x + 0.5) * (x + 0.5))) + ((a * a) * ((y - 1) * (y - 1))) - ((a * a) * (b * b));

	while (y > 0) //Points will be drawn till y's value reaches x axis, meaning 0
	{
		y -= 1;
		fy -= ((a * a) * 2);
		
		if (d < 0) //SE Point
		{
			x += 1;
			fx += ((b * b) * 2);
			d -= fy + (a * a) + fx;
		}
		
		else //E Point
			d -= fy + (a * a);
		
		DrawPoint(x + xi, y + yi); //1st Quad
		DrawPoint(-x + xi, y + yi); //2nd Quad
		DrawPoint(-x + xi, -y + yi); //3rd Quad
		DrawPoint(x + xi, -y + yi); //4th Quad
	}

	DrawPoint(x + xi, y + yi); //1st Quad
	DrawPoint(-x + xi, y + yi); //2nd Quad
	DrawPoint(-x + xi, -y + yi); //3rd Quad
	DrawPoint(x + xi, -y + yi); //4th Quad
}

void MidpointEllipseAlgorithm()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0); //RED
	glPointSize(5.0);

	//d = d(strat)
	d = (b * b) - ((a * a) * b) + (0.25 * (a * a));

	x = 0;
	y = b;
	fx = 2 * (b * b) * x;		//2b^2x
	fy = 2 * (a * a) * y;		//2a^2y

	while (fy > fx)
	{
		DrawPoint(x + xi, y + yi); //1st Quad
		DrawPoint(-x + xi, y + yi); //2nd Quad
		DrawPoint(-x + xi, -y + yi); //3rd Quad
		DrawPoint(x + xi,  -y + yi); //4th Quad

		if (x > a) //Checking if the x's value doesn't overflows
			break;

		x += 1;
		fx += 2 * (b * b);
		
		if (d >= 0) //SE Point
		{
			y -= 1;
			fy -= 2 * (a * a);
			d += fx + (b * b) - fy;
		}
		else //E Point as d < 0
			d += fx + (b * b); //  d = d + fx + b^2
	}

	DrawPoint(x + xi, y + yi); //1st Quad
	DrawPoint(-x + xi, y + yi); //2nd Quad
	DrawPoint(-x + xi, -y + yi); //3rd Quad
	DrawPoint(x + xi, -y + yi); //4th Quad
	
	DrawingPointsTillY();

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
	glutCreateWindow("Midpoint Ellipse Algorithm"); //Creates the graphical window, titled within the brackets

	printf("Enter the coordinates of the center:\n\n");
	printf("X-coordinate = ");
	scanf("%d", &xi);
	printf("Y-coordinate = ");
	scanf("%d", &yi);
	printf("Enter the major axix: ");
	scanf("%d", &a);
	printf("Enter the minor axix: ");
	scanf("%d", &b);

	glutDisplayFunc(MidpointEllipseAlgorithm);	
	myInit();
	glutMainLoop();
}