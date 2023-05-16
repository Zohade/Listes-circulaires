// Liste circulaire double
#include <iostream>

using namespace std;
typedef struct Cellule Cellule;
struct Cellule
{
    int val;
    Cellule * before;
    Cellule * next;
};
typedef struct ListeCirc ListeCirc;
struct ListeCirc
{
    int taille;
    int id;
    Cellule * tete;
};

/**
    IMPLEMENTATION DES FONCTIONS CRUD
*/
/** Détermine le nombre d ’éléments de la liste
@pre list != null
@post la liste reste inchangée
@return n = | list | , le nombre d ’élément dans la liste
*/

int taille ( ListeCirc toto )
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
int estVide ( ListeCirc toto )
{
    if(&toto!=NULL)
        return{(toto.taille==0)?1:0};
}
/** Initialise la liste list en lui attribuant le numéro number
@pre list != NULL
@post list est initialisée et porte le numéro number
@result -
*/
void initList ( ListeCirc * toto , int number )
{
        if(toto==NULL)
        {
            exit(EXIT_FAILURE);
        }
        toto->taille=0;
        toto->id=number;
        toto->tete= new Cellule;
        toto->tete->next=toto->tete;
        toto->tete->before=toto->tete;
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
void ajouteDebut(ListeCirc * toto, int valeur)
{
    if(toto==NULL)
    {
        exit(EXIT_FAILURE);
    }
    Cellule * ajout=new Cellule;
    ajout->val=valeur;
    ajout->next=toto->tete->next;
    toto->tete->next->before=ajout; 
    toto->tete->next=ajout;
    ajout->before=toto->tete;
    toto->taille+=1;
}

/** Ajoute la valeur val à la fin de la liste
@pre list != NULL
@post list devient list + Cellule ( val ) à la derni è re position
@result -
*/
void ajouteFin(ListeCirc * toto, int valeur)
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
        ajout->before=cur->next;
        ajout->next=toto->tete;
        toto->tete->before=ajout;
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
void ajoutePosition ( ListeCirc * toto , int valeur , int n )
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
        ajout->before=cur->next;
        ajout->next=reste;
        reste->before=ajout;
        toto->taille+=1;
    }
}

/** Supprime la première Node de la liste list
@pre list != NULL
@post list devient list ’ qui est la list sans son premier
élément
@result -
*/
void supprimeDebut(ListeCirc * toto)
{
    if(&toto==NULL)
    {
        exit(EXIT_FAILURE);
    }
    if(toto->taille>0)
    {
        Cellule * suppri=toto->tete->next;
        toto->tete->next=toto->tete->next->next;
        toto->tete->next->next->before=toto->tete;
        delete suppri;
        toto->taille-=1;
    }
}

/** Supprime la dernière Cellule de la liste list
@pre list != NULL
@post list devient list ’ qui est la list sans son dernier élément
@result -
*/
void supprimerFin(ListeCirc * toto)
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
    toto->tete->before=cur;
    delete suppri;
    toto->taille-=1;
}
/** Supprime la Cellule de la position pos dans la liste list
@pre list != NULL
@post list devient list ’ qui est la list sans son pos i è me é l é ment
@result -
*/
void supprimerPosition(ListeCirc * toto, int pos)
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
        reste->before=cur;
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
void detruitList ( ListeCirc * toto )
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
ListeCirc * unnion(ListeCirc A, ListeCirc B, int n)
{
    ///STEP1
    ListeCirc *C=new ListeCirc;
    initList(C,n);
    ///STEP2
    if(C==NULL || &A==NULL || &B==NULL)
    {
        exit(EXIT_FAILURE);
    }

    ///STEP3
    Cellule* cur=A.tete;
    int i=0;
    while(i<A.taille)
    {
        ajouteDebut(C,cur->val);
        cur=cur->next;
        i++;
    }
    delete cur;
    Cellule * actuel=B.tete;
    int j=0;
    while(j<B.taille)
    {
        ajouteFin(C,actuel->val);
        actuel=actuel->next;
        j++;
    }
    delete actuel;
    return C;
}










/**
Fonction d'affichage de la liste
*/
void afficher(ListeCirc toto)
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



int main ()
{
    ListeCirc * coco= new ListeCirc;
    initList(coco,0);
    cout<<taille(*coco);
    ajouteDebut(coco, 2);
    ajouteFin(coco, 6);
    ajoutePosition(coco, 4,1);
    cout<<taille(*coco);
    cout<<endl;
    supprimeDebut(coco);
    supprimerFin(coco);
    supprimerPosition(coco,1);
    afficher(*coco);

}
