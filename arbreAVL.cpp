#include <iostream>
#include "arbreBST.cpp"

using namespace std;

/*BALDJ17058609 - BALDO jerome
état : je n'ai pas pu finir l'AVL. Je n'ai pas pu résoudre le probléme de modification 
réalisé : rotation simple droite / rotation simple gauche / rotation double gauche / rotation double  droit 
affichage du parent -+ des enfants */

void chargerArbre(BinarySearchTree<int>& arbreAVL);

int main(int argc, char* argv[])
{
	BinarySearchTree<int> arbreAVL;
	chargerArbre(arbreAVL);
	cout << arbreAVL;
	
	system("PAUSE");
	return EXIT_SUCCESS;
}
void chargerArbre(BinarySearchTree<int>& arbreAVL)
{
	//int valeurs[] = { 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9 };
	int valeurs[] = { 3,2,1,4,5,6,7,16,15,14,13,12,11,10};
	int nbValeurs = sizeof valeurs / sizeof * valeurs;
	for (int x = 0; x < nbValeurs; x++)
	{
		arbreAVL.insert(valeurs[x]);
		arbreAVL.VerifBalanc(arbreAVL);
	}
}