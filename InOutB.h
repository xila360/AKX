#ifndef INOUTB_H
#define INOUTB_H

#include "Arduino.h"


// Inclure la classe In
class In {
public:
    // Constructeur prenant le numéro de la broche en paramètre
    In(int pin) : _pin(pin) {
        pinMode(_pin, INPUT);
    }

    // Méthode pour lire l'état de la broche
    int read() const {
        return digitalRead(_pin);  // Lit l'état de la broche (HIGH ou LOW)
    }
	
    // Surcharge de l'opérateur [] pour renvoyer l'état de la broche
    int operator[](int index) const {
        if (index == 0) {
            return digitalRead(_pin) == LOW ? 1 : 0;  // 0 si LOW, 1 si HIGH
        } else if (index == 1) {
            return digitalRead(_pin) == HIGH ? 1 : 0;  // 1 si HIGH, 0 si LOW
        }
    }

    // Méthode pour lire l'état inversé de la broche
    bool readInverted() const {
        return !digitalRead(_pin);  // Inverse l'état de la broche
    }

    // Conversion booléenne pour évaluer les expressions comme un booléen
    operator bool() const {
        return read();  // Convertit en booléen en fonction de l'état de la broche
    }

private:
    int _pin; // numéro de la broche associée à l'entrée
};

// Classe pour les sorties
class Out {
public:
    // Constructeur prenant le numéro de la broche en paramètre
    Out(int pin) : pin(pin) {
        pinMode(pin, OUTPUT);
    }

    // Surcharge de l'opérateur = pour allumer ou éteindre la LED
    void operator=(int state) {
        digitalWrite(pin, state ? HIGH : LOW);
    }

private:
    int pin; // numéro de la broche associée à la sortie
};

// Classe pour gérer les entrées analogiques
class AI {
public:
    AI(int pin) : _pin(pin) {
        pinMode(_pin, INPUT);
    }

    // Lire une valeur analogique
    int read() const {
        return analogRead(_pin);
    }

    // Surcharge de l'opérateur () pour retourner la valeur lue
    operator int() const {
        return read();
    }

private:
    int _pin;
};

// Classe pour gérer les sorties analogiques (PWM)
class AO {
public:
    AO(int pin) : _pin(pin) {
        pinMode(_pin, OUTPUT);
    }

    // Écrire une valeur PWM (entre 0 et 255)
    void write(int value) const {
        value = constrain(value, 0, 255); // Limiter la valeur entre 0 et 255
        analogWrite(_pin, value);
    }

    // Surcharge de l'opérateur () pour écrire une valeur PWM
    void operator()(int value) const {
        write(value);
    }

    // Surcharge pour écrire directement la valeur d'une entrée analogique
    void operator()(const AI &analogInput) const {
        int pwmValue = map(analogInput.read(), 0, 1023, 0, 255);
        write(pwmValue); // Utiliser la méthode write pour éviter la redondance
    }

private:
    int _pin;
};

#endif
