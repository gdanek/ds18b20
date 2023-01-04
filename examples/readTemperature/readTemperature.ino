// gdanek 2022
// Библиотека для работы с датчиком ds18b20
//GitHub: https://github.com/gdanek
// version 1.0
#include <arduino_ds18b20.h>  // подключение библиотеки
danekDS18B20 ds(8); // датчик подключен к 8 пину
void setup()
{
  Serial.begin(115200); // для atmega подключим Serial
}
void loop()
{  
  float temperature = ds.getTemperature();  // читаем температуру
  Serial.println(temperature); // печатаем 5 раз в секунду
  delay(200);
}