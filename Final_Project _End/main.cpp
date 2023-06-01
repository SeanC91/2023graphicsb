#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"
#include "CMP3_MCI.h"
CMP3_MCI myMP3;
GLMmodel*head=NULL;
GLMmodel*body=NULL;
GLMmodel*uphandr=NULL;
GLMmodel*downhandr=NULL;
GLMmodel*uphandl=NULL;
GLMmodel*downhandl=NULL;
GLMmodel*upfootr=NULL;
GLMmodel*downfootr=NULL;
GLMmodel*upfootl=NULL;
GLMmodel*downfootl=NULL;
GLMmodel*circle=NULL;
GLMmodel*circle1=NULL;
GLMmodel*face=NULL;
GLMmodel*eye=NULL;
GLMmodel*under=NULL;
GLMmodel*mark=NULL;
GLMmodel*mark1=NULL;
GLMmodel*fly=NULL;
int show[10]={1,1,1,1,1,1,1,1,1,1};///week14_step03_1
int ID =8;///week14_step03_1
float teapotX=0,teapotY=0;
float angle[20]={};
FILE*fout=NULL;
FILE*fin=NULL;
void keyboard(unsigned char key,int x,int y)
{
    if(key=='0') ID=0;///show[0]=!show[0];
    if(key=='1') ID=1;///show[1]=!show[1];
    if(key=='2') ID=2;///show[2]=!show[2];
    if(key=='3') ID=3;///show[3]=!show[3];
    if(key=='4') ID=4;
    if(key=='5') ID=5;
    if(key=='6') ID=6;
    if(key=='7') ID=7;
    if(key=='8') ID=8;
    if(key=='9') ID=9;
    glutPostRedisplay();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(head==NULL){
        fly=glmReadOBJ("model/fly.obj");
        circle1=glmReadOBJ("model/circle1.obj");
        mark=glmReadOBJ("model/mark.obj");
        mark1=glmReadOBJ("model/mark1.obj");
        under=glmReadOBJ("model/under.obj");
        eye=glmReadOBJ("model/eye.obj");
        face=glmReadOBJ("model/face1.obj");
        circle=glmReadOBJ("model/circle.obj");
        head=glmReadOBJ("model/face.obj");
        body=glmReadOBJ("model/body.obj");
        uphandr=glmReadOBJ("model/uphand.obj");
        downhandr=glmReadOBJ("model/downhand.obj");
        uphandl=glmReadOBJ("model/uphand1.obj");
        downhandl=glmReadOBJ("model/downhand1.obj");
        upfootr=glmReadOBJ("model/upfoot.obj");
        downfootr=glmReadOBJ("model/downfoot.obj");
        upfootl=glmReadOBJ("model/upfoot1.obj");
        downfootl=glmReadOBJ("model/downfoot1.obj");
        }
    glPushMatrix();
        glScalef(0.2,0.2,0.2);
        glTranslatef(0, -0.5, 0);///©¹¤U¤@¥b
        glPushMatrix();
            ///glTranslatef(teapotX,teapotY,0);
            if(ID==0)glColor3f(1,0,0);
            else glColor3f(240/255.0,135/255.0,132/255.0);
            if(show[0]) glmDraw(head,GLM_MATERIAL);
    glPopMatrix();
        glColor3f(1,1,1);
        glmDraw(eye,GLM_MATERIAL);
        glColor3f(0,0,0);
        glmDraw(face,GLM_MATERIAL);
        glColor3f(1,0,0);
        glmDraw(fly,GLM_MATERIAL);
        if(ID==1)glColor3f(1,0,0);
        else glColor3f(0/255.0,35/255.0,245/255.0);
        if(show[1]) glmDraw(body,GLM_MATERIAL);
        glPushMatrix();
        glTranslatef(-1,+3.5,0);
        glRotatef(angle[2],0,0,1);
        glTranslatef(1,-3.5,0);
        if(ID==2)glColor3f(1,0,0);
        else glColor3f(0/255.0,35/255.0,245/255.0);
        if(show[2]) glmDraw(uphandr,GLM_MATERIAL);
        glPushMatrix();
        glTranslatef(-2.1,+1.3,0);
        glRotatef(angle[3],0,0,1);
        glTranslatef(2.1,-1.3,0);
        if(ID==3)glColor3f(1,0,0);
        else glColor3f(240/255.0,135/255.0,132/255.0);
        if(show[3]) glmDraw(downhandr,GLM_MATERIAL);
        glPopMatrix();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(1,+3.5,0);
        glRotatef(angle[4],0,0,1);
        glTranslatef(-1,-3.5,0);
        if(ID==4)glColor3f(1,0,0);
        else glColor3f(0/255.0,35/255.0,245/255.0);
        if(show[4]) glmDraw(uphandl,GLM_MATERIAL);
        glPushMatrix();
        glTranslatef(2.1,+1.3,0);
        glRotatef(angle[5],0,0,1);
        glTranslatef(-2.1,-1.3,0);
        if(ID==5)glColor3f(1,0,0);
        else glColor3f(240/255.0,135/255.0,132/255.0);
        if(show[5]) glmDraw(downhandl,GLM_MATERIAL);
        glPopMatrix();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-0.6,-0.4,0);
        glRotatef(angle[6],0,0,1);
        glTranslatef(0.6,0.4,0);
        if(ID==6)glColor3f(1,0,0);
        else glColor3f(0/255.0,35/255.0,245/255.0);
        if(show[6]) glmDraw(upfootr,GLM_MATERIAL);
        glPushMatrix();
        glTranslatef(-0.8,-3.3,0);
        glRotatef(angle[7],0,0,1);
        glTranslatef(0.8,3.3,0);
        if(ID==7)glColor3f(1,0,0);
        else glColor3f(1,0,0);
        if(show[7]) glmDraw(downfootr,GLM_MATERIAL);
        glPopMatrix();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.6,-0.4,0);
        glRotatef(angle[8],0,0,1);
        glTranslatef(-0.6,0.4,0);
        if(ID==8)glColor3f(1,0,0);
        else glColor3f(0/255.0,35/255.0,245/255.0);
        if(show[8]) glmDraw(upfootl,GLM_MATERIAL);
        glPushMatrix();
        glTranslatef(0.8,-3.3,0);
        glRotatef(angle[9],0,0,1);
        glTranslatef(-0.8,3.3,0);
        if(ID==9)glColor3f(1,0,0);
        else glColor3f(1,0,0);
        if(show[9]) glmDraw(downfootl,GLM_MATERIAL);
        glPopMatrix();
        glPopMatrix();
        glColor3f(1,0,0);
        glmDraw(under,GLM_MATERIAL);
        glColor3f(255/255.0,253/255.0,85/255.0);
        glmDraw(circle,GLM_MATERIAL);
        glColor3f(240/255.0,155/255.0,89/255.0);
        glmDraw(circle1,GLM_MATERIAL);
        glColor3f(255/255.0,253/255.0,85/255.0);
        glmDraw(mark1,GLM_MATERIAL);
        glColor3f(1,0,0);
        glmDraw(mark,GLM_MATERIAL);
        glPopMatrix();
        ///glColor3f(0,1,0);
        ///glutSolidTeapot(0.02);

    glutSwapBuffers();
}
int oldX=0,oldY=0;
void mouse(int button,int state,int x,int y)
{
    if(state==GLUT_DOWN){
        oldX=x;
        oldY=y;
    }
}
void motion(int x,int y){
    teapotX+=(x-oldX)/150.0*3;
    teapotY-=(y-oldY)/150.0*3;
    printf("glTranslatef(%f,%f,0);\n",teapotX,teapotY);
    angle[ID]+=x-oldX;
    oldX=x;
    oldY=y;
    glutPostRedisplay();
}
int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("Final_Project");
    myMP3.Load("arrow.mp3");
    myMP3.Play();
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
}
