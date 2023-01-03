// gdanek 2022
// Библиотека для работы с датчиком ds18b20
//GitHub: https://github.com/gdanek
// version 1.0
#ifndef ds18b20_h
#define ds18b20_h
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

// Всего одна структура. Больше не надо
class danekDS18B20
{
 
  uint8_t pin;  // номер пина, к которому подключен датчик температуры
  inline void _ddr(uint8_t dir);
  bool rst();    // Сброс линии OneWire
  bool getBit();     // Читать бит, отправленный датчиком
  uint8_t getByte(); // Считать байт. Чтение бита 8 раз со сдвигом вправо(т.к. младший вперёд)
  void sendBit(bool transmittedBit); // Отправить бит 
  void sendByte(uint8_t transmittedByte); // Отправить байт
  public: // Публичные методы. Конструктор и функция получения температуры
  danekDS18B20(uint8_t pin){this->pin = pin;} // Указываем пин, на котором висит датчик
  float getTemperature();
};// Всё !
#endif 
// danek 2022
