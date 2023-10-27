#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h> //libreria de tiempo
#include <GL/glut.h>


#include "Model.h"


double vert_[5][3] = { { 0.5, 0.0, -0.5},
					  {-0.5, 0.0, -0.5},
					  {-0.5, 0.0,  0.5},
					  { 0.5, 0.0,  0.5},
					  { 0.0, 1.0,  0.0} };

int face_[6][3] = { {0, 1, 4},
				   {1, 2, 4},
				   {2, 3, 4},
				   {3, 0, 4},
				   {3, 2, 0},
				   {2, 1, 0} };


Model::Model()
{
	nvert = 5;
	nface = 6;

	V = new vertex[nvert];
	for (int i = 0; i < nvert; i++)
		for (int j = 0; j < 3; j++)
			V[i].ver[j] = vert_[i][j];

	F = new face[nface];
	for (int i = 0; i < nface; i++)
		for (int j = 0; j < 3; j++)
			F[i].tri[j] = face_[i][j];

	CalcNorms();
}

Model::~Model()
{
	if (V != NULL)
		delete V;
	
	if (F != NULL)
		delete F;
}

void Model::DrawM(float diff[4]) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
	DrawM();
}

void Model::DrawM() {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < nface; i++) {
		glNormal3dv(F[i].N);
		for (int j = 0; j < 3; j++)
			glVertex3dv(V[F[i].tri[j]].ver);
	}
	glEnd();
}

void Model::CalcNormV(double a[3], double b[3], double c[3], double N[3])
{
	double Vab[3], Vac[3], norm;

	for (int i = 0; i < 3; i++)
	{
		Vab[i] = b[i] - a[i];
		Vac[i] = c[i] - a[i];
	}

	N[0] = Vab[1] * Vac[2] - Vab[2] * Vac[1];
	N[1] = Vab[2] * Vac[0] - Vab[0] * Vac[2];
	N[2] = Vab[0] * Vac[1] - Vab[1] * Vac[0];

	norm = sqrt(N[0] * N[0] + N[1] * N[1] + N[2] * N[2]);

	for (int i = 0; i < 3; i++)
		N[i] = N[i] / norm;
}

void Model::CalcNorms() {
	for (int i = 0; i < nface; i++) {
		CalcNormV(V[F[i].tri[0]].ver, V[F[i].tri[1]].ver, V[F[i].tri[2]].ver, F[i].N);
	}
}
