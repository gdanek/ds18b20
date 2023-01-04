// gdanek 2022
// Библиотека для работы с датчиком ds18b20
//GitHub: https://github.com/gdanek
// version 1.0
#include "arduino_ds18b20.h"
bool danekDS18B20::rst(void)
{
  pinMode(pin,OUTPUT);
  delayMicroseconds(250);
  digitalWrite(pin,LOW);  
  delayMicroseconds(500);
  digitalWrite(pin,HIGH);
  pinMode(pin,INPUT);
  delayMicroseconds(70);
  while(digitalRead(pin)){;} // Ждём пока датчик проснётся
  delayMicroseconds(400);
    
}
bool danekDS18B20::getBit(void)
{
	bool bt;
  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
  delayMicroseconds(2);
  digitalWrite(pin,HIGH);
  delayMicroseconds(5);               //менять если не работает
  pinMode(pin,INPUT);
  bt = digitalRead(pin); // Прочитали состояние пина
  delayMicroseconds(70);
  return bt; // Вернули бит
}
uint8_t danekDS18B20::getByte(void)
{
 	uint8_t r = 0;
  for (uint8_t bitnum = 8; bitnum; bitnum--) // Можно и от 0 до 8
  {
    r >>= 1; // Двигаем бит на один вправо
    if (this->getBit())r |= 0x80;  // Если считана единица - ставим старший бит
  }
    return r; // Вернуть байт
}
void  danekDS18B20::sendBit(bool transmittedBit)
{
  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
  if (transmittedBit) // Если единицу отправляем
  {
    delayMicroseconds(10);
    digitalWrite(pin,HIGH);
    delayMicroseconds(80); 
  } 
  else // Если ноль отправляем
  {
    delayMicroseconds(80); 
    digitalWrite(pin,HIGH);
    delayMicroseconds(10); // Микросекунды подбираются вручную тут.
  }
}
void danekDS18B20::sendByte(uint8_t transmittedByte) 
{
 	for (uint8_t bitnum = 8; bitnum; bitnum--) 
  {
    this->sendBit(transmittedByte & 1); // Отправляем побитово(последний бит сначала)
    transmittedByte >>= 1;// Сдвигаем вправо на 1
  }
}
float danekDS18B20::getTemperature(void)
{
  int dat[8]; // Читаем 8 байт памяти датчика. Можно меньше - всё равно не нужны последние
  this->rst();
  this->sendByte(0xCC); // На линии 1 датчик, адресацию игнорировать
  this->sendByte(0x44); // Читай температуру - скоро спросим( точность 0.0625)
  this->rst(); // Перезагрузка линии перед запросом температуры
  this->sendByte(0xCC); // На линии 1 датчик, адресацию игнорировать
  this->sendByte(0xBE); // Спрашиваем температуру
  for(uint8_t j = 0;j < 8;j++){dat[j] = this->getByte();} // Интересны только 2 первых байта
  int raw = ((dat[1] << 8) | dat[0]); // Первый бит за знак отвечает - поэтому int
  float temperature = (float)raw* 0.0625; // Переводим в температуру
  return temperature; // Отправляем температуру
  }
// danek 2022