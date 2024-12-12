// Heap.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include "Tree.h"


int main() {

    int nombre = 1000;
    Tree tree(nombre);
    for (int i = 0; i < nombre; i++)
    {
        tree.push(rand() % nombre);
    }
    
    // afficher l'arbre
    //tree.printTree();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Retirer tous les elements de l'arbre"  << std::endl;
    std::cout<< std::endl;

    while (!tree.isEmpty())
    {
        std::cout << "Retrait de : " << tree.pop() << std::endl;
    }


    return 0;
}




