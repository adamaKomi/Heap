#include "Tree.h"
#include <chrono>

Tree::Tree()// le constructeur
{
    this->root = nullptr;
}




// verifier si l'arbre est vide
bool Tree::isEmpty() const
{
    return this->root == nullptr;
}




// fonction pour inserer une valeur
void Tree::push(int val)
{
    // mesurer le debut de l'operation d'insertion
    auto debut = std::chrono::high_resolution_clock::now();

    // si l'arbre est vide, on crée un noeud
    if (isEmpty()) {
        this->root = new Node(val);
        return;
    }

    // Ajout en parcourant l'arbre
    Node* tmp = this->root;
    while (true) {

        // ajouter a gauche
        if (val < tmp->val) {
            if (!tmp->fg) {
                tmp->fg = new Node(val);
                break;
            }
            else {
                tmp = tmp->fg;
            }
        }
        // ajouter a droite
        else {
            if (!tmp->fd) {
                tmp->fd = new Node(val);
                break;
            }
            else {
                tmp = tmp->fd;
            }
        }
    }

    // mesurer la fin de l'operation d'insertion
    auto fin = std::chrono::high_resolution_clock::now();
    // compter la duree totale de l'insertion en microsecondes
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut);

    //std::cout << "Duree de l'insertion de \""<<val<<"\" : "<< duration.count() << " microsecondes" << std::endl;

    // mesurer le debut de l'operation de reamenagement
    debut = std::chrono::high_resolution_clock::now();

    // reorganiser l'arbre pour avoir le minimum a la racine
    this->organize();

    // mesurer la fin de l'operation de reamenagement
    fin = std::chrono::high_resolution_clock::now();
  
    // compter la duree totale du reamenagement en microsecondes
    duration = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut);

    //std::cout << "Duree de reamenagement : " << duration.count() << " microsecondes" << std::endl;
    //std::cout<< std::endl;
}




// fonction qui permet de changer les noeud de façon recursive
void Tree::change(Node* tmp, int& check)
{
    //std::cout << "Avant organisation :" << std::endl;
    //this->printTree();

    if (tmp == nullptr) return;

    // si le noeud a deux fils, on echange avec le plus petit
    if (tmp->fg && tmp->fd)
    {
        // le fils gauche est plus petit
        if ((tmp->fg->val < tmp->val) && (tmp->fg->val <= tmp->fd->val))
        {
            swap(tmp->val, tmp->fg->val);
            check = 1;
        }
        // le fils droit est plus petit
        else if ((tmp->fd->val < tmp->val) && (tmp->fd->val <= tmp->fg->val))
        {
            swap(tmp->val, tmp->fd->val);
            check = 1;
        }
    }

    else // si le noeud a un seul fils gauche, on echange si le fils est plus petit
    if (tmp->fg && (tmp->fg->val < tmp->val)) {
        swap(tmp->val, tmp->fg->val);
        check = 1;
    }
    else // si le noeud a un seul fils droit, on echange si le fils est plus petit
    if (tmp->fd && (tmp->fd->val < tmp->val)) {
        swap(tmp->val, tmp->fd->val);
        check = 1;
    }

    // Récurse sur les fils
    change(tmp->fg, check);
    change(tmp->fd, check);
}




// fonction pour reorganiser tout l'arbre pour avoir le minimum a la racine
void Tree::organize()
{
    Node* tmp;
    int check;// pour verifier s'il y a encore du changement a faire dans l'arbre

    // on doit boucler jusqu'a ce qu'il n'y ait plus d'echange a faire
    do
    {
        check = 0;
        tmp = this->root;
        change(tmp, check);
    } while (check != 0);

    return;
}




// fonction pour supprimer un noeud
void Tree::deleteNode(Node*& root)
{
    // si le noeud a un fils droit, on fait le remplacement et on supprime
    if (root->fd) {
        Node* tmp = root->fd;
        Node* parent = root;

        while (tmp->fg) {// chercher le fils le plus a gauche
            parent = tmp;
            tmp = tmp->fg;
        }
        root->val = tmp->val; // remplacer
        if (parent->fg == tmp) parent->fg = tmp->fd;
        else parent->fd = tmp->fd;

        delete tmp;
        tmp = nullptr;
        organize();
        return;
    }
    // si le noeud a un fils gauche, on fait le remplacement et on supprime
    else if (root->fg)
    {

        Node* tmp = root->fg;
        Node* parent = root;

        while (tmp->fd) {// chercher le fils le plus a gauche
            parent = tmp;
            tmp = tmp->fd;
        }
        root->val = tmp->val; // remplacer
        if (parent->fd == tmp) parent->fd = tmp->fg;
        else parent->fg = tmp->fg;

        delete tmp;
        tmp = nullptr;
        organize();
        return;
    }
    // si le noeud n'a pas de fils, on le supprime
    else
    {

        delete root;
        root = nullptr;
        return;
    }
}




// fonction pour retirer une valeur a la racine
int Tree::pop()
{
    // veirifier si l'arbre est vide
    if (isEmpty())
    {
        std::cout << "Erreur : arbre vide" << std::endl;
        return -1;
    }

    Node* tmp = this->root;
    int val = tmp->val;

    // si le noeud n'a pas de fils, on supprime le noeud
    if (!this->root->fd && !this->root->fg)
    {
        delete this->root;
        this->root = nullptr;
        return val;
    }
    // si le noeud n'a pas de fils droit, le fils gauche devient la racine
    if (!this->root->fd )
    {
        tmp = this->root;
        this->root = this->root->fg;
        delete tmp;
        tmp = nullptr;
        return val;
    }
    // si le noeud n'a pas de fils gauche, le fils droit devient la racine
    if (!tmp->fg)
    {
        tmp = this->root;
        this->root = this->root->fd;
        delete tmp;
        tmp = nullptr;
        organize();
        return val;
    }

    // si le noeud a deux fils, on le remplace par le plus petit de ses fils

    if (this->root->fd->val < this->root->fg->val)// le fils droit est le minimun des fils
    {

        swap(this->root->val, this->root->fd->val);
        deleteNode(this->root->fd);// permet de supprimer le fils droit
        return val;
    }
    else// le fils gauche est le minimun des fils
    {
        swap(this->root->val, this->root->fg->val);
        deleteNode(this->root->fg);// permet de supprimer le fils gauche
        return val;
    }
    organize();
    return val;// retourner la valeur de la racine
}




// Fonction pour afficher l'arbre sous forme d'arbre
void Tree::print(Node* root, int space, int indent) {
    if (root == nullptr) return;

    // Augmenter l'espace entre les niveaux
    space += indent;

    // Afficher le sous-arbre droit
    print(root->fd, space);

    // Afficher le nœud courant avec le bon espacement
    cout << endl;
    for (int i = indent; i < space; i++) cout << " ";
    cout << root->val << endl;

    // Afficher le sous-arbre gauche
    print(root->fg, space);
}




// fonction d'affichage de l'arbre
void Tree::printTree()
{
    // si l'arbre est vide
    if (isEmpty()) {
        cout << "Arbre vide!" << endl;
        return;
    }

    int space = 0, indent = 4;
    print(this->root, space, indent);// afficher l'arbre sous forme d'arbre
}
