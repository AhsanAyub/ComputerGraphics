#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>
#include <gl\GL.h>
#include <math.h>
#include <string>

const int static YiOfRunner = 200, YfOfRunner = 500;
const int static XiOfObstacle = 920, XfOfObstacle = 1000;

int Obstacle_Xf = XfOfObstacle, Obstacle_Xi = XiOfObstacle, Obstacle_Yi = 200, Obstacle_Yf = 300;
int Runner_Xi = 200, Runner_Xf = 300, Runner_Yi = YiOfRunner, Runner_Yf = YfOfRunner;

int refreshMilis = 20;
bool RunnerMovementUpwardStatus = false, RunnerMovementDownwardStatus = false;

void ObstracleMovement()
{
	glColor3f(0.0, 0.0, 0.0); //Black colored boxed obstacle
	glBegin(GL_POLYGON);
	glVertex2i(Obstacle_Xf, Obstacle_Yi);
	glVertex2i(Obstacle_Xf, Obstacle_Yf);
	glVertex2i(Obstacle_Xi, Obstacle_Yf);
	glVertex2i(Obstacle_Xi, Obstacle_Yi);
	glEnd();
	//printf("ObstacleTranslaionThroughXAxis = %d\n", ObstacleTranslaionThroughXAxis);
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
}

void RunnerDesign()
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

void RunnerMovementDownward()
{
	if (Runner_Yi != Obstacle_Yi)
	{
		Runner_Yi--;
		Runner_Yf--;
		glutPostRedisplay();
	}
	else if (Runner_Xi <= Obstacle_Xf && Runner_Xf >= Obstacle_Xi)
	{
		//Collision

		glutDestroyWindow(0);
		exit(0);
	}
	else
	{
		RunnerMovementDownwardStatus = false;

		return;
	}
}

void RunnerMovementUpward()
{
	if (Runner_Yi < (Obstacle_Yf + 70))
	{
		Runner_Yi++;
		Runner_Yf++;
		glutPostRedisplay();
	}
	else if (Runner_Xi <= Obstacle_Xf && Runner_Xf >= Obstacle_Xi)
	{
		//Collision

		glutDestroyWindow(0);
		exit(0);
	}
	else
	{
		RunnerMovementDownwardStatus = true;
		RunnerMovementUpwardStatus = false;
		RunnerMovementDownward();
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	BasementForRunning(); //It will always remain static

	ObstracleMovement();
	RunnerDesign();
	
	glutSwapBuffers();

	/* Obstacle's Continuous Increamental Conditions*/
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

	/* Runner's Increamental Condition if Keyboard button is pressed*/
	if (RunnerMovementUpwardStatus == true)
		//RunnerMovementUpward();
	{
		if (Runner_Yi < (Obstacle_Yf + 120))
		{
			Runner_Yi++;
			Runner_Yf++;
			if(Runner_Xi <= Obstacle_Xf && Runner_Xf >= Obstacle_Xi)
			{
				//Collision
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
			Runner_Yi--;
			Runner_Yf--;
			if (Runner_Xi <= Obstacle_Xf && Runner_Xf >= Obstacle_Xi)
			{
				//Collision
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
			printf("\nSUCCESSFULL JUMP\n\n");
			RunnerMovementDownwardStatus = false;
		}
	}
	else
	{
		if (Runner_Xi <= Obstacle_Xf && Runner_Xf >= Obstacle_Xi)
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

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(refreshMilis, Timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
	{
		RunnerMovementUpwardStatus = true;
		glutPostRedisplay();
	}
}

void myinit()
{
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1000.0, 0.0, 1000.0); // LEFT, RIGHT, BOTTOM & TOP
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Dauntless Runner");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutTimerFunc(0, Timer, 0);
	
	myinit();
	glutMainLoop();
}