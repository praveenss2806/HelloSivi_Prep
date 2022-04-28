#include <windows.h>
#include <bits/stdc++.h>
#include <GL/glut.h>
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

void polygonDraw(){
    glColor3d(0,1,1);

    glBegin(GL_LINE_LOOP);
        glVertex2f(arrX[0],arrY[0]);
        glVertex2f(arrX[0],arrY[1]);
        glVertex2f(arrX[1],arrY[1]);
        glVertex2f(arrX[1],arrY[0]);
    glEnd();

    glFlush();
}

void lineClipping(){
    float xmin=min(arrX[0],arrX[1]);
    float xmax=max(arrX[1],arrX[0]);
    float ymin=min(arrY[0],arrY[1]);
    float ymax=max(arrY[1],arrY[0]);

    float delx=arrX[3]-arrX[2];
    float dely=arrY[3]-arrY[2];
    float x1=arrX[2];
    float y1=arrY[2];

    float p1=-delx;
    float p2=delx;
    float p3=-dely;
    float p4=dely;

    float q1=x1-xmin;
    float q2=xmax-x1;
    float q3=y1-ymin;
    float q4=ymax-y1;

    float r1=q1/p1;
    float r2=q2/p2;
    float r3=q3/p3;
    float r4=q4/p4;

    float arr1[4]={p1,p2,p3,p4};
    float arr2[4]={r1,r2,r3,r4};

    float u1=0.0,u2=1.0;

    for(int i=0;i<4;i++){
        if(arr1[i]<0){
            u1=max(u1,arr2[i]);
        }
        else if(arr1[i]>0){
            u2=min(u2,arr2[i]);
        }
    }

    if(u1>u2){
        cout<<"Trival Reject\n";
        return;
    }
    else{
        float x1new=x1+(arrX[3]-arrX[2])*u1;
        float y1new=y1+(arrY[3]-arrY[2])*u1;
        float x2new=x1+(arrX[3]-arrX[2])*u2;
        float y2new=y1+(arrY[3]-arrY[2])*u2;

        glColor3d(1,0,0);
        glBegin(GL_LINES);
            glVertex2f(x1new,y1new);
            glVertex2f(x2new,y2new);
        glEnd();
        glFlush();
    }
}

void lineDraw(){
    glColor3d(0,1,1);

    glBegin(GL_LINES);
        glVertex2f(arrX[2],arrY[2]);
        glVertex2f(arrX[3],arrY[3]);
    glEnd();

    glFlush();

    lineClipping();
}

void mouseHandler(int button,int state,int x,int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        cout<<x<<" "<<y<<"\n";
        arrX[n]=x;
        arrY[n]=480-y;
        n++;
    }
    if(n==2){
        polygonDraw();
    }
    else if(n==4){
        lineDraw();
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
