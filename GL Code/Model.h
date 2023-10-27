#pragma once
class Model
{
private:
	struct vertex {
		double ver[3];
	};
	struct face {
		double N[3];
		int tri[3];
	};

	vertex* V;
	face* F;

	int nvert, nface;


public:
	Model();
	~Model();

	void DrawM();
	// Funcion sobrecargada mismo nombre, dif variables de entrada
	void DrawM(float diff[4]);

private:
	void CalcNormV(double a[3], double b[3], double c[3], double N[3]);
	void CalcNorms();

};

