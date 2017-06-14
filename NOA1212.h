#ifndef NOA1212_h
#define NOA1212_h

#include <Arduino.h>

class NOA1212
{
public:
  /**
   * Instancie le capteur de lumière avec les paramètres demandés
   * @param pinGB1 la broche sur laquelle est branchée GB1
   * @param pinGB2 la broche sur laquelle est branchée GB2
   * @param pinIOUT la broche sur laquelle est branchée la sortie du capteur
   * @param resistor la valeur de resistance connectée sur la sortie
   */
  NOA1212(int pinGB1, int pinGB2, int pinIOUT, unsigned long resistor);
  ~NOA1212();
  /**
   * Enumération pour les différents modes de gain
   */
  enum class PowerMode {
    HighGain,
    MediumGain,
    LowGain,
    Off
  };
  /**
   * Mets en sommeil le capteur de lumière
   */
  void setPowerDown();
  /**
   * Allume le capteur dans le mode de gain désiré.
   * Le capteur prend 300us au maximum pour s'allumer.
   * @param mode Le gain dans lequel le capteur doit s'allumer
   */
  void setPowerUp(PowerMode mode);
  /**
   * Renvoie la mesure du capteur
   * @return La mesure en lux du capteur de lumière
   */
  unsigned int read();

private:
  PowerMode _currentMode;
  int _pinGB1;
  int _pinGB2;
  int _pinIOUT;
  unsigned long _resistor;
};

#endif
