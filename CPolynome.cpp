#include "CPolynome.h"

CPolynome::CPolynome()
{
	nb_poly = 0;
	nb_coef = NULL;
	coef = NULL;
}

CPolynome::CPolynome(int nbpoly, int* nbcoef, double** coefs)
{
	nb_poly = nbpoly;

	if (nb_coef != NULL)
	{
		delete[] nb_coef;
	}

	if (coef != NULL)
	{
		delete[] coef;
	}

	nb_coef = new int[nb_poly];
	coef = new double* [nb_poly];

	for (int i = 0; i < nb_poly; i++)
	{
		nb_coef[i] = nbcoef[i];
		coef[i] = new double[nb_coef[i]];
		for (int j = 0; j < nb_coef[i]; j++)
		{
			coef[i][j] = coefs[i][j];
		}
	}
}

CPolynome::CPolynome(CPolynome& P)
{
	if (coef != NULL) //on peut se permettre d'écrire ceci car coef dépend de toutes les autres variables
	{
		P.nb_coef = new int[nb_poly];
		P.coef = new double* [nb_poly];
		for (int i = 0; i < P.nb_poly; i++)
		{
			P.coef[i] = new double[nb_coef[i]];
		}
		P.nb_poly = nb_poly;

		for (int i = 0; i < nb_poly; i++)
		{
			P.nb_coef[i] = nb_coef[i];
			for (int j = 0; j < nb_coef[i]; j++)
			{
				P.coef[i][j] = coef[i][j];
			}
		}
	}
	else
	{
		P.nb_poly = 0;
		P.nb_coef = NULL;
		P.coef = NULL;
	}

}

CPolynome::~CPolynome()
{
	for (int i = 0; i < nb_poly; i++)
	{
		delete[] coef[i];
	}
	delete[] coef;
	delete[] nb_coef;
}

double CPolynome::abs(double x)
{
	double a;

	if (x < 0)
	{
		a = (-1.) * x;
	}
	else
	{
		a = x;
	}

	return a;
}

ostream& operator<<(ostream& os, CPolynome& P)
{
	//lignes obligatoire pour le bon fonctionnement de la bibliothèque windows.h
	HWND Hcon = GetConsoleWindow();
	HDC Hdc = GetDC(Hcon);

	//pour ajuster l'ordonnée
	int ajord = -41;
	//-41 car il y a 50 lignes dans la fenêtre de débogage avant que ça commence à défiler mais 9 permanentes

	for (int i = 0; i < P.nb_poly; i++)
	{
		ajord += P.nb_coef[i]*2 ; //*2 car chaque coefficient prend deux lignes 
	}

	ajord += P.nb_poly * 4; //*4 car chaque polynôme prend par défaut 4 lignes

	//si le nombre de lignes ne nécessite pas un ajustement des ordonnées, alors on ne change pas les ordonnées
	if (ajord < 0)
	{
		ajord = 0;
	}

	os << "Graphique representant les polynomes d'equations : \n";
	for (int i = 0; i < P.nb_poly; i++)
	{
		//affichage des équations inscrites par l'utilisateur
		os << "\ny = ";
		
		if (P.nb_coef[i] == 0)
		{
			os << "0";
		}
		else
		{
			for (int j = 0; j < P.nb_coef[i]; j++)
			{
				//cette boucle est nécessaire car le premier coefficient affiché n'est pas forcément positif
				if (j == 0)
				{
					os << P.coef[i][j];
				}
				else
				{
					os << abs(P.coef[i][j]); //pour pas que ça affiche deux fois le signe (voir juste après)
				}

				
				//si le coefficient que l'on vient d'entrer n'est pas le dernier coefficient...
				if ((P.nb_coef[i] - j - 1) > 0)
				{
					if (P.coef[i][j + 1] < 0)
					{
						os << "x^" << P.nb_coef[i] - j - 1 << " - "; //affiche avec un signe - si le coefficient suivant est négatif
					}
					else
					{
						os << "x^" << P.nb_coef[i] - j - 1 << " + "; //affiche avec un signe + si le coefficient est positif
					}
				}
			}
		}

		for (double j = -10; j < 10; j += 0.001)
		{
			double ordonnee_point = 0;

			for (int u = 0; u < P.nb_coef[i]; u++)
			{
				ordonnee_point += P.coef[i][u] * pow(j, u);
			}

			if ((ordonnee_point * 40 < 400) && (ordonnee_point * 40 > -400))
			{
				SetPixel(Hdc, j*40. + 1200., (-1.) * ordonnee_point * 40. + 400. + (double)ajord*5, RGB(210 - 30 * i, 255, 210 - 30 * i));
			}
		}
	}

	// AXES
	for (int u = -400; u < 400; u++)
	{
		SetPixel(Hdc, u + 1200, 400 + ajord*5, RGB(172, 0, 255));
		SetPixel(Hdc, 1200, -u + 400 + ajord*5, RGB(172, 0, 255));
	}

	os << "\n\nNB1 : Plus un polynome est rentre au debut, plus sa representation sera claire\n";
	os << "NB2 : Si les polynomes s'affichent mal, essayez d'en rentrer moins\n\n";

	if (P.nb_poly < 3)
	{
		if(P.nb_poly==2)
		{
			os << "\n\n\n\n\n\n\n\n";
		}
		else
		{
			os << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		}
		
	}
	return os;
}

istream& operator>>(istream& is, CPolynome& P)
{
	if (P.coef != NULL)
	{
		for (int i = 0; i < P.nb_poly; i++)
		{
			delete[] P.coef[i];
		}
		delete[] P.coef;
	}

	if (P.nb_coef != NULL)
	{
		delete[] P.nb_coef;
	}

	cout << "Entrer le nombre de polynomes : ";
	is >> P.nb_poly;

	P.nb_coef = new int[P.nb_poly];
	P.coef = new double* [P.nb_poly];

	for (int i = 0; i < P.nb_poly; i++)
	{
		cout << "\n\nInformations sur le polynome " << i + 1 << " : ";
		cout << "\nEntrer le nombre de coefficients du polynome : ";
		is >> P.nb_coef[i];

		P.coef[i] = new double[P.nb_coef[i]];

		for (int j = 0; j < P.nb_coef[i]; j++)
		{
			cout << "\n Coefficient d'ordre " << P.nb_coef[i] - j - 1 << " : ";
			is >> P.coef[i][j];
		}
	}
	return is;
}