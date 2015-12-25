#include <iostream>
#include <cmath>
#include <cstdlib>
#include <GL/glut.h>

using namespace std;
int a,b,radius;
void writepoint(int x, int y)
{
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
}
void midPointCircle()
{
  int x = radius;
  int y = 0;
  int decision = 1 - x;
  while( y <= x )
  {
    writepoint( x + a,  y + b);
    writepoint( y + a,  x + b);
    writepoint(-x + a,  y + b);
    writepoint(-y + a,  x + b);
    writepoint(-x + a, -y + b);
    writepoint(-y + a, -x + b);
    writepoint( x + a, -y + b);
    writepoint( y + a, -x + b);
    y++;
    if (decision<=0)
    {
      decision += 2 * y + 1;
    }
    else
    {
      x--;
      decision += 2 * (y - x) + 1;
    }
  }
}
void myDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	glPointSize(1.0);

	midPointCircle();


	glFlush();
}

void myInit (void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}


void main(int argc, char** argv)
{
    cout<<"Mid-Point Circle Algorithm: "<<endl<<"==========================="<<endl<<endl<<endl;
    cout<<"Enter the x-coordinate for center: ";
    cin>>a;
    cout<<"Enter the y-coordinate for center: ";
    cin>>b;
    cout<<"Enter the radius length: ";
    cin>>radius;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (100, 150);
	glutCreateWindow ("my first attempt");
	glutDisplayFunc(myDisplay);
	myInit ();
	glutMainLoop();
}


