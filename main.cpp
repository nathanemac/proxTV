#include <iostream>
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
#define NOMATLAB
// Include the headers
#include "src/TVopt.h"  
#include "src/LPopt.h"  

int main() {
    std::cout << "Programme démarré..." << std::endl;

    // Paramètres pour la fonction PN_LPp
    int n = 10;  // Taille du tableau
    double lambda = 1.0;  // Paramètre lambda
    double p = 2.34;  // Paramètre de la norme LPp
    double objGap = 0.0001;  // Objectif de précision
    int positive = 1;  // Indicateur de contrainte de positivité (0 = pas de contrainte)

    // Allocation des tableaux pour les données d'entrée et de sortie
    double y[n];  // Signal d'entrée
    double x[n];  // Résultat de la fonction
    double info[3];  // Informations supplémentaires (par exemple nombre d'itérations)

    // Initialisation du générateur de nombres aléatoires
    srand(static_cast<unsigned>(time(0)));  // Initialise le générateur avec le temps courant

    // Remplissage du tableau y avec des valeurs aléatoires
    for (int i = 0; i < n; ++i) {
        y[i] = static_cast<double>(rand()) / RAND_MAX;  // Génère un nombre entre 0 et 1
    }

    // Affichage du tableau y généré
    std::cout << "Vecteur y aléatoire: ";
    for (int i = 0; i < n; ++i) {
        std::cout << y[i] << " ";
    }
    std::cout << std::endl;

    // Création d'un Workspace (structure spécifique à la bibliothèque)
    Workspace* ws = newWorkspace(n);  // Appel à la fonction de création du Workspace

    // Appel de la fonction TV
    int result = TV(y, lambda, x, info, n, p, ws);

    // Vérification des résultats
    std::cout << "Résultat de la fonction TV: " << result << std::endl;

    std::cout << "Solution x: ";
    for (int i = 0; i < n; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Info: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << info[i] << " ";
    }
    std::cout << std::endl;

    // Nettoyage du Workspace
    //if (ws != NULL) {
    //    freeWorkspace(ws);  // Libération de la mémoire allouée au Workspace
    //}

    std::cout << "Test terminé." << std::endl;

    return 0;
}