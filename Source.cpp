#include "CPolynome.h"

int main()
{
	HWND Hcon = GetConsoleWindow();
	HDC Hdc = GetDC(Hcon);

	cout << "MERCI DE BIEN VOULOIR PASSER LA FENETRE EN PLEIN ECRAN\n\n";

	CPolynome P;

	cin >> P;	
	cout << P;
	
	ReleaseDC(Hcon, Hdc);
	return 0;
}