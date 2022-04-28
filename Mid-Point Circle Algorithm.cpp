#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

int n=0,arrX[100],arrY[100],Xc,Yc;

void init(){
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

static void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

void drawPixel(int x,int y){
    glColor3d(0,1,1);

    glBegin(GL_POINTS);
        glVertex2f(Xc+x,Yc+y);
    glEnd();

    glFlush();
}

int radius(int x1,int y1,int x2,int y2){
    return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}

void midpointCircle(){
    int index=n-2;

    int xc,yc,x1,y1;

    xc=arrX[index];
    yc=arrY[index];
    x1=arrX[index+1];
    y1=arrY[index+1];

    cout<<xc<<" "<<yc<<" "<<x1<<" "<<y1<<"\n";

    int r=radius(xc,yc,x1,y1);
    int x=0,y=r,pk;

    pk=1-r;

    Xc=xc;
    Yc=yc;

    drawPixel(x,y);

    while(x<=y){
        x++;

        if(pk<0){
            pk+=(2*x+1);
        }
        else{
            y--;
            pk+=(2*x - 2*y +1);
        }

        drawPixel(x,y);
        drawPixel(x,-y);
        drawPixel(-x,y);
        drawPixel(-x,-y);
        drawPixel(y,x);
        drawPixel(y,-x);
        drawPixel(-y,x);
        drawPixel(-y,-x);
    }

}

void mouseHandler(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        arrX[n]=x;
        arrY[n]=480-y;
        n++;
    }

    if(n>=2 && n%2==0){
        midpointCircle();
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseHandler);
    glutMainLoop();

    return EXIT_SUCCESS;
}
