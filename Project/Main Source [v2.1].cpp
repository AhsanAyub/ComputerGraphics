#include <stdio.h>
#include <GL\glut.h>

//Initial position of the variable ordinates of runner and obstacle
const int static YiOfRunner = 200, YfOfRunner = 500;
const int static XiOfObstacle = 920, XfOfObstacle = 1000;

//Defining all the ordinates for both runner and obstacles
int Obstacle_Xf = XfOfObstacle, Obstacle_Xi = XiOfObstacle, Obstacle_Yi = 200, Obstacle_Yf = 300;
int Runner_Xi = 200, Runner_Xf = 300, Runner_Yi = YiOfRunner, Runner_Yf = YfOfRunner;

int WaitCallInMS = 1; //Responsible for refreshing or call back function, measured in Mili Secs
//Two status flags for upward and downward (vertical) movement of runner
bool RunnerMovementUpwardStatus = false, RunnerMovementDownwardStatus = false;



void myinit(void)
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1000.0, 00.0, 1000.0); // LEFT, RIGHT, BOTTOM & TOP
}

void ObstracleMovement() //Obstacle drawing function in polygon shaped
{
	glColor3f(0.0, 0.0, 0.0); //Black colored boxed obstacle
	glBegin(GL_POLYGON);
	glVertex2i(Obstacle_Xf, Obstacle_Yi);
	glVertex2i(Obstacle_Xf, Obstacle_Yf);
	glVertex2i(Obstacle_Xi, Obstacle_Yf);
	glVertex2i(Obstacle_Xi, Obstacle_Yi);
	glEnd();
}

void BasementForRunning()
{
	glColor3f(0.7, 0.0, 0.0); //Light red colored basement
	glBegin(GL_POLYGON);
	glVertex2d(0, 0);
	glVertex2d(0, 200);
	glVertex2d(1000, 200);
	glVertex2d(1000, 0);
	glEnd();
	glFlush();
}

void RunnerDesign() //Runner is designed in three parts -> Head, Mid region and Legs
{
	printf("Runner: Yi = %d & Yf = %d	||	Obstacle: Xi = %d & Xf = %d\n", Runner_Yi, Runner_Yf, Obstacle_Xi, Obstacle_Xf);
	glColor3f(0.0, 0.0, 0.6); //Light Blue colored
	glBegin(GL_QUADS); //Head of runner
	glVertex2i(Runner_Xi, Runner_Yf);
	glVertex2i(Runner_Xf, Runner_Yf);
	glVertex2i(Runner_Xf, Runner_Yf - 100);
	glVertex2i(Runner_Xi, Runner_Yf - 100);
	glEnd();

	glColor3f(0.0, 0.0, 0.2); //Light Blue colored
	glBegin(GL_QUADS); //Middle region of runner
	glVertex2i(Runner_Xi, Runner_Yf - 100);
	glVertex2i(Runner_Xf, Runner_Yf - 100);
	glVertex2i(Runner_Xf, Runner_Yi + 100);
	glVertex2i(Runner_Xi, Runner_Yi + 100);
	glEnd();

	glColor3f(0.0, 0.0, 0.4); //Light Blue colored
	glBegin(GL_QUADS); //Lower region of runner
	glVertex2i(Runner_Xi, Runner_Yi + 100);
	glVertex2i(Runner_Xf, Runner_Yi + 100);
	glVertex2i(Runner_Xf, Runner_Yi);
	glVertex2i(Runner_Xi, Runner_Yi);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);

	BasementForRunning(); //It will always remain static

	ObstracleMovement(); //involing obstacle function to draw obstacle
	RunnerDesign(); //involing runner function to draw obstacle

	glutSwapBuffers();

	/* Obstacle's Continuous Decremental Conditions along X axis*/
	if (Obstacle_Xi >= 1)
	{
		Obstacle_Xi--;
		Obstacle_Xf--;
	}
	else
	{
		Obstacle_Xf = 1000;
		Obstacle_Xi = 920;
	}

	/* Runner's Increamental/ Decremental Conditions along Y axis while Keyboard button W is pressed*/
	if (RunnerMovementUpwardStatus == true)
	{
		if (Runner_Yi < (Obstacle_Yf + 120))
		{
			//Upward incremental condition of Runner is performed below
			Runner_Yi++;
			Runner_Yf++;
			if (Runner_Xi <= Obstacle_Xf && Runner_Xf >= Obstacle_Xi) //Collision occuring condition
			{
				if (Runner_Yi <= Obstacle_Yf)
				{
					printf("\nUPWARD COLLISION\n");
					printf("GAME RESTARTED\n\n");

					RunnerMovementUpwardStatus = false;
					RunnerMovementDownwardStatus = false;
					//Setting to the initial values
					Obstacle_Xf = XfOfObstacle;
					Obstacle_Xi = XiOfObstacle;
					Runner_Yi = YiOfRunner;
					Runner_Yf = YfOfRunner;
				}
			}
		}
		else
		{
			RunnerMovementDownwardStatus = true;
			RunnerMovementUpwardStatus = false;
		}
	}
	else if (RunnerMovementDownwardStatus == true)
		//RunnerMovementDownward();
	{
		if (Runner_Yi != Obstacle_Yi)
		{
			//Downward decremental condition of Runner is performed below
			Runner_Yi--;
			Runner_Yf--;
			if (Runner_Xi <= Obstacle_Xf && Runner_Xf >= Obstacle_Xi) //Collision occuring condition
			{
				if (Runner_Yi <= Obstacle_Yf)
				{
					printf("\nDOWNWARD COLLISION\n");
					printf("GAME RESTARTED\n\n");

					RunnerMovementUpwardStatus = false;
					RunnerMovementDownwardStatus = false;
					//Setting to the initial values
					Obstacle_Xf = XfOfObstacle;
					Obstacle_Xi = XiOfObstacle;
					Runner_Yi = YiOfRunner;
					Runner_Yf = YfOfRunner;
				}
			}
		}
		else
		{
			printf("\nSUCCESSFULL JUMP\n\n"); //No flaws found!!
			RunnerMovementDownwardStatus = false;
		}
	}
	else //It will occur if runner and obstacle collide on basement
	{
		if (Runner_Xi <= Obstacle_Xf && Runner_Xf >= Obstacle_Xi) //Collision condition
		{
			//yiObject <= yfObstacle)
			if (Runner_Yi <= Obstacle_Yf)
			{
				printf("\nOverlapping Collision\n");
				printf("GAME RESTARTED\n\n");

				//Setting to the initial values
				Obstacle_Xf = XfOfObstacle;
				Obstacle_Xi = XiOfObstacle;
				Runner_Yi = YiOfRunner;
				Runner_Yf = YfOfRunner;
			}
		}
	}
}

void reshape(GLsizei width, GLsizei height) // This effing method cost me a day :@
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(WaitCallInMS, Timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W') // Upward Movement of Runner
	{
		RunnerMovementUpwardStatus = true;
		RunnerMovementDownwardStatus = false;
		glutPostRedisplay();
	}
	else if (key == 'x' || key == 'X') // Downward movement of runner OCCURED!
	{
		RunnerMovementDownwardStatus = true;
		RunnerMovementUpwardStatus = false;
		glutPostRedisplay();
	}
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Dauntless Runner");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutTimerFunc(0, Timer, 0);

	myinit();
	glutMainLoop();
	return 0;
}