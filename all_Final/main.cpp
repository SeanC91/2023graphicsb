#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
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
GLMmodel*plane=NULL;
int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
int show[10]={1,1,1,1,1,1,1,1,1,1};///week14_step03_1
int ID =0;///week14_step03_1
float teapotX = 0, teapotY = 0, oldX = 0, oldY = 0;
float angle[20] = {}, angle2[20] = {};///float angle = 0, angle2 = 0;
float NewAngle[20] = {}, NewAngle2[20] = {};
float OldAngle[20] = {}, OldAngle2[20] = {};
FILE * fout = NULL;
FILE * fin = NULL;
void timer(int t) {
    printf("nowtimer(%d)\n", t);
    glutTimerFunc(40, timer, t+1); ///馬上設定下一個鬧鐘

    float alpha = (t%50) / 50.0; ///0.0 ~ 1.0

    if(t%50==0){
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            OldAngle[i] = NewAngle[i];
            OldAngle2[i] = NewAngle2[i];
            fscanf(fin, "%f", &NewAngle[i] );
            fscanf(fin, "%f", &NewAngle2[i] );
        }
    }
    for(int i=0; i<20; i++){
        angle[i] = NewAngle[i] * alpha + OldAngle[i] * (1-alpha);
        angle2[i] = NewAngle2[i] * alpha + OldAngle2[i] * (1-alpha);
    }

    glutPostRedisplay();
}
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
    if(key=='s'){ ///save存檔 也會動到檔案
        if(fout == NULL) fout = fopen("motion.txt", "w");
        for(int i=0; i<20; i++){
            fprintf(fout, "%.2f ", angle[i] );
            fprintf(fout, "%.2f ", angle2[i] );
        }
        fprintf(fout, "\n");
        printf("writedown\n");
    }
    if(key=='r'){ ///read讀檔 也會動到檔案
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            fscanf(fin, "%f", &angle[i] );
            fscanf(fin, "%f", &angle2[i] );
        }
        glutPostRedisplay();
    }
    if(key=='p'){ ///play播放 也會動到檔案
        glutTimerFunc(0, timer, 0);
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(head==NULL){
        plane=glmReadOBJ("model/plane.obj");
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
        glColor3f(1,1,1);
        glmDraw(plane,GLM_MATERIAL|GLM_TEXTURE);
        ///myTexture("pic.jfif");
    glPushMatrix();
        glScalef(0.09,0.09,0.09);
        glTranslatef(0, -0.2, 0);
        glRotatef(angle[0], 0, 1, 0);
        glPushMatrix();
            ///glTranslatef(teapotX,teapotY,0);
            if(ID==0)glColor3f(240/255.0,135/255.0,132/255.0);
            else glColor3f(240/255.0,135/255.0,132/255.0);
            if(show[0]) glmDraw(head,GLM_MATERIAL);
    glPopMatrix();
        glColor3f(1,1,1);
        glmDraw(eye,GLM_MATERIAL);
        glColor3f(0,0,0);
        glmDraw(face,GLM_MATERIAL);
        glColor3f(1,0,0);
        glmDraw(fly,GLM_MATERIAL);
        if(ID==1)glColor3f(0/255.0,35/255.0,245/255.0);
        else glColor3f(0/255.0,35/255.0,245/255.0);
        if(show[1]) glmDraw(body,GLM_MATERIAL);
        glPushMatrix();
        glTranslatef(-1,+3.5,0);
        glRotatef(angle[2],0,0,1);
        glRotatef(angle2[2], 1, 0, 0);
        glTranslatef(1,-3.5,0);
        if(ID==2)glColor3f(0/255.0,35/255.0,245/255.0);
        else glColor3f(0/255.0,35/255.0,245/255.0);
        if(show[2]) glmDraw(uphandr,GLM_MATERIAL);
        glPushMatrix();
        glTranslatef(-2.1,+1.3,0);
        glRotatef(angle[3],0,0,1);
        glRotatef(angle2[3], 1, 0, 0);
        glTranslatef(2.1,-1.3,0);
        if(ID==3)glColor3f(240/255.0,135/255.0,132/255.0);
        else glColor3f(240/255.0,135/255.0,132/255.0);
        if(show[3]) glmDraw(downhandr,GLM_MATERIAL);
        glPopMatrix();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(1,+3.5,0);
        glRotatef(angle[4],0,0,1);
        glRotatef(angle2[4], 1, 0, 0);
        glTranslatef(-1,-3.5,0);
        if(ID==4)glColor3f(0/255.0,35/255.0,245/255.0);
        else glColor3f(0/255.0,35/255.0,245/255.0);
        if(show[4]) glmDraw(uphandl,GLM_MATERIAL);
        glPushMatrix();
        glTranslatef(2.1,+1.3,0);
        glRotatef(angle[5],0,0,1);
        glRotatef(angle2[5], 1, 0, 0);
        glTranslatef(-2.1,-1.3,0);
        if(ID==5)glColor3f(240/255.0,135/255.0,132/255.0);
        else glColor3f(240/255.0,135/255.0,132/255.0);
        if(show[5]) glmDraw(downhandl,GLM_MATERIAL);
        glPopMatrix();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-0.6,-0.4,0);
        glRotatef(angle[6],0,0,1);
        glRotatef(angle2[6], 1, 0, 0);
        glTranslatef(0.6,0.4,0);
        if(ID==6)glColor3f(0/255.0,35/255.0,245/255.0);
        else glColor3f(0/255.0,35/255.0,245/255.0);
        if(show[6]) glmDraw(upfootr,GLM_MATERIAL);
        glPushMatrix();
        glTranslatef(-0.8,-3.3,0);
        glRotatef(angle[7],0,0,1);
        glRotatef(angle2[7], 1, 0, 0);
        glTranslatef(0.8,3.3,0);
        if(ID==7)glColor3f(1,0,0);
        else glColor3f(1,0,0);
        if(show[7]) glmDraw(downfootr,GLM_MATERIAL);
        glPopMatrix();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.6,-0.4,0);
        glRotatef(angle[8],0,0,1);
        glRotatef(angle2[8], 1, 0, 0);
        glTranslatef(-0.6,0.4,0);
        if(ID==8)glColor3f(0/255.0,35/255.0,245/255.0);
        else glColor3f(0/255.0,35/255.0,245/255.0);
        if(show[8]) glmDraw(upfootl,GLM_MATERIAL);
        glPushMatrix();
        glTranslatef(0.8,-3.3,0);
        glRotatef(angle[9],0,0,1);
        glRotatef(angle2[9], 1, 0, 0);
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
void mouse(int button,int state,int x,int y)
{
    if(state==GLUT_DOWN){
        oldX=x;
        oldY=y;
    }
}
void motion(int x,int y){
    teapotX += (x - oldX) / 150.0 * 10; ///teapotX = (x-150)/150.0;
    teapotY += (oldY - y) / 150.0 * 10; ///teapotY = (150-y)/150.0;
    angle[ID] += x - oldX;
    angle2[ID] += oldY - y;
    oldX = x;
    oldY = y;
    glutPostRedisplay();
}
void reshape(int w,int h){
    float ar=w/(float)h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,ar,0.01,1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,1,   0,0,0,   0,1,0);
}
int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("Final_Project");
    glutInitWindowSize(500,500);
    myMP3.Load("arrow.mp3");
    myMP3.Play();
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
