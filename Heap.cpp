// Heap.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include "Tree.h"


int main()
{
    Tree T;
    int nombre = 10000;
    
   std::vector<int> valeurs(nombre);
    for (int i = 0; i < valeurs.size(); i++)
    {
        valeurs[i] = rand() % nombre;
    }

    for (int i = 0; i < valeurs.size(); i++)
    {
        T.push(valeurs[i]);
    }
     
    // afficher l'arbre
    // 
    //std::cout << "Avant de retirer :" << std::endl;
    //T.printTree();


    // retirer tous les elements : ils seront retires du plus petit au plus grand
    while (!T.isEmpty())
    {
        std::cout << "Retrait de :" << T.pop() << std::endl;
        //T.printTree();
    }

   

}




