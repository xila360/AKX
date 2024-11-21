#ifndef SERIALPRINT_H
#define SERIALPRINT_H

#include "Arduino.h"

class SerialPrint {
public:
    // M�thode statique pour imprimer une cha�ne de caract�res
    static void printMessage(const char* message) {
        // V�rifie si un des caract�res sp�cifi�s est pr�sent dans la cha�ne
        if ((strchr(message, '.') || strchr(message, ':') || strchr(message, '!') || strchr(message, '?')) && strcmp(message, ".") != 0) {
            Serial.println(message);  // Si le message contient un de ces caract�res, on l'imprime avec un saut de ligne
        } else if (strcmp(message, ".") == 0) {
            Serial.println();  // Si le message est exactement un ".", on imprime un saut de ligne vide
        } else {
            Serial.print(message);  // Sinon, on l'imprime sans saut de ligne
        }
    }
};

// Fonctions globales pour simplifier l'appel
inline void TXT(const char* message) {
    SerialPrint::printMessage(message);  // Appel de la m�thode corrig�e
}

#endif
