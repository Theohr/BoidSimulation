#include "Main.h"

using namespace std;

float alpha = 45;
float beta = 90;
int viewMode = 1;
bool hide = false;
bool pause = false;
bool tf = false;
float zoom = 1.0;
int w = 1400, h = 800;
int i;
float goal = 1;

Vector view, center;
std::list<Obstacles> obs;
Flock* flock;

// Window resize function to stay always the same 
void resize(int width, int height) {
	if (h == 0) {
		h = 1; //prevent a divide by zero, when window is too short
	}
	glViewport(0, 0, width, height); // viewport is the entire window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, width / (GLdouble)height, 5.0, AREA);
	glMatrixMode(GL_MODELVIEW);
}

// Watch over the flock function
void watchFlock() {
	// gets the centroid of the flock
	center = flock->centroid();

	// gets the position of the leader
	Vector u = Difference((flock->getLeader())->getPosition(), center); 

	// sets the distance according to leader and gets the radius of the flock
	float dist = Distance((flock->getLeader())->getPosition(), center);
	float r = flock->radius() / 4;

	Vector norm = Normalize(u);
	// setting the view
	view.x = center.x - norm.x * (dist + 4 * r) * zoom;
	view.y = center.y - norm.y * (dist + 4 * r) * zoom;
	view.z = center.z + (dist + 0.5 * r) * zoom;
}

// init function
void init() {
	// Creating the scene
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0);
	glPointSize(1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CW);
	glDisable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_COLOR_MATERIAL);

	// loop to draw the obstacles 
	for (i = 0; i < OBSTACLES; i++) {
		Obstacles* obstacles;

		// if there are no obstacles then draw them
		if (i == 0) {
			obstacles = new Obstacles(NullVector(), 20);
		}
		else {
			obstacles = new Obstacles(NewVector(rand() % 1000 - 500, rand() % 1000 - 500, 10), 15 + rand() % 10);
		}
			
		obs.push_back(*obstacles);
	}

	//create a flock and watch it
	flock = new Flock();
	watchFlock();
}

// Display function calling the Camera function the drawObstacles function, drawBoids function 
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	adjustCamera();
	drawObstacles();
	flock->drawBoids();
	glPopMatrix();
	glutSwapBuffers();
}

// Adjusting the camera to view the specific flock whatever happens
void adjustCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(15.0, (w / h), 5.0, AREA);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	switch (viewMode) {
	case 1:
		gluLookAt(view.x, view.y, view.z + 0, center.x, center.y, center.z, 0.0, 0.0, 1.0);
		break;
	}
}

// Updates the animations of the scene based on a timer
void update(int value) {

	if (!pause || tf) {

		ItObs itr;

		if (beta > 91)
		{
			beta -= 0.1;
		}
		if (beta < 89) {
			beta += 0.1;
		}

		(flock->getLeader())->walls();

		(flock->getLeader())->setVelocity(goal * (w/h) * cos(PI * alpha / 180), 
			goal * (w / h) * sin(PI * alpha / 180), goal * (w / h) * cos(beta * PI / 180));

		flock->moveBoids();
	}

	watchFlock();

	if (!tf)
	{
		glutTimerFunc(TIMERMSECS, update, value);
	}
	else if (tf) {
		if (value > 0)
		{
			glutTimerFunc(TIMERMSECS, update, --value);
		}
	}

	glutPostRedisplay();
}

// User can interact with the executable on button clicks below
void userInteractions(unsigned char key, int x, int y) {

	Vector speed = (flock->getLeader())->getVelocity();

	switch (key) {
	case ESCAPE_KEY: exit(0); break;
	case 'p':
		pause = !pause;
		if (tf && !pause) {
			tf = false;
			glutTimerFunc(TIMERMSECS, update, 1);
		} break;
	case 'd':
		if (tf) glutTimerFunc(TIMERMSECS, update, 1);
		else tf = !tf; pause = true; break;
	case 'v': goal += 0.1; break;
	case 'b': if (goal > 0.2) goal -= 0.1; break;
	case 'h': hide = !hide; break;
	//case 'a': flock->addBoid(); break;
	case 'r': if (flock->getSize() > 3) flock->removeBoid(); break;
	case 'x': if (zoom > 0) zoom -= 0.05; break;
	case 'X': if (zoom > 0) zoom += 0.05; break;
	default:
		break;
	}

	glutPostRedisplay();
}

// Main function
int main(int argc, char** argv) {
	// Printing the instructions 
	cout << " ---User Instructions:---" << endl;
	cout << "__________________________\n" << endl;
	cout << " 1) Esc = Break Simulation." << endl;
	cout << " 2) p = Pause Screen." << endl;
	cout << " 3) b = Predator chases Boids in the scene." << endl;
	cout << " 4) h = Hide/Unhide Leader." << endl;
	//cout << " 5) a = Add Boid to the flock." << endl;
	cout << " 6) r = Remove Boid from the flock" << endl;
	cout << " 7) x = Zoom Out" << endl;
	cout << " 8) X = Zoom In" << endl;
	cout << " 9) b = FLock breaks and try to flee from predator" << endl;
	cout << " 10) v = Flock changes direction" << endl;

	// calling the rest of the functions to create the scene and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(w, h);
	glutCreateWindow("Boid Simulation by Theo");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(TIMERMSECS, update, 1);
	glutKeyboardFunc(userInteractions);
	init();
	glutMainLoop();
	return(0);
}
