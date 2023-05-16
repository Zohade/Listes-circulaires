//Liste circulaire simple
#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct Cellule Cellule ;
struct Cellule
{
    int val;
    Cellule * next;
};

typedef struct ListeCircular ListeCircular;
struct ListeCircular
{
    int id ;
    int taille;
    Cellule * tete;
} ;

/** Détermine le nombre d ’éléments de la liste
@pre list != null
@post la liste reste inchangée
@return n = | list | , le nombre d ’élément dans la liste
*/

int taille ( ListeCircular toto )
{
    if(&toto!=NULL)
    return toto.taille;
    cout<<"La liste n\'existe pas \n";
}
/** Détermine si la liste est vide
@pre list != null
@post list reste inchangée
@result 1 si list == {} , 0 sinon
*/
int estVide ( ListeCircular toto )
{
    if(&toto!=NULL)
        return{(toto.taille==0)?1:0};
}
/** Initialise la liste list en lui attribuant le numéro number
@pre list != NULL
@post list est initialisée et porte le numéro number
@result -
*/
void initList ( ListeCircular * toto , int number )
{
        if(toto==NULL)
        {
            exit(EXIT_FAILURE);
        }
        toto->taille=0;
        toto->id=number;
        toto->tete= new Cellule;
        toto->tete->next=toto->tete;
}
/**
  ajoute un element au debut de la liste
 * @brief ajouteDebut
 * @param toto
 * @param valeur
 * @pre
        toto est une liste non NULL;
        valeur est un entier
 * @post
        toto->tete devient la nouvelle valeur
        la taille de toto est augmentée
 * @return
        -
        */
void ajouteDebut(ListeCircular * toto, int valeur)
{
    if(toto==NULL)
    {
        exit(EXIT_FAILURE);
    }
    Cellule * ajout=new Cellule;
    ajout->val=valeur;
    ajout->next=toto->tete->next;
    toto->tete->next=ajout;
    toto->taille+=1;
}


/** Ajoute la valeur val à la fin de la liste
@pre list != NULL
@post list devient list + Cellule ( val ) à la derni è re position
@result -
*/
void ajouteFin(ListeCircular * toto, int valeur)
{
    if(toto==NULL)
    {
        exit(EXIT_FAILURE);
    }
    if(toto->taille>0)
    {
        int i=0;
        Cellule * cur=toto->tete;
        while(i<toto->taille)
        {
            cur=cur->next;
            i++;
        } 
        Cellule * ajout= new Cellule;
        ajout->val=valeur;
        cur->next=ajout;
        ajout->next=toto->tete;
        toto->taille+=1;
    }
    else if(toto->taille==0)
    {
        ajouteDebut(toto, valeur);
    }
}
/** Ajoute la valeur val à la position n de la liste
@pre list != NULL
0 <= n <= list -> taille

@post liste devient list + Node ( val ) à
la position n de la liste
@result -
*/
void ajoutePosition ( ListeCircular * toto , int valeur , int n )
{
    if(&toto==NULL)
    {
        exit(EXIT_FAILURE);
    }
    if( n<=toto->taille)
    {
        int i=0;
        Cellule *cur= toto->tete;
        while(i<n-1)
        {
            cur=cur->next;
            i++;
        }
        Cellule *reste=new Cellule;
        Cellule * ajout= new Cellule;
        ajout->val=valeur;
        reste=cur->next;
        cur->next=ajout;
        ajout->next=reste;
        toto->taille+=1;

    }
}

/** Supprime la première Node de la liste list
@pre list != NULL
@post list devient list ’ qui est la list sans son premier
élément
@result -
*/
void supprimeDebut(ListeCircular * toto)
{
    if(&toto==NULL)
    {
        exit(EXIT_FAILURE);
    }
    if(toto->taille>0)
    {
        Cellule * suppri=toto->tete->next;
        toto->tete->next=toto->tete->next->next;
        delete suppri;
        toto->taille-=1;
    }
}

/** Supprime la dernière Cellule de la liste list
@pre list != NULL
@post list devient list ’ qui est la list sans son dernier élément
@result -
*/
void supprimerFin(ListeCircular * toto)
{
    if(&toto==NULL)
    {
        exit(EXIT_FAILURE);
    }
    Cellule * cur=toto->tete;
    int i=0;
    while(i<toto->taille-1)
    {
        cur=cur->next;
        i++;
    }
    Cellule * suppri=cur->next;
    cur->next=toto->tete;
    delete suppri;
    toto->taille-=1;
}
/** Supprime la Cellule de la position pos dans la liste list
@pre list != NULL
@post list devient list ’ qui est la list sans son pos i è me é l é ment
@result -
*/
void supprimerPosition(ListeCircular * toto, int pos)
{
     if(&toto==NULL)
    {
        exit(EXIT_FAILURE);
    }
    if(pos<=toto->taille)
    {
        int i=0;
        Cellule * cur=toto->tete;
        while(i<pos-1)
        {
            cur=cur->next;
            i++;
        }
        Cellule *suppri=cur->next;
        Cellule * reste =cur->next->next;
        cur->next=reste;
        delete suppri;
        toto->taille-=1;
    }
}

/** Destruction de la liste
@pre list != NULL
@post la liste est d é truite , y compris toutes ces Cellules
@return -

STEP1:
    supprimer tous les elements de la liste, en partant du debut
STEP2:
    supprimer la liste en libérant la mémoire allouée à la liste
*/
void detruitList ( ListeCircular * toto )
{
    if (&toto == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while(toto->taille>0)
    {
        supprimeDebut(toto);
    }
    delete toto->tete;
    delete toto;
}
/** Union de deux listes
 @pre
    A et B sont deux listes et n est id de la liste union;
 @post
        C vaut A+B;
        C a pour taille A->taille + B->taille
        C->tete=A->tete
 @return
    C
=========================================================================================
                            STEP
=========================================================================================

STEP1:
    Creation de la liste C en initialisant l'identifiant
    à n;
STEP2:
    verifier que les listes A B et C sont non vides;
STEP3:
    Copie des elements de A dans C avec C->tete=A->tete;
STEP4:
   copie les elements de B dans C
 */
ListeCircular * unnion(ListeCircular A, ListeCircular B, int n)
{
    ///STEP1
    ListeCircular *C=new ListeCircular;
    initList(C,n);
    ///STEP2
    if(C==NULL || &A==NULL || &B==NULL)
    {
        exit(EXIT_FAILURE);
    }

    ///STEP3
    Cellule* cur=A.tete;
    while(cur!=NULL)
    {
        ajouteDebut(C,cur->val);
        cur=cur->next;
    }
    delete cur;
    Cellule * actuel=B.tete;
    while(actuel!=NULL)
    {
        ajouteFin(C,actuel->val);
        actuel=actuel->next;
    }
    delete actuel;
    return C;
}



void afficher(ListeCircular toto)
{
    if(&toto==NULL)
    {
        exit(EXIT_FAILURE);
    }
    if(toto.taille>0)
    {
        int i=0;
        Cellule * cur=toto.tete->next;
        while(i<toto.taille)
        {
            cout<<cur->val<<"->";
            cur=cur->next;
            i++;
        }
    }
    else
    {
        cout<<"NULL";
    }
}


int main()
{
    ListeCircular * coco =new ListeCircular;
    initList(coco, 1);
    ajouteDebut(coco,4);
    ajouteDebut(coco,5);
    ajouteFin(coco, 3);
    ajoutePosition(coco, 6,2);
    afficher(*coco);
    cout<<endl;
    detruitList(coco);
    cout<<coco->taille<<endl;
    afficher(*coco);


    return EXIT_SUCCESS;
}
