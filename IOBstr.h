#ifndef IOBSTR_H
#define IOBSTR_H

#include "Arduino.h"
#include "InOutB.h"    // Pour la classe Out
#include "ESP8266GLB.h" // Inclure le fichier contenant ESPO

class IOBstr {
public:
    IOBstr(bool value) : _value(value) {}

    // Surcharge de l'opérateur `&&` pour combiner des états
    IOBstr operator&&(const IOBstr &other) const {
        return IOBstr(_value && other._value);
    }

    // Surcharge de l'opérateur `||` pour combiner des états logiques OU
    IOBstr operator||(const IOBstr &other) const {
        return IOBstr(_value || other._value);
    }

    // Surcharge de l'opérateur `==` pour affecter l'état d'une sortie (Out ou ESPO)
    template <typename T>
    void operator==(T &led) const {
        led = (_value ? HIGH : LOW);
    }

    // Conversion booléenne pour évaluer les expressions comme un booléen
    operator bool() const {
        return _value;
    }

private:
    bool _value; // Valeur stockée pour l'état
};

#endif
