#ifndef FRONT_H
#define FRONT_H

#include "Arduino.h"

class HighFront {
public:
    // Constructeur pour une broche donnée et un type d'IO ("IN" ou "OUT")
    HighFront(int pin, String IO, byte timer) 
        : _pin(pin), _ERRpin(""), _IO(IO), _ERRio(""), _timer(timer), _ERRtimer(""), _lastState(LOW), _currentState(LOW) {
        if (_IO == "IN" || _IO == "In" || _IO == "Input" || _IO == "INPUT") {
            pinMode(_pin, INPUT);
			_ERRio = "INPUT";
        } else if (_IO == "OUT" || _IO == "Out" || _IO == "Output" || _IO == "OUTPUT") {
            pinMode(_pin, OUTPUT);
			_ERRio = "OUTPUT";
        } else {_ERRio = "#ERR_TYPE";}
		
		if (_timer < 2 ) {
			_timer = 2;
			_ERRtimer = "#ERR_TIME[2]";
		}
		else if  (_timer > 10 ) {
			_timer = 10;
			_ERRtimer = "#ERR_TIME[10]";
		}
		else {
			_timer = _timer;
			_ERRtimer = _timer;
		}
		
		if(_pin <= 54 && _pin >= 1){
			_ERRpin = _pin;
		} else {
			_ERRpin = "#ERR_PIN";
		}
		
		// Initialiser les états à l'état actuel de la broche pour éviter une détection de front
        _lastState = digitalRead(_pin);
        _currentState = _lastState;
		
    }
	
	// verification de la bonne configuration du FRONT
	void Config(){
		Serial.println();
		Serial.println("--------|HighFront|--------");
		Serial.print("Num Pin    : ");Serial.println(_ERRpin);
		Serial.print("Mode I/O   : ");Serial.println(_ERRio);
		Serial.print("Timer High : ");Serial.println(_ERRtimer);
		Serial.println("---------------------------");
	}

    // Méthode pour mettre à jour l'état et vérifier le front montant
    void update() {
		delay(_timer);
        _lastState = _currentState;
        _currentState = digitalRead(_pin);
    }

    // Surcharge de l'opérateur booléen pour détecter un front montant
    operator bool() {
        update();  // Met à jour l'état de la broche
        return (_lastState == LOW && _currentState == HIGH);
    }

private:
    int _pin;           // Broche associée
    String _IO;         // Type d'IO (IN ou OUT)
	byte _timer;		// definir le timer pour eviter les debounce
	String _ERRtimer;	// definir si il y a une erreur de saisie temp
	String _ERRio;		// definir si il y a une erreur de saisie mode
	String _ERRpin;		// definir si il y a une erreur de saisie pin
    int _lastState;     // Dernier état de la broche
    int _currentState;  // État actuel de la broche
};

class LowFront {
public:
    // Constructeur pour une broche donnée et un type d'IO ("IN" ou "OUT")
    LowFront(int pin, String IO, byte timer) 
        : _pin(pin), _ERRpin(""), _IO(IO), _ERRio(""), _timer(timer), _ERRtimer(""), _lastState(LOW), _currentState(LOW) {
        if (_IO == "IN" || _IO == "In" || _IO == "Input" || _IO == "INPUT") {
            pinMode(_pin, INPUT);
			_ERRio = "INPUT";
        } else if (_IO == "OUT" || _IO == "Out" || _IO == "Output" || _IO == "OUTPUT") {
            pinMode(_pin, OUTPUT);
			_ERRio = "OUTPUT";
        } else {_ERRio = "#ERR_TYPE";}
		
		if (_timer < 2 ) {
			_timer = 2;
			_ERRtimer = "#ERR_TIME[2]";
		}
		else if  (_timer > 10 ) {
			_timer = 10;
			_ERRtimer = "#ERR_TIME[10]";
		}
		else {
			_timer = _timer;
			_ERRtimer = _timer;
		}
		
		if(_pin <= 54 && _pin >= 1){
			_ERRpin = _pin;
		} else {
			_ERRpin = "#ERR_PIN";
		}
		
		// Initialiser les états à l'état actuel de la broche pour éviter une détection de front
        _lastState = digitalRead(_pin);
        _currentState = _lastState;
		
    }
	
	// verification de la bonne configuration du FRONT
	void Config(){
		Serial.println();
		Serial.println("--------|LowFront|--------");
		Serial.print("Num Pin    : ");Serial.println(_ERRpin);
		Serial.print("Mode I/O   : ");Serial.println(_ERRio);
		Serial.print("Timer High : ");Serial.println(_ERRtimer);
		Serial.println("--------------------------");
	}

    // Méthode pour mettre à jour l'état et vérifier le front descendant
    void update() {
		delay(_timer);
        _lastState = _currentState;
        _currentState = digitalRead(_pin);
    }

    // Surcharge de l'opérateur booléen pour détecter un front descendant
    operator bool() {
        update();  // Met à jour l'état de la broche
        return (_lastState == HIGH && _currentState == LOW);
    }

private:
    int _pin;           // Broche associée
    String _IO;         // Type d'IO (IN ou OUT)
	byte _timer;		// definir le timer pour eviter les debounce
	String _ERRtimer;	// definir si il y a une erreur de saisie temp
	String _ERRio;		// definir si il y a une erreur de saisie mode
	String _ERRpin;		// definir si il y a une erreur de saisie pin
    int _lastState;     // Dernier état de la broche
    int _currentState;  // État actuel de la broche
};

#endif
