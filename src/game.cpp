/*	UNIVERSIDADE FEDERAL DE MATO GROSSO
 * 	DISCIPLINA: Programação II
 * 	PROFESSOR: Ivairton M. Santos 
 * 	AUTOR: Daniel Oliveira Souza
 * 	VERSÃO: 0.0.1
 * 	DESCRIÇÃO: Modelo de código
 * 	DATA:
 */

 //iostream é uma classe e std é um objeto de uso geral
 //Definição de constante
 //Definição de classe
 //Importando biblioteca padrão
 #include <iostream>

//função que controla a camera
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

void display(void)
{ 
  //
	luz();
	MoveTARDIS();
	glutSwapBuffers();
}
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


