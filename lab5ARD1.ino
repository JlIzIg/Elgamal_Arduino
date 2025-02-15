#include <BigNumber.h>
#include "DFRobot_RGBLCD1602.h"


/*Transmiter*/

const int buttonPin1 = 2;


DFRobot_RGBLCD1602 lcd(/*RGBAddr*/ 0x60, /*lcdCols*/ 16, /*lcdRows*/ 2);  //16 characters and 2 lines of show

const int cR = 255;
const int cG = 0;
const int cB = 0;
/*
BigNumber p = 103;
BigNumber g = 5;*/
/*

BigNumber p = 71;
BigNumber g = 2;*/


BigNumber p = 37;
BigNumber g = 2;



BigNumber x;
BigNumber y;
BigNumber k;
BigNumber a;
BigNumber b;
BigNumber message;


BigNumber modPow(BigNumber base1, BigNumber exponent, BigNumber modulus) {
  BigNumber result;
  result = base1.pow(exponent);
  BigNumber result2;
  result2 = BigNumber(result) / BigNumber(modulus);
  BigNumber result3;
  result3 = result - (result2 * modulus);
  return result3;
}

BigNumber encrypt(BigNumber b, BigNumber a, BigNumber p, BigNumber x) {
  BigNumber power = BigNumber(p - BigNumber(1) - x);

  BigNumber res1 = a.pow(power);

  BigNumber base = res1 * BigNumber(b);

  BigNumber result2;
  result2 = BigNumber(base) / BigNumber(p);
  BigNumber result3;
  result3 = base - (result2 * p);

  return result3;
}
void setup() {

  Serial.begin(9600);
  Serial.setTimeout(50);
  lcd.init();
  lcd.setRGB(cR, cG, cB);
  BigNumber::begin();
  randomSeed(analogRead(0));
}
void loop() {


  int code;

  while (!Serial.available())
    ;
  {
    code = Serial.parseInt();
    Serial.end();
    if (code == 1) {

      x = random(1, p);

      y = modPow(g, x, p);

      k = random(1, (p - BigNumber(1)));

      Serial.begin(9600);


      Serial.println(y);

      Serial.println(k);

      lcd.setCursor(0, 0);
      lcd.println("M=" + String(k) + "x=" + String(x));
      while (!Serial.available())
        ;

      {
        a = Serial.parseInt();

        b = Serial.parseInt();
      }

      Serial.end();

      message = encrypt(b, a, p, x);

      lcd.setCursor(0, 1);
      lcd.println("M=" + String(message));

      delay(500);
      if (message == k) {
        
        Serial.begin(9600);
      } 
    }
  }
}