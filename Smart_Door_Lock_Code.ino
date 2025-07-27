//RFID and Password based door lock system code Written by Prajwal Navalagi
#include <Wire.h>
#include<SPI.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>


#define SS_PIN 53
#define RST_PIN 49

MFRC522 mfrc522(SS_PIN, RST_PIN);

#define Relay A0
#define Red 2
#define Green 3
#define Blue 4
#define Buzzer 5
#define Button 6
int count = 0;
int z;
int count1 = 0;
int z1;
int buttonstate = 0;


byte Lock[8] = {
  0b01110,
  0b10001,
  0b10001,
  0b11111,
  0b11011,
  0b11011,
  0b11111,
  0b00000
};
byte unLock[8] = {
  0b01110,
  0b00001,
  0b00001,
  0b11111,
  0b11011,
  0b11011,
  0b11111,
  0b00000
};
byte load1[8] = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b11111
};



LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte numRows = 4;
const byte numCols = 4;

char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

char keypressed;
char code[] = {'1', '2', '3', '4', '5', '6'};
char personal_code[] = {'8', '8', '8', '8', '8', '8'};

char check1[sizeof(code)];
char check2[sizeof(code)];

short a = 0, i = 0, s = 0, j = 0;

byte rowPins[numRows] = {22, 23, 24, 25};
byte colPins[numCols] = {26, 27, 28, 29};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
//---------------------------------------------------------- Void setup()------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16, 2);

  lcd.createChar(0, Lock);
  lcd.createChar(1, unLock);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Booting:)");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">Scan RFID Card/");
  lcd.setCursor(0 , 1);
  lcd.print("Enter Password");
  lcd.setCursor(15, 1);
  lcd.write(byte(0));




  pinMode(Relay, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Button, INPUT);


  for (i = 0 ; i < sizeof(code); i++)
  {
    EEPROM.get(i, code[i]);
  }


}
//-----------------------------------------------------------Void loop()-----------------------------------------------------------------------------

void loop()
{
  keypressed = myKeypad.getKey();

  if (digitalRead(Button) == HIGH)
  {
    digitalWrite(Relay, HIGH);
    delay(7000);
    digitalWrite(Relay, LOW);

  }
  else if (keypressed == 'A')
  {
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Password");
    ReadCode();
    if (a == sizeof(code)|| a == sizeof(personal_code))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      digitalWrite(Green, HIGH);
      lcd.print("Access Granted");
      lcd.setCursor(0, 1);
      lcd.print("Door Opened");
      lcd.setCursor(13, 1);
      lcd.write(byte(1));
      digitalWrite(Relay, HIGH);
      tone(Buzzer, 1000);
      delay(100);
      noTone(Buzzer);
      delay(50);
      tone(Buzzer, 1000);
      delay(100);
      noTone(Buzzer);
      delay(4000);
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Locking....");
      lcd.setCursor(5, 1);
      lcd.print("Get In");
      delay(2000);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Door Locked");
      digitalWrite(Green, LOW);
      digitalWrite(Relay, LOW);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">Scan RFID Card/");
      lcd.setCursor(0 , 1);
      lcd.print("Enter Password");
      lcd.setCursor(15, 1);
      lcd.write(byte(0));
      count = 0;

    }
    else
    {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Wrong Password");
      lcd.setCursor(3, 1);
      lcd.print("Try Again");
      digitalWrite(Red, HIGH);
      tone(Buzzer, 1500);
      delay(500);
      digitalWrite(Red, LOW);
      noTone(Buzzer);
      delay(100);
      digitalWrite(Red, HIGH);
      tone(Buzzer, 1500);
      delay(500);
      digitalWrite(Red, LOW);
      noTone(Buzzer);
      delay(100);
      digitalWrite(Red, HIGH);
      tone(Buzzer, 1500);
      delay(500);
      digitalWrite(Red, LOW);
      noTone(Buzzer);
      digitalWrite(Relay, LOW);
      delay(1000);
      count++;
      z = count;
      if (z == 3)
      {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("System Locked");
        digitalWrite(Red, HIGH);
        tone(Buzzer, 1500);
        delay(2000);
        digitalWrite(Red, LOW);
        noTone(Buzzer);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wait & try after");
        lcd.setCursor(5, 1);
        lcd.print("1 Minute");
        delay(60000);
        count = 0;
        z = 0;
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">Scan RFID Card/");
      lcd.setCursor(0 , 1);
      lcd.print("Enter Password");
      lcd.setCursor(15, 1);
      lcd.write(byte(0));
    }
  }

  else if (keypressed == 'C')
  {
    digitalWrite(Blue, HIGH);
    ChangeCode();
    digitalWrite(Blue, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Scan RFID Card/");
    lcd.setCursor(0 , 1);
    lcd.print("Enter Password");
    lcd.setCursor(15, 1);
    lcd.write(byte(0));
  }

  

  else
  {
    if ( ! mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }

    if ( ! mfrc522.PICC_ReadCardSerial())
    {
      return;
    }

    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Scan RFID Tag");

    if (content.substring(1) == "6A 8C 57 02")// Enter your RFID Code
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      digitalWrite(Green, HIGH);
      lcd.print("Access Granted");
      lcd.setCursor(0, 1);
      lcd.print("Door Opened");
      lcd.setCursor(13, 1);
      lcd.write(byte(1));
      digitalWrite(Relay, HIGH);
      tone(Buzzer, 1000);
      delay(100);
      noTone(Buzzer);
      delay(50);
      tone(Buzzer, 1000);
      delay(100);
      noTone(Buzzer);
      delay(4000);
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Locking....");
      lcd.setCursor(5, 1);
      lcd.print("Get In");
      delay(2000);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Door Locked");
      digitalWrite(Green, LOW);
      digitalWrite(Relay, LOW);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">Scan RFID Card/");
      lcd.setCursor(0 , 1);
      lcd.print("Enter Password");
      lcd.setCursor(15, 1);
      lcd.write(byte(0));
      count1 = 0;
    }
    else if (content.substring(1) == "04 70 27 D2 BB 5F 80")// Enter your RFID Code
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      digitalWrite(Green, HIGH);
      lcd.print("Access Granted");
      lcd.setCursor(0, 1);
      lcd.print("Door Opened");
      lcd.setCursor(13, 1);
      lcd.write(byte(1));
      digitalWrite(Relay, HIGH);
      tone(Buzzer, 1000);
      delay(100);
      noTone(Buzzer);
      delay(50);
      tone(Buzzer, 1000);
      delay(100);
      noTone(Buzzer);
      delay(4000);
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Locking....");
      lcd.setCursor(5, 1);
      lcd.print("Get In");
      delay(2000);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Door Locked");
      digitalWrite(Green, LOW);
      digitalWrite(Relay, LOW);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">Scan RFID Card/");
      lcd.setCursor(0 , 1);
      lcd.print("Enter Password");
      lcd.setCursor(15, 1);
      lcd.write(byte(0));
      count1 = 0;

    }
    else
    {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Tag Mismatched");
      lcd.setCursor(3, 1);
      lcd.print("Try Again");
      digitalWrite(Red, HIGH);
      tone(Buzzer, 1500);
      delay(500);
      digitalWrite(Red, LOW);
      noTone(Buzzer);
      delay(100);
      digitalWrite(Red, HIGH);
      tone(Buzzer, 1500);
      delay(500);
      digitalWrite(Red, LOW);
      noTone(Buzzer);
      delay(100);
      digitalWrite(Red, HIGH);
      tone(Buzzer, 1500);
      delay(500);
      digitalWrite(Red, LOW);
      noTone(Buzzer);
      digitalWrite(Relay, LOW);
      delay(1000);
      count1++;
      z1 = count1;
      if (z1 == 5)
      {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("System Locked");
        digitalWrite(Red, HIGH);
        tone(Buzzer, 1500);
        delay(2000);
        digitalWrite(Red, LOW);
        noTone(Buzzer);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wait & try after");
        lcd.setCursor(5, 1);
        lcd.print("1 Minute");
        delay(60000);
        count1 = 0;
        z1 = 0;
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">Scan RFID Card/");
      lcd.setCursor(0 , 1);
      lcd.print("Enter Password");
      lcd.setCursor(15, 1);
      lcd.write(byte(0));
    }
  }
}

void ReadCode()
{
  i = 0;
  a = 0;
  j = 0;

  while (keypressed != '#') {
    keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY && keypressed != '#' )
    {
      tone(Buzzer, 1000);
      delay(100);
      noTone(Buzzer);
      lcd.setCursor(j + 5, 1);
      lcd.print("*");
      j++;
      if (keypressed == code[i] || i < sizeof(code) && keypressed == personal_code[i] ) {
        a++;
        i++;
      }
      else
        a--;
    }
  }
  keypressed = NO_KEY;

}


void ChangeCode()
{
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Changing");
  lcd.setCursor(2, 1);
  lcd.print("Password...");
  delay(2000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Old Password");
  ReadCode();

  if (a == sizeof(code))
  {
    lcd.clear();
    //lcd.print("Changing code");
    GetNewCode1();
    GetNewCode2();
    s = 0;
    for (i = 0 ; i < sizeof(code) ; i++)
    {
      if (check1[i] == check2[i])
        s++;
    }
    if (s == sizeof(code)) {

      for (i = 0 ; i < sizeof(code) ; i++)
      {
        code[i] = check2[i];
        EEPROM.put(i, code[i]);

      }
      lcd.clear();
      lcd.print("Password Changed");
      delay(2000);
    }
    else {
      lcd.clear();
      lcd.print("Password not");
      lcd.setCursor(4, 1);
      lcd.print("matching !!");
      delay(2000);

    }

  }

  else {
    lcd.clear();
    lcd.print("Wrong Password");
    delay(2000);
  }
}

void GetNewCode1()
{
  i = 0;
  j = 0;

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("New password");
  lcd.setCursor(4, 1);
  lcd.print("& press C");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("& press C");

  while (keypressed != 'C') {
    keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY && keypressed != 'C' )
    {
      tone(Buzzer, 1000);
      delay(100);
      noTone(Buzzer);
      lcd.setCursor(j + 4, 0);
      lcd.print("*");
      check1[i] = keypressed;
      i++;
      j++;

    }
  }
  keypressed = NO_KEY;
}

void GetNewCode2()
{
  i = 0;
  j = 0;


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Confirm password");
  lcd.setCursor(4, 1);
  lcd.print("& press C");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("& press C");

  while (keypressed != 'C') {
    keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY && keypressed != 'C' )
    {
      tone(Buzzer, 1000);
      delay(100);
      noTone(Buzzer);
      lcd.setCursor(j + 4, 0);
      lcd.print("*");
      check2[i] = keypressed;
      i++;
      j++;

    }
  }
  keypressed = NO_KEY;
}

