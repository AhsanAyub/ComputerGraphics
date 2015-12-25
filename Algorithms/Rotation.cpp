#include <stdio.h>
#include <math.h>
#include <GL\glut.h>

int edgeNumber, angle;
static int arraySize = 1;
double arr[22], R[2] = { 0, 0 }, AngleInRadian, S[2][2];

/*
	S Matrix:
	cos(AngleInRadian), -sin(AngleInRadian),
	sin(AngleInRadian), cos(AngleInRadian)
*/

void matrixCalculation(int index)
{
	// X' = S * X ; here, X' = R
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			R[i] += (arr[index + j] * S[i][j]); //arr[] is just providing the ordinates
		}
		arr[index + i] = R[i]; //Converting the result to the inserted array
		R[i] = 0;
		//Making the element zero for further calculation for the next ordinates
	}
}

void drawOriginal()
{
	glColor3f(0.0, 0.0, 1.0); //BLUE
	glPointSize(2.0);

	int tracingIndex = 1; //responsible for indexing the array
	glBegin(GL_POLYGON);

	while (tracingIndex < (edgeNumber * 2))
	{
		glVertex2i(arr[tracingIndex], arr[tracingIndex + 1]);
		tracingIndex += 2;
		//jumping to the next x and y
	}
	glEnd();	
}

void rotation()
{
	glColor3f(1.0, 0.0, 0.0); //RED
	glPointSize(2.0);

	int tracingIndex = 1; //responsible for indexing the array
	glBegin(GL_POLYGON);

	while (tracingIndex < (edgeNumber * 2))
	{
		matrixCalculation(tracingIndex);
		glVertex2i((arr[tracingIndex]), (arr[tracingIndex + 1]));
		//x & y's value will be added to the inserted ordinate respectively
		tracingIndex += 2;
		//jumping to the next x and y
	}
	glEnd();
}

void basicTransformation()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);

	drawOriginal(); //Drawn as BLUE color
	rotation(); //Drawn as RED color

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
	glutCreateWindow("Basic Transformation"); //Creates the graphical window, titled within the brackets

	printf("Enter the no. of edges:- ");
	scanf("%d", &edgeNumber);

	for (int i = 1; i <= edgeNumber; i++)
	{
		printf("Enter the co-ordinate of vertex %d:- ", i);
		scanf("%lf %lf", &arr[arraySize], &arr[arraySize + 1]);
		arraySize += 2;
	}

	printf("Angle to ROTATE: ");
	scanf("%d", &angle);

	AngleInRadian = angle * (3.1416 / 180);
	//Converting the given angle(in degree) into the radian

	//Initializing S matrix
	S[0][0] = cos(AngleInRadian);
	S[0][1] = -sin(AngleInRadian);
	S[1][0] = sin(AngleInRadian);
	S[1][1] = cos(AngleInRadian);

	glutDisplayFunc(basicTransformation);
	myInit();
	glutMainLoop();
}