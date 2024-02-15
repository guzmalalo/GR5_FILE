#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maillon
struct v{
    char immat[10];
    int type;

    struct v * suivante;
};
typedef struct v Voiture;

// File
struct f {
    // nombre de voitures
    int n;

    Voiture * first;
    Voiture * last;
};
typedef struct f File;

// initialiser une voiture
Voiture * initVoiture(char * immat, int type);

// Ajouter
void ajouter(File * voitures, char * immat, int type);

// afficher File
void afficherFile(File voitures);

// Affiche voiture
void afficherVoiture(Voiture v);

// liberation
void vider(File * voitures);

// piocher procedure
void piocherP(File * voitures, Voiture** v);

// piocher fonction
Voiture * piocherF(File * voitures);


int main() {
    File voitures = {0, NULL, NULL};
    Voiture * pioche = NULL;

    ajouter(&voitures, "1111",1);
    ajouter(&voitures, "2222",2);
    ajouter(&voitures, "3333",3);
    ajouter(&voitures, "4444",4);

    afficherFile(voitures);
    printf("Nb Voitures %d\n", voitures.n);

    pioche = piocherF(&voitures);

    afficherFile(voitures);
    printf("Nb Voitures %d\n", voitures.n);

    afficherVoiture(*pioche);
    free(pioche);

    vider(&voitures);

    afficherFile(voitures);

    return 0;
}

Voiture * initVoiture(char * immat, int type){
    Voiture * newV = malloc(sizeof(Voiture));

    // initialisation
    strcpy(newV->immat, immat);
    newV->type = type;

    newV->suivante = NULL;

    return newV;
}

void ajouter(File * voitures, char * immat, int type){
    Voiture * newV = initVoiture(immat, type);

    if(voitures->first == NULL || voitures->last == NULL){
        // liste vide
        voitures->first = newV;
        voitures->last =  newV;
    } else{
        // au moins un élément
        voitures->last->suivante = newV;
        voitures->last = newV;
    }

    voitures->n++;

}

void afficherFile(File voitures){
    if(voitures.first == NULL || voitures.last == NULL) {
        printf("La liste es vide\n");
        return;
    }
    printf("First\n");
    while (voitures.first != NULL){
        afficherVoiture(*(voitures.first));
        voitures.first = voitures.first->suivante;
    }
    printf("Last\n");
}

void afficherVoiture(Voiture v){
    printf("Voiture : %s, type: %d\n",v.immat, v.type);
}

Voiture * piocherF(File * voitures){

    if(voitures->first == NULL || voitures->last == NULL){
        return NULL;
    }

    Voiture * temp = voitures->first;
    // modify the head
    voitures->first = temp->suivante;
    temp->suivante = NULL;

    // verify if the head is NULL --> we have no element in the list
    if(voitures->first == NULL){
        voitures->last = NULL;
    }

    voitures->n--;

    return temp;

}

void piocherP(File * voitures, Voiture ** v){
    *v = voitures->first;

    if (voitures->first!=NULL){
        voitures->first = (*v)->suivante;
        (*v)->suivante = NULL;
    }

    // si fin de liste
    if (voitures->first==NULL){
        voitures->last=NULL;
    }

}

// liberation
void vider(File * voitures){
    Voiture * temp;

    while(voitures->first!=NULL){
        temp = piocherF(voitures);
        free(temp);
    }


}



void freeRec(Voiture * v) {

    if (v == NULL) {
        return;
    }

    freeRec(v->suivante);
    free(v);
}


int nbElements(Voiture * v){

    if (v== NULL){
        return 0;
    }

    return 1 + nbElements(v->suivante);
}
