#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Tree
{
private:
	vector<int> tab;
	int capacity;
	int indice;
public:
	Tree(int capacite);// constructeur de l'arbre
	bool isEmpty()const;
	void push(int val);// fonction pour inserer une veleur
	void organize();// pour organiser l'arbre pour avoir le minimum a la racine

	int pop();// pour retirer une valeur a la racine
	void print(int ind, int space = 0, int indent = 4) const; // afficher sous forme d'arbre
	void printTree() const; // afficher l'arbre
	
};

