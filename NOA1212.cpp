#include "NOA1212.h"

NOA1212::NOA1212(int pinGB1, int pinGB2, int pinIOUT, unsigned long resistor) {
  _pinGB1 = pinGB1;
  _pinGB2 = pinGB2;
  _pinIOUT = pinIOUT;
  _resistor = resistor;
  pinMode(_pinGB1, OUTPUT);
  pinMode(_pinGB2, OUTPUT);
  pinMode(_pinIOUT, INPUT);

  setPowerDown();
}

NOA1212::~NOA1212()
{

}

void NOA1212::setPowerDown() {
  setPowerUp(NOA1212::PowerMode::Off);
}

void NOA1212::setPowerUp(PowerMode mode) {
  switch (mode) {
    case NOA1212::PowerMode::LowGain:
      digitalWrite(_pinGB1, HIGH);
      digitalWrite(_pinGB2, HIGH);
    break;
    case NOA1212::PowerMode::MediumGain:
      digitalWrite(_pinGB1, LOW);
      digitalWrite(_pinGB2, HIGH);
    break;
    case NOA1212::PowerMode::HighGain:
      digitalWrite(_pinGB1, HIGH);
      digitalWrite(_pinGB2, LOW);
    break;
    case NOA1212::PowerMode::Off:
      digitalWrite(_pinGB1, LOW);
      digitalWrite(_pinGB2, LOW);
    break;
  }
  _currentMode = mode;
}

unsigned int NOA1212::read() {
  unsigned long lux = 0;
  unsigned int value = analogRead(_pinIOUT);
  unsigned long constante = 0; // La constante est calculée par rapport à la table
                              // donnée dans la datasheet
                              // Cst = (100Lux) / (OutputCurrent)

  switch (_currentMode) {
    case NOA1212::PowerMode::LowGain:
      constante = 100/(51/1000000.0);   // 100Lux => 51uA
    break;
    case NOA1212::PowerMode::MediumGain:
      constante = 100/(4.9/1000000.0);  // 100Lux => 4.9uA
    break;
    case NOA1212::PowerMode::HighGain:
      constante = 100/(0.54/1000000.0); // 100Lux => 0.54uA
    break;
    case NOA1212::PowerMode::Off:
      constante = 0;
    break;
  }

  // Les Lux sont calculés avec cette formule
  // Lux = Vout * cst * (1/RL)
  lux = value * constante * (1.0/_resistor);

  return lux;
}
