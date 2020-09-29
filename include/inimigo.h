/*	UNIVERSIDADE FEDERAL DE MATO GROSSO
 * 	DISCIPLINA: Sistemas Operacionais 
 * 	PROFESSOR: Linder
 * 	AUTOR: Daniel Oliveira Souza
 * 	VERSÃO: 0.0.1
 * 	DESCRIÇÃO: Implementa um arquivo de cabeçalho 
 * 	DATA:
 */
#ifndef INIMIGO_H_
#define INIMIGO_H_

#include <stdio.h>
#include <stdlib.h>
#include "Model_OBJ.h"
 
 
 struct inimigo {
 //Inimigo daleks[MAX];

	bool flag_vida;
	float fX;
	float fY;
	float fZ;
	float dX;
	float dY;
	float dZ;
	Model_OBJ obj;
};
typedef struct inimigo tipo_inimigo;

void MoveInimigo (tipo_inimigo * self );
void SetInimigo (tipo_inimigo *self, bool flag_vida, float fX, float fY, float fZ, Model_OBJ obj );
void SetFd(tipo_inimigo *self, float fX);
void SetVida (tipo_inimigo * self, bool flag_vida);
 

#endif /* INIMIGO_H_ */
