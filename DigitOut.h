#ifndef DigitOut_h
#define DigitOut_h

#include <Arduino.h>

class DigitOut {
public:
    // Constructeur
    DigitOut(int pin, int maxPeriod, int ctuITERATE) 
        : _pin(pin), _maxPeriod(maxPeriod), _ctuITERATE(ctuITERATE), _ITERATE(ctuITERATE), _ITERATEpass(0), _isRunning(false) {
        pinMode(_pin, OUTPUT); // Configure la broche comme sortie
		Serial.begin(250000);
    }

    // Démarre la séquence d'allumage
    void start() {
	
		if (_ctuITERATE == 0){_ctuITERATE = -1;}
        if (_isRunning) return; // Empêche de démarrer plusieurs fois
        _isRunning = true;
		}

    // Arrête la séquence d'allumage
    void stop() {
        _isRunning = false;
        digitalWrite(_pin, LOW); // Assure que la LED est éteinte
    }

    // Boucle principale
    void loop() {
        if (!_isRunning || _ctuITERATE == 0) return; // Si non actif, sortir
		Serial.println("A");
        // Phase d'allumage progressif
        for (int A = 00; A <= _maxPeriod; A++) {
            digitalWrite(_pin, HIGH);  // Allume la LED
            delayMicroseconds(A);      // Durée d'allumage
            digitalWrite(_pin, LOW);   // Éteint la LED
            delayMicroseconds(_maxPeriod - A); // Durée d'extinction
            // Serial.println(A);         // Affiche la valeur d'intensité
        }
		Serial.println("B");
        // Phase d'extinction progressive
        for (int A = _maxPeriod; A >= 00; A--) {
            digitalWrite(_pin, HIGH);  // Allume la LED
            delayMicroseconds(A);      // Durée d'allumage
            digitalWrite(_pin, LOW);   // Éteint la LED
            delayMicroseconds(_maxPeriod - A); // Durée d'extinction
            // Serial.println(A);         // Affiche la valeur d'intensité
        }
		Serial.println("C");
		if (_ctuITERATE > 0){
		_ctuITERATE--;
		}
		_ITERATEpass++;
    }
	
    // Boucle Serial.print();
	void Moniteur() {
		if (_ctuITERATE > 0){
		Serial.print("Iteration : ");
		Serial.print("Il reste [ ");
		Serial.print(_ctuITERATE);
		Serial.print(" ] sur [ ");
		Serial.print(_ITERATE);
		Serial.println(" ].");
		}
		else {
			Serial.print("Nombre d'iteration passe : ");
			Serial.println(_ITERATEpass);
		}
	}

private:
    int _pin;           // Pin de la LED
    int _maxPeriod;     // Durée maximale pour un cycle d'allumage/extinction
	int _ctuITERATE;	// Nombre d'iteration demmandé
	int _ITERATE;		// Nombre d'iteration
	int _ITERATEpass;	// Nombre d'iteration passe
    bool _isRunning;    // Statut du démarrage
};

#endif
