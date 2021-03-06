// Arcade.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <math.h>
#include <iostream>
using namespace std;

//Declaracion de la ventana
GLFWwindow *window;

GLfloat jugadorY = -0.8f;
GLfloat jugadorX = 0.0f;
GLfloat bombaY = 0.0f;
GLfloat bombaX = 0.0f;

bool bomba = false;
bool bloque1 = true;
bool explosion = false;

double tiempoAnterior = 0.0;
double tiempoAnteriorBomba = 0.0;
double tiempoAnteriorExplosion = 0.0;
double velocidad = 2.0;

void dibujarBomba();
void dibujarExplosion();

void dibujarMapa() {
	/*glPushMatrix();
	glTranslated(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glEnd();
	glPopMatrix();*/
}

void dibujarJugador() {
	glPushMatrix();
	glTranslated(jugadorX, jugadorY, 0.0f);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glEnd();
	glPopMatrix();
}

void moverJugador(double tiempoTranscurrido) {
	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS && jugadorX < 0.9) {
		jugadorX += 1 * velocidad * tiempoTranscurrido;
	}

	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS && jugadorX > -0.9) {
		jugadorX -= 1 * velocidad * tiempoTranscurrido;
	}

	int estadoEspacio = glfwGetKey(window, GLFW_KEY_SPACE);
	if (estadoEspacio == GLFW_PRESS) {
		bombaX = jugadorX + 0.2;
		bombaY = jugadorY + 0.0;
		bomba = true;
	}

	if (bomba) {
		dibujarBomba();
	}

	if (explosion) {
		dibujarExplosion();
	}

	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS && jugadorY < 1.0) {
		jugadorY += 1 * velocidad * tiempoTranscurrido;
	}

	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS && jugadorY > -1.0) {
		jugadorY -= 1 * velocidad * tiempoTranscurrido;
	}

	/*int estadoMasVelocidad = glfwGetKey(window, GLFW_KEY_E);
	if (estadoMasVelocidad == GLFW_PRESS && velocidad < 10.0) {
		velocidad += 0.1;
	}

	int estadoMenosVelocidad = glfwGetKey(window, GLFW_KEY_Q);
	if (estadoMenosVelocidad == GLFW_PRESS && velocidad > 0.0) {
		velocidad -= 0.1;
		if (velocidad < 0)
			velocidad = 0;
	}*/
}

void dibujarBomba() {
	double tiempoActual = glfwGetTime();
	double tiempoTranscurridoBomba = tiempoActual - tiempoAnteriorBomba;
	if (tiempoTranscurridoBomba < 2) {
		glPushMatrix();
		glTranslated(bombaX, bombaY, 0.0f);
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glEnd();
		glPopMatrix();
	}
	else if(bomba) {
		tiempoAnteriorExplosion = glfwGetTime();
		explosion = true;
		bomba = false;
		tiempoAnteriorBomba = tiempoActual;
	}
}

void dibujarExplosion() {
	double tiempoActual = glfwGetTime();
	double tiempoTranscurridoExplosion = tiempoActual - tiempoAnteriorExplosion;
	if (tiempoTranscurridoExplosion < 2) {
		glPushMatrix();
		glTranslated(bombaX + 0.2, bombaY, 0.0f);
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslated(bombaX, bombaY + 0.2, 0.0f);
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslated(bombaX - 0.2, bombaY, 0.0f);
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslated(bombaX, bombaY - 0.2, 0.0f);
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glEnd();
		glPopMatrix();
	}
	else if (explosion) {
		explosion = false;
		tiempoAnteriorExplosion = tiempoActual;
	}
}

//Aqui esta bien para cambiar los valores de las variables de mi programa
void actualizar() {
	double tiempoActual = glfwGetTime();
	double tiempoTranscurrido = tiempoActual - tiempoAnterior;

	dibujarMapa();
	dibujarJugador();
	moverJugador(tiempoTranscurrido);

	tiempoAnterior = tiempoActual;
}

void dibujar() {

}

int main()
{
	//Declaracion de la ventana
	//GLFWwindow *window;

	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 720;

	//Inicializacion de GLFW
	if (!glfwInit()) {
		//Si no se inicio bien, terminar la ejecucion
		exit(EXIT_FAILURE);
	}

	//Iniciar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verificar si se creo bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecucion
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como conexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;

	tiempoAnterior = glfwGetTime();
	tiempoAnteriorBomba = glfwGetTime();

	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia
		glClearColor(0.0f, 0.0f, 0.0f, 1);
		//Limpiar la pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar señal de entrada
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
