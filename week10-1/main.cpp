#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <GL/glut.h>
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
#include "glm.h"
GLMmodel * pmodel = NULL;
GLMmodel * phand = NULL;
float angle=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if(pmodel==NULL)
    {
        pmodel=glmReadOBJ("hand_left.obj");  //模型檔名
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel,90);  //縮放成單位大小
    }
    if(phand==NULL)
    {
        phand=glmReadOBJ("body.obj");  //模型檔名
        glmUnitize(phand);
        glmFacetNormals(phand);
        glmVertexNormals(phand,90);  //縮放成單位大小
    }
    glPushMatrix();
    glRotatef(angle,0,1,0);
    glmDraw(pmodel,GLM_SMOOTH|GLM_MATERIAL|GLM_TEXTURE);
    glPopMatrix();
    angle++;
    //glutSolidTeapot(0.3);
    glutSwapBuffers();  //交換顯示
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  //設定顯示模式
    glutCreateWindow("week08");  //視窗名稱
    myTexture("Diffuse.jpg");
    glutDisplayFunc(display);  //顯示的函式
    glutIdleFunc(display);
    glutMainLoop();  //主要迴圈最後
}
