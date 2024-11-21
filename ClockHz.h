#ifndef CLOCKHZ_H
#define CLOCKHZ_H

#include "Arduino.h"

class ClockS {
public:
    ClockS(int frequency) : frequency(frequency), lastToggle(0), state(false) {}

    void update() {
        unsigned long currentMillis = millis();
        if (currentMillis - lastToggle >= 1000 / frequency) {
            lastToggle = currentMillis;
            state = !state;  // Change l'état (allumé ou éteint) à chaque période
        }
    }

    operator bool() const {
        return state;
    }

private:
    int frequency;            // Fréquence de clignotement en Hz
    unsigned long lastToggle; // Temps de la dernière inversion d'état
    bool state;               // État courant (allumé ou éteint)
};

class ClockD {
public:
    ClockD(int minHz, int maxHz) : minHz(minHz), maxHz(maxHz), lastUpdate(0), currentHz(minHz), directionUp(true) {}

    void update() {
        unsigned long currentMillis = millis();
        unsigned long elapsedTime = currentMillis - lastUpdate;

        if (elapsedTime >= 1000) {  // 1 seconde pour inverser
            directionUp = !directionUp;
            lastUpdate = currentMillis;
            elapsedTime = 0;
        }

        float progress = (float)elapsedTime / 1000.0;

        if (directionUp) {
            currentHz = minHz + progress * (maxHz - minHz);
        } else {
            currentHz = maxHz - progress * (maxHz - minHz);
        }

        // Toggle l'état selon la fréquence actuelle
        if (currentMillis - lastToggle >= 1000 / currentHz) {
            lastToggle = currentMillis;
            state = !state;
        }
    }

    operator bool() const {
        return state;
    }

private:
    int minHz, maxHz;
    int currentHz;
    bool directionUp;
    unsigned long lastUpdate, lastToggle;
    bool state;
};


class ClockT {
public:
    ClockT(int minHz, int maxHz, unsigned long transferTime)
        : minHz(minHz), maxHz(maxHz), transferTime(transferTime), lastUpdate(0), lastToggle(0), currentHz(minHz), directionUp(true) {}

    void update() {
        unsigned long currentMillis = millis();
        unsigned long elapsedTime = currentMillis - lastUpdate;

        if (elapsedTime >= transferTime) {
            directionUp = !directionUp;
            lastUpdate = currentMillis;
            elapsedTime = 0;
        }

        float progress = (float)elapsedTime / (float)transferTime;

        if (directionUp) {
            currentHz = minHz + progress * (maxHz - minHz);
        } else {
            currentHz = maxHz - progress * (maxHz - minHz);
        }

        if (currentMillis - lastToggle >= 1000 / currentHz) {
            lastToggle = currentMillis;
            state = !state;
        }
    }

    operator bool() const {
        return state;
    }

private:
    int minHz, maxHz;
    unsigned long transferTime, lastUpdate, lastToggle;
    int currentHz;
    bool directionUp, state;
};


#endif
