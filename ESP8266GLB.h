#ifndef ESP8266GLB_H
#define ESP8266GLB_H

#include "Arduino.h"
#include "InOutB.h" // Assurez-vous d'inclure la définition de la classe Out
#include "ClockHz.h"
#include "IOBstr.h"

// Définition des pins D0 à D8
#define D0 16  // GPIO16
#define D1 5   // GPIO5
#define D2 4   // GPIO4
#define D3 0   // GPIO0
#define D4 2   // GPIO2
#define D5 14  // GPIO14
#define D6 12  // GPIO12
#define D7 13  // GPIO13
#define D8 15  // GPIO15

// ******************************************************
// ******************** ESP8266GLB.h ********************
// ******************************************************

// Classe pour gérer les entrées (Input)
class ESPI {
private:
    int pin;  // Numéro de la broche

public:
    // Constructeur pour initialiser la broche
    ESPI(int pinNumber) : pin(pinNumber) {
        pinMode(pin, INPUT);  // Configurer la broche en tant qu'entrée
    }

    // Méthode pour lire la valeur de la broche
    int read() {
        return digitalRead(pin);
    }

    // Surcharge de l'opérateur de cast pour permettre une lecture facile
    operator int() {
        return read();
    }
};

// Classe pour gérer les sorties (Output)
class ESPO {
private:
    int pin;  // Numéro de la broche

public:
    // Constructeur pour initialiser la broche
    ESPO(int pinNumber) : pin(pinNumber) {
        pinMode(pin, OUTPUT);  // Configurer la broche en tant que sortie
    }

    // Méthode pour écrire une valeur sur la broche
    void write(int value) {
        digitalWrite(pin, value);
    }

    // Surcharge de l'opérateur d'affectation pour permettre un accès facile
    ESPO& operator=(int value) {
        write(value);
        return *this;
    }
};

#endif