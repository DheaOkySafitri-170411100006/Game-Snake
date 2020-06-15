#include <iostream>
using namespace std;
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<string.h>
#include <math.h>
#include <stdlib.h>
#include<sstream>



int line = 19, cols = 19, vertical = 0.0, horizontal = 0.0;

float posx = 0.0, posy = 0.0, posz = 0.0;

int sudut=0, xx=0, yy=0, zz=0;// membuat variable untuk merotasi tampilan game maze

float gx = 0.0;
float gy = 0.0;

float gx1 = 0.0;
float gy1 = 0.0;

float kx = line/2+0.5;// memuat variable untuk menggeser posisi objeck sesuai koordinat x
float ky = 0.5;// memuat variable untuk menggeser posisi objeck sesuai koordinat x

float kam = 50;// 45

boolean view = false;
float kejauhan = 0.0;

int index = line-1;// membuat variable untuk pengindexan baris pada matrix

// membuat variable untuk pengaturan kamera
float ty = int(ky)-1.0;// translasi hadapan kamera di sumbu y (posisi kamera ada di belakang pemain)
float ty1 = int(ky)+1.0;// translasi hadapan kamera di sumbu y (posisi kamera ada di depan pemain)

float tx = int(kx)-10.0;// translasi hadapan kamera di sumbu x (posisi kamera ada di kiri pemain)
float tx1 = int(kx)+10.0;// translasi hadapan kamera di sumbu x (posisi kamera ada di kanan pemain)

// viewing
// membuat variable untuk mentranslasi kamera
float tranx = -(line/2)-0.5;
float trany = 0.0;
float tranz = 1.0;
float tranx1 = 0.0;
float trany1 = 0.0;
float tranz1 = 3.0;

// kiri
float tranx2 = 0.5;
float trany2 = 0.2;
float tranz2 = 10.0;

// kanan
float tranx3 = -0.5;
float trany3 = 0.2;
float tranz3 = 9;

int modex = 0;
int modey = 0;
int modez = 1;

float tempx, tempy, tempz, tempx1, tempy1, tempz1, tempx2, tempy2, tempz2, tempx3, tempy3, tempz3, tempx4, tempy4, tempz4;

boolean depan = true, belakang = false, kanan = false, kiri = false;

GLUquadricObj*quadObj;

float posisi[6][3] = {
    {line/2+0.5, cols/2+0.5, 0},
    {line/2+0.5, cols/2+0.5-1, 0},
    {line/2+0.5, cols/2+0.5-2, 0},
    {line/2+0.5, cols/2+0.5-3, 0},
    {line/2+0.5, cols/2+0.5-4, 0},
};
int px = rand()%18;
int py = rand()%18;

float derajat = 0.0;
float X = 0.0;
float Y = 0.0;
float Z = 0.0;


float matrix[100][100];

void metrial(float xx, float yy, float zz, float xx1, float yy1, float zz1)// fungsi untuk membuat material
{
    GLfloat mat_specular[] = { xx1, yy1, zz1, 1.0 };// membuat material cahaya specular
    GLfloat mat_shininess[] = { 10.0 };// membuat material cahaya shininess
    GLfloat mat_diffuse[] = { xx, yy, zz, 1.0 };// membuat material cahaya diffuse

    GLfloat diffuse_light[] = { xx, yy, zz, 1.0 };
    GLfloat specular_light[] = { xx, yy, zz, 1.0 };
    GLfloat ambient_light[] = { xx, yy, zz, 1.0 };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);


    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);// memilih material specular
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// memilih material shininess
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);// memilih material diffuse
}


void kepala(){
    quadObj = gluNewQuadric();
    glPushMatrix();
    metrial(0, 1.0, 0, 0, 1.0, 0.0);
    glutSolidSphere(0.55,15,10);
    glPopMatrix();

    // tanduk kiri
    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glRotatef(15, 0, 0, 1);
    glRotatef(-15, 1, 0, 0);
    gluCylinder(quadObj, 0.05, 0.05, 1.5, 30, 30);
    glPopMatrix();

    // tanduk kiri
    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glRotatef(-15, 0, 0, 1);
    glRotatef(-15, 1, 0, 0);
    gluCylinder(quadObj, 0.05, 0.05, 1.5, 30, 30);
    glPopMatrix();

    // mata kanan
    glPushMatrix();
    metrial(0, 0, 0, 0, 0, 0);
    glTranslatef(0.2, 0.45, 0.25);
    glutSolidSphere(0.1, 50, 50);
    glPopMatrix();

    // mata kiri
    glPushMatrix();
    metrial(0, 0, 0, 0, 0, 0);
    glTranslatef(-0.2, 0.45, 0.25);
    glutSolidSphere(0.1, 50, 50);
    glPopMatrix();

    // ujung tanduk kanan
    glPushMatrix();
    metrial(0, 1.0, 0, 0, 1.0, 0.0);
    glTranslatef(0.2, 0.37, 1.48);
    glutSolidSphere(0.12, 50, 50);
    glPopMatrix();

    // ujung tanduk kiri
    glPushMatrix();
    metrial(0, 1.0, 0, 0, 1.0, 0.0);
    glTranslatef(-0.2, 0.37, 1.48);
    glutSolidSphere(0.12, 50, 50);
    glPopMatrix();

}

void badan()
{
    glPushMatrix();
    metrial(0.0, 0.8, 0.0, 0.0, 0.8, 0.0);
    glutSolidSphere(0.55,15,10);
    glPopMatrix();
}

void snake(){

    glPushMatrix();
    glTranslatef(posisi[0][0], posisi[0][1], posisi[0][2]);
    glRotatef(derajat, X, Y, Z);
    kepala();
    glPopMatrix();

     // 1
    glPushMatrix();
    glTranslatef(posisi[1][0], posisi[1][1], posisi[1][2]);
    badan();
    glPopMatrix();

     // 2
    glPushMatrix();
    glTranslatef(posisi[2][0], posisi[2][1], posisi[2][2]);
    badan();
    glPopMatrix();

     // 3
    glPushMatrix();
    glTranslatef(posisi[3][0], posisi[3][1], posisi[3][2]);
    badan();
    glPopMatrix();

     // 4
    glPushMatrix();
    glTranslatef(posisi[4][0], posisi[4][1], posisi[4][2]);
    badan();
    glPopMatrix();
}

void umpan(){
    glPushMatrix();
    metrial(1, 1, 0, 1, 1, 0);
    glTranslatef(px+0.5, py+0.5, 0);
    glutSolidSphere(0.55,15,10);
    glPopMatrix();
}



void batangPohon(){
    glPushMatrix();
     metrial(0.7,0.3,0, 0.7,0.3,0);
    gluCylinder(quadObj, 0.2, 0.2, 1.5, 30, 30);
    glPopMatrix();
}

void pohon(){
    glTranslatef(0,0,0.6);
    glPushMatrix();
    metrial(0, 1, 0, 0, 1, 0);
    glutSolidCone(0.6,1.5,20,20);
    glTranslatef(0, 0, -0.5);
    glutSolidCone(0.6,1.5,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -1.5);
    batangPohon();
    glPopMatrix();
}

void area(){
    int h = 0;
    int a = 0;
    int n= 1;
    for(int i = line; i >= 0; i--){
        for(int u = 0; u < cols; u++){
            if(matrix[i][u] == 1){
                glPushMatrix();
                metrial(1, 0, 0, 1, 0, 0);
                glTranslatef(u+0.5, a-0.5, 0.4);
                pohon();
                glPopMatrix();
            }
            if(matrix[i][u] == 0 || matrix[i][u] == 1){
                glPushMatrix();
                if(h == 0){
                    metrial(0, 1, 0, 0, 1, 0);
                }
                else if(h == 1){
                    metrial(0, 0.7, 1, 0, 0.7, 1);
                }
                glTranslatef(u+0.5, n-0.5, -0.5);
                glScalef(1, 1, 0.1);
                glutSolidCube(1);
                glPopMatrix();
            }
            if(h == 0){
                h = 1;
            }
            else if(h == 1){
                h = 0;
            }
        }
        a += 1;
        if(n<=18){
            n+=1;
        }
    }
}

void pagar(){
    // membuat matrix
    for(int i = 0; i < line; i++){
        for(int u = 0; u < cols; u++){
            if(i == 0 || i == line-1 || u == 0 || u == cols-1){
                matrix[i][u] = 1;
            }
            else{
                matrix[i][u] = 0;
            }
        }
    }

}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    quadObj = gluNewQuadric();
    glLoadIdentity();
    glTranslatef(-9.5, -9.5, 0);
    gluLookAt(0,0,kam, 0,0,0, 0,1,0);

    //Area Permainan
    glPushMatrix();
    glTranslatef(gx1, gy1, 0);
    glRotatef(sudut, xx, yy, zz);
    glTranslatef(gx, gy, 0);
    area();
    pagar();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(gx1, gy1, 0);
    glRotatef(sudut, xx, yy, zz);
    glTranslatef(gx, gy, 0);
    snake();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(gx1, gy1, 0);
    glRotatef(sudut, xx, yy, zz);
    glTranslatef(gx, gy, 0);
    umpan();
    glPopMatrix();

    glFlush();
}

void input(unsigned char key, int x, int y)
{
    int indline = int(ky)+index;
        if(key == 'a'){
            //if(){
                sudut -= 15;
                xx = 0;
                yy = 1;
                zz = 0;
        }
        else if(key == 'd'){
            sudut += 15;
            xx = 0;
            yy = 1;
            zz = 0;
        }
        else if(key == 'w'){
            sudut -= 15;
            xx = 1;
            yy = 0;
            zz = 0;
        }
        else if(key == 's'){
            sudut += 15;
            xx = 1;
            yy = 0;
            zz = 0;
        }
        else if(key == 'q'){
            sudut += 15;
            xx = 0;
            yy = 0;
            zz = 1;
        }
        else if(key == 'e'){
            sudut -= 15;
            xx = 0;
            yy = 0;
            zz = 1;
        }
        gx = -(line/2)-0.5;
        gy = -(cols/2)-0.5;
        gx1 = (line/2)+0.5;
        gy1 = (cols/2)+0.5;


    if(key == 'i' || key=='I'){
        tempx = posisi[0][0];
        tempy = posisi[0][1];
        tempz = posisi[0][2];
        tempx1 = posisi[1][0];
        tempy1 = posisi[1][1];
        tempz1 = posisi[1][2];
        tempx2 = posisi[2][0];
        tempy2 = posisi[2][1];
        tempz2 = posisi[2][2];
        tempx3 = posisi[3][0];
        tempy3 = posisi[3][1];
        tempz3 = posisi[3][2];
        if(matrix[int(tempx)][int(tempy)+1] != 1){
            // kepala
            posisi[0][1] += 1;
            // badan 1
            //lingkar badan 1
            posisi[1][0] = tempx;
            posisi[1][1] = tempy;
            posisi[1][2] = tempz;
            //lingkar badan 2
            posisi[2][0] = tempx1;
            posisi[2][1] = tempy1;
            posisi[2][2] = tempz1;
            //linfkar badan 3
            posisi[3][0] = tempx2;
            posisi[3][1] = tempy2;
            posisi[3][2] = tempz2;
            //lingkar badan 4
            posisi[4][0] = tempx3;
            posisi[4][1] = tempy3;
            posisi[4][2] = tempz3;

            derajat = 0;
            X = 0;
            Y = 0;
            Z = 0;
        }
    }
    else if(key == 'k'){
        tempx = posisi[0][0];
        tempy = posisi[0][1];
        tempz = posisi[0][2];
        tempx1 = posisi[1][0];
        tempy1 = posisi[1][1];
        tempz1 = posisi[1][2];
        tempx2 = posisi[2][0];
        tempy2 = posisi[2][1];
        tempz2 = posisi[2][2];
        tempx3 = posisi[3][0];
        tempy3 = posisi[3][1];
        tempz3 = posisi[3][2];
        if(matrix[int(tempx)][int(tempy)-1] != 1){
            // kepala
            posisi[0][1] -= 1;
            // badan
            posisi[1][0] = tempx;
            posisi[1][1] = tempy;
            posisi[1][2] = tempz;
            posisi[2][0] = tempx1;
            posisi[2][1] = tempy1;
            posisi[2][2] = tempz1;
            posisi[3][0] = tempx2;
            posisi[3][1] = tempy2;
            posisi[3][2] = tempz2;
            posisi[4][0] = tempx3;
            posisi[4][1] = tempy3;
            posisi[4][2] = tempz3;

            derajat = 180;
            X = 0;
            Y = 0;
            Z = 1;
        }
    }
    else if(key == 'l' || key == 'L'){
        tempx = posisi[0][0];
        tempy = posisi[0][1];
        tempz = posisi[0][2];
        tempx1 = posisi[1][0];
        tempy1 = posisi[1][1];
        tempz1 = posisi[1][2];
        tempx2 = posisi[2][0];
        tempy2 = posisi[2][1];
        tempz2 = posisi[2][2];
        tempx3 = posisi[3][0];
        tempy3 = posisi[3][1];
        tempz3 = posisi[3][2];
        if(matrix[int(tempx)+1][int(tempy)] != 1){
            // kondisi kepala
            posisi[0][0] += 1;
            // kondisi badan
            posisi[1][0] = tempx;
            posisi[1][1] = tempy;
            posisi[1][2] = tempz;
            posisi[2][0] = tempx1;
            posisi[2][1] = tempy1;
            posisi[2][2] = tempz1;
            posisi[3][0] = tempx2;
            posisi[3][1] = tempy2;
            posisi[3][2] = tempz2;
            posisi[4][0] = tempx3;
            posisi[4][1] = tempy3;
            posisi[4][2] = tempz3;
            // rotasi kepeala ular
            derajat = -90;
            X = 0;
            Y = 0;
            Z = 1;
        }
    }
    else if(key == 'j' || key == 'J'){
        tempx = posisi[0][0];
        tempy = posisi[0][1];
        tempz = posisi[0][2];
        tempx1 = posisi[1][0];
        tempy1 = posisi[1][1];
        tempz1 = posisi[1][2];
        tempx2 = posisi[2][0];
        tempy2 = posisi[2][1];
        tempz2 = posisi[2][2];
        tempx3 = posisi[3][0];
        tempy3 = posisi[3][1];
        tempz3 = posisi[3][2];
        if(matrix[int(tempx)-1][int(tempy)] != 1){
            // kepala
            posisi[0][0] -= 1;
            // badan 1
            posisi[1][0] = tempx;
            posisi[1][1] = tempy;
            posisi[1][2] = tempz;
            posisi[2][0] = tempx1;
            posisi[2][1] = tempy1;
            posisi[2][2] = tempz1;
            posisi[3][0] = tempx2;
            posisi[3][1] = tempy2;
            posisi[3][2] = tempz2;
            posisi[4][0] = tempx3;
            posisi[4][1] = tempy3;
            posisi[4][2] = tempz3;
            // rotasi kepala ular
            derajat = 90;
            X = 0;
            Y = 0;
            Z = 1;
        }
    }
    if((int(posisi[0][0])) == px && int(posisi[0][1]) == py){
        while(px <= 0 || px >= 18 || py <= 0 || py >= 18 || (int(posisi[0][0])) == px && int(posisi[0][1]) == py){

            px = rand()%18;
            py = rand()%18;
        }
    }
    display();

}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25.0, (GLfloat) w/(GLfloat) h, 1, 500);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
    glLoadIdentity();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPointSize(50.0);
    glOrtho(vertical, line, horizontal, cols, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0,1.0,1.0,1.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glutPostRedisplay();

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(730, 730);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("170411100006  DHEA OKY SAFITRI");
    glutReshapeFunc(reshape);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(input);
    glutMainLoop();
}

