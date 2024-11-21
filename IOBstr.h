#ifndef IOBSTR_H
#define IOBSTR_H

#include "Arduino.h"
#include "InOutB.h"    // Pour la classe Out
#include "ESP8266GLB.h" // Inclure le fichier contenant ESPO

class IOBstr {
public:
    IOBstr(bool value) : _value(value) {}

    // Surcharge de l'op�rateur `&&` pour combiner des �tats
    IOBstr operator&&(const IOBstr &other) const {
        return IOBstr(_value && other._value);
    }

    // Surcharge de l'op�rateur `||` pour combiner des �tats logiques OU
    IOBstr operator||(const IOBstr &other) const {
        return IOBstr(_value || other._value);
    }

    // Surcharge de l'op�rateur `==` pour affecter l'�tat d'une sortie (Out ou ESPO)
    template <typename T>
    void operator==(T &led) const {
        led = (_value ? HIGH : LOW);
    }

    // Conversion bool�enne pour �valuer les expressions comme un bool�en
    operator bool() const {
        return _value;
    }

private:
    bool _value; // Valeur stock�e pour l'�tat
};

#endif
