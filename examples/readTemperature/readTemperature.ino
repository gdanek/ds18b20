// gdanek 2022
// Библиотека для работы с датчиком ds18b20
//GitHub: https://github.com/gdanek
// version 1.0
#include <ds18b20.h>  // подключение библиотеки
danekDS18B20 ds(PB0); // датчик подключен к PB0 (программа привязана к регистру B, порты 8-16 arduino). Поправим
int main(void)
{
  Serial.begin(115200); // для atmega подключим Serial
  while(1)
  {
  float temperature = ds.getTemperature();  // читаем температуру. На atmega первое чтение может подвисать
  Serial.println(temperature); // печатаем 20 раз в секунду
  _delay_ms(50);
  }
  return 0;
}
