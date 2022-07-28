#include<stdio.h>
#include<GL/glut.h>
#include<stdbool.h>
int xvmin=200, yvmin=200, xvmax=300, yvmax=300;
float x1, x2, y1, y2, xmin, ymin, xmax, ymax;
int TOP=8, BOTTOM=4, LEFT=1, RIGHT=2;
int cRC(int x, int y) {
    int code=0;
    if (x>xmax)
        code|=RIGHT;
    else if (x<xmin) 
        code|=LEFT;
    if (y>ymax) 
        code|=TOP;
    else if (y<ymin)
        code|=BOTTOM;
    return code;
}
void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}
void cslad() {
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xvmin, yvmin);
    glVertex2i(xvmin, yvmax);
    glVertex2i(xvmax, yvmax);
    glVertex2i(xvmax, yvmin);
    glEnd();
    bool accept=false;
    int code1 = cRC(x1, y1);
    int code2 = cRC(x2, y2);
    int m = (y2-y1)/(x2-x1);
    while (1) {
        if (!(code1|code2)) {
            accept=true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            double x, y;
            int outCode = code1?code1:code2;
            if (outCode & TOP) {
                y=ymax;
                x=x1+(y-y1)/m;
            } else if (outCode & BOTTOM) {
                y=ymin;
                x=x1+(y-y1)/m;
            } else if (outCode & LEFT) {
                x=xmin;
                y=y1+m*(x-x1);
            } else if (outCode & RIGHT) {
                x=xmax;
                y=y1+m*(x-x1);
            }
            if (outCode == code1) {
                y1 = y;
                x1 = x;
                code1 = cRC(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = cRC(x2, y2);
            }
        }
    }
    if (accept) {
        int Sx = (xvmax-xvmin)/(xmax-xmin);
        int Sy = (yvmax-yvmin)/(ymax-ymin);
        int vx1 = xvmin+(x1-xmin)*Sx;
        int vy1 = yvmin+(y1-ymin)*Sy;
        int vx2 = xvmin+(x2-xmin)*Sx;
        int vy2 = yvmin+(y2-ymin)*Sy;
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2i(vx1, vy1);
        glVertex2i(vx2, vy2);
        glEnd();
    }
}
void display() {
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
    cslad();
    glFlush();
}
int main(int argc, char* argv[]) {
    printf("\nEnter the end points of the clipping window: ");
	scanf("%f%f%f%f", &xmin, &ymin, &xmax , &ymax);
	printf("Enter the end points: ");
	scanf("%f%f%f%f", &x1, &y1, &x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Lab 5");
	myInit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}