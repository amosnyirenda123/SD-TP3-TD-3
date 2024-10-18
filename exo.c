#include <stdlib.h>
#include <stdio.h>



FILE* ouvrir_fichier(char nom[], char mode[] ){
    FILE *ptr_f;

    ptr_f = fopen(nom, mode);
    if(ptr_f == NULL){
        perror("Impossible d'ouvrir le fichier.");
        return NULL;
    }else{
        return ptr_f;
    }
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");  
    #else
        system("clear");  
    #endif
}

void creer_fichier_txt(char produits[][3][30], int nombre_produits ){

    FILE *ptr_f = ouvrir_fichier("produits.txt", "w");
    int i;

    fprintf(ptr_f, "Nom |  Prix  |  Quantite  |\n");
    fprintf(ptr_f, "-----------------------------------\n");

    for(i = 0; i < nombre_produits; i++){
        clear_screen();
        printf("Ajouter un nouveau Produit.\n");
        printf("Entrez le nom du produit: ");
        scanf("%s", produits[i][0]);
        printf("Entrez le prix du produit: ");
        scanf("%s", produits[i][1]);
        printf("Entrez la quantite du produit: ");
        scanf("%s", produits[i][2]);
    }

    for(i = 0; i < nombre_produits; i++){
        fprintf(ptr_f, "%s    |   %s   |   %s   |\n", produits[i][0], produits[i][1], produits[i][2]);
        printf("Produit ajoute avec success : %s \n", produits[i][0]);
    }   

    fclose(ptr_f);
    
}

void afficher_produits(){
    FILE *ptr_f = ouvrir_fichier("produits.txt", "r");
    int i;
    char nom[30], prix[30], quantity[30], buffer[100];

    fgets(buffer, sizeof(buffer), ptr_f);
    fgets(buffer, sizeof(buffer), ptr_f);

    printf("Nom |  Prix  |  Quantity  |\n");
    printf("-----------------------------------\n");

    while (fscanf(ptr_f, "%s | %s | %s\n", nom, prix, quantity) == 3) {
        printf("%s    |   %s   |   %s   |\n", nom, prix, quantity);
    }

    fclose(ptr_f);
}

void ajouter_produit(){
    FILE *ptr_f = ouvrir_fichier("produits.txt", "a");

    char nom[20];
    int quantity;
    float price;

    clear_screen();
    printf("Ajouter un nouveau Produit.\n");
    printf("Entrez le nom du produit: ");
    scanf("%s", nom);
    printf("Entrez le prix du produit: ");
    scanf("%f", &price);
    printf("Entrez la quantite du produit: ");
    scanf("%d", &quantity);

    fprintf(ptr_f, "%s    |   %.2f   |   %d   |\n", nom, price, quantity);
    fclose(ptr_f);
    printf("Produit ajoute avec success : %s \n", nom);

}

float calculer_valeur_totale(float** produits, int nombre_produits) {
    float somme = 0;
    int i;
    
    for (i = 0; i < nombre_produits; i++) {
        somme += produits[i][0] * produits[i][1];  
    }

    return somme;
}


float** lire_fichier_txt(){
    int nombre_produits = 6;
    float **ptr_tableau;

    ptr_tableau = (float**)malloc(nombre_produits * sizeof(float*));

    for (int i = 0; i < nombre_produits; i++) {
        ptr_tableau[i] = (float*)malloc(2 * sizeof(float)); 
    }

    FILE *ptr_f = ouvrir_fichier("produits.txt", "r");
    int i;
    char nom[30], prix[30], quantity[30], buffer[100];

    fgets(buffer, sizeof(buffer), ptr_f);
    fgets(buffer, sizeof(buffer), ptr_f);

    for(i = 0; i < nombre_produits; i++){
        fscanf(ptr_f, "%s | %s | %s\n", nom, prix, quantity);
        ptr_tableau[i][0] = atof(prix);
        ptr_tableau[i][1] = atoi(quantity);
    }
    
    fclose(ptr_f);
    return ptr_tableau;

}

int main(){
    int nombres_des_produits = 6;
    char produits[nombres_des_produits][3][30];
    printf("Valeur totale des produits: $%.2f", calculer_valeur_totale(lire_fichier_txt(), nombres_des_produits ));
    // creer_fichier_txt(produits, nombres_des_produits);
    // afficher_produits();
    // ajouter_produit();
    // lire_fichier_txt();
    return 0;
    
}