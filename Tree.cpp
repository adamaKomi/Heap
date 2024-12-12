#include "Tree.h"
#include <chrono>


// constructeur
Tree::Tree(int capacite)
    : capacity(capacite), indice(-1) 
{
    tab.resize(capacite); // Redimensionne le tableau
}


// Fonction pour verifier si l'a capacité est 'arbre est vide
bool Tree::isEmpty() const
{
    return indice < 0;
}


// fonction pour ajouter une valeur dans l'arbre
void Tree::push(int val)
{
    //verifier si la capacité est atteinte
    if (indice >= capacity -1) {
        cout << "Erreur: capacité maximale atteinte." << endl;
        return;
    }


    // mesurer le debut de l'insertion
    auto debut = std::chrono::high_resolution_clock::now();

    // ajouter une valeur
    this->tab[++indice] = val;

    // mesurer la fin de l'insertion
    auto fin = std::chrono::high_resolution_clock::now();

    //calculer la duree de l'insertion en nanosecondes
    auto duree = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - debut);
    std::cout << "Duree de l'insertion de \"" << val << "\" : " << duree.count() << std::endl;

    

    // mesurer le debut de la reorganisation
    debut = std::chrono::high_resolution_clock::now();

    // reorganiser l'arbre après l'ajout
    organize();

    // mesurer la fin de la reorganisation
    fin = std::chrono::high_resolution_clock::now();

    //calculer la duree de la reorganisation en nanosecondes
    duree = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - debut);
    std::cout << "Duree de la reorganisation : " << duree.count()  << std::endl;
}



//fonction pour reorganiser l'arbre pour avoir toujours le max a la racine
void Tree::organize()
{
    // indice du dernier parent ayant un fils
    int id_tmp = indice  / 2 ;

    // repeter jusqu'à atteindre la racine
    while (id_tmp >= 0)
    {
        // verifier si la racine est plus petit que son fils gauche, on echange si c'est le cas
        if ((2 * id_tmp + 1 <= indice) && (tab[id_tmp] < tab[2*id_tmp +1]))
        {
            swap(tab[id_tmp], tab[2 * id_tmp + 1]);
        }
        // verifier si la racine est plus petit que son fils droit, on echange si c'est le cas
        if ((2 * id_tmp + 2 <= indice) && (tab[id_tmp] < tab[ id_tmp*2 + 2]))
        {
            swap(tab[id_tmp], tab[2 * id_tmp + 2]);
        }
        // passer à l'indice inferieur
        id_tmp --;
    }
}




// fonction pour supprimer une valeur a la racine(valeur maximale)
int Tree::pop()
{
    if (isEmpty()) {
        cout << "Erreur: l'arbre est vide." << endl;
        return -1; // Valeur par défaut en cas d'erreur
    }
   
    // mesurer le debut de la suppression
    //auto debut = std::chrono::high_resolution_clock::now();


    // recuperer la valeur da la racine
    int val = this->tab[0];
    // remplacer la racine par la derniere feuille
    tab[0] = tab[this->indice];
    // supprimer la dernière feuille
    this->indice--;
    //reorganiser
    organize();

    // mesurer la fin de la suppression
    //auto fin = std::chrono::high_resolution_clock::now();

    //calculer la duree de la suppression en nanosecondes
    //auto duree = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - debut);
    //std::cout << "Duree de la suppression : " << duree.count() << std::endl;
    return val;
}




//Fonction pour afficher l'arbre sous forme d'arbre
void Tree::print(int ind, int space, int indent) const {
    if (ind > indice) return;

    // Augmenter l'espace entre les niveaux
    space += indent;

    // Afficher le sous-arbre droit
    print(2 * ind + 2, space, indent);

    // Afficher le nœud courant avec le bon espacement
    cout << endl;
    for (int i = indent; i < space; i++) cout << " ";
    cout << tab[ind];

    // Afficher le sous-arbre gauche
    print(2 * ind + 1, space, indent);
}


//Fonction pour afficher l'arbre 
void Tree::printTree() const {
    //si l'arbre est vide
    if (isEmpty()) {
        cout << "Arbre vide!" << endl;
        return;
    }

    print(0); // Afficher l'arbre en commençant par la racine
}