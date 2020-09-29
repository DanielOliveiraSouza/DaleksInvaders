/* 
 * File:   main.c
 * Author: rafael
 *
 * Created on 2 de Julho de 2014, 18:21
 */

#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "particules.h"
#define V 0.1

#define PART 100         //limite de particulas
#define EXPLOSAO_TEMPO 0.01     //Tempo de vida
/*
float T=0;
float viewangle=0, tippangle=0;
int *keys;

GLint viewport[4];
GLdouble modelview[16];
GLdouble projection[16];
GLfloat winX, winY, winZ;
GLdouble posX, posY, posZ;
*/

explosao *explosoes = NULL;

GLvoid CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[],
                             GLfloat fVert3[], GLfloat *fNormalX,
                             GLfloat *fNormalY, GLfloat *fNormalZ)
    {
    GLfloat Qx, Qy, Qz, Px, Py, Pz;

   Qx = fVert2[0]-fVert1[0];
   Qy = fVert2[1]-fVert1[1];
   Qz = fVert2[2]-fVert1[2];
   Px = fVert3[0]-fVert1[0];
   Py = fVert3[1]-fVert1[1];
   Pz = fVert3[2]-fVert1[2];

   *fNormalX = Py*Qz - Pz*Qy;
   *fNormalY = Pz*Qx - Px*Qz;
   *fNormalZ = Px*Qy - Py*Qx;

}


void kabum(float posx, float posy, float posz){
    float  r = 5.0, ang = 0.0;
    if(explosoes == NULL){
        explosoes = (explosao*)malloc(sizeof(explosao));
        explosoes[0].posx = posx;
        explosoes[0].posy = posy;
        explosoes[0].posz = posz;
        explosoes[0].prox = NULL;
        explosoes[0].ant  = NULL;
        explosoes[0].contador = 1.0;
        explosoes[0].particulas = (part*)malloc(3*PART*sizeof(part));
        srand (time(NULL));

        int i;
        for(i=0;i<PART;i++){
      r = (rand()%100-50)/50.0;
    //  printf("%f\n",r);
            explosoes[0].particulas[i].vetx = (rand()%4-2)*r;
            explosoes[0].particulas[i].vety = (rand()%4-2)*r;
            explosoes[0].particulas[i].vetz = (rand()%4-2)*r;
        }
        for(i=PART;i<PART*2;i++){
      r = (rand()%100-50)/50.0;
            explosoes[0].particulas[i].vetx = (rand()%6-3)*r;
            explosoes[0].particulas[i].vety = (rand()%6-3)*r;
            explosoes[0].particulas[i].vetz = (rand()%6-3)*r;
        }
        for(i=PART*2;i<PART*3;i++){
      r = (rand()%100-50)/50.0;
            explosoes[0].particulas[i].vetx = (rand()%10-5)*r;
            explosoes[0].particulas[i].vety = (rand()%10-5)*r;
            explosoes[0].particulas[i].vetz = (rand()%10-5)*r;
        }
        
        
    }else{
        explosao *aux = explosoes;
        while(aux->prox!=NULL)
            aux = aux->prox;
        
        aux->prox = (explosao*)malloc(sizeof(explosao));
        aux->prox->posx = posx;
        aux->prox->posy = posy;
        aux->prox->posz = posz;
        aux->prox->prox = NULL;
        aux->prox->ant  = aux;
        aux->prox->contador = 1.0;
        aux->prox->particulas = (part*)malloc(3*PART*sizeof(part));
        
        int i;
        for(i=0;i<PART;i++){
      r = (rand()%100-50)/50.0;
            aux->prox->particulas[i].vetx = (rand()%4-2)/r;
            aux->prox->particulas[i].vety = (rand()%4-2)/r;
            aux->prox->particulas[i].vetz = (rand()%4-2)/r;
        }
        for(i=PART;i<PART*2;i++){
      r = (rand()%100-50)/50.0;
            aux->prox->particulas[i].vetx = (rand()%6-3)/r;
            aux->prox->particulas[i].vety = (rand()%6-3)/r;
            aux->prox->particulas[i].vetz = (rand()%6-3)/r;
        }
        for(i=PART*2;i<PART*3;i++){
      r = (rand()%100-50)/50.0;
            aux->prox->particulas[i].vetx = (rand()%10-5)*r;
            aux->prox->particulas[i].vety = (rand()%10-5)*r;
            aux->prox->particulas[i].vetz = (rand()%10-5)*r;
        }
        
        
    }
    //printf("criou explosao\n");
   // printf("%f // %f // %f\n",posx, posy, posz);
}

void desenhaExplosoes(){
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE); 
    
    GLfloat triang1[3], triang2[3], triang3[3];
    GLfloat normalx = 0.0, normaly= 0.0, normalz= 0.0;
    
    triang1[0] =  0.0; triang1[1] = 0.0; triang1[2] = 0.0;
    triang2[0] =  0.0; triang2[1] = 0.1; triang2[2] = 0.0;
    triang3[0] =  0.1; triang3[1] = 0.0; triang3[2] = 0.0;
    CalculateVectorNormal(triang1, triang2, triang3, &normalx, &normaly, &normalz);
    
    int i;
    explosao *aux = explosoes, *aux2 = explosoes, *aux3 = explosoes;
    
    while(aux!=NULL){
        
        for(i=0;i<PART;i++){
            glPushMatrix();
            glTranslatef(aux->posx, aux->posy, aux->posz);
            glTranslatef(aux->particulas[i].vetx*(1-aux->contador), aux->particulas[i].vety*(1-aux->contador), aux->particulas[i].vetz*(1-aux->contador));
            glBegin(GL_TRIANGLES);
            glColor4f( 0.9,  0.1, 0.1, aux->contador);
            glNormal3f(normalx, normaly, normalz);
            glVertex3fv(triang1);
            glVertex3fv(triang2);
            glVertex3fv(triang3);
            glEnd();
            glPopMatrix();
        }

        

        for(i=PART;i<PART*2;i++){
            glPushMatrix();
            glTranslatef(aux2->posx, aux2->posy, aux2->posz);
            glTranslatef(aux->particulas[i].vetx*(1-aux->contador), aux->particulas[i].vety*(1-aux->contador), aux->particulas[i].vetz*(1-aux->contador));
            glBegin(GL_TRIANGLES);
            glColor4f( 0.9,  0.9, 0.1, aux->contador);
            glNormal3f(normalx, normaly, normalz);
            glVertex3fv(triang1);
            glVertex3fv(triang2);
            glVertex3fv(triang3);
            glEnd();
            glPopMatrix();
            
        }

        

        for(i=PART*2;i<PART*3;i++){
            glPushMatrix();
            glTranslatef(aux3->posx, aux3->posy, aux3->posz);
            glTranslatef(aux->particulas[i].vetx*(1-aux->contador), aux->particulas[i].vety*(1-aux->contador), aux->particulas[i].vetz*(1-aux->contador));
            glBegin(GL_TRIANGLES);
            glColor4f( 0.9,  0.9, 0.9, aux->contador);
            glNormal3f(normalx, normaly, normalz);
            glVertex3fv(triang1);
            glVertex3fv(triang2);
            glVertex3fv(triang3);
            glEnd();
            glPopMatrix();
        }

        
        
        aux->contador -= EXPLOSAO_TEMPO;
        
        aux = aux->prox;
        aux2 = aux2->prox;
        aux3 = aux3->prox;
        
    }
}

void limpaExplosoes(){
    explosao *aux = explosoes;
    while(aux!=NULL){
        if(aux->contador <= 0.0){
            if(aux->ant!=NULL){
                if(aux->prox == NULL)
                    aux->ant = NULL;
                else
                    aux->ant->prox = aux->prox;
                explosao *aux2 = aux;
                aux = aux->prox;
                free(aux2);
            }else{
                explosoes = NULL;
                free(aux);
                aux = NULL;
            }
        }else
            aux = aux->prox;
    }
}


/*
void display(void)
{      
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  
  
  glPushMatrix();
  desenhaExplosoes();
  glPopMatrix();
  
  limpaExplosoes();
  glEnable(GL_NORMALIZE);
  glFlush();
}


void resize(int w, int h){
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLdouble) w/h,
      1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, -6.0,
      0.0, 0.0, 0.0,
      0.0, 1.0, 0.0);

}

void key(unsigned char key, int a, int b){
  float x, y;
  x = rand()%8-4.0;
  y = rand()%8-4.0;
  kabum(x,y,0.0);
}

void init (void) 
{
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
  glEnable(GL_DEPTH_TEST);

  GLfloat lightpos[] = {10.0, 10.0, 10.0, 1.0};
  GLfloat lightcol[] = {0.9, 0.9, 0.9, 1.0};

  GLfloat lightamb[] = {.1, .1, .1, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);

  glLightfv(GL_LIGHT1, GL_AMBIENT, lightamb);

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

}

*/

void timer(int value){  
  glutPostRedisplay();
  glutTimerFunc(10, timer, 1);
}

/*
int main(int argc, char** argv)
{

  
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize (600, 600); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Space Invaders 1.0");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(resize);
   glutKeyboardFunc(key);
   glutTimerFunc(30, timer, 1);
   glutMainLoop();

   return 0;
}
*/
