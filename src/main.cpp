#include "variables.h"
#include "defines.h"

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

/*Определение NTP-клиента для получения времени*/
WiFiUDP ntpUDP;
/*Второй аргумент - российский сервер поддерживаемый MSK-IX*/
/*Третий аргумент -  смещение по часовому поясу(3600*3 или +3) чтобы получить время именно по МСК*/
/*Четвертый аргумент - интервал обновления запроса в миллисекундах*/
NTPClient timeClient(ntpUDP,"ntp.msk-ix.ru",10800,60000);

void setup() {
  /*Работаем через Serial, стандартная последовательность процедур*/
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  /*Запускаем NTP-клиент*/
  timeClient.begin();
}

void loop(){
  /*Запрос текущего времени у NTP-сервера*/
  timeClient.update();
  /*Выводим в Serial*/
  Serial.println(timeClient.getFormattedTime());
  /**/
  delay(1000);
}
