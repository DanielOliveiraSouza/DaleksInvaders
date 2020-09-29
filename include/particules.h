
/* 
 * File:   main.c
 * Author: rafael
 *
 * Created on 2 de Julho de 2014, 18:21
 */

#ifndef PARTICULES_H_
#define PARTICULES_H_

#include <stdio.h>
 #include <stdlib.h>
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>

typedef struct particula{
  float vetx, vety, vetz;
}part;

typedef struct explos{
    float posx, posy, posz;
    float contador;
    part *particulas;
    struct explos *prox;
    struct explos *ant;
}explosao;



GLvoid CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[],
                             GLfloat fVert3[], GLfloat *fNormalX,
                             GLfloat *fNormalY, GLfloat *fNormalZ);

void kabum(float posx, float posy, float posz);

 void desenhaExplosoes();
 void limpaExplosoes();

#endif /* PARTICULES_H_ */

