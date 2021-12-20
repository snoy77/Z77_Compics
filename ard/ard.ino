#include <OLED_I2C.h>

OLED myOLED(A4, A5, A4); //какие пины используются для передачи данных
extern uint8_t RusFont[]; //Русский шрифт
extern uint8_t SmallFont[]; //Латинский шрифт
String sendMes = "ard";
String ViewMassage = "";
uint8_t strCount = -1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  myOLED.begin();//Типа инициализация экранчика
  myOLED.setFont(SmallFont);//Инициализация русского шрифта
}
void loop() {
  
  Serial.println(sendMes);//Сообщает о себе на порт для обнаружения.
  if(Serial.available() > 0){
    strCount++;
    if(strCount > 4){
      myOLED.clrScr();
      strCount = 0;
    }
    ViewMassage = Serial.readString();
    myOLED.print(ViewMassage, CENTER, strCount*12);
    myOLED.update();
    
  }
  delay(300);
}
