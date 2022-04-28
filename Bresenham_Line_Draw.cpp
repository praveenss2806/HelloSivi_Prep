#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

int n=0,arrX[100],arrY[100];

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

int sign(int x){
    if(x<0){
        return -1;
    }
    if(x>0){
        return 1;
    }
    return 0;
}

void drawPixel(int x,int y){
    glColor3d(0,1,1);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    glFlush();
}

void bresenham(){
    int index=n-2,flag=0,pk;
    int x1,y1,x2,y2;

    x1=arrX[index];
    y1=arrY[index];
    x2=arrX[index+1];
    y2=arrY[index+1];

    int delx=abs(x2-x1);
    int dely=abs(y2-y1);

    int s1=sign(x2-x1);
    int s2=sign(y2-y1);

    if(dely>delx){
        swap(dely,delx);
        flag=1;
    }

    pk=2*delx-dely;

    for(int i=0;i<delx;i++){
        drawPixel(x1,y1);

        while(pk>0){
            if(flag==1){
                x1=x1+s1;
            }
            else{
                y1=y1+s2;
            }
            pk=pk-2*delx;
        }

        if(flag==1){
            y1=y1+s2;
        }
        else{
            x1=x1+s1;
        }
        pk=pk+2*dely;
    }

    return ;
}

void mouseHandler(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        //cout<<x<<" "<<y<<"\n";
        arrX[n]=x;
        arrY[n]=480-y;
        n++;
    }
    if(n>=2 && n%2==0){
        bresenham();
    }
}

int main(int argc, char *argv[]){
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
