#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>

// Inclure les en-têtes nécessaires
#include "src/TVopt.h"
#include "src/LPopt.h"

// Définition d'une structure de contexte
struct Context {

};

// Fonction callback minimaliste
int simple_callback(const double* s_ptr, size_t s_length, double delta_k, void* ctx_ptr) {
    // Ici, nous ne faisons rien de particulier avec s_ptr, delta_k ou ctx_ptr
    // Nous retournons simplement 0 pour continuer l'algorithme
    return 0;
}


int main() {
    // Paramètres pour la fonction TV
    int n = 20;          // Taille du tableau
    double lambda = 0.01; // Paramètre lambda
    double p = 1.7;      // Norme p pour TV
    double objGapTVp = 1e-6; // Précision désirée pour le dual gap

    // Allocation des tableaux pour les données d'entrée et de sortie
    double y[20];      // Signal d'entrée
    double x[20];      // Résultat de la fonction
    double info[3];    // Informations supplémentaires (par exemple, nombre d'itérations, qualité du gap, etc.)

    // Initialisation des données d'entrée avec des valeurs simples
    for (int i = 0; i < n; i++) {
        y[i] = static_cast<double>(i) / n; // Exemple : y[i] = i / n
    }

    // Création du Workspace
    Workspace* ws = newWorkspace(n);

    // Création d'un contexte pour le callback
    Context context;  // Initialisation : itération courante = 0, limite = 10

    // Appel de la fonction TV
    int result = TV(
        y,
        lambda,
        x,
        info,
        n,
        p,
        ws,
        &context,                   // Pointeur vers le contexte
        simple_callback,            // Fonction callback
        objGapTVp                   // Dual gap
    );

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

    // Libération du Workspace
    if (ws != NULL) {
        freeWorkspace(ws);
    }

    std::cout << "Test terminé." << std::endl;

    return 0;
}
