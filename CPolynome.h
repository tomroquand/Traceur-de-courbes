#pragma once
#include <windows.h>
#define LARGEUR 10
#define HAUTEUR 10
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class CPolynome
{
private:
	int nb_poly;
	int* nb_coef;
	double** coef;

public:
	CPolynome();
	CPolynome(int nbpoly, int* nbcoef, double** coefs);
	CPolynome(CPolynome& P);
	~CPolynome();

	friend ostream& operator<<(ostream& os, CPolynome& P);
	friend istream& operator>>(istream& is, CPolynome& P);

	double abs(double x); //cf. l.133
};

