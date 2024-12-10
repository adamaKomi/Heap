#pragma once

#include <iostream>

using namespace std;

struct Node{
	int val;// valeur du noeud
	Node* fg;// le fils gauche 
	Node* fd;// le fils droit

	Node(int val)// constructeur du noued
	{
		this->val = val;
		this->fg = nullptr;
		this->fd = nullptr;
	}
};


class Tree
{
private:
	Node* root;// racine de l'arbre
public:
	Tree();// constructeur de l'arbre
	bool isEmpty()const;
	void push(int val);// fonction pour inserer une veleur
	void change(Node* tmp, int& check);// pour faire le chagement des noeuds
	void organize();// pour organiser l'arbre pour avoir le minimum a la racine
	void deleteNode(Node*& root);// supprimer un noeud
	int pop();// pour retirer une valeur a la racine
	void print(Node* root , int space = 0, int indent = 4);// afficher sous forme d'arbre
	void printTree();// afficher l'arbre
	
};

