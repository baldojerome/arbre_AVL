#include<iostream>

using namespace std;

/*BALDJ17058609 - BALDO jerome
état : je n'ai pas pu finir l'AVL. Je n'ai pas pu résoudre le probléme de modification
réalisé : rotation simple droite / rotation simple gauche / rotation double gauche / rotation double  droit
affichage du parent -+ des enfants */

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree() { root = NULL; }
    BinarySearchTree(const BinarySearchTree& rhs) { *this = rhs; }

    void insert(const Comparable& x) 
    { 
        BinaryNode* parent = NULL;
        insert(x, parent, root);
    }

    friend ostream& operator<< (ostream& out, const BinarySearchTree& arbre)
    {
        BinaryNode* rootTemp = arbre.root;
        cout << "TYPE\t" << "PARENT\t" << "NOEUD\t" << "DBAL\t" << "ENFGAU\t" << "ENFDROIT" << endl;
        cout << "____\t______\t_____\t_______\t_______\t_______" << endl;
        arbre.imprimer(rootTemp);

        return out;
    }
    //verifie le balancement 
    bool Verif(BinarySearchTree& arbre)
    {
        bool verif = false;
        BinaryNode* rootTemp = arbre.root;
        int verifCompt = arbre.VerifBalancArbre(rootTemp);
        //cout << verifCompt << endl;
        BinaryNode* BalancGauch = VerifBalancNoeud(rootTemp->left);
        BinaryNode* BalancDroit = VerifBalancNoeud(rootTemp->right);
        //if (verifCompt != NULL || (BalancGauch != NULL || BalancDroit != NULL))
        if ((verifCompt < -1 || verifCompt > 1) || (BalancGauch != NULL || BalancDroit != NULL))
        {
            verif = true;
        }
      
        return verif;
    }
    //permet de faire les rotations 
    void VerifBalanc(BinarySearchTree& arbre)
    {
        BinaryNode* rootTemp = arbre.root;
        
        bool verif = Verif(arbre);
        if( verif == 1)
        {
            BinaryNode* noeudCible = VerifNoeud(rootTemp);
            //traiter le cas de la racine 
            if (noeudCible == rootTemp && ((noeudCible->left == NULL && noeudCible->right != NULL) || (noeudCible->left != NULL && noeudCible->right == NULL)))
            {
                //cout << "rotation sur racine" << endl;
                if (noeudCible->left != NULL)
                {
                    //cout << "rotation droite" << endl;
                    BinaryNode* chang = arbre.RotSimplDroit(noeudCible);
                    arbre.root = chang;
                }
                else
                {
                    //cout << "rotation gauche" << endl;
                    BinaryNode* chang = arbre.RotSimplGauche(noeudCible);
                    arbre.root = chang;
                }
            }
            else
            {
                BinaryNode* deltaGauche = NULL;
                BinaryNode* deltaDroit = NULL;
                BinaryNode* delta = NULL;
                //verification du balancement pour les enfants 
                do
                {
                    deltaGauche = BalancNoeud(rootTemp->left);
                    deltaDroit = BalancNoeud(rootTemp->right);

                } while (deltaGauche != NULL && deltaDroit != NULL);
                
                if (deltaGauche != NULL && deltaDroit == NULL)
                {
                    delta = deltaGauche;
                    cout << deltaGauche->element << endl;
                }
                else if(deltaDroit != NULL && deltaGauche == NULL)
                {
                    delta = deltaDroit;
                    
                }
                else if(deltaDroit == NULL && deltaGauche == NULL)
                {
                    delta = rootTemp;
                }

                //cout << "noeud : " << delta->element << endl;
                
                if (delta->left == NULL && delta->right != NULL)
                {
                    //cout << "rotation gauche simple" << endl;
                    BinaryNode* rSG = RotSimplGauche(delta);
                    if (delta == arbre.root)
                    {
                        arbre.root = rSG;
                    }
                    //verification si pas bon alors on relance la methode 
                    BinaryNode* verifRSG = BalancNoeud(arbre.root);
                    if (verifRSG != NULL)
                    {
                        VerifBalanc(arbre);
                    }
                    
                }
                else if (delta->left != NULL && delta->right == NULL)
                {
                    //cout << "rotation droite simple" << endl;
                    BinaryNode* rSD =RotSimplDroit(delta);
                    if (delta == arbre.root)
                    {
                        arbre.root = rSD;
                    }
                    //verification si pas bon alors on relance la methode
                    BinaryNode* verifRSD = BalancNoeud(arbre.root);
                    if ( verifRSD != NULL)
                    {
                        VerifBalanc(arbre);
                    }
                }
                else if (delta->left != NULL && delta->right != NULL)
                {
                    int gauch = HautNoeud(delta->left);
                    int droit = HautNoeud(delta->right);
                    if (gauch > droit)
                    {
                        //cout << "double rot droite" << endl;
                        BinaryNode* dDD = RotDoubleDroit(delta);
                        if (delta == arbre.root)
                        {
                            arbre.root = dDD;
                        }
                        //verification si pas bon alors on relance la methode
                        BinaryNode* verifDDD = BalancNoeud(arbre.root);
                        if ( verifDDD != NULL)
                        {
                            VerifBalanc(arbre);
                        }
                    }
                    else
                    {
                        //cout << "double rot gauch" << endl;
                        BinaryNode* dDG = RotDoubleGauche(delta);
                        if (delta == arbre.root)
                        {
                            arbre.root = dDG;
                        }
                        //verification si pas bon alors on relance la methode
                        BinaryNode* verifDDG = BalancNoeud(arbre.root);
                        if (verifDDG != NULL)
                        {
                            VerifBalanc(arbre);
                        }
                    }
                }
            }   
        }   
    }

    int HauteurArbre(const BinarySearchTree& arbre)
    {
        BinaryNode* rootTemp = arbre.root;
        return HautNoeud(rootTemp);
    }

private:

    // Type de noeuds utilis�s dans l'arbre
    struct BinaryNode
    {
        Comparable element;
        BinaryNode* parent;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable& theElement, BinaryNode* parent, BinaryNode* lt, BinaryNode* rt)
            : element(theElement), parent(parent), left(lt), right(rt) { }
    };

    // Pointeur vers la racine de l'arbre.
    BinaryNode* root;

    BinaryNode* RotSimplDroit(BinaryNode* t)
    {
        
        BinaryNode* tmp;

        tmp = t->left;
        if (tmp->right == NULL)
        {
            tmp->right = t;
            t->left = NULL;
            t->right = NULL;
            tmp->parent = t->parent;
            t->parent = tmp;

            if (tmp->parent != NULL && tmp->parent->left != NULL)
            {
                tmp->parent->right = tmp;
            }
        }
        
        return tmp;
    }

    BinaryNode* RotSimplGauche(BinaryNode* t)
    {
        BinaryNode* tmp;

        tmp = t->right;
        if (tmp->left == NULL)
        {
            tmp->left = t;
            t->left = NULL;
            t->right = NULL;
            tmp->parent = t->parent;
            t->parent = tmp;
            if (tmp->parent != NULL)
            {
                tmp->parent->right = tmp;
            }
        }
        
        return tmp;
    }

    BinaryNode* RotDoubleGauche(BinaryNode* t)
    {
        BinaryNode* temp = t->right;
        if (temp->left != NULL)
        {
            t->right = temp->left;
            temp->left = t;
            temp->parent = t->parent;
            t->parent = temp;
            t->right->parent = t;
        }
        if (temp->left == NULL && temp->parent->parent != NULL)
        {
            temp->left = t;
            t->parent->right = temp;
            temp->parent = t->parent;
            t->parent = temp;
            t->right = NULL;
        }
        return temp;
    }

    BinaryNode* RotDoubleDroit(BinaryNode* t)
    {
        //cout << "je rentre la methode RDD" << endl;
        BinaryNode* temp = t->left;
        
        if (temp->right == NULL && temp->parent->parent != NULL)
        {
            temp->right = t;
            t->left = NULL;
            temp->parent = t->parent;
            temp->parent->right = temp;
            temp->parent = t->parent;
            t->parent = temp;
        }
        
        return temp;
    }
       //permet de verifier le balancement pour un noeud cible 
    BinaryNode* BalancNoeud(BinaryNode* t)
    {
        if (t == NULL)
        {
            return NULL;
        }
        int difference = HautNoeud(t->left) - HautNoeud(t->right);
        if (difference > 1 || difference < -1)
        {
            return t;
        }
        BalancNoeud(t->left);
        BalancNoeud(t->right);
        
    }

    BinaryNode* VerifNoeud(BinaryNode* t)
    {
        if (t == NULL)
        {
            return NULL;
        }
        int  difference = HautNoeud(t->left) - HautNoeud(t->right);
        VerifNoeud(t->left);
        VerifNoeud(t->right);
        if (difference < -1 || difference > 1)
        {
            return t;
        }
        
    }

    BinaryNode* VerifBalancNoeud(BinaryNode* t) const
    {
        if (t == NULL)
        {
            return NULL ;
        }
        
        int delta = VerifBalancArbre(t);
        if (delta < -1 && delta > 1)
        {
            return t->parent;
        }

        VerifBalancNoeud(t->left);
        VerifBalancNoeud(t->right);
        
    }
    //verifie le balancement global 
    int VerifBalancArbre(BinaryNode* t) const
    {
        if (t == NULL)
        {
            return 0;
        }

        int deltaBalance = HautNoeud(t->left) - HautNoeud(t->right);
        
        return deltaBalance;
    }
    //affiche la hauteur d'un noeud 
    int HautNoeud(BinaryNode* t) const
    {
        if (t == NULL)
        {
            return -1;
        }
        int hGauch = HautNoeud(t->left);
        int hDroit = HautNoeud(t->right);

        return 1 + max(hGauch, hDroit);
    }
    //pour afficher les noeud autre la racine de l'arbre 
    void AfficherNoeud(BinaryNode* t) const
    {
        if (t == NULL)
        {
            return;
        }
        BinaryNode* temp = t;
        if (t->left == NULL && t->right != NULL)
        {
            cout << "TYPE\t" << t->parent->element << "\t" << temp->element << "\t0\t" << "-" << "\t" << t->right->element << endl;
        }
        else if (t->left != NULL && t->right == NULL)
        {
            cout << "TYPE\t" << t->parent->element << "\t" << temp->element << "\t0\t" << t->left->element << "\t" << "-" << endl;
        }
        else if (t->left != NULL && t->right != NULL)
        {
            cout << "TYPE\t" << t->parent->element << "\t" << temp->element << "\t0\t" << t->left->element << "\t" << t->right->element << endl;
        }
        else
        {
            cout << "TYPE\t" << t->parent->element << "\t" << temp->element << "\t0\t" << "-" << "\t" << "-" << endl;
        }
    }
    //parcours en largeur 
    void imprimer(BinaryNode*& t) const
    {
        if (t == NULL)
        {
            return;
        }
        if (t == this->root)
        {
            if (t->left == NULL && t->right != NULL)
            {
                cout << "TYPE\t" << "-" << "\t" << t->element << "\t0\t" << "-" << "\t" << t->right->element << endl;
            }
            else if (t->left != NULL && t->right == NULL)
            {
                cout << "TYPE\t" << "-" << "\t" << t->element << "\t0\t" << t->left->element << "\t" << "-" << endl;
            }
            else
            {
                cout << "TYPE\t" << "-" << "\t" << t->element << "\t0\t" << t->left->element << "\t" << t->right->element << endl;
            }
        }
        AfficherNoeud(t->left);
        AfficherNoeud(t->right);
        
        imprimer(t->left);
        imprimer(t->right);
    }
        //prend en compte le parent
    void insert(const Comparable & x, BinaryNode * &parent, BinaryNode * &t)
        {
            if (t == NULL)
                t = new BinaryNode(x, parent, NULL, NULL);
            else if (x < t->element)
                insert(x, t, t->left);
            else if (t->element < x)
                insert(x, t, t->right);
            else
                ;
        }

    };
