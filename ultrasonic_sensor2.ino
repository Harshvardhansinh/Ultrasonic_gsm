// Created by The Electronic Guy
// www.youtube.com/theelectronicguy

 #include <LiquidCrystal.h> //LCD library
 #include <SoftwareSerial.h>
 
  #define echo 6
  #define trig 7
  int threshold=10;
  float  duration; // time taken by the pulse to return back
  float  distance; // oneway distance travelled by the pulse
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//lcd(RS,EN,D4,D5,D6,D7) 
  SoftwareSerial mySerial(9, 10);

  void setup() {
    pinMode(8,OUTPUT);
    pinMode(trig, OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(echo, INPUT);
    mySerial.begin(9600);   // Setting the baud rate of GSM Module  
    Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
    lcd.begin(16,2);
    delay(100);
  }
  
 // void loop() {
  
   // time_Measurement();
    //distance = duration * (0.0343) / 2;// calculate the oneway distance travelled by the pulse   
    //display_distance(); 
    
  //}
  
  void loop()
  {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = 0.017*duration;
  
  if (distance<threshold)
  {
      SendMessage();
    //digitalWrite(10,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(13,HIGH);
      Serial.println("Distance in Cm: ");
      Serial.println(distance);
      Serial.println();
    lcd.setCursor(0,0);
    lcd.print("Distance in Cm: ");
    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.setCursor(5,1);
    lcd.print("Object Near");
      delay(1000);
    }
    else
    {
      //digitalWrite(10,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(13,LOW);
      lcd.setCursor(0,0);
      lcd.print("All Clear");
      delay(100);
    }
    lcd.clear();
 }
 
 void SendMessage()
 {
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(100);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919959928595\"\r"); // Replace x with mobile number
  delay(100);
  mySerial.println("Object detected!!");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}
