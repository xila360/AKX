#ifndef ESP8266GLB_H
#define ESP8266GLB_H

#include "Arduino.h"
#include "InOutB.h" // Assurez-vous d'inclure la d�finition de la classe Out
#include "ClockHz.h"
#include "IOBstr.h"

// D�finition des pins D0 � D8
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

// Classe pour g�rer les entr�es (Input)
class ESPI {
private:
    int pin;  // Num�ro de la broche

public:
    // Constructeur pour initialiser la broche
    ESPI(int pinNumber) : pin(pinNumber) {
        pinMode(pin, INPUT);  // Configurer la broche en tant qu'entr�e
    }

    // M�thode pour lire la valeur de la broche
    int read() {
        return digitalRead(pin);
    }

    // Surcharge de l'op�rateur de cast pour permettre une lecture facile
    operator int() {
        return read();
    }
};

// Classe pour g�rer les sorties (Output)
class ESPO {
private:
    int pin;  // Num�ro de la broche

public:
    // Constructeur pour initialiser la broche
    ESPO(int pinNumber) : pin(pinNumber) {
        pinMode(pin, OUTPUT);  // Configurer la broche en tant que sortie
    }

    // M�thode pour �crire une valeur sur la broche
    void write(int value) {
        digitalWrite(pin, value);
    }

    // Surcharge de l'op�rateur d'affectation pour permettre un acc�s facile
    ESPO& operator=(int value) {
        write(value);
        return *this;
    }
};

#endif