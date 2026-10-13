#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    int choice = 0;

    do {
        printf("\n--- MENU SVG ---\n");
        printf("1. Create a shape\n");
        printf("2. Modify a shape\n");
        printf("3. Delete a shape\n");
        printf("4. Save\n");
        printf("5. Load\n");
        printf("6. Visualize (Afficher les formes)\n");
        printf("0. Quit\n");
        printf("Votre choix : ");
        
        scanf("%d", &choice); // Lecture du choix de l'utilisateur

        switch (choice) {
            case 1:
                printf("--> Création d'une forme...\n");
                break;
            case 2:
                printf("--> Modification...\n");
                break;
            case 3:
                printf("--> Suppression...\n");
                break;
            case 4:
                printf("--> Sauvegarde...\n");
                break;
            case 5:
                printf("--> Chargement...\n");
                break;
            case 6:
                printf("--> Affichage...\n");
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choice != 0);
        
    return EXIT_SUCCESS;
}
