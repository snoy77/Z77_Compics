#include <OLED_I2C.h>
#include <Adafruit_NeoPixel.h>

//Подключаю графику к экранчику
OLED myOLED(A4, A5, A4); //какие пины используются для передачи данных
//extern uint8_t RusFont[]; //Русский шрифт
extern uint8_t SmallFont[]; //Латинский шрифт

//Подключаю лампочки
#define NUM_LEDS 8
Adafruit_NeoPixel pix = Adafruit_NeoPixel(NUM_LEDS, 6, NEO_GRB + NEO_KHZ800);

String readMes;
uint8_t strCount = -1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pix.begin();
  myOLED.begin();//Типа инициализация экранчика
  myOLED.setFont(SmallFont);//Инициализация английского шрифта
}
//check special comand
//-- проверяет полученное сообщение на специальную команду. Если специальная команда - выполняет и возвращает true
void setAllLed(byte value){
  for(int i = 0; i < NUM_LEDS; i++){
    pix.setPixelColor(i, pix.Color(value, value, value));
  }
  pix.show();
}
bool chspcmd(String mes){
  if(mes.substring(0,2) == "q1"){
    
    setAllLed(mes.substring(3).toInt());
  }
  else if(mes == "q2"){
    setAllLed(0);
  }
  else{
    return false;
  }
  return true;
}
void loop() {
  Serial.println("anime");//Сообщает о себе на порт для обнаружения.
  if(Serial.available() > 0){
    readMes = Serial.readString();
    if(chspcmd(readMes) == false){

      strCount++;
      if(strCount > 4){
        myOLED.clrScr();
        strCount = 0;
      }
      myOLED.print(readMes, CENTER, strCount*12);
      myOLED.update();
    }
  }
  delay(300);
}
