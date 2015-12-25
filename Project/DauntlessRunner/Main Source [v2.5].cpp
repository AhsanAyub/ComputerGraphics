#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <GL\glut.h>
#include "imageloader.h"

//Initial position of the variable ordinates of runner and obstacle and background
const int static YiOfRunner = 200, YfOfRunner = 500;
const int static XiOfObstacle = 920, XfOfObstacle = 1000;
const int static XiOfBackground = 0, XfOfBackground = 1000;

//Variables to store and display score
int scoreReal = 0;
int num[10];

//Defining all the ordinates for runner, obstacles and background
int Obstacle_Xf = XfOfObstacle, Obstacle_Xi = XiOfObstacle, Obstacle_Yi = 200, Obstacle_Yf = 300;
int Runner_Xi = 200, Runner_Xf = 300, Runner_Yi = YiOfRunner, Runner_Yf = YfOfRunner;
int Background_Xf = XfOfBackground, Background_Xi = XiOfBackground, Background_Yi = 0, Background_Yf = 1000;
int Background2_Xf = XfOfBackground + 1000, Background2_Xi = XiOfBackground + 1000, Background2_Yi = 0, Background2_Yf = 1000;

int WaitCallInMS = 1; //Responsible for refreshing or call back function, measured in Mili Secs

//Variables to help display texts
char *_stringScore = "Score : ";
char *_stringGameOver = "GAME OVER --- TOTAL SCORE : ";
char *_stringStart = "Computer Graphics [A] - \"Dauntless Runner\" (an obstacle avoidance game) ### Ayub, Md. Ahsan : 13-23980-2 # Ali, Nafis : 13-24925-3 # Orko, Mahabub Sobhan : 13-25055-3 ## Music Credit : \"We Can Make The World Stop\" by The Glitch Mob ### Instructions : # Press W to jump and avoid incoming cactus. # Press P/R to pause/resume game. # Press ENTER to start/reset game. # Press ESCAPE to return to start screen.";


//Two status flags for upward and downward (vertical) movement of runner
bool RunnerMovementUpwardStatus = false, RunnerMovementDownwardStatus = false;

//Status flag for pause/resume game
bool Paused = false;

//Flag for game being and end
bool gameStart = true;
bool gameOver = false;

//Input flag
bool keyFlag = false;

//Texture initialization
GLuint _textureCactus;
GLuint _textureHead;
GLuint _textureBody;
GLuint _textureLegs;
GLuint _textureBackground;


//Function to initialize textures
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
		//as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void myinit(void)
{
	glClearColor(1, 1, 1, 1);
	//glColor3f(0.0f, 0.0f, 0.0f);
	//glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1000.0, 00.0, 1000.0); // LEFT, RIGHT, BOTTOM & TOP

	Image* cactus = loadBMP("cactus.bmp");	
	Image* head = loadBMP("head.bmp");
	Image* body = loadBMP("body.bmp");
	Image* legs = loadBMP("legs.bmp");
	Image* background = loadBMP("background.bmp");

	_textureCactus = loadTexture(cactus);	
	_textureHead = loadTexture(head);
	_textureBody = loadTexture(body);
	_textureLegs = loadTexture(legs);
	_textureBackground = loadTexture(background);

	delete cactus;
	delete head;
	delete body;
	delete legs;
	delete background;
}

void Environment() //Background drawing. Same image rendered twice to imitate continuity
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureBackground);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex2i(Background_Xf, Background_Yi);
		glTexCoord2f(1.0, 1.0);
		glVertex2i(Background_Xf, Background_Yf);
		glTexCoord2f(0.0, 1.0);
		glVertex2i(Background_Xi, Background_Yf);
		glTexCoord2f(0.0, 0.0);
		glVertex2i(Background_Xi, Background_Yi);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, _textureBackground);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_POLYGON);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex2i(Background2_Xf, Background2_Yi);
		glTexCoord2f(1.0, 1.0);
		glVertex2i(Background2_Xf, Background2_Yf);
		glTexCoord2f(0.0, 1.0);
		glVertex2i(Background2_Xi, Background2_Yf);
		glTexCoord2f(0.0, 0.0);
		glVertex2i(Background2_Xi, Background2_Yi);
	glEnd();

	glFlush();
}

void ObstacleDesign() //Obstacle drawing function in polygon shaped
{
	glEnable(GL_TEXTURE_2D);	

	glBindTexture(GL_TEXTURE_2D, _textureCactus);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex2i(Obstacle_Xf, Obstacle_Yi);
		glTexCoord2f(0.0, 1.0);
		glVertex2i(Obstacle_Xf, Obstacle_Yf);
		glTexCoord2f(1.0, 1.0);
		glVertex2i(Obstacle_Xi, Obstacle_Yf);
		glTexCoord2f(1.0, 0.0);
		glVertex2i(Obstacle_Xi, Obstacle_Yi);
	glEnd();
}

void RunnerDesign() //Runner is designed in three parts -> Head, Mid region and Legs
{
	printf("Runner: Yi = %d & Yf = %d	||	Obstacle: Xi = %d & Xf = %d\n", Runner_Yi, Runner_Yf, Obstacle_Xi, Obstacle_Xf);
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, _textureHead);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_POLYGON); //Head of runner
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex2i(Runner_Xi, Runner_Yf);
		glTexCoord2f(1.0, 1.0);
		glVertex2i(Runner_Xf, Runner_Yf);
		glTexCoord2f(1.0, 0.0);
		glVertex2i(Runner_Xf, Runner_Yf - 100);
		glTexCoord2f(0.0, 0.0);
		glVertex2i(Runner_Xi, Runner_Yf - 100);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, _textureBody);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS); //Middle region of runner
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex2i(Runner_Xi, Runner_Yf - 100);
		glTexCoord2f(1.0, 1.0);
		glVertex2i(Runner_Xf, Runner_Yf - 100);
		glTexCoord2f(1.0, 0.0);
		glVertex2i(Runner_Xf, Runner_Yi + 100);
		glTexCoord2f(0.0, 0.0);
		glVertex2i(Runner_Xi, Runner_Yi + 100);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, _textureLegs);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS); //Legs region of runner
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex2i(Runner_Xi, Runner_Yi + 100);
		glTexCoord2f(1.0, 1.0);
		glVertex2i(Runner_Xf, Runner_Yi + 100);
		glTexCoord2f(1.0, 0.0);
		glVertex2i(Runner_Xf, Runner_Yi);
		glTexCoord2f(0.0, 0.0);
		glVertex2i(Runner_Xi, Runner_Yi);
	glEnd();
}

//Function to help converting integer score to string
void eop(float x, float y, char *number)
{
	char *p;
	glRasterPos2f(x, y);
	for (p = number; *p != '\0'; p++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);

}

//Function to show score
void scoreText()
{
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(430, 980);
	int len, i, shift = 0, numlen = 0, score = scoreReal;

	len = (int)strlen(_stringScore);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, _stringScore[i]);
	}

	for (i = 0; i<10; i++)
	{
		num[i] = score % 10;
		score = score / 10;
		if (score == 0)
			break;
		numlen++;
	}
	for (i = numlen; i >= 0; i--)
	{
		shift += 10;
		if (num[i] == 1)
			eop(500 + shift, 980, "1");
		else if (num[i] == 2)
			eop(500 + shift, 980, "2");
		else if (num[i] == 3)
			eop(500 + shift, 980, "3");
		else if (num[i] == 4)
			eop(500 + shift, 980, "4");
		else if (num[i] == 5)
			eop(500 + shift, 980, "5");
		else if (num[i] == 6)
			eop(500 + shift, 980, "6");
		else if (num[i] == 7)
			eop(500 + shift, 980, "7");
		else if (num[i] == 8)
			eop(500 + shift, 980, "8");
		else if (num[i] == 9)
			eop(500 + shift, 980, "9");
		else if (num[i] == 0)
			eop(500 + shift, 980, "0");
	}
}

//Function to show game over
void gameOverText()
{
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2f(350, 980);
	int len, i, shift = 0, numlen = 0, score = scoreReal;

	len = (int)strlen(_stringGameOver);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, _stringGameOver[i]);
	}

	for (i = 0; i<10; i++)
	{
		num[i] = score % 10;
		score = score / 10;
		if (score == 0)
			break;
		numlen++;
	}
	for (i = numlen; i >= 0; i--)
	{
		shift += 10;
		if (num[i] == 1)
			eop(650 + shift, 980, "1");
		else if (num[i] == 2)
			eop(650 + shift, 980, "2");
		else if (num[i] == 3)
			eop(650 + shift, 980, "3");
		else if (num[i] == 4)
			eop(650 + shift, 980, "4");
		else if (num[i] == 5)
			eop(650 + shift, 980, "5");
		else if (num[i] == 6)
			eop(650 + shift, 980, "6");
		else if (num[i] == 7)
			eop(650 + shift, 980, "7");
		else if (num[i] == 8)
			eop(650 + shift, 980, "8");
		else if (num[i] == 9)
			eop(650 + shift, 980, "9");
		else if (num[i] == 0)
			eop(650 + shift, 980, "0");
	}
}

//Function to draw start screen
void startScreen()
{
	int linePosX = 250, linePosY = 700;

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);	
		glVertex2i(0, 0);	
		glVertex2i(1000, 0);	
		glVertex2i(1000, 1000);
		glVertex2i(0, 1000);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2f(linePosX, linePosY);
	int len, i;

	len = (int)strlen(_stringStart);
	for (i = 0; i < len; i++)
	{
		if (_stringStart[i] == '#')
		{
			linePosY -= 25;
			glRasterPos2f(linePosX, linePosY);
		}
		else
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, _stringStart[i]);
		}
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);

	WaitCallInMS = 1;

	//Proceed drawing the game elements
	if (gameStart != true)
	{
		Environment(); //Moves with obstacle
		ObstacleDesign(); //involing obstacle function to draw obstacle
		RunnerDesign(); //involing runner function to draw obstacle
	}
	//Render start screen and wait
	else 
	{
		startScreen();
	}
	
	//Render score system
	if (gameOver == false && gameStart != true)
	{
		scoreText();
	}
	else if (gameOver != false && gameStart != true)
	{
		gameOverText();
	}

	glutSwapBuffers();

	// Obstacle's and environment's Continuous Decremental Conditions along X axis.
	if (Paused != true && gameStart != true)
	{
		if (Obstacle_Xf >= 1)
		{
			Obstacle_Xi--;
			Obstacle_Xf--;
			Background_Xi--;
			Background_Xf--;
			Background2_Xi--;
			Background2_Xf--;
		}
		else
		{
			Obstacle_Xf = 1000;
			Obstacle_Xi = 920;
			Background_Xi = 0;
			Background_Xf = 1000;
			Background2_Xi = 1000;
			Background2_Xf = 2000;
		}
	}

	/* Runner's Increamental/ Decremental Conditions along Y axis while Keyboard button W is pressed*/
	if (RunnerMovementUpwardStatus == true)
	{
		if (Runner_Yi < (Obstacle_Yf + 130))
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
					Paused = true;
					keyFlag = true;	
					gameOver = true;
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
					Paused = true;
					keyFlag = true;
					gameOver = true;
				}
			}
		}
		else
		{
			printf("\nSUCCESSFULL JUMP\n\n"); //No flaws found!!
			RunnerMovementDownwardStatus = false;
			keyFlag = false;
			scoreReal+=10;
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

				Paused = true;
				keyFlag = true;		
				gameOver = true;
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
	if ((key == 'w' || key == 'W') && keyFlag == false)// Upward Movement of Runner
	{
		keyFlag = true;
		RunnerMovementUpwardStatus = true;
		RunnerMovementDownwardStatus = false;
		glutPostRedisplay();
	}
	else if (key == 's' || key == 'S') // Downward movement of runner OCCURED!
	{
		RunnerMovementDownwardStatus = true;
		RunnerMovementUpwardStatus = false;
		glutPostRedisplay();
	}
	else if (key == 'r' || key == 'R') // Resume game
	{		
		Paused = false;
		keyFlag = false;
		glutPostRedisplay();
	}

	else if (key == 'p' || key == 'P') // Pause game
	{
		Paused = true;
		keyFlag = true;
		glutPostRedisplay();
	}

	else if (key == 13) // Reset game
	{
		Paused = false;
		keyFlag = false;
		gameOver = false;
		gameStart = false;
		scoreReal = 0;

		Obstacle_Xf = XfOfObstacle;
		Obstacle_Xi = XiOfObstacle;
		Runner_Yi = YiOfRunner;
		Runner_Yf = YfOfRunner;
		Background_Xf = XfOfBackground;
		Background_Xi = XiOfBackground;
		Background2_Xf = XfOfBackground + 1000;
		Background2_Xi = XiOfBackground + 1000;

		glutPostRedisplay();
	}
	else if (key == 27) // Return to start screen
	{
		Paused = false;
		keyFlag = false;
		gameOver = false;
		gameStart = true;
		scoreReal = 0;

		Obstacle_Xf = XfOfObstacle;
		Obstacle_Xi = XiOfObstacle;
		Runner_Yi = YiOfRunner;
		Runner_Yf = YfOfRunner;
		Background_Xf = XfOfBackground;
		Background_Xi = XiOfBackground;
		Background2_Xf = XfOfBackground + 1000;
		Background2_Xi = XiOfBackground + 1000;

		glutPostRedisplay();
	}
}


void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Dauntless Runner");

	myinit();
	glutDisplayFunc(display);
	PlaySoundA("music.wav", NULL, SND_ASYNC);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, Timer, 0);
		
	glutMainLoop();		
}