// gdanek 2022
// Библиотека для работы с датчиком ds18b20
//GitHub: https://github.com/gdanek
// version 1.0
#include "ds18b20.h"
inline void danekDS18B20::_ddr(uint8_t dir)
{if(dir)DDRB |= (1<<pin);else  DDRB &= ~(1<<pin);_delay_us(2); }  // Необходимо для правильного изменения состояния пина. Иначе не работает.
bool danekDS18B20::rst(void)
{
	_ddr(1); 
  _delay_us(250);
  PORTB &= ~(1 << pin);  
  _delay_us(500);
  PORTB |= (1 << pin);
  _ddr(0); 
  _delay_us(70);
  while(PINB & (1 << pin)){;} // Ждём пока датчик проснётся
  _delay_us(400);
    
}
bool danekDS18B20::getBit(void)
{
	bool bt;
  _ddr(1); 
  PORTB &= ~(1 << pin);
  _delay_us(2);
  PORTB |= (1 << pin);
  _delay_us(5);               //менять если не работает
  _ddr(0); 
  bt = PINB & (1 << pin); // Прочитали состояние пина
  _delay_us(70);
  return bt; // Вернули бит
}
uint8_t danekDS18B20::getByte(void)
{
 	uint8_t r = 0;
  for (uint8_t bitnum = 8; bitnum; bitnum--) // Можно и от 0 до 8
  {
    r >>= 1; // Двигаем бит на один вправо
    if (getBit())r |= 0x80;  // Если считана единица - ставим старший бит
  }
    return r; // Вернуть байт
}
void  danekDS18B20::sendBit(bool transmittedBit)
{
 	_ddr(1); 
  PORTB &= ~(1 << pin);
  if (transmittedBit) // Если единицу отправляем
  {
    _delay_us(10);
    PORTB |= (1 << pin);
    _delay_us(80); 
  } 
  else // Если ноль отправляем
  {
    _delay_us(80); 
    PORTB |= (1 << pin);
    _delay_us(10); // Микросекунды подбираются вручную тут.
  }
}
void danekDS18B20::sendByte(uint8_t transmittedByte) 
{
 	for (uint8_t bitnum = 8; bitnum; bitnum--) 
  {
    sendBit(transmittedByte & 1); // Отправляем побитово(последний бит сначала)
    transmittedByte >>= 1;// Сдвигаем вправо на 1
  }
}
float danekDS18B20::getTemperature(void)
{
  int dat[8]; // Читаем 8 байт памяти датчика. Можно меньше - всё равно не нужны последние
  rst();
  sendByte(0xCC); // На линии 1 датчик, адресацию игнорировать
  sendByte(0x44); // Читай температуру - скоро спросим( точность 0.0625)
  rst(); // Перезагрузка линии перед запросом температуры
  sendByte(0xCC); // На линии 1 датчик, адресацию игнорировать
  sendByte(0xBE); // Спрашиваем температуру
  for(uint8_t j = 0;j < 8;j++){dat[j] = getByte();} // Интересны только 2 первых байта
  int raw = ((dat[1] << 8) | dat[0]); // Первый бит за знак отвечает - поэтому int
  float temperature = (float)raw* 0.0625; // Переводим в температуру
  return temperature; // Отправляем температуру
  }
// danek 2022