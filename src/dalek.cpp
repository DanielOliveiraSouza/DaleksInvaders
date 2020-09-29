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
#include "particules.h"
#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
#define  MAX 10
#define MAX_ROT 360.00
#define  QUADROS 5.00
#define MAX_LIN 1000
#define MAX_COL 500
#define MAX_BALAS (10 * MAX)
#define K 3.00
#define VEL_INIMIGO (0.1)
#define VEL_BALAS (0.075000)
#define INIMIGO_X_INICIAL  -12.5
#define INIMIGO_X_INCREMENTO  7.5
#define INIMIGO_Y_INICIAL 0.0
#define INIMIGO_Y_INCREMENTO 12.0
#define TECLA_TIRO 115
#include "Model_OBJ.h"
#include "inimigo.h"
//#include "Inimigo.h"

//http://bit.ly/29jm7vl

using namespace std;

float T = 0;
float T2 = 0;
float T3 = 1;
float y =-1;
int flag_red = 0;
int flag_scale=0;
int flag_rot = 0;
int flag_reset_inimigo = 0;
int flag_colisao = 0;
int indice_colisao=-1;
int pos = 0;
int sentido = 0;
int i = 0;
float z =  0.0;
//float y;
float x=0.0;
float vel_sca=1.00;
int inimigos_vivos = MAX;
int flag_metade=0;

float rx;
int a,s,d,f,g,h;
float viewangle= 0 , tippangle = 0, luz_x = 10.0, luz_z = 10.0, luz_y = 10.00;

tipo_inimigo daleks[MAX];
struct bala{
	float x;
	float y;
	float z;
	int flag_balas;
};

typedef struct bala tipo_bala;
struct lista_balas {
	tipo_bala balas[MAX_BALAS];
	int tam;
};
typedef struct lista_balas tipo_balas;
//Model_OBJ nave;
//Model_OBJ nave;
/*
struct s_nave{
	Model_OBJ obj;
	float rx;
	float ry;
	float rz;
};

typedef struct s_nave tipo_nave;

tipo_nave nave;*/
tipo_balas projeteis;
Model_OBJ nave;


void Insert_balas(){
	if (projeteis.tam < MAX_BALAS){
		if(projeteis.tam == 0){
			for (int i=0; i < MAX_BALAS;i++)
				projeteis.balas[i].flag_balas = 0;
		}
		projeteis.balas[projeteis.tam].x = T;
		projeteis.balas[projeteis.tam].y =-12.0;
		projeteis.balas[projeteis.tam].z =0.0;
		projeteis.tam++;
	}else{
		printf("Limite excedido\n");
	}
}
void luz();
void camera();
void MoveTardis();
void MoveBala();
int Colisao(float x1, float z1);

void Reset_Inimigo(){
	int i;
	float altura;
	float largura= INIMIGO_X_INICIAL;
	for(i = 0; i < MAX;i++){
		if ( i < (float) MAX /2.0)
	   			altura  =INIMIGO_Y_INCREMENTO;
	   		else {
	   			if ( i == (float) MAX/2.0){
	   				altura = INIMIGO_Y_INICIAL;
	   				largura= INIMIGO_X_INICIAL;
	   			}
	   		}
	   		daleks[i].fY=altura;
	   		daleks[i].fX=largura;

	   		largura+= INIMIGO_X_INCREMENTO;
	   	}

}

int Colisao(float x1,  float y1, float z1){
	int i;
	i = 0;
	float aux=-1000.00;
	float x0;

	while (i < MAX){
		aux = daleks[i].fY;
		x0 = daleks[i].fX;
		float ax2 = aux -y1;

		//printf("d(y,y0)=%f\n",ax2);
		//printf("aux=%f\n",aux);
		if((floorf((aux -y1)) == 0.0000000) && (floorf(x0-x1) == 0.0000000) && (daleks[i].flag_vida == true) && (y1 <= 6.00)){
			printf("Colidiu em %d \n",i);
			return i;
		}
		i++;
	}
	return -1;
}


void MoveBala(){
	//int flag_colisao;

	for(int i  =0;  i < projeteis.tam;i++){
		printf("y1= %f\n",floorf(projeteis.balas[i].y));
		projeteis.balas[i].flag_balas = Colisao(projeteis.balas[i].x,projeteis.balas[i].y,projeteis.balas[i].z);
		if((projeteis.balas[i].flag_balas == -1) && (projeteis.balas[i].y < (MAX_LIN/100.00))) {
			glBegin(GL_POLYGON);
			/*glVertex3f(projeteis.balas[i].x,projeteis.balas[i].y,projeteis.balas[i].z);
			glVertex3f(projeteis.balas[i].x + 1,projeteis.balas[i].y,projeteis.balas[i].z);
			glVertex3f(projeteis.balas[i].x,projeteis.balas[i].y,projeteis.balas[i].z + 2);
			*/
			glVertex2f(projeteis.balas[i].x,projeteis.balas[i].y);
			glVertex2f(projeteis.balas[i].x+1.0,projeteis.balas[i].y );
			glVertex2f((projeteis.balas[i].x+1.0)/2.0,projeteis.balas[i].y+1.0);
			glEnd();
			if (projeteis.balas[i].y < QUADROS)
				projeteis.balas[i].y+= VEL_BALAS;
			/*else
			*	projeteis.balas[i].z =0.0;*/
			projeteis.balas[i].y+= VEL_BALAS;
			floorf(projeteis.balas[i].y);
		}else{
			if(projeteis.balas[i].flag_balas){
				flag_colisao = 1;
	 			daleks[projeteis.balas[i].flag_balas].flag_vida = false;
	 			//inimigos_vivos--;
	 			//flag_colisao = 0;

				//printf("Colidiu\n");
				kabum(projeteis.balas[i].x,projeteis.balas[i].y,projeteis.balas[i].z);
		
				;
			}
			projeteis.balas[i].flag_balas = 0;
			projeteis.tam--;
			
			//break;
			
		}
		
	}
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

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);

	//printf("rx=%lf\n",rx);

	glPushMatrix();
	//glRotatef(T,0.0,0.0,1.0);
	glTranslatef(T, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0,-10.0,0);

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

	if ( rx < MAX_ROT )
		rx = rx + 18.00;
	else rx = 0.0;
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//glPopMatrix();
	
}
void MoveInimigo (tipo_inimigo * self ){
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	if(self->flag_vida){

			GLfloat dalek_amb[4] = {  0.2125 ,	0.1275 	,0.054, 1.0};
	  		GLfloat dalek_dif[4] = { 0.714 ,	0.4284 	,0.18144 , 1.0};
	   		GLfloat dalek_spe[4] = { 0.393548 ,0.271906 ,	0.166721,1.0};
	   		GLfloat dalek_shi = 0.2*128.0;
		 	glMaterialfv(GL_FRONT,GL_AMBIENT,dalek_amb);
	   		glMaterialfv(GL_FRONT,GL_DIFFUSE,dalek_dif);
	   		glMaterialfv(GL_FRONT,GL_SPECULAR,dalek_spe);
	  		glMaterialf(GL_FRONT,GL_SHININESS, dalek_shi);

		if ( flag_red == 0){
					glScalef(1.0/K,1.0/K,1.0/K);//Redimensiona o objeto
					flag_red =1;
		}


		//for (int i = 0 ; i < MAX ; i++){
			if ( sentido == 0){
				//printf("self-y=%f\n",self->fY);
				//while (z < QUADROS){
					glPushMatrix();
					//printf("z= %f\n",z);3
					glPushMatrix();
					glTranslatef(self->fX,0.0,0.0);
					glPushMatrix();
					glTranslatef(0.0,self->fY,0.0);
					glPushMatrix();

					glTranslatef(0.0,0.0,self->fZ);
					//printf("desenha\n");
					self->obj.Draw();
					glPopMatrix();
					glPopMatrix();
					glPopMatrix();
					//system("sleep 1");
					glPopMatrix();

					z= self->fZ;
					x= self->fX;
					//y= self->fY;
					
					if(self->fX < (MAX_COL /10.00))
						self->fX+= (vel_sca)*(VEL_INIMIGO);
					else
						flag_reset_inimigo = 1;
					
					/*if ( z < QUADROS)
						z+= VEL_INIMIGO;
					else
							z=0.0;
							*/
			}else{
				;
					/*glPushMatrix();
					//printf("z= %f\n",z);
					glPushMatrix();
					glTranslatef(self->fX,0,0);
					glPushMatrix();
					glTranslatef(0,T2,0);
					glPushMatrix();
					glTranslatef(0,0,z);
					//printf("desenha\n");
					self->obj.Draw();
					glPopMatrix();
					glPopMatrix();
					glPopMatrix();
					//system("sleep 1");
					glPopMatrix();
					
					if ( z > -QUADROS )
						z-= 0.001;
					else
						sentido = 0;
						*/
		}

	}
	//glutSwapBuffers();
	
}
void SetInimigo (tipo_inimigo *self, bool flag_vida, float fX, float fY, float fZ, Model_OBJ obj ){
	if (self != NULL){
		self->flag_vida = flag_vida;
		self->fX = fX;
		self->fY = fY;
		self->fZ = fZ;
		self->obj = obj;
	}
}

void SetFd(tipo_inimigo *self, float fX){
	if (self != NULL){
		self->fX = fX;
	}
}

void SetVida (tipo_inimigo * self, bool flag_vida){
	if (self != NULL){
		self->flag_vida = flag_vida;
	}
}


  
   
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	 glLoadIdentity();

	 //glTranslatef(tippangle,0,0,0)

 
   
   //Seta a camera
   camera();
   
   //Ligas as luzes
   luz();
	//glPushMatrix();
	//glTranslatef(viewangle, 0.0, 0.0);
	//glPushMatrix();
	//glTranslatef(0.0, tippangle, 0.0);
   glPushMatrix();
  desenhaExplosoes();
  //glEnable(GL_NORMALIZE);
 //glFlush();
	MoveTARDIS();
	MoveBala();
   
   	 
	 for (int i = 0 ; i < MAX ; i++){
	 	MoveInimigo(&daleks[i]);
	 	if(flag_colisao == 1){
	 		inimigos_vivos--;
	 		flag_colisao = 0;
	 	}
	 	//pos = i;
	 	
	 	;
	}
	

	flag_red=0;
	if(flag_reset_inimigo){
		//System("sleep 5");
		Reset_Inimigo();

	//	printf("Chamei reset inimigo\n");
		flag_reset_inimigo = 0;
	}
	//glPushMatrix();
	
	//glPushMatrix();	
	//glPushMatrix();
	//glPushMatrix();
	//glPushMatrix();
	//glPushMatrix();
	glPopMatrix();
	limpaExplosoes();
	glEnable(GL_NORMALIZE);
  	glFlush();
	glutSwapBuffers();
 
 	//glPopMatrix();
 	/*if(inimigos_vivos == (MAX /2.0)){
 		vel_sca= 1.0;
 		//flag_metade = 1;
 	}
*/
 	if(inimigos_vivos == 0){
 		printf("Fim de jogo!\n");
 		exit(1);   
 	}else
 		;//printf("Restam %d\n",inimigos_vivos);

}
void Keys (int key, int x, int y)
{
	//printf("pressionou a key =  %d\n",key);
    switch (key) {
 
       case GLUT_KEY_LEFT :  T -= 1.25; break;
       case GLUT_KEY_RIGHT:  T += 1.25; break;
       case GLUT_KEY_UP   :  T2 -= 5.0;  break;
       case GLUT_KEY_DOWN :  T2 += 5.0;  break;
       case GLUT_KEY_PAGE_UP   :  T3 -= 5.0;  break;
       case GLUT_KEY_PAGE_DOWN :  T3 += 5.0;  break;
       case TECLA_TIRO:
       		//printf("Disparou o evento atirar\n");
       		Insert_balas();
       		break;
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
  gluLookAt(0.0, 20.0, 10.0,
	    0.0, 0.0, 0.0,
	    0.0, 1.0, 0.0);


}


void animacao(int value){
  glutPostRedisplay();
  glutTimerFunc(30, animacao,1);
  
  
}

void init (void) 
{
	/* glClearColor (0.3, 0.3, 0.3, 0.0);
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
   // GLfloat light_spot[] = {0.0, 0.0, 0.0};3, 0.3, 0.0);
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
   */

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
/*
	GLfloat lightpos[] = {10.0, 10.0, 10.0, 1.0};
	GLfloat lightcol[] = {0.9, 0.9, 0.9, 1.0};

	GLfloat lightamb[] = {.1, .1, .1, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);

	lLightfv(GL_LIGHT1, GL_AMBIENT, lightamb);
	*/

//	glEnable(GL_COLOR_MATERIAL);

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

void camera(){

	/* eye x , eye y , eye z ,
aim x , aim y , aim z ,
up x , up y , up z );
 eye = ponto onde a câmera será
posicionada
 aim = ponto para onde a câmera
será apontada
 up = vetor que dá a direção
“para cima” da câmera*/
  gluLookAt(0.00,10.00,15.00,
	    0.0, 0.0, 0.0,
	    0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{  
	Model_OBJ aux;
	int i;
	a=s=d=g=h=f=1;

	float largura=-12.50;
	float altura = 0;
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (1000, 500); 
   glutInitWindowPosition (500, 500);
   glutCreateWindow ("Dalek");
   init ();
   luz ();
   glEnable(GL_DEPTH_TEST);
   glutDisplayFunc(display); 
   glutReshapeFunc(resize);
   glutTimerFunc(30,animacao,1);
  glutSpecialFunc(Keys);
   //glutKeyFunc(Keys);
 //  if ( argc > 1){
	   aux.Load("objs/Dalek_bir.obj");
	   nave.Load("objs/blendswap.obj");
	  /* projeteis.tam=1;
	   projeteis.balas[0].x = -5.0;
	   projeteis.balas[0].y=-10.0;
	   projeteis.balas[0].z=-10.0000;
	   projeteis.balas[0].flag_balas=0;
	   */
	   //printf("Importei %s\n",argv[1]); 	
	   for (i= 0;i < MAX; i++){
	   		if ( i < (float) MAX /2.0)
	   			altura  = INIMIGO_Y_INCREMENTO;
	   		else {
	   			if ( i == (float) MAX/2.0){
					altura = INIMIGO_Y_INICIAL;
		   			largura= INIMIGO_X_INICIAL;
	   			}

	   		}
	   		//printf("l = %f h = %f\n",largura,altura);
	   		SetInimigo(&daleks[i],1, largura, altura , 0 , aux);
	   		largura += 7.50;
	   }
	  //daleks[3].flag_vida=false; //testando a morte do inimigo
	   //nave.ry -10.00;

 //  }
	//else{
		//char str;
		//scanf("%s",str);
	//	puts("Falta informar o parametro com o objeto");

		//dalek.Load(str);
	//}
 //  carro.Load("carro.obj");
   
   srand (time(NULL));
   
   glutMainLoop();

   return 0;
}
