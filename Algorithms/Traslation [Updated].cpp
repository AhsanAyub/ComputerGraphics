#include <stdio.h>
#include <gl\glut.h>

int x, y, edgeNumber, arr[22];
static int arraySize = 1;

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

void translation()
{
	glColor3f(1.0, 0.0, 0.0); //RED
	glPointSize(2.0);

	int tracingIndex = 1; //responsible for indexing the array
	glBegin(GL_POLYGON);

	while (tracingIndex < (edgeNumber * 2))
	{
		glVertex2i((arr[tracingIndex] + x), (arr[tracingIndex + 1] +y));
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
	translation(); //Drawn as RED color

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

	for (int i = 1; i <= edgeNumber; i++) //Ordinates are inserted into the array
	{
		printf("Enter the co-ordinate of vertex %d:- ", i);
		scanf("%d %d", &arr[arraySize], &arr[arraySize + 1]);
		arraySize += 2;
	}
	printf("Enter the Translation factor for x and y:");
	scanf("%d %d", &x, &y);
	//translated values of x & y ordinate are inserted above
	
	glutDisplayFunc(basicTransformation);
	myInit();
	glutMainLoop();
}