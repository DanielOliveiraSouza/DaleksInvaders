#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
#include "Model_OBJ.h"

#define MAX 360.00
//http://bit.ly/29jm7vl

using namespace std;

void camera();
void luz();
void MoveTARDIS();


float T = 0;
float T2 = 0;
float T3 = 1;
float rx = 0;
int a,s,d,f,g,h;
float viewangle= 0 , tippangle=0, luz_x=10.0, luz_z=10.0, luz_y= 10.0;


Model_OBJ nave;
struct nave{
	Model_OBJ obj;
	int rx;
};

typedef struct nave tipo_nave;
void camera(){
  gluLookAt(0.0,35.00,35.00,
      0.0, 0.0, 0.0,
      0.0, 1.0, 0.0);
}

void luz(){
  GLfloat desligado[] = { 0.0, 0.0, 0.0, 1.0};
  GLfloat amb_light[] = { 0.3, 0.3, 0.3, 1.0 };
  GLfloat diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
  GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = {luz_x, luz_y, luz_z, 1.0};
  glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );

  if(a==1)
    glLightfv( GL_LIGHT0, GL_AMBIENT, amb_light );
  else
    glLightfv( GL_LIGHT0, GL_AMBIENT, desligado );

  if(s==1)
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
  else
    glLightfv( GL_LIGHT0, GL_DIFFUSE, desligado );

  if(d==1)
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
  else
    glLightfv( GL_LIGHT0, GL_SPECULAR, desligado );

  if(f==1)
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01);
  else
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

  glLightfv( GL_LIGHT0, GL_POSITION, light_position);
   
}
void MoveTARDIS(){

  //#referencia da tabela de cores https://www.opengl.org/discussion_boards/showthread.php/132502-Color-tables
	//0.137255 green 0.137255 blue 0.556863
  //0.0225,0.0225,0.0225
   //0.184314 , 0.184314 ,0.309804
   //0.35 ,0.35 , 0.67
	GLfloat tardis_amb[4]={0.0,0.0,0.0,1.0};
	GLfloat tardis_dif[4]={0.15 ,0.15 , 0.79,1.0};
	GLfloat tardis_esp[4]={0.0225,0.0225,0.0225,1.0};
	GLfloat tardis_shi=0.1*128.00;
  glMaterialfv(GL_FRONT,GL_AMBIENT,tardis_amb);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,tardis_dif);
  glMaterialfv(GL_FRONT,GL_SPECULAR,tardis_esp);
  glMaterialf(GL_FRONT,GL_SHININESS, tardis_shi);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	//glRotatef(T,0.0,0.0,1.0);
	glTranslatef(T, 0, 0.0);

	//glPopMatrix();

	glPushMatrix();
	glRotatef(rx,0.0,1.0,0.0);
	//glPopMatrix();
	//glPushMatrix();

	// 	  glTranslatef(T, 0.0, T2);
	//         glRotatef(T3, 0.0, 1.0, 0.0);

	// glScalef(T, T2, T3);




	//Desenha corpo do carro
	nave.Draw();

	if ( rx < MAX )
		rx= rx + 10.00;
	else rx = 0.0;
	glPopMatrix();
	glPopMatrix();
	//glPopMatrix();
	
}

void display(void)
{ 
  //
  luz();
/*
	GLfloat tardis_amb[4]={}
	GLfloat tardis_dif[4]={}
	GLfloat tardis_esp[4]={}
	GLfloat tardis_shi=0.1*128.00;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	//glRotatef(T,0.0,0.0,1.0);
	glTranslatef(T, 0, 0.0);

	//glPopMatrix();

	glPushMatrix();
	glRotatef(rx,0.0,1.0,0.0);
	//glPopMatrix();
	//glPushMatrix();

	// 	  glTranslatef(T, 0.0, T2);
	//         glRotatef(T3, 0.0, 1.0, 0.0);

	// glScalef(T, T2, T3);
	
	


	//Desenha corpo do carro
	nave.Draw();

	if ( rx < MAX )
		rx= rx + 1.5;
	else rx = 0.0;
	glPopMatrix();
	glPopMatrix();
	//glPopMatrix();*/
  MoveTARDIS();
	glutSwapBuffers();
}
void Keys (int key, int x, int y)

{
    switch (key) {
 
       case GLUT_KEY_LEFT :  T -= 0.5; break;
       case GLUT_KEY_RIGHT:  T += 0.5; break;
       case GLUT_KEY_UP   :  T2 -= 0.5;  break;
       case GLUT_KEY_DOWN :  T2 += 5;  break;
       case GLUT_KEY_PAGE_UP   :  T3 -= 0.5;  break;
       case GLUT_KEY_PAGE_DOWN :  T3 += 0.5;  break;
    }
}

void resize(int w, int h){
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLdouble) w/h,
		  1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 10.0, 10.0,
	    0.0, 0.0, 0.0,
	    0.0, 1.0, 0.0);


}


void animacao(int value){
  glutPostRedisplay();
  glutTimerFunc(30, animacao,1);
  
  
}

void init (void) 
{
  glClearColor (0.3, 0.3, 0.3, 0.0);
   glEnable( GL_DEPTH_TEST );
   glDepthFunc(GL_LESS);
   glEnable(GL_LIGHTING);   //Liga iluminação
   glEnable( GL_LIGHT0 );   //Liga luz 0
   //glEnable( GL_COLOR_MATERIAL ); //Transforma cor em material
   glShadeModel( GL_SMOOTH );   //Suaviza normais
   glEnable(GL_NORMALIZE);
   // glClearColor (0.3, 0.3, 0.3, 0.0);
   // glShadeModel( GL_SMOOTH );
   // glClearColor( 0.0f, 0.1f, 0.0f, 0.5f );
   // glClearDepth( 1.0f );
   // glEnable( GL_DEPTH_TEST );
   // glDepthFunc( GL_LEQUAL );
   // glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
  
   // GLfloat amb_light[] = { 0.3, 0.3, 0.3, 1.0 };
   // GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
   // GLfloat specular[] = { 0.7, 0.7, 0.7, 1 };
   // GLfloat light_position[] = {2.0, 2.0, 1.0, 0.0};
   // GLfloat light_spot[] = {0.0, 0.0, 0.0};
   // glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
   // glLightfv( GL_LIGHT0, GL_AMBIENT, amb_light );
   // glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
   // glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
   // glLightfv( GL_LIGHT0, GL_POSITION, light_position);
   // glEnable( GL_LIGHT0 );
   // glEnable( GL_COLOR_MATERIAL );
   // glShadeModel( GL_SMOOTH );
   // glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
   // glDepthFunc( GL_LEQUAL );
   // glEnable( GL_DEPTH_TEST );
   // glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT0); 

}

int main(int argc, char** argv)
{  
  a=s=d=g=h=f=1;
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (1000, 500); 
  glutInitWindowPosition (500, 500);
  glutCreateWindow ("Nave");
  init ();
  luz () ;
  glEnable(GL_DEPTH_TEST);
  glutDisplayFunc(display); 
  glutReshapeFunc(resize);
  glutTimerFunc(30,animacao,1);
  glutSpecialFunc(Keys);
  if ( argc > 1){
  nave.Load(argv[1]);
  //  carro.Load("carro.obj");

  srand (time(NULL));

  glutMainLoop();
  }else
    printf("falta o argumento");


   return 0;
}
