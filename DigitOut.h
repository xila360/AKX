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

    // D�marre la s�quence d'allumage
    void start() {
	
		if (_ctuITERATE == 0){_ctuITERATE = -1;}
        if (_isRunning) return; // Emp�che de d�marrer plusieurs fois
        _isRunning = true;
		}

    // Arr�te la s�quence d'allumage
    void stop() {
        _isRunning = false;
        digitalWrite(_pin, LOW); // Assure que la LED est �teinte
    }

    // Boucle principale
    void loop() {
        if (!_isRunning || _ctuITERATE == 0) return; // Si non actif, sortir
		Serial.println("A");
        // Phase d'allumage progressif
        for (int A = 00; A <= _maxPeriod; A++) {
            digitalWrite(_pin, HIGH);  // Allume la LED
            delayMicroseconds(A);      // Dur�e d'allumage
            digitalWrite(_pin, LOW);   // �teint la LED
            delayMicroseconds(_maxPeriod - A); // Dur�e d'extinction
            // Serial.println(A);         // Affiche la valeur d'intensit�
        }
		Serial.println("B");
        // Phase d'extinction progressive
        for (int A = _maxPeriod; A >= 00; A--) {
            digitalWrite(_pin, HIGH);  // Allume la LED
            delayMicroseconds(A);      // Dur�e d'allumage
            digitalWrite(_pin, LOW);   // �teint la LED
            delayMicroseconds(_maxPeriod - A); // Dur�e d'extinction
            // Serial.println(A);         // Affiche la valeur d'intensit�
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
    int _maxPeriod;     // Dur�e maximale pour un cycle d'allumage/extinction
	int _ctuITERATE;	// Nombre d'iteration demmand�
	int _ITERATE;		// Nombre d'iteration
	int _ITERATEpass;	// Nombre d'iteration passe
    bool _isRunning;    // Statut du d�marrage
};

#endif
