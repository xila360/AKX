#ifndef SERIALPRINT_H
#define SERIALPRINT_H

#include "Arduino.h"

class SerialPrint {
public:
    // Méthode statique pour imprimer une chaîne de caractères
    static void printMessage(const char* message) {
        // Vérifie si un des caractères spécifiés est présent dans la chaîne
        if ((strchr(message, '.') || strchr(message, ':') || strchr(message, '!') || strchr(message, '?')) && strcmp(message, ".") != 0) {
            Serial.println(message);  // Si le message contient un de ces caractères, on l'imprime avec un saut de ligne
        } else if (strcmp(message, ".") == 0) {
            Serial.println();  // Si le message est exactement un ".", on imprime un saut de ligne vide
        } else {
            Serial.print(message);  // Sinon, on l'imprime sans saut de ligne
        }
    }
};

// Fonctions globales pour simplifier l'appel
inline void TXT(const char* message) {
    SerialPrint::printMessage(message);  // Appel de la méthode corrigée
}

#endif
