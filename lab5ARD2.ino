#include <BigNumber.h>
#include "DFRobot_RGBLCD1602.h"
#include <VirtualWire.h>

const int buttonPin = 2;
int flag = 0;


DFRobot_RGBLCD1602 lcd(/*RGBAddr*/ 0x60, /*lcdCols*/ 16, /*lcdRows*/ 2);  //16 characters and 2 lines of show
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

/*
BigNumber p = 103;
BigNumber g = 5;*/
/*

BigNumber p = 71;
BigNumber g = 2;*/


BigNumber p = 37;
BigNumber g = 2;



BigNumber y;
BigNumber a;
BigNumber b;

BigNumber k;

BigNumber K;


BigNumber modPow(BigNumber base1, BigNumber exponent, BigNumber modulus) {
  BigNumber result;
  result = base1.pow(exponent);
  BigNumber result2;
  result2 = BigNumber(result) / BigNumber(modulus);
  BigNumber result3;
  result3 = result - (result2 * modulus);
  return result3;
}


BigNumber modPowMultiplication(BigNumber base1, BigNumber exponent, BigNumber mult, BigNumber modulus) {
  BigNumber result;
  result = base1.pow(exponent);
  result = BigNumber(result)*BigNumber(mult);
  BigNumber result2;
  result2 = BigNumber(result) / BigNumber(modulus);
  BigNumber result3;
  result3 = result - (result2 * modulus);
  return result3;
}

BigNumber strToBigNum(String stringValue){

    BigNumber bigNumber;
    for (int i = 0; i < stringValue.length(); ++i) {
        int digit = stringValue.charAt(i) - '0';
        bigNumber = bigNumber * BigNumber(10) + BigNumber(digit);
    }
    return bigNumber;
}


void setup() {

  
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(buttonPin, INPUT_PULLUP);
  BigNumber::begin();
  lcd.init();
  lcd.setRGB(colorR, colorG, colorB);



}


void loop() {
  if (digitalRead(buttonPin) == HIGH && flag == 0) {
    flag = 1;
  }
  if (digitalRead(buttonPin) == LOW && flag == 1) {
    flag = 0;

    Serial.println(1);


    while (!Serial.available());
    {
      y = Serial.parseInt();
      
      k = Serial.parseInt();
    }
      Serial.end();
      K = random(1, (p - BigNumber(1)));
      a=modPow(g, K, p);
      b=modPowMultiplication(y, K, k, p);
      Serial.begin(9600);
      Serial.println(a);
      Serial.println(b);
  }
}